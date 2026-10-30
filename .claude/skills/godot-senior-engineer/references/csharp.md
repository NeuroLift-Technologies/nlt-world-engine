# C# in Godot 4 — senior-level notes

Godot 4 C# runs on modern .NET (the `Godot.NET.Sdk` in the `.csproj` pins the version). Source generators wire up exports, signals and methods, which is why the rules below matter.

## Non-negotiables
- Every class deriving from a Godot type must be `partial`. Without it the source generators can't attach, and exports/signals silently fail or the build errors.
- File name must match the class name for the script to attach to a node.
- Build before running in the editor (the editor's Build button or `dotnet build`); stale assemblies are a top cause of "my change did nothing."

```csharp
using Godot;

public partial class Enemy : CharacterBody3D
{
    [Signal] public delegate void DiedEventHandler(Enemy enemy);

    [Export] public int MaxHealth { get; set; } = 100;
    [Export(PropertyHint.Range, "0,20,0.1")] public float Speed { get; set; } = 5f;
    [Export] public EnemyStats Stats { get; set; }

    private NavigationAgent3D _nav;
    private static readonly StringName JumpAction = "jump"; // avoid per-frame string→StringName conversion

    public override void _Ready()
    {
        _nav = GetNode<NavigationAgent3D>("%NavAgent");
        Stats = (EnemyStats)Stats.Duplicate();
    }

    public override void _PhysicsProcess(double delta)
    {
        var v = Velocity;
        if (!IsOnFloor()) v += GetGravity() * (float)delta;
        Velocity = v;           // Velocity is a struct property: copy, modify, assign back
        MoveAndSlide();
    }

    private void Die() => EmitSignal(SignalName.Died, this);
}
```

## Signals
- Declare with `[Signal] public delegate void XEventHandler(...)`; the generator creates the `X` event and `SignalName.X`.
- Connect with C# events: `enemy.Died += OnEnemyDied;` — and unsubscribe (`-=`) in `_ExitTree` when the subscriber can outlive the emitter, or you leak / call into freed objects. Godot can clean up connections whose target is a Godot object when it's freed, but lambdas and non-Godot targets are a common leak and "disposed object" error source — be explicit and unsubscribe.
- Signal parameters must be Variant-compatible types (Godot objects, primitives, Godot structs, Godot collections).

## Interop and GC costs (the real C# performance story)
- Every call into the engine crosses the managed/native boundary. Cache `GetNode` results; don't call engine APIs in tight inner loops when a local C# computation will do.
- `Godot.Collections.Array`/`Dictionary` are engine-side and marshal on every access; use `System.Collections.Generic` types for internal logic and convert only at the boundary.
- Avoid per-frame allocations in `_Process`/`_PhysicsProcess` (LINQ, closures, string formatting, `new` arrays). GC pauses show up as frame spikes on low-end CPUs.
- Structs like `Vector3`, `Transform3D` are C# value types — mutate a local copy and assign back (see `Velocity` above).
- String → `StringName`/`NodePath` conversions allocate; cache them as `static readonly`.

## Mixing with GDScript
- C# can call GDScript via `node.Call("method_name", args)`, `Get("prop")`, `Set("prop", value)` — untyped and slower; fine at boundaries, not in hot paths.
- GDScript can call public C# methods/properties on the node directly.
- Prefer one language per system. A mixed project is fine; a mixed *system* is a maintenance tax.

## Platform caveats
- C# web export has historically been unsupported in Godot 4; mobile C# export exists but has caveats. Check the current version's docs before promising a C# target platform.
- Hot-reload of C# while the game runs is limited; expect to restart.

## Testing
`dotnet test` with a regular test project works for pure-logic classes. For node/scene tests, gdUnit4 has C# support. Keep game logic in plain C# classes where possible so it's testable without the engine.
