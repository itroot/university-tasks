using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;

namespace TopologyVisualization.SimpleShapes
{
    class Sphere : SimpleShape
    {
        public int[] position;

        public Sphere(int[] Position,float radius, int slices, int stacks,Device dev)
        {
            device = dev;
            if (Position.Length!=Basis.Length) 
                throw new Exception("Размерность базиса не совпадает с размерностью вектора позиции.");
            position = Position;
            Vector3 pos = new Vector3(0.0f, 0.0f, 0.0f);
            for (int i = 0; i < Basis.Length; i++)
                pos += Position[i] * Basis[i];    
            MovingMatrix = Matrix.Translation(pos);
            meshes = new Mesh[1];
            meshes[0] = Mesh.Sphere(device, radius, slices, stacks);
            material = new Material();       
        }
    }
}
