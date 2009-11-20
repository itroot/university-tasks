using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.DirectX;
using System.Drawing;
using Microsoft.DirectX.Direct3D;

namespace TopologyVisualization.Shapes
{
    class Axises
    {
        private Axis[] axises;
        private Device device;
        private Matrix matr;

        public Axises(Vector3 Position,Device dev)
        {
            matr = Matrix.Translation(Position);
            device = dev;
            axises = new Axis[MainForm.Basis.Length];
            float[] coordinates = new float[MainForm.Basis.Length];
            float[] begin = new float[MainForm.Basis.Length];
            for (int i = 0; i < coordinates.Length; i++)
            {
                coordinates[i] = 0;
                begin[i] = 0;
            }
            coordinates[0] = Constants.AxisLength;
            for (int i = 0; i < coordinates.Length; i++)
            {
                axises[i] = new Axis(begin, coordinates, Position, Constants.AxisRadius, Constants.CylinderSlices, Constants.CylinderStacks, device);
                coordinates[i] = 0;
                if (i!=coordinates.Length-1) 
                    coordinates[i + 1] = Constants.AxisLength;
            }
        }

        public void paint(Color c)
        {
            for (int i = 0; i < axises.Length; i++)
                axises[i].paint(c);
        }

        public void draw()
        {
            for (int i = 0; i < axises.Length; i++)
            {
                axises[i].draw();
            }
        }

        public void Dispose()
        {
            for (int i = 0; i < axises.Length; i++)
                axises[i].Dispose();
        }
    }
}
