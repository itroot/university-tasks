using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using TopologyVisualization.SimpleShapes;
using System.Drawing;

namespace TopologyVisualization.Shapes
{
    class Shape
    {
        protected SimpleShape[] shapes;

        public void paint(Color c)
        {
            for (int i = 0; i < shapes.Length; i++)
                shapes[i].paint(c);
        }

        public void draw()
        {
            for (int i = 0; i < shapes.Length; i++)
                shapes[i].draw();
        }

        public void Dispose()
        {
            for (int i = 0; i < shapes.Length; i++)
                shapes[i].Dispose();
        }
    }
}
