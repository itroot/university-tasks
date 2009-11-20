using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using TopologyVisualization.SimpleShapes;
using TopologyVisualization.Help;
using TopologyVisualization.Shapes;
using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;
using System.Drawing;

namespace TopologyVisualization.DifficultShapes
{
    public class Hypercube
    {
        public static Vector3[] Basis;
        public int[][] BasisElements;
        private LinkedList<Sphere> spheres;
        private LinkedList<Cylinder> cylinders;
        public LinkedList<string> cubants;
        public LinkedList<Color> cubantColors;
        public LinkedList<Square> squares;
        private Device device;
        public static bool setCamera = true;

        public Hypercube(Color SphereColor, Color CylinderColor, Device dev)
        {
            device = dev;
            spheres = new LinkedList<Sphere>();
            cylinders = new LinkedList<Cylinder>();
            cubants = new LinkedList<string>();
            cubantColors = new LinkedList<Color>();
            squares = new LinkedList<Square>();
            BasisElements = new int[Basis.Length][];
            for (int i = 0; i < BasisElements.Length; i++)
            {
                BasisElements[i] = new int[Basis.Length];
                for (int j = 0; j < BasisElements[i].Length; j++)
                    if (i != j)
                        BasisElements[i][j] = 0;
                    else
                        BasisElements[i][j] = 1;
            }
            int[] nullcoord = CoordinatesActions.getNullIntCoord(Basis.Length);
            Sphere first = new Sphere(nullcoord, Constants.SphereRadius,
                Constants.SphereSlices, Constants.SphereStacks, dev);
            first.paint(SphereColor);
            spheres.AddLast(first);
            for (int i = 0; i < Basis.Length; i++)
            {
                LinkedList<Sphere> newSpheres = new LinkedList<Sphere>();
                LinkedList<Cylinder> newCylinders = new LinkedList<Cylinder>();
                foreach(Sphere s in spheres)
                {
                    Sphere newsphere = new Sphere(CoordinatesActions.add(s.position, BasisElements[i]), Constants.SphereRadius,
                        Constants.SphereSlices, Constants.SphereStacks, device);
                    newsphere.paint(SphereColor);
                    newSpheres.AddLast(newsphere);
                    Cylinder newcylinder = new Cylinder(s.position, CoordinatesActions.add(s.position, BasisElements[i]),
                        Constants.CylinderRadius, Constants.CylinderRadius, Constants.CylinderSlices, Constants.CylinderStacks, 
                        device);
                    newcylinder.paint(CylinderColor);
                    newCylinders.AddLast(newcylinder);
                }
                foreach(Cylinder c in cylinders)
                {
                    Cylinder newCylinder = new Cylinder(CoordinatesActions.add(c.int_coordinates[0], BasisElements[i]),
                        CoordinatesActions.add(c.int_coordinates[1], BasisElements[i]),
                        Constants.CylinderRadius, Constants.CylinderRadius, Constants.CylinderSlices, Constants.CylinderStacks,
                        device);
                    newCylinder.paint(CylinderColor);
                    newCylinders.AddLast(newCylinder);
                }
                foreach (Sphere s in newSpheres)
                    spheres.AddLast(s);
                foreach (Cylinder c in newCylinders)
                    cylinders.AddLast(c);
            }

            float[] camerapos = new float[Basis.Length];
            if (setCamera)
            {
                for (int i = 0; i < camerapos.Length; i++)
                    camerapos[i] = 0.5f;
                Vector3 cameraposition = CoordinatesActions.getVector(camerapos, Basis);
                Vector3 tmp1 = new Vector3(-cameraposition.X, cameraposition.Y, -cameraposition.Z);
                Camera.Position = tmp1;
                Camera.Target = cameraposition;
            }
            setCamera = false;
        }

        public void setCubant(string str,Color SphereColor,Color CylinderColor,Color BorderColor)
        {
            if (str.Length != Basis.Length)
                throw new Exception("Размерность кубанта не соответствует размерности гиперкуба.");
            int[] code = new int[str.Length];
            for (int i=0;i<str.Length;i++)
                if (str[i]=='0')
                    code[i] = 0;
                else
                    if (str[i]=='1')
                        code[i]=1;
                    else 
                        if (str[i]=='2')
                            code[i]=2;
                        else
                            throw new Exception("Код кубанта содержит недопустимые символы: "+str[i]);
            foreach (Sphere s in spheres)
                if (CoordinatesActions.consist(s.position, code))
                    s.paint(SphereColor);
            foreach (Cylinder c in cylinders)
                if (CoordinatesActions.consist(c.int_coordinates[0], code) && CoordinatesActions.consist(c.int_coordinates[1], code))
                    c.paint(CylinderColor);
            if (Constants.UseBordersOption== BordersOption.OnlyDoors)
                foreach (string s in cubants)
                {
                    int[] cubantCode = CoordinatesActions.getCode(s);
                    int[] per = CoordinatesActions.peresechenie(cubantCode, code);
                    if (per != null && CoordinatesActions.isSquare(per))
                        addSquare(per,BorderColor);
                }
            if (Constants.UseBordersOption == BordersOption.All)
                try
                {
                    LinkedList<int[]> squares = CoordinatesActions.getAllSquares(code);
                    foreach (int[] squarecode in squares)
                        addSquare(squarecode, BorderColor);
                }
                catch (Exception)
                {
                    //nothing to do here
                }
            cubants.AddLast(str);
            cubantColors.AddLast(SphereColor);
            cubantColors.AddLast(CylinderColor);
            cubantColors.AddLast(BorderColor);
        }

        private void addSquare(int[] code,Color BorderColor)
        {
            int firstTwo = -1, SecondTwo = -1;
            for (int i = 0; i < code.Length; i++)
                if (code[i] == 2)
                {
                    if (firstTwo < 0)
                        firstTwo = i;
                    else
                    {
                        SecondTwo = i;
                        break;
                    }
                }
            float[][] points = new float[4][];
            for (int i = 0; i < 4; i++)
            {
                points[i] = new float[code.Length];
                for (int j = 0; j < code.Length; j++)
                    points[i][j] = code[j];
            }
            points[0][firstTwo] = 0.0f; points[0][SecondTwo] = 0.0f;
            points[1][firstTwo] = 0.0f; points[1][SecondTwo] = 1.0f;
            points[2][firstTwo] = 1.0f; points[2][SecondTwo] = 1.0f;
            points[3][firstTwo] = 1.0f; points[3][SecondTwo] = 0.0f;
            Square tmpsqr = new Square(points, device);
            tmpsqr.paint(BorderColor);
            squares.AddLast(tmpsqr);
        }
        
        public void draw()
        {
            foreach (Sphere s in spheres)
                s.draw();
            foreach (Cylinder c in cylinders)
                c.draw();
            foreach (Square s in squares)
                s.draw();
        }

        public void pant(LinkedList<string> codes, Color SphereColor, Color CylinderColor)
        {
            string[] Codes = new string[codes.Count];
            int counter = 0;
            foreach (string s in codes)
                Codes[counter++] = s;
            foreach (Sphere s in spheres)
                if (CoordinatesActions.consist(Codes, s.position))
                    s.paint(SphereColor);
            foreach (Cylinder c in cylinders)
                if (CoordinatesActions.consist(Codes, c.int_coordinates[0])
                    && CoordinatesActions.consist(Codes, c.int_coordinates[1]))
                    c.paint(CylinderColor);
        }

        public void pant(Color SphereColor, Color CylinderColor, Color OldSphereColor, Color OldCylinderColor)
        {
            foreach (Sphere s in spheres)
                if (s.material.Diffuse.Equals(OldSphereColor))
                    s.paint(SphereColor);
            foreach (Cylinder c in cylinders)
                if (c.material.Diffuse.Equals(OldCylinderColor))
                    c.paint(CylinderColor);
        }

        public void VisualizeOnly(LinkedList<string> codes,bool drawEdge)
        {
            string[] Codes = new string[codes.Count];
            int counter = 0;
            foreach (string s in codes)
                Codes[counter++] = s;
            foreach (Sphere s in spheres)
                if (!CoordinatesActions.consist(Codes, s.position))
                    s.visualize = false;
                else
                    s.visualize = true;
            if (drawEdge)
                foreach (Cylinder c in cylinders)
                    if (!CoordinatesActions.consist(Codes, c.int_coordinates[0]) 
                        || !CoordinatesActions.consist(Codes, c.int_coordinates[1]))
                        c.visualize = false;
                    else
                        c.visualize = true;
            else
                foreach (Cylinder c in cylinders)
                    if (!CoordinatesActions.consist(Codes,c.int_coordinates[0],c.int_coordinates[1]))
                        c.visualize = false;
                    else
                        c.visualize = true;
        }

        public void Delete(LinkedList<string> codes)
        {
            string[] Codes = new string[codes.Count];
            int counter = 0;
            foreach (string s in codes)
                Codes[counter++] = s;
            foreach (Sphere s in spheres)
                if (CoordinatesActions.consist(Codes, s.position))
                    s.visualize = false;
            foreach (Cylinder c in cylinders)
                if (CoordinatesActions.consist(Codes, c.int_coordinates[0])
                    || CoordinatesActions.consist(Codes, c.int_coordinates[1]))
                    c.visualize = false;
        }

        public void Dispose()
        {
            foreach (Sphere s in spheres)
                s.Dispose();
            foreach (Cylinder c in cylinders)
                c.Dispose();
            spheres.Clear();
            cylinders.Clear();
        }
   
    }
}
