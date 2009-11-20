using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;
using TopologyVisualization.Help;
using TopologyVisualization.SimpleShapes;

namespace TopologyVisualization.Shapes
{
    class Axis : Shape
    {
        public Axis(float[] Begin, float[] End,Vector3 Position, float radius, int slices, int stacks, Device dev)
        {
            shapes = new SimpleShape[2];
            float[] middlePoint = new float[Begin.Length];
            for (int i=0;i<Begin.Length;i++)
            {
                middlePoint[i] = 0.8f*End[i]+0.2f*Begin[i];
            }
            shapes[0] = new Cylinder(Begin, middlePoint, radius,
                radius, slices, stacks, dev);
            shapes[1] = new Cylinder(middlePoint, End, 1.6f*radius,
                0.0f, slices, stacks, dev);
            for (int i = 0; i < shapes.Length; i++)
                shapes[i].MovingMatrix *= Matrix.Translation(Position);
        }
    }
}
