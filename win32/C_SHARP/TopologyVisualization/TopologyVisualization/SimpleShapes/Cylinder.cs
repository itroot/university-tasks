using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;
using TopologyVisualization.Help;

namespace TopologyVisualization.SimpleShapes
{
    class Cylinder : SimpleShape
    {
        public int[][] int_coordinates;
        public float[][] float_coordinates;

        public Cylinder(int[] Begin, int[] End, float radius1, float radius2, int slices, int stacks,Device dev)
        {
            int_coordinates = new int[2][];
            int_coordinates[0] = Begin;
            int_coordinates[1] = End;
            device = dev;
            if ((Begin.Length != Basis.Length) || (End.Length != Basis.Length))
                throw new Exception("Размерность базиса не совпадает с размерностью вектора позиции.");

            Vector3 begin = new Vector3(0.0f, 0.0f, 0.0f);
            Vector3 end = new Vector3(0.0f, 0.0f, 0.0f);
            for (int i = 0; i < Basis.Length; i++)
            {
                begin += Begin[i]*Basis[i];
                end += End[i] * Basis[i];
            }

            MovingMatrix = Matrix.Translation(new Vector3(0, 0, (begin - end).Length() / 2));
            Vector3 be = end - begin;
            Vector3 curpos = new Vector3(0, 0, (begin - end).Length());
            float angle = (float)Math.Acos(VectorActions.scalmul(be, curpos) / (be.Length() * curpos.Length()));
            Vector3 axis = VectorActions.vectmul(be, curpos);

            MovingMatrix *= Matrix.RotationAxis(axis, -angle);
            MovingMatrix *= Matrix.Translation(begin);

            meshes = new Mesh[1];
            meshes[0] = Mesh.Cylinder(device, radius1, radius2, (begin - end).Length(), slices, stacks);
            meshes[0].ComputeNormals();
            material = new Material();
        }

        public Cylinder(float[] Begin, float[] End, float radius1, float radius2, int slices, int stacks, Device dev)
        {
            float_coordinates = new float[2][];
            float_coordinates[0] = Begin;
            float_coordinates[1] = End;
            device = dev;
            if ((Begin.Length != Basis.Length) || (End.Length != Basis.Length))
                throw new Exception("Размерность базиса не совпадает с размерностью вектора позиции.");
            Vector3 begin = new Vector3(0.0f, 0.0f, 0.0f);
            Vector3 end = new Vector3(0.0f, 0.0f, 0.0f);
            for (int i = 0; i < Basis.Length; i++)
            {
                begin += Begin[i] * Basis[i];
                end += End[i] * Basis[i];
            }

            MovingMatrix = Matrix.Translation(new Vector3(0, 0, (begin - end).Length() / 2));
            Vector3 be = end - begin;
            Vector3 curpos = new Vector3(0, 0, (begin - end).Length());
            float angle = (float)Math.Acos(VectorActions.scalmul(be, curpos) / (be.Length() * curpos.Length()));
            Vector3 axis = VectorActions.vectmul(be, curpos);

            MovingMatrix *= Matrix.RotationAxis(axis, -angle);
            MovingMatrix *= Matrix.Translation(begin);

            meshes = new Mesh[1];
            meshes[0] = Mesh.Cylinder(device, radius1, radius2, (begin - end).Length(), slices, stacks);
            meshes[0].ComputeNormals();
            material = new Material();
        }
    }
}
