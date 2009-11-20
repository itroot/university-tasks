using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;
using TopologyVisualization.Help;

namespace TopologyVisualization.SimpleShapes
{
    class Triangle
    {
        public static Vector3[] Basis;

        protected Device device;
        protected int[][] int_coordinates;
        protected float[][] float_coordinates;
        protected Vector3[] position;
        protected Vector3 normal;
        protected Material material;
        CustomVertex.PositionNormalColored[] verts;

        public Triangle(int[] FirstPoint, int[] SecondPoint, int[] ThirdPoint,float[] Normal,Device dev)
        {
            device = dev;

            if ((Basis.Length != FirstPoint.Length) || (Basis.Length != SecondPoint.Length) ||
                (Basis.Length != ThirdPoint.Length) || (Basis.Length != Normal.Length))
                throw new Exception("Размерность базиса не совпадает с размерностью вектора позиции или нормали.");

            int_coordinates = new int[3][];
            int_coordinates[0] = FirstPoint;
            int_coordinates[1] = SecondPoint;
            int_coordinates[2] = ThirdPoint;

            Vector3 first = new Vector3(0.0f, 0.0f, 0.0f);
            Vector3 second = new Vector3(0.0f, 0.0f, 0.0f);
            Vector3 third = new Vector3(0.0f, 0.0f, 0.0f);
            normal = new Vector3(0.0f, 0.0f, 0.0f);

            for (int i=0;i<Basis.Length;i++)
            {
                first += FirstPoint[i] * Basis[i];
                second += SecondPoint[i] * Basis[i];
                third += ThirdPoint[i] * Basis[i];
                normal += Normal[i] * Basis[i];
            }

            verts = new CustomVertex.PositionNormalColored[3];
            position = new Vector3[3];
            position[0] = first;
            position[1] = second;
            position[2] = third;
            verts[0].Position = first;
            verts[1].Position = second;
            verts[2].Position = third;
            normal.Normalize();
            verts[0].Normal = verts[1].Normal = verts[2].Normal = normal;
        }

        public Triangle(float[] FirstPoint, float[] SecondPoint, float[] ThirdPoint, float[] Normal, Device dev)
        {
            device = dev;

            if ((Basis.Length != FirstPoint.Length) || (Basis.Length != SecondPoint.Length) ||
                (Basis.Length != ThirdPoint.Length) || (Basis.Length != Normal.Length))
                throw new Exception("Размерность базиса не совпадает с размерностью вектора позиции или нормали.");

            float_coordinates = new float[3][];
            float_coordinates[0] = FirstPoint;
            float_coordinates[1] = SecondPoint;
            float_coordinates[2] = ThirdPoint;

            Vector3 first = new Vector3(0.0f, 0.0f, 0.0f);
            Vector3 second = new Vector3(0.0f, 0.0f, 0.0f);
            Vector3 third = new Vector3(0.0f, 0.0f, 0.0f);
            normal = new Vector3(0.0f, 0.0f, 0.0f);

            for (int i = 0; i < Basis.Length; i++)
            {
                first += FirstPoint[i] * Basis[i];
                second += SecondPoint[i] * Basis[i];
                third += ThirdPoint[i] * Basis[i];
                normal += Normal[i] * Basis[i];
            }

            verts = new CustomVertex.PositionNormalColored[3];
            position = new Vector3[3];
            position[0] = first;
            position[1] = second;
            position[2] = third;
            verts[0].Position = first;
            verts[1].Position = second;
            verts[2].Position = third;
            normal.Normalize();
            verts[0].Normal = verts[1].Normal = verts[2].Normal = normal;
        }

        public Triangle(float[] FirstPoint, float[] SecondPoint, float[] ThirdPoint, Device dev)
        {
            device = dev;

            if ((Basis.Length != FirstPoint.Length) || (Basis.Length != SecondPoint.Length) ||
                (Basis.Length != ThirdPoint.Length))
                throw new Exception("Размерность базиса не совпадает с размерностью вектора позиции или нормали.");

            float_coordinates = new float[3][];
            float_coordinates[0] = FirstPoint;
            float_coordinates[1] = SecondPoint;
            float_coordinates[2] = ThirdPoint;

            Vector3 first = new Vector3(0.0f, 0.0f, 0.0f);
            Vector3 second = new Vector3(0.0f, 0.0f, 0.0f);
            Vector3 third = new Vector3(0.0f, 0.0f, 0.0f);

            for (int i = 0; i < Basis.Length; i++)
            {
                first += FirstPoint[i] * Basis[i];
                second += SecondPoint[i] * Basis[i];
                third += ThirdPoint[i] * Basis[i];
            }

            verts = new CustomVertex.PositionNormalColored[3];
            position = new Vector3[3];
            position[0] = first;
            position[1] = second;
            position[2] = third;
            verts[0].Position = first;
            verts[1].Position = second;
            verts[2].Position = third;
            normal = VectorActions.vectmul(first - second, first - third);
            normal.Normalize();
            verts[0].Normal = verts[1].Normal = verts[2].Normal = normal;
        }


        public void paint(Color c)
        {
            //verts[0].Color = verts[1].Color = verts[2].Color = c.ToArgb();
            material.Ambient = c;
            material.Diffuse = c;
            material.Specular = c;
        }

        public void draw()
        {
            Material tmp = device.Material;
            VertexFormats tmpverfor = device.VertexFormat;
            device.Material = material;
            device.VertexFormat = CustomVertex.PositionNormalColored.Format;
            device.DrawUserPrimitives(PrimitiveType.TriangleList, 1, verts);
            device.Material = tmp;
            device.VertexFormat = tmpverfor;
        }
    }
}
