---
tags: [skill-creator]
max_turns: 20
timeout_seconds: 600
allowed_tools: [Read, Glob, Grep, Skill, Write, Edit, Bash]
---

my godot game stutters really bad on my old optiplex (i3-3220, intel hd 2500, ubuntu). there's like 200 of these crates in the level. can you review this and tell me whats wrong? save your review to a markdown file

```csharp
using Godot;
using System.Linq;

public class Crate : RigidBody3D
{
    [Export] public float FloatForce = 5f;

    public override void _Process(double delta)
    {
        var player = GetTree().Root.GetNode<Node3D>("Main/World/Player");
        var nearby = GetTree().GetNodesInGroup("crates")
            .Cast<Node3D>()
            .Where(c => c.GlobalPosition.DistanceTo(GlobalPosition) < 3f)
            .ToList();

        if (Input.IsActionPressed("lift") && GlobalPosition.DistanceTo(player.GlobalPosition) < 4f)
        {
            Position = Position + new Vector3(0, FloatForce * (float)delta, 0);
        }

        GetNode<Label3D>("Label").Text = $"Crate {Name} - {nearby.Count} nearby";
    }
}
```
