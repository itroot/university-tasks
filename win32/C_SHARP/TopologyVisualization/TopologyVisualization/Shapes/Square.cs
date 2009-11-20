using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using TopologyVisualization.SimpleShapes;
using Microsoft.DirectX.Direct3D;
using System.Drawing;

namespace TopologyVisualization.Shapes
{
    public class Square
    {
        private Triangle[] triangles;

        public Square(float[][] Points, float[] normal, Device dev)
        {
            triangles = new Triangle[2];
            triangles[0] = new Triangle(Points[0], Points[1], Points[2], normal, dev);
            triangles[1] = new Triangle(Points[2], Points[3], Points[0], normal, dev);
        }

        public Square(float[][] Points, Device dev)
        {
            triangles = new Triangle[2];
            triangles[0] = new Triangle(Points[0], Points[1], Points[2], dev);
            triangles[1] = new Triangle(Points[2], Points[3], Points[0], dev);
        }

        public void paint(Color c)
        {
            for (int i = 0; i < triangles.Length; i++)
                triangles[i].paint(c);
        }

        public void draw()
        {
            for (int i = 0; i < triangles.Length; i++)
                triangles[i].draw();
        }
    }
}
