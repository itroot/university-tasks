using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.DirectX;

namespace TopologyVisualization.Help
{
    class VectorActions
    {
        public static float scalmul(Vector3 v1, Vector3 v2)
        {
            return (v1.X * v2.X + v1.Y * v2.Y + v1.Z * v2.Z);
        }

        public static Vector3 vectmul(Vector3 v1, Vector3 v2)
        {
            float X = v1.Y * v2.Z - v1.Z * v2.Y;
            float Y = v1.X * v2.Z - v1.Z * v2.X;
            float Z = v1.X * v2.Y - v1.Y * v2.X;
            return new Vector3(X, -Y, Z);
        }
    }
}
