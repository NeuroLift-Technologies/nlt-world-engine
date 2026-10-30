#!/usr/bin/env python3
"""Check Godot API names against the official class reference XML for an exact engine version.

Why: Godot's API shifts between versions and generated code often uses names that don't exist
(Godot 3 leftovers, invented helpers). This turns "I think that exists" into a checked fact.

Class reference sources (any one):
  * a local engine:      godot --headless --doctool /tmp/godot-doc   (writes doc/classes/*.xml)
  * the engine repo:     git clone --depth 1 --branch <ver>-stable --filter=blob:none --sparse \
                           https://github.com/godotengine/godot && git sparse-checkout set doc/classes modules
  * pass several --docs dirs to include module classes (modules/*/doc_classes).

Usage:
  godot_api_check.py Class Class.member ... --docs DIR [DIR2 ...]     # names first, or put `--` before them
  godot_api_check.py --docs DIR DIR2 -- Class Class.member ...
  godot_api_check.py --docs DIR --scan FILE.md|FILE.gd|FILE.cs   # check `Class.member` / `Class` mentions
  godot_api_check.py --docs DIR --show Class                       # list a class's members
C# PascalCase members are matched against snake_case names (MoveAndSlide -> move_and_slide).
"""
import argparse, os, re, sys, glob
import xml.etree.ElementTree as ET

def snake(name):
    if "_" in name or name.islower():
        return name
    s = re.sub(r"(?<=[a-z0-9])([A-Z])", r"_\1", name)
    s = re.sub(r"(?<=[A-Z])([A-Z][a-z])", r"_\1", s)
    return s.lower()

def load(dirs):
    classes = {}
    for d in dirs:
        for f in glob.glob(os.path.join(d, "**", "*.xml"), recursive=True):
            try:
                root = ET.parse(f).getroot()
            except ET.ParseError:
                continue
            if root.tag != "class":
                continue
            name = root.get("name")
            members = {}
            for tag, kind in (("methods/method", "method"), ("members/member", "property"),
                              ("signals/signal", "signal"), ("constants/constant", "constant"),
                              ("theme_items/theme_item", "theme_item"), ("annotations/annotation", "annotation")):
                for el in root.findall(tag):
                    n = el.get("name")
                    if n:
                        members[n] = (kind, el.get("deprecated") is not None or el.get("is_deprecated") == "true")
                    en = el.get("enum")
                    if kind == "constant" and en:
                        # enums are only recorded on their constants; C# exposes them as <Name>Enum
                        members.setdefault(en, ("enum", False))
                        members.setdefault(en + "Enum", ("enum", False))
            classes[name] = {"inherits": root.get("inherits"), "members": members,
                             "deprecated": root.get("deprecated") is not None,
                             "experimental": root.get("experimental") is not None}
    return classes

def lookup(classes, cls, member):
    """Search member through the inheritance chain."""
    seen, c = set(), cls
    while c and c in classes and c not in seen:
        seen.add(c)
        m = classes[c]["members"]
        for cand in (member, snake(member), member.upper(), snake(member).upper()):
            if cand in m:
                return c, cand, m[cand]
        c = classes[c]["inherits"]
    return None

def check(classes, item):
    if "." in item:
        cls, member = item.split(".", 1)
    else:
        cls, member = item, None
    if cls not in classes:
        return f"MISSING class   {item}"
    tag = ""
    if classes[cls]["deprecated"]:
        tag += " [class deprecated]"
    if classes[cls]["experimental"]:
        tag += " [experimental]"
    if member is None:
        return f"ok              {item}{tag}"
    hit = lookup(classes, cls, member)
    if not hit:
        return f"MISSING member  {item}{tag}"
    owner, name, (kind, dep) = hit
    via = f" (on {owner})" if owner != cls else ""
    return f"ok              {item} -> {kind} {name}{via}{' [deprecated]' if dep else ''}{tag}"

def scan(classes, path):
    text = open(path, encoding="utf-8").read()
    found = set(re.findall(r"\b([A-Z][A-Za-z0-9]+(?:2D|3D)?)\.([A-Za-z_][A-Za-z0-9_]+)\b", text))
    skip_ext = {"cs", "gd", "md", "tscn", "tres", "xml", "json", "cfg", "godot", "uid", "csproj", "py", "cpp", "h", "inc"}
    items = sorted({f"{c}.{m}" for c, m in found if c in classes and m.lower() not in skip_ext})
    # bare node/class names in backticks, e.g. `TileMapLayer`
    bare = set(re.findall(r"`([A-Z][A-Za-z0-9]+)`", text))
    # bare names are noisy (method names, project node names), so only check 2D/3D-suffixed ones
    items += sorted(b for b in bare if re.search(r"(2D|3D)$", b))
    return items

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--docs", action="extend", nargs="+", required=True,
                    help="one or more dirs with class XML; repeatable (e.g. --docs godot/doc/classes godot/modules)")
    ap.add_argument("--scan")
    ap.add_argument("--show")
    ap.add_argument("items", nargs="*")
    a = ap.parse_args()
    # --docs takes several dirs; anything after it that isn't a directory is a name to check.
    # (Without this, `--docs DIR Class.member` would silently check nothing and "pass".)
    stray = [d for d in a.docs if not os.path.isdir(d)]
    a.docs = [d for d in a.docs if os.path.isdir(d)]
    a.items = list(a.items) + stray
    if not a.docs:
        sys.exit("No existing --docs directory given")
    classes = load(a.docs)
    if not classes:
        sys.exit("No class XML found under --docs")
    if a.show:
        c = classes.get(a.show)
        if not c:
            sys.exit(f"MISSING class {a.show}")
        print(f"{a.show} inherits {c['inherits']}")
        for n, (k, d) in sorted(c["members"].items(), key=lambda x: (x[1][0], x[0])):
            print(f"  {k:10} {n}{' [deprecated]' if d else ''}")
        return
    items = list(a.items)
    if a.scan:
        items += scan(classes, a.scan)
    if not items:
        sys.exit("Nothing to check: pass Class / Class.member names or --scan FILE")
    bad = 0
    for it in items:
        r = check(classes, it)
        bad += r.startswith("MISSING")
        print(r)
    print(f"\n{len(items)} checked, {bad} missing ({len(classes)} classes loaded)")
    sys.exit(1 if bad else 0)

if __name__ == "__main__":
    main()
