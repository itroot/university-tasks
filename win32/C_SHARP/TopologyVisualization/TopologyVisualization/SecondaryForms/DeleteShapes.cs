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
    public partial class DeleteShapes : Form
    {
        MainForm parent;

        public DeleteShapes(object Parent)
        {
            parent = (MainForm)Parent;
            InitializeComponent();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            Close();
            Dispose();
        }

        private void DeleteShapes_FormClosed(object sender, FormClosedEventArgs e)
        {
            parent.hasChilds = false;
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
            MainForm.cube.Delete(codes);
            Close();
            Dispose();
        }
    }
}
