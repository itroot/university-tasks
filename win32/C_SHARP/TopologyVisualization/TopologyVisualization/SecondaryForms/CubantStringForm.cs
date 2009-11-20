using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using TopologyVisualization.Help;

namespace TopologyVisualization.SecondaryForms
{
    public partial class CubantStringForm : Form
    {
        private MainForm parent;

        public CubantStringForm(object Parent)
        {
            parent = (MainForm)Parent;
            InitializeComponent();
            label1.Text = "Задайте двухзначный код кубанта. Размерность базиса "+MainForm.Basis.Length;
            Width = label1.Width + 30;
            textBox1.Bounds = new Rectangle((Width - textBox1.Width) / 2, textBox1.Bounds.Y, textBox1.Width, textBox1.Height);
            button1.Bounds = new Rectangle((Width - button1.Width) / 4, button1.Bounds.Y, button1.Width, button1.Height);
            button2.Bounds = new Rectangle(((Width - button1.Width) * 3) / 4, button2.Bounds.Y, button2.Width, button2.Height);
        }

        private void CubantStringForm_FormClosed(object sender, FormClosedEventArgs e)
        {
            parent.hasChilds = false;
            parent.updateGraphics(Constants.SphereColor,Constants.CylinderColor,Constants.SphereColor,Constants.CylinderColor);
        }

        private void button2_Click(object sender, EventArgs e)
        {
            Close();
            Dispose();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            string str = textBox1.Text;
            string code = CoordinatesActions.CubantRecord2Code(str);
            if (code.Length == MainForm.Basis.Length)
            {
                for (int i = 0; i < code.Length; i++)
                    if (code[i] != '0' && code[i] != '1' && code[i] != '2')
                        return;
                MainForm.cube.setCubant(code, Constants.CubantSphereColor, Constants.CubantCylinderColor, Constants.BordersColor);
                button2_Click(this, new EventArgs());
            }
        }
    }
}
