using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using Microsoft.DirectX;

namespace TopologyVisualization.SecondaryForms
{
    public partial class HypercubeForm : Form
    {
        private TextBox[] tb;
        private MainForm parent;

        public HypercubeForm(object Parent)
        {
            parent = (MainForm)Parent;
            InitializeComponent();
            numericUpDown1.Maximum = 12;
            numericUpDown1.Minimum = 2;
            numericUpDown1.Value = 3;
            numericUpDown1.ReadOnly = true;
            numericUpDown1.BackColor = Color.White;
        }

        private void numericUpDown1_ValueChanged(object sender, EventArgs e)
        {
            int vertstep = 40, height = 23;
            int index = (int)numericUpDown1.Value;
            groupBox1.Controls.Clear();
            tb = new TextBox[index * 3];
            for (int i = 0; i < index * 3; i++)
            {
                if (i % 3 == 0)
                {
                    Label lb = new Label();
                    lb.Text = "E" + (i / 3).ToString();
                    lb.Bounds = new Rectangle(10, 20 + vertstep * (i / 3), 20, height);
                    groupBox1.Controls.Add(lb);
                }
                tb[i] = new TextBox();
                tb[i].Bounds = new Rectangle(30 + (i % 3) * 80, 20 + vertstep * (i / 3), 60, height);
                groupBox1.Controls.Add(tb[i]);
            }

            groupBox1.Bounds = new Rectangle(groupBox1.Bounds.X, groupBox1.Bounds.Y, groupBox1.Width, 20 + vertstep * index);
            Rectangle tmpr = button1.Bounds;
            button1.Bounds = new Rectangle(tmpr.X, groupBox1.Bounds.Y + groupBox1.Bounds.Height + 20, tmpr.Width, tmpr.Height);
            tmpr = button2.Bounds;
            button2.Bounds = new Rectangle(tmpr.X, groupBox1.Bounds.Y + groupBox1.Bounds.Height + 20, tmpr.Width, tmpr.Height);
            tmpr = Bounds;
            Bounds = new Rectangle(tmpr.X, tmpr.Y, tmpr.Width, button2.Bottom + 20 + button2.Size.Height);

            switch (index)
            {
                case 12:
                case 11:
                case 10:
                case 9: tb[24].Text = "17"; tb[25].Text = "1"; tb[26].Text = "4"; goto case 8;
                case 8: tb[21].Text = "1"; tb[22].Text = "4"; tb[23].Text = "17"; goto case 7;
                case 7: tb[18].Text = "17"; tb[19].Text = "4"; tb[20].Text = "1"; goto case 6;
                case 6: tb[15].Text = "1"; tb[16].Text = "5"; tb[17].Text = "1"; goto case 5;
                case 5: tb[12].Text = "1"; tb[13].Text = "1"; tb[14].Text = "5"; goto case 4;
                case 4: tb[9].Text = "5"; tb[10].Text = "1"; tb[11].Text = "1"; goto case 3;
                case 3: tb[6].Text = "0"; tb[7].Text = "0"; tb[8].Text = "1"; goto case 2;
                case 2: tb[0].Text = "1"; tb[1].Text = "0"; tb[2].Text = "0";
                    tb[3].Text = "0"; tb[4].Text = "1"; tb[5].Text = "0"; break;
                default: throw new Exception("Выбрана непредусмотренная размерность: "+index.ToString());
            }

            for (int i = index * 3; i < tb.Length; i++)
                tb[i].Enabled = false;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            Close();
            Dispose();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                int index = (int)numericUpDown1.Value;
                Vector3[] BaseVect = new Vector3[index];
                for (int i = 0; i < index; i++)
                {
                    BaseVect[i] = new Vector3(float.Parse(tb[i * 3].Text), float.Parse(tb[i * 3 + 1].Text), float.Parse(tb[i * 3 + 2].Text));
                }
                parent.setBasis(BaseVect);
                button2_Click(sender, e);
            }
            catch
            { }
        }

        private void HypercubeForm_FormClosed(object sender, FormClosedEventArgs e)
        {
            parent.hasChilds = false;
        }
    }
}
