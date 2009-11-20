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
    public partial class SizesForm : Form
    {
        private MainForm parent;

        public SizesForm(object Parent)
        {
            parent = (MainForm)Parent;
            InitializeComponent();
            trackBar1.Minimum = trackBar2.Minimum = trackBar3.Minimum = trackBar4.Minimum = trackBar7.Minimum = trackBar8.Minimum = 1;
            trackBar1.Maximum = trackBar2.Maximum = trackBar3.Maximum = trackBar4.Maximum = trackBar7.Maximum = 100;
            trackBar8.Maximum = 20;
            trackBar5.Minimum = trackBar6.Minimum = 4;
            trackBar5.Maximum = trackBar6.Maximum = 32;
            trackBar1.Value = (int)(Constants.SphereRadius * 100);
            trackBar2.Value = (int)(Constants.CylinderRadius * 100);
            trackBar3.Value = (int)(Constants.CameraTranslateSpeed * 100);
            trackBar4.Value = (int)(Constants.CameraRotateSpeed * 500);
            trackBar5.Value = Constants.CylinderSlices;
            trackBar6.Value = Constants.SphereSlices;
            trackBar7.Value = (int)(Constants.AxisLength * 10);
            trackBar8.Value = (int)(Constants.AxisRadius * 100);
            label3.Text = trackBar1.Value.ToString();
            label4.Text = trackBar2.Value.ToString();
            label5.Text = trackBar3.Value.ToString();
            label7.Text = trackBar4.Value.ToString();
            label9.Text = trackBar5.Value.ToString();
            label11.Text = trackBar6.Value.ToString();
            label14.Text = trackBar7.Value.ToString();
            label15.Text = trackBar8.Value.ToString();
            checkBox1.Checked = Constants.DrawAxis;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            this.Close();
            this.Dispose();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Constants.SphereRadius = (float)(trackBar1.Value / 100.0);
            Constants.CylinderRadius = (float)(trackBar2.Value / 100.0);
            Constants.CameraTranslateSpeed = (float)(trackBar3.Value / 100.0);
            Constants.CameraRotateSpeed = (float)(trackBar4.Value / 500.0);
            Constants.SphereSlices = Constants.SphereStacks = trackBar6.Value;
            Constants.CylinderSlices = Constants.CylinderStacks = trackBar5.Value;
            Constants.DrawAxis = checkBox1.Checked;
            Constants.AxisLength = (float)(trackBar7.Value / 10f);
            Constants.AxisRadius = (float)(trackBar8.Value / 100f);
            Constants.save();
            button2_Click(sender, e);
        }

        private void trackBar1_Scroll(object sender, EventArgs e)
        {
            label3.Text = trackBar1.Value.ToString();
        }

        private void trackBar2_Scroll(object sender, EventArgs e)
        {
            label4.Text = trackBar2.Value.ToString();
        }

        private void trackBar3_Scroll(object sender, EventArgs e)
        {
            label5.Text = trackBar3.Value.ToString();
        }

        private void trackBar4_Scroll(object sender, EventArgs e)
        {
            label7.Text = trackBar4.Value.ToString();
        }

        private void trackBar5_Scroll(object sender, EventArgs e)
        {
            label9.Text = trackBar5.Value.ToString();
        }

        private void trackBar6_Scroll(object sender, EventArgs e)
        {
            label11.Text = trackBar6.Value.ToString();
        }

        private void trackBar7_Scroll(object sender, EventArgs e)
        {
            label14.Text = trackBar7.Value.ToString();
        }

        private void trackBar8_Scroll(object sender, EventArgs e)
        {
            label15.Text = trackBar8.Value.ToString();
        }

        private void SizesForm_FormClosed(object sender, FormClosedEventArgs e)
        {
            parent.hasChilds = false;
            parent.updateGraphics(Constants.SphereColor,Constants.CylinderColor,
                Constants.SphereColor,Constants.CylinderColor);
        }
    }
}
