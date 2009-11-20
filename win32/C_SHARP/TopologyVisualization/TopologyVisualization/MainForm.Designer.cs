namespace TopologyVisualization
{
    partial class MainForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.визуализироватьToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.гиперкубToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.кубантToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.строкойToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.изФайлаToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.параметрыToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.общиеToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.цвToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.вершиныToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.визуализироватьToolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.задатьToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.изФайлаToolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.выкинутьToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.задатьКодомToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.задатьИзФайлаToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.покраситьToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.задатьКодомToolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.визуализироватьToolStripMenuItem,
            this.параметрыToolStripMenuItem,
            this.вершиныToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(292, 24);
            this.menuStrip1.TabIndex = 0;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // визуализироватьToolStripMenuItem
            // 
            this.визуализироватьToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.гиперкубToolStripMenuItem,
            this.кубантToolStripMenuItem});
            this.визуализироватьToolStripMenuItem.Name = "визуализироватьToolStripMenuItem";
            this.визуализироватьToolStripMenuItem.Size = new System.Drawing.Size(107, 20);
            this.визуализироватьToolStripMenuItem.Text = "Визуализировать";
            // 
            // гиперкубToolStripMenuItem
            // 
            this.гиперкубToolStripMenuItem.Name = "гиперкубToolStripMenuItem";
            this.гиперкубToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.гиперкубToolStripMenuItem.Text = "Гиперкуб";
            this.гиперкубToolStripMenuItem.Click += new System.EventHandler(this.гиперкубToolStripMenuItem_Click);
            // 
            // кубантToolStripMenuItem
            // 
            this.кубантToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.строкойToolStripMenuItem,
            this.изФайлаToolStripMenuItem});
            this.кубантToolStripMenuItem.Name = "кубантToolStripMenuItem";
            this.кубантToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.кубантToolStripMenuItem.Text = "Кубант";
            // 
            // строкойToolStripMenuItem
            // 
            this.строкойToolStripMenuItem.Name = "строкойToolStripMenuItem";
            this.строкойToolStripMenuItem.Size = new System.Drawing.Size(132, 22);
            this.строкойToolStripMenuItem.Text = "Строкой";
            this.строкойToolStripMenuItem.Click += new System.EventHandler(this.строкойToolStripMenuItem_Click);
            // 
            // изФайлаToolStripMenuItem
            // 
            this.изФайлаToolStripMenuItem.Name = "изФайлаToolStripMenuItem";
            this.изФайлаToolStripMenuItem.Size = new System.Drawing.Size(132, 22);
            this.изФайлаToolStripMenuItem.Text = "Из файла";
            this.изФайлаToolStripMenuItem.Click += new System.EventHandler(this.изФайлаToolStripMenuItem_Click);
            // 
            // параметрыToolStripMenuItem
            // 
            this.параметрыToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.общиеToolStripMenuItem,
            this.цвToolStripMenuItem});
            this.параметрыToolStripMenuItem.Name = "параметрыToolStripMenuItem";
            this.параметрыToolStripMenuItem.Size = new System.Drawing.Size(76, 20);
            this.параметрыToolStripMenuItem.Text = "Параметры";
            // 
            // общиеToolStripMenuItem
            // 
            this.общиеToolStripMenuItem.Name = "общиеToolStripMenuItem";
            this.общиеToolStripMenuItem.Size = new System.Drawing.Size(128, 22);
            this.общиеToolStripMenuItem.Text = "Размеры";
            this.общиеToolStripMenuItem.Click += new System.EventHandler(this.общиеToolStripMenuItem_Click);
            // 
            // цвToolStripMenuItem
            // 
            this.цвToolStripMenuItem.Name = "цвToolStripMenuItem";
            this.цвToolStripMenuItem.Size = new System.Drawing.Size(128, 22);
            this.цвToolStripMenuItem.Text = "Цвета";
            this.цвToolStripMenuItem.Click += new System.EventHandler(this.цвToolStripMenuItem_Click);
            // 
            // вершиныToolStripMenuItem
            // 
            this.вершиныToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.визуализироватьToolStripMenuItem1,
            this.выкинутьToolStripMenuItem,
            this.покраситьToolStripMenuItem});
            this.вершиныToolStripMenuItem.Name = "вершиныToolStripMenuItem";
            this.вершиныToolStripMenuItem.Size = new System.Drawing.Size(65, 20);
            this.вершиныToolStripMenuItem.Text = "Вершины";
            // 
            // визуализироватьToolStripMenuItem1
            // 
            this.визуализироватьToolStripMenuItem1.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.задатьToolStripMenuItem,
            this.изФайлаToolStripMenuItem1});
            this.визуализироватьToolStripMenuItem1.Name = "визуализироватьToolStripMenuItem1";
            this.визуализироватьToolStripMenuItem1.Size = new System.Drawing.Size(173, 22);
            this.визуализироватьToolStripMenuItem1.Text = "Визуализировать";
            // 
            // задатьToolStripMenuItem
            // 
            this.задатьToolStripMenuItem.Name = "задатьToolStripMenuItem";
            this.задатьToolStripMenuItem.Size = new System.Drawing.Size(171, 22);
            this.задатьToolStripMenuItem.Text = "Задать кодом";
            this.задатьToolStripMenuItem.Click += new System.EventHandler(this.задатьToolStripMenuItem_Click);
            // 
            // изФайлаToolStripMenuItem1
            // 
            this.изФайлаToolStripMenuItem1.Name = "изФайлаToolStripMenuItem1";
            this.изФайлаToolStripMenuItem1.Size = new System.Drawing.Size(171, 22);
            this.изФайлаToolStripMenuItem1.Text = "Задать из файла";
            this.изФайлаToolStripMenuItem1.Click += new System.EventHandler(this.изФайлаToolStripMenuItem1_Click);
            // 
            // выкинутьToolStripMenuItem
            // 
            this.выкинутьToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.задатьКодомToolStripMenuItem,
            this.задатьИзФайлаToolStripMenuItem});
            this.выкинутьToolStripMenuItem.Name = "выкинутьToolStripMenuItem";
            this.выкинутьToolStripMenuItem.Size = new System.Drawing.Size(173, 22);
            this.выкинутьToolStripMenuItem.Text = "Выкинуть";
            // 
            // задатьКодомToolStripMenuItem
            // 
            this.задатьКодомToolStripMenuItem.Name = "задатьКодомToolStripMenuItem";
            this.задатьКодомToolStripMenuItem.Size = new System.Drawing.Size(171, 22);
            this.задатьКодомToolStripMenuItem.Text = "Задать кодом";
            this.задатьКодомToolStripMenuItem.Click += new System.EventHandler(this.задатьКодомToolStripMenuItem_Click);
            // 
            // задатьИзФайлаToolStripMenuItem
            // 
            this.задатьИзФайлаToolStripMenuItem.Name = "задатьИзФайлаToolStripMenuItem";
            this.задатьИзФайлаToolStripMenuItem.Size = new System.Drawing.Size(171, 22);
            this.задатьИзФайлаToolStripMenuItem.Text = "Задать из файла";
            this.задатьИзФайлаToolStripMenuItem.Click += new System.EventHandler(this.задатьИзФайлаToolStripMenuItem_Click);
            // 
            // покраситьToolStripMenuItem
            // 
            this.покраситьToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.задатьКодомToolStripMenuItem1});
            this.покраситьToolStripMenuItem.Name = "покраситьToolStripMenuItem";
            this.покраситьToolStripMenuItem.Size = new System.Drawing.Size(173, 22);
            this.покраситьToolStripMenuItem.Text = "Покрасить";
            // 
            // задатьКодомToolStripMenuItem1
            // 
            this.задатьКодомToolStripMenuItem1.Name = "задатьКодомToolStripMenuItem1";
            this.задатьКодомToolStripMenuItem1.Size = new System.Drawing.Size(156, 22);
            this.задатьКодомToolStripMenuItem1.Text = "Задать кодом";
            this.задатьКодомToolStripMenuItem1.Click += new System.EventHandler(this.задатьКодомToolStripMenuItem1_Click);
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(292, 266);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "MainForm";
            this.Text = "Hypercybe visualization";
            this.Load += new System.EventHandler(this.MainForm_Load);
            this.Paint += new System.Windows.Forms.PaintEventHandler(this.MainForm_Paint);
            this.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.MainForm_KeyPress);
            this.MouseMove += new System.Windows.Forms.MouseEventHandler(this.MainForm_MouseMove);
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem визуализироватьToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem параметрыToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem общиеToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem цвToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem гиперкубToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem кубантToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem строкойToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem изФайлаToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem вершиныToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem визуализироватьToolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem задатьToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem изФайлаToolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem выкинутьToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem задатьКодомToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem задатьИзФайлаToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem покраситьToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem задатьКодомToolStripMenuItem1;
    }
}

