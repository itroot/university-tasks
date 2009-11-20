using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using System.IO;
using Microsoft.DirectX;

namespace TopologyVisualization
{
    public enum BordersOption {NoBorders,OnlyDoors,All};

    public static class Constants
    {
        public static Color SphereColor;
        public static Color CylinderColor;
        public static float SphereRadius;
        public static float CylinderRadius;
        public static Color CubantSphereColor;
        public static Color CubantCylinderColor;
        public static Color BordersColor;
        public static int SphereSlices;
        public static int SphereStacks;
        public static int CylinderSlices;
        public static int CylinderStacks;
        public static float CameraTranslateSpeed;
        public static float CameraRotateSpeed;
        public static bool DrawAxis;
        public static Color AxisColor;
        public static float AxisLength;
        public static float AxisRadius;
        public static bool UseSameColorForSphereAndCylinderCubant;
        public static BordersOption UseBordersOption;
        public static Vector3 axisPosition;
        public static Color BackGroundColor;

        static Constants()
        {
            int A, R, G, B;
            double X, Y, Z;
            StreamReader sr = new StreamReader("../../params.txt");

            A = Int32.Parse(sr.ReadLine());
            R = Int32.Parse(sr.ReadLine());
            G = Int32.Parse(sr.ReadLine());
            B = Int32.Parse(sr.ReadLine());
            BackGroundColor = Color.FromArgb(A, R, G, B);

            A = Int32.Parse(sr.ReadLine());
            R = Int32.Parse(sr.ReadLine());
            G = Int32.Parse(sr.ReadLine());
            B = Int32.Parse(sr.ReadLine());
            SphereColor = Color.FromArgb(A, R, G, B);

            A = Int32.Parse(sr.ReadLine());
            R = Int32.Parse(sr.ReadLine());
            G = Int32.Parse(sr.ReadLine());
            B = Int32.Parse(sr.ReadLine());
            CylinderColor = Color.FromArgb(A, R, G, B);

            SphereRadius = float.Parse(sr.ReadLine());
            CylinderRadius = float.Parse(sr.ReadLine());

            A = Int32.Parse(sr.ReadLine());
            R = Int32.Parse(sr.ReadLine());
            G = Int32.Parse(sr.ReadLine());
            B = Int32.Parse(sr.ReadLine());
            CubantSphereColor = Color.FromArgb(A, R, G, B);

            A = Int32.Parse(sr.ReadLine());
            R = Int32.Parse(sr.ReadLine());
            G = Int32.Parse(sr.ReadLine());
            B = Int32.Parse(sr.ReadLine());
            CubantCylinderColor = Color.FromArgb(A, R, G, B);

            A = Int32.Parse(sr.ReadLine());
            R = Int32.Parse(sr.ReadLine());
            G = Int32.Parse(sr.ReadLine());
            B = Int32.Parse(sr.ReadLine());
            BordersColor = Color.FromArgb(A, R, G, B);

            SphereSlices = Int32.Parse(sr.ReadLine());
            SphereStacks = Int32.Parse(sr.ReadLine());
            CylinderSlices = Int32.Parse(sr.ReadLine());
            CylinderStacks = Int32.Parse(sr.ReadLine());

            CameraTranslateSpeed = float.Parse(sr.ReadLine());
            CameraRotateSpeed = float.Parse(sr.ReadLine());

            A = Int32.Parse(sr.ReadLine());
            R = Int32.Parse(sr.ReadLine());
            G = Int32.Parse(sr.ReadLine());
            B = Int32.Parse(sr.ReadLine());
            AxisColor = Color.FromArgb(A, R, G, B);

            DrawAxis = bool.Parse(sr.ReadLine());
            AxisLength = float.Parse(sr.ReadLine());
            AxisRadius = float.Parse(sr.ReadLine());

            UseSameColorForSphereAndCylinderCubant = bool.Parse(sr.ReadLine());

            int bo = Int32.Parse(sr.ReadLine());
            if (bo == 1)
                UseBordersOption = BordersOption.NoBorders;
            else
                if (bo == 2)
                    UseBordersOption = BordersOption.OnlyDoors;
                else
                    if (bo == 3)
                        UseBordersOption = BordersOption.All;
                    else
                        throw new Exception("Не заданы опции отображения границы");
            try
            {
                X = double.Parse(sr.ReadLine());
                Y = double.Parse(sr.ReadLine());
                Z = double.Parse(sr.ReadLine());
                axisPosition = new Vector3((float)X, (float)Y, (float)Z);
            }
            catch (Exception exc)
            {
                System.Windows.Forms.MessageBox.Show(exc.Message);
            }

            sr.Close();
        }

        public static void save()
        {
            StreamWriter sr = new StreamWriter("../../params.txt");

            sr.WriteLine(BackGroundColor.A.ToString());
            sr.WriteLine(BackGroundColor.R.ToString());
            sr.WriteLine(BackGroundColor.G.ToString());
            sr.WriteLine(BackGroundColor.B.ToString());

            sr.WriteLine(SphereColor.A.ToString());
            sr.WriteLine(SphereColor.R.ToString());
            sr.WriteLine(SphereColor.G.ToString());
            sr.WriteLine(SphereColor.B.ToString());

            sr.WriteLine(CylinderColor.A.ToString());
            sr.WriteLine(CylinderColor.R.ToString());
            sr.WriteLine(CylinderColor.G.ToString());
            sr.WriteLine(CylinderColor.B.ToString());

            sr.WriteLine(SphereRadius.ToString());
            sr.WriteLine(CylinderRadius.ToString());

            sr.WriteLine(CubantSphereColor.A.ToString());
            sr.WriteLine(CubantSphereColor.R.ToString());
            sr.WriteLine(CubantSphereColor.G.ToString());
            sr.WriteLine(CubantSphereColor.B.ToString());

            sr.WriteLine(CubantCylinderColor.A.ToString());
            sr.WriteLine(CubantCylinderColor.R.ToString());
            sr.WriteLine(CubantCylinderColor.G.ToString());
            sr.WriteLine(CubantCylinderColor.B.ToString());

            sr.WriteLine(BordersColor.A.ToString());
            sr.WriteLine(BordersColor.R.ToString());
            sr.WriteLine(BordersColor.G.ToString());
            sr.WriteLine(BordersColor.B.ToString());

            sr.WriteLine(SphereSlices.ToString());
            sr.WriteLine(SphereStacks.ToString());
            sr.WriteLine(CylinderSlices.ToString());
            sr.WriteLine(CylinderStacks.ToString());

            sr.WriteLine(CameraTranslateSpeed.ToString());
            sr.WriteLine(CameraRotateSpeed.ToString());

            sr.WriteLine(AxisColor.A.ToString());
            sr.WriteLine(AxisColor.R.ToString());
            sr.WriteLine(AxisColor.G.ToString());
            sr.WriteLine(AxisColor.B.ToString());

            sr.WriteLine(DrawAxis.ToString());
            sr.WriteLine(AxisLength.ToString());
            sr.WriteLine(AxisRadius.ToString());

            sr.WriteLine(UseSameColorForSphereAndCylinderCubant.ToString());

            if (UseBordersOption == BordersOption.NoBorders)
                sr.WriteLine("1");
            else
                if (UseBordersOption == BordersOption.OnlyDoors)
                    sr.WriteLine("2");
                else
                    if (UseBordersOption == BordersOption.All)
                        sr.WriteLine("3");
                    else
                        throw new Exception("Опции отображения границы не уложились в допустимый дипозон.");

            sr.WriteLine(axisPosition.X.ToString());
            sr.WriteLine(axisPosition.Y.ToString());
            sr.WriteLine(axisPosition.Z.ToString());

            sr.Flush();
            sr.Close();
        }
    }
}
