using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;
using TopologyVisualization.SimpleShapes;
using TopologyVisualization.Shapes;
using TopologyVisualization.DifficultShapes;
using TopologyVisualization.SecondaryForms;
using TopologyVisualization.Help;
using System.IO;
namespace TopologyVisualization
{
    public partial class MainForm : Form
    {
        public static Device device;
        private int MouseX = 0;
        private int MouseY = 0;
        public static Vector3[] Basis;
        public static Hypercube cube;
        public static bool hasChildForms;
        public bool hasChilds;
        private Axises axises;

        public void setBasis(Vector3[] newBasis)
        {
            Basis = Cylinder.Basis = Sphere.Basis = Triangle.Basis = Hypercube.Basis = newBasis;
            axises = new Axises(Constants.axisPosition,device);
            axises.paint(Constants.AxisColor);
            Hypercube.setCamera = true;
            cube = new Hypercube(Constants.SphereColor, Constants.CylinderColor, device);
            Invalidate();
        }


        public void updateGraphics(Color SphereColor,Color CylinderColor,Color OldSphereColor,Color OldCylinderColor)
        {
            if (Basis != null)
            {
                axises = new Axises(Constants.axisPosition,device);
                axises.paint(Constants.AxisColor);
                //string[] cubants = cube.cubants.ToArray();
                //Color[] cubantColors = cube.cubantColors.ToArray();
                //cube = new Hypercube(Constants.SphereColor, Constants.CylinderColor, device);
                cube.pant(SphereColor, CylinderColor, OldSphereColor, OldCylinderColor);
                //for (int i = 0; i < cubants.Length; i++)
                //{
                //   cube.setCubant(cubants[i], cubantColors[3 * i], cubantColors[3 * i + 1], cubantColors[3 * i + 2]);
                //}
                
            }
            Invalidate();
        }

        public MainForm()
        {
            hasChilds = false;
            hasChildForms = false;
            SetStyle(ControlStyles.ResizeRedraw, true);
            Cylinder.Basis = Sphere.Basis = Triangle.Basis = Hypercube.Basis = Basis;
            InitializeComponent();
            this.Size = new Size(1024, 768);
            MouseWheel += new System.Windows.Forms.MouseEventHandler(OnMouseWheel);
        }

        private void MainForm_Load(object sender, EventArgs e)
        {
            try
            {
                // Устанавливаем режим отображения трехмерной графики
                PresentParameters d3dpp = new PresentParameters();
                d3dpp.BackBufferCount = 1;
                d3dpp.SwapEffect = SwapEffect.Discard;
                d3dpp.Windowed = true; // Выводим графику в окно
                d3dpp.MultiSample = MultiSampleType.None; // Выключаем антиалиасинг
                d3dpp.EnableAutoDepthStencil = true; // Разрешаем создание z-буфера
                d3dpp.AutoDepthStencilFormat = DepthFormat.D16; // Z-буфер в 16 бит
                device = new Device(0, // D3D_ADAPTER_DEFAULT - видеоадаптер по умолчанию
                DeviceType.Hardware, // Тип устройства - аппаратный ускоритель
                this, // Окно для вывода графики
                
                CreateFlags.SoftwareVertexProcessing, // Геометрию обрабатывает CPU
                d3dpp);
                device.RenderState.Lighting = Enabled;
                device.RenderState.Ambient = System.Drawing.Color.White;
                device.RenderState.CullMode = Cull.None;
                device.Lights[0].Enabled = true;
                device.Lights[0].Diffuse = Color.White;
                device.Lights[0].Position = new Vector3(10, 10, 10);
                device.Lights[0].Range = 1000f;

                device.Lights[1].Enabled = true;
                device.Lights[1].Diffuse = Color.White;
                device.Lights[1].Position = new Vector3(-10, 10, -10);
                device.Lights[1].Range = 1000f;

                device.Transform.Projection = Matrix.PerspectiveFovLH((float)Math.PI / 3,Width / (float)Height,0.5f, 500f);

                MouseX = Cursor.Position.X;
                MouseY = Cursor.Position.Y;
                Camera.Initialize(new Vector3(-Constants.AxisLength, Constants.AxisLength, Constants.AxisLength), new Vector3(0, 0, 0), new Vector3(0, 1, 0));

                
                //code for testing
            }
            catch (Exception exc)
            {
                MessageBox.Show(this, exc.Message, "Ошибка инициализации");
                Close();
            }
        }

        private void OnMouseWheel(object o, MouseEventArgs e)
        {
            Camera.Forward(e.Delta * Constants.CameraTranslateSpeed * 0.05f);
            MainForm_Paint(this, null);
        }

        private void MainForm_Paint(object sender, PaintEventArgs e)
        {
            device.Lights[0].Position = Camera.Position;
            device.Clear(ClearFlags.Target | ClearFlags.ZBuffer, Constants.BackGroundColor, 1.0f, 0);
            device.BeginScene();

            if (cube != null)
            {
                cube.draw();
            }

            if (Constants.DrawAxis && axises != null)
                axises.draw();

            device.EndScene();
            device.Present();
        }

        private void MainForm_MouseMove(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                int xdist = MouseX - e.X;
                int ydist = MouseY - e.Y;
                Camera.RotateHorizontal(-xdist * Constants.CameraRotateSpeed);
                Camera.RotateVertical(ydist * Constants.CameraRotateSpeed);
                MainForm_Paint(this, null);
            }
            MouseX = e.X;
            MouseY = e.Y;
        }

        private void MainForm_KeyPress(object sender, KeyPressEventArgs e)
        {
            switch (e.KeyChar)
            {
                case (char)Keys.Escape: Close(); Dispose(); return; 
                case 'w':
                case 'W':
                case 'Ц':
                case 'ц': Camera.Forward(Constants.CameraTranslateSpeed); break;
                case 's':
                case 'S':
                case 'Ы':
                case 'ы': Camera.Backward(Constants.CameraTranslateSpeed); break;
                case 'd':
                case 'D':
                case 'В':
                case 'в': Camera.MoveRight(Constants.CameraTranslateSpeed); break;
                case 'a':
                case 'A':
                case 'Ф':
                case 'ф': Camera.MoveLeft(Constants.CameraTranslateSpeed);  break;
                default: break;
            }
            MainForm_Paint(this, null);
        }

        private void цвToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (!hasChilds)
            {
                hasChilds = true;
                ColorForm subform = new ColorForm(this);
                subform.Show();
            }
        }

        private void общиеToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (!hasChilds)
            {
                hasChilds = true;
                SizesForm subform = new SizesForm(this);
                subform.Show();
            }
        }

        private void гиперкубToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (!hasChilds)
            {
                hasChilds = true;
                HypercubeForm subform = new HypercubeForm(this);
                subform.Show();
            }
        }

        private void строкойToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (!hasChilds&&cube!=null)
            {
                hasChilds = true;
                CubantStringForm subform = new CubantStringForm(this);
                subform.Show();
            }
        }

        private void изФайлаToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (!hasChilds && cube != null)
            {
                hasChilds = true;
                OpenFileDialog subform = new OpenFileDialog();
                subform.ShowDialog();
                string filename = subform.FileName;
                if (filename != null && filename!="")
                {
                    StreamReader sr = new StreamReader(filename);
                    string cubant;
                    while ((cubant = sr.ReadLine()) != null)
                    {
                        cubant = CoordinatesActions.CubantRecord2Code(cubant);
                        if (cubant.Length == Basis.Length)
                            cube.setCubant(cubant, Constants.CubantSphereColor, Constants.CubantCylinderColor, Constants.BordersColor);
                    }
                    sr.Close();
                }
                //cube.setCubant("22200", Constants.CubantSphereColor, Constants.CubantCylinderColor, Constants.BordersColor);
                //cube.setCubant("21220", Constants.CubantSphereColor, Constants.CubantCylinderColor, Constants.BordersColor);
            }
            hasChilds = false;
        }

        private void задатьToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (!hasChilds && cube != null)
            {
                hasChilds = true;
                VisualizeShapes subform = new VisualizeShapes(this);
                subform.Show();
            }
        }

        private void изФайлаToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            if (!hasChilds && cube != null)
            {
                hasChilds = true;
                OpenFileDialog subform = new OpenFileDialog();
                subform.ShowDialog();
                string file = subform.FileName;
                subform.Dispose();
                StreamReader sr = new StreamReader(file);
                LinkedList<string> codes = new LinkedList<string>();
                string code;
                try
                {
                    while ((code = sr.ReadLine()) != null || code.Length != 0)
                        codes.AddLast(code);
                }
                catch (Exception) { }
                sr.Close();
                cube.VisualizeOnly(codes,true);
                hasChilds = false;
            }
        }

        private void задатьКодомToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (!hasChilds && cube != null)
            {
                hasChilds = true;
                DeleteShapes subform = new DeleteShapes(this);
                subform.Show();
            }
        }

        private void задатьИзФайлаToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (!hasChilds && cube != null)
            {
                hasChilds = true;
                OpenFileDialog subform = new OpenFileDialog();
                subform.ShowDialog();
                string file = subform.FileName;
                subform.Dispose();
                StreamReader sr = new StreamReader(file);
                LinkedList<string> codes = new LinkedList<string>();
                string code;
                try
                {
                    while ((code = sr.ReadLine()) != null || code.Length != 0)
                        codes.AddLast(code);
                }
                catch (Exception) { }
                sr.Close();
                cube.Delete(codes);
                hasChilds = false;
            }
        }

        private void задатьКодомToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            if (!hasChilds && cube != null)
            {
                hasChilds = true;
                PaintForm subform = new PaintForm(this);
                subform.Show();
            }
        }
    }
}
