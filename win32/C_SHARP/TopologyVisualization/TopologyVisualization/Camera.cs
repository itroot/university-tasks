using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;
using TopologyVisualization.Help;

namespace TopologyVisualization
{
    class Camera
        {
            private static Vector3 position;
            private static Vector3 lookat;
            private static Vector3 vertical;

            public static Vector3 Position
            {
                get
                {
                    return position;
                }
                set
                {
                    position = value;
                    MainForm.device.Transform.View = Matrix.LookAtLH(position, lookat, vertical);
                }
            }

            public static Vector3 Target
            {
                get
                {
                    return lookat;
                }
                set
                {
                    lookat = value;
                    MainForm.device.Transform.View = Matrix.LookAtLH(position, lookat, vertical);
                }
            }

            public static Vector3 Vertical
            {
                get
                {
                    return vertical;
                }
                set
                {
                    vertical = value;
                    MainForm.device.Transform.View = Matrix.LookAtLH(position, lookat, vertical);
                }
            }

            public static void Initialize(Vector3 Position, Vector3 Target, Vector3 Vertical)
            {
                position = Position;
                lookat = Target;
                vertical = Vertical;
                MainForm.device.Transform.View = Matrix.LookAtLH(position, lookat, vertical);
            }

            public static void Forward(float distance)
            {
                Vector3 sdvig = lookat - position;
                sdvig.Normalize();
                position += sdvig * distance;
                lookat += sdvig * distance;
                Initialize(position, lookat, vertical);
            }

            public static void Backward(float distance)
            {
                Vector3 sdvig = lookat - position;
                sdvig.Normalize();
                position -= sdvig * distance;
                lookat -= sdvig * distance;
                Initialize(position, lookat, vertical);
            }

            public static void MoveRight(float distanse)
            {
                Vector3 tmp = position - lookat;
                Vector2 dir = new Vector2(tmp.X, tmp.Z);
                dir.Normalize();
                dir = new Vector2(-dir.Y, dir.X);

                position.X += dir.X * distanse;
                position.Z += dir.Y * distanse;
                lookat.X += dir.X * distanse;
                lookat.Z += dir.Y * distanse;
                Initialize(position, lookat, vertical);
            }

            public static void MoveLeft(float distanse)
            {
                Vector3 tmp = position - lookat;
                Vector2 dir = new Vector2(tmp.X, tmp.Z);
                dir.Normalize();
                dir = new Vector2(dir.Y, -dir.X);

                position.X += dir.X * distanse;
                position.Z += dir.Y * distanse;
                lookat.X += dir.X * distanse;
                lookat.Z += dir.Y * distanse;
                Initialize(position, lookat, vertical);
            }

            public static void RotateHorizontal(float angle)
            {
                Vector3 direction = lookat - position;
                direction.TransformCoordinate(Matrix.RotationY(angle));
                lookat = direction + position;
                Initialize(position, lookat, vertical);
            }

            public static void RotateVertical(float angle)
            {
                Vector3 direction = lookat - position;
                Vector3 normal = VectorActions.vectmul(vertical, direction);
                direction.TransformCoordinate(Matrix.RotationAxis(normal, -angle));
                lookat = direction + position;
                Initialize(position, lookat, vertical);
            }
        }
}
