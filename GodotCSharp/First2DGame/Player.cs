using Godot;
using System;

public class Player : Area2D
{
    [Export]
    public int Speed = 400;

    [Signal]
    public delegate void Hit();

    public void OnPlayerBodyEntered(PhysicsBody2D body)
    {
        Hide(); // Player disappears after being hit.
        EmitSignal("Hit");
        GetNode<CollisionShape2D>("CollisionShape2D").SetDeferred("disabled", true);
    }

    private Vector2 _screenSize;

    // Called when the node enters the scene tree for the first time.
    public override void _Ready()
    {
        _screenSize = GetViewport().Size;
    }

    //  // Called every frame. 'delta' is the elapsed time since the previous frame.
    public override void _Process(float delta)
    {
        var velocity = new Vector2(); // The player's movement vector.
        velocity = CheckInput(velocity);
        var animatedSprite = GetNode<AnimatedSprite>("AnimatedSprite");
        velocity = SetVelocityAndDisplay(velocity, animatedSprite);
        Position += velocity * delta;
        Position = new Vector2
            (
                x: Mathf.Clamp(Position.x, 0, _screenSize.x),
                y: Mathf.Clamp(Position.y, 0, _screenSize.y)
            );
        FlipSprite(velocity, animatedSprite);

    }

    private static void FlipSprite(Vector2 velocity, AnimatedSprite animatedSprite)
    {
        if (velocity.x != 0)
        {
            animatedSprite.Animation = "walk";
            animatedSprite.FlipV = false;
            // See the note below about boolean assignment
            animatedSprite.FlipH = velocity.x < 0;
        }
        else if (velocity.y != 0)
        {
            animatedSprite.Animation = "up";
            animatedSprite.FlipV = velocity.y > 0;
        }
    }

    private Vector2 SetVelocityAndDisplay(Vector2 velocity, AnimatedSprite animatedSprite)
    {
        if (velocity.Length() > 0)
        {
            velocity = velocity.Normalized() * Speed;
            animatedSprite.Play();
        }
        else
        {
            animatedSprite.Stop();
        }

        return velocity;
    }

    private static Vector2 CheckInput(Vector2 velocity)
    {
        if (Input.IsActionPressed("ui_right"))
        {
            velocity.x += 1;
        }

        if (Input.IsActionPressed("ui_left"))
        {
            velocity.x -= 1;
        }

        if (Input.IsActionPressed("ui_down"))
        {
            velocity.y += 1;
        }

        if (Input.IsActionPressed("ui_up"))
        {
            velocity.y -= 1;
        }

        return velocity;
    }
}
