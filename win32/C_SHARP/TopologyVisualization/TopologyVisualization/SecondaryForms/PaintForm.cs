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
    public partial class PaintForm : Form
    {
        private MainForm parent;

        public PaintForm(object Parent)
        {
            parent = (MainForm)Parent;
            InitializeComponent();
            pictureBox1.BackColor = pictureBox2.BackColor = Color.Green;
            checkBox1.Checked = true;
        }

        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox1.Checked)
                pictureBox2.BackColor = pictureBox1.BackColor;
        }

        private void PaintForm_FormClosed(object sender, FormClosedEventArgs e)
        {
            parent.hasChilds = false;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            Close();
            Dispose();
        }

        private void pictureBox1_Click(object sender, EventArgs e)
        {
            ColorDialog cd = new ColorDialog();
            cd.ShowDialog();
            pictureBox1.BackColor = cd.Color;
            if (checkBox1.Checked)
                pictureBox2.BackColor = cd.Color;
        }

        private void pictureBox2_Click(object sender, EventArgs e)
        {
            ColorDialog cd = new ColorDialog();
            cd.ShowDialog();
            pictureBox2.BackColor = cd.Color;
            if (checkBox1.Checked)
                pictureBox1.BackColor = cd.Color;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            int NormalLength = MainForm.Basis.Length;
            LinkedList<string> codes = new LinkedList<string>();
            string srt = textBox1.Text;
            while (srt.Length != 0)
            {
                int index = srt.IndexOf(';');
                if (index > 0)
                {
                    string code = srt.Substring(0, index);
                    if (code.Length != NormalLength)
                        return;
                    srt = srt.Substring(index + 1, srt.Length - index - 1);
                    codes.AddLast(code);
                }
                else
                {
                    if (srt.Length != NormalLength)
                        return;
                    codes.AddLast(new string(srt.ToCharArray()));
                    srt = "";
                }
            }
            MainForm.cube.pant(codes,pictureBox1.BackColor,pictureBox2.BackColor);
            Close();
            Dispose();
        }
    }
}
