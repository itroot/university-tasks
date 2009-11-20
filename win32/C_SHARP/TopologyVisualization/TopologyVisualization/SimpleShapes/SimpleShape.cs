using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;
using System.Drawing;

namespace TopologyVisualization.SimpleShapes
{
    class SimpleShape
    {
        public static Vector3[] Basis;

        protected Device device;
        public Matrix MovingMatrix;
        protected Mesh[] meshes;
        public Material material;
        public bool visualize;

        public SimpleShape()
        {
            visualize = true;
        }

        public void paint(Color c)
        {
            material.Ambient = material.Diffuse = material.Specular = c;
        }

        public void draw()
        {
            if (visualize)
            {
                Matrix tmpmatrix = device.Transform.World;
                Material tmpmaterial = device.Material;
                device.Transform.World *= MovingMatrix;
                device.Material = material;
                for (int i = 0; i < meshes.Length; i++)
                    meshes[i].DrawSubset(0);
                device.Transform.World = tmpmatrix;
                device.Material = tmpmaterial;
            }
        }

        public void Dispose()
        {
            for (int i = 0; i < meshes.Length; i++)
                meshes[i].Dispose();
        }
    }
}
