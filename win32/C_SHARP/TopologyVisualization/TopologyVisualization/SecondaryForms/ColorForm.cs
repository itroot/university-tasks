using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace TopologyVisualization.SecondaryForms
{
    public partial class ColorForm : Form
    {
        private MainForm parent;
        private Color OldSphereColor;
        private Color OldCylinderColor;

        public ColorForm(object Parent)
        {
            OldSphereColor = Constants.SphereColor;
            OldCylinderColor = Constants.CylinderColor;
            parent = (MainForm)Parent;
            InitializeComponent();
            pictureBox1.BackColor = Constants.SphereColor;
            pictureBox2.BackColor = Constants.CylinderColor;
            pictureBox3.BackColor = Constants.CubantSphereColor;
            pictureBox4.BackColor = Constants.CubantCylinderColor;
            pictureBox5.BackColor = Constants.BordersColor;
            pictureBox6.BackColor = Constants.AxisColor;
            pictureBox7.BackColor = Constants.BackGroundColor;
            checkBox1.Checked = Constants.UseSameColorForSphereAndCylinderCubant;
            if (Constants.UseBordersOption == BordersOption.NoBorders)
                radioButton1.Checked = true;
            else
                if (Constants.UseBordersOption == BordersOption.OnlyDoors)
                    radioButton2.Checked = true;
                else
                    if (Constants.UseBordersOption == BordersOption.All)
                        radioButton3.Checked = true;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            this.Close();
            this.Dispose();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Constants.SphereColor = pictureBox1.BackColor;
            Constants.CylinderColor = pictureBox2.BackColor;
            Constants.CubantSphereColor = pictureBox3.BackColor;
            Constants.CubantCylinderColor = pictureBox4.BackColor;
            Constants.BordersColor = pictureBox5.BackColor;
            Constants.AxisColor = pictureBox6.BackColor;
            Constants.UseSameColorForSphereAndCylinderCubant = checkBox1.Checked;
            Constants.BackGroundColor = pictureBox7.BackColor;
            if (radioButton1.Checked)
                Constants.UseBordersOption = BordersOption.NoBorders;
            else
                if (radioButton2.Checked)
                    Constants.UseBordersOption = BordersOption.OnlyDoors;
                else
                    if (radioButton3.Checked)
                        Constants.UseBordersOption = BordersOption.All;
            Constants.save();
            Close();
            Dispose();
        }

        private void pictureBox1_Click(object sender, EventArgs e)
        {
            ColorDialog cd = new ColorDialog();
            cd.Color = pictureBox1.BackColor;
            cd.ShowDialog();
            pictureBox1.BackColor = cd.Color;
        }

        private void pictureBox2_Click(object sender, EventArgs e)
        {
            ColorDialog cd = new ColorDialog();
            cd.Color = pictureBox2.BackColor;
            cd.ShowDialog();
            pictureBox2.BackColor = cd.Color;
        }

        private void pictureBox3_Click(object sender, EventArgs e)
        {
            ColorDialog cd = new ColorDialog();
            cd.Color = pictureBox3.BackColor;
            cd.ShowDialog();
            pictureBox3.BackColor = cd.Color;
            if (checkBox1.Checked)
                pictureBox4.BackColor = cd.Color;
        }

        private void pictureBox4_Click(object sender, EventArgs e)
        {
            ColorDialog cd = new ColorDialog();
            cd.Color = pictureBox4.BackColor;
            cd.ShowDialog();
            pictureBox4.BackColor = cd.Color;
            if (checkBox1.Checked)
                pictureBox3.BackColor = cd.Color;
        }

        private void pictureBox5_Click(object sender, EventArgs e)
        {
            ColorDialog cd = new ColorDialog();
            cd.Color = pictureBox5.BackColor;
            cd.ShowDialog();
            pictureBox5.BackColor = cd.Color;
        }

        private void ColorForm_FormClosed(object sender, FormClosedEventArgs e)
        {
            parent.hasChilds = false;
            parent.updateGraphics(Constants.SphereColor, Constants.CylinderColor, 
                OldSphereColor, OldCylinderColor);
        }

        private void pictureBox6_Click(object sender, EventArgs e)
        {
            ColorDialog cd = new ColorDialog();
            cd.Color = pictureBox6.BackColor;
            cd.ShowDialog();
            pictureBox6.BackColor = cd.Color;
        }

        private void pictureBox7_Click(object sender, EventArgs e)
        {
            ColorDialog cd = new ColorDialog();
            cd.Color = pictureBox7.BackColor;
            cd.ShowDialog();
            pictureBox7.BackColor = cd.Color;
        }
    }
}
