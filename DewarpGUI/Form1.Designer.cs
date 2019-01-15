namespace DewarpGUI
{
    partial class Form1
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
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.label1 = new System.Windows.Forms.Label();
            this.clientIP = new System.Windows.Forms.TextBox();
            this.clientPort = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.clientUserID = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.clientPassword = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.clientCH = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.clientStreamType = new System.Windows.Forms.TextBox();
            this.clientDeviceType = new System.Windows.Forms.ComboBox();
            this.label7 = new System.Windows.Forms.Label();
            this.button1 = new System.Windows.Forms.Button();
            this.panel1 = new System.Windows.Forms.Panel();
            this.srcCam = new System.Windows.Forms.Panel();
            this.tableLayoutPanel1.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.panel1.SuspendLayout();
            this.SuspendLayout();
            // 
            // tableLayoutPanel1
            // 
            this.tableLayoutPanel1.ColumnCount = 2;
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 300F));
            this.tableLayoutPanel1.Controls.Add(this.groupBox1, 1, 0);
            this.tableLayoutPanel1.Controls.Add(this.panel1, 0, 0);
            this.tableLayoutPanel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel1.Location = new System.Drawing.Point(0, 0);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.RowCount = 1;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel1.Size = new System.Drawing.Size(1040, 669);
            this.tableLayoutPanel1.TabIndex = 0;
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.button1);
            this.groupBox1.Controls.Add(this.label7);
            this.groupBox1.Controls.Add(this.clientDeviceType);
            this.groupBox1.Controls.Add(this.clientStreamType);
            this.groupBox1.Controls.Add(this.label6);
            this.groupBox1.Controls.Add(this.clientCH);
            this.groupBox1.Controls.Add(this.label5);
            this.groupBox1.Controls.Add(this.clientPassword);
            this.groupBox1.Controls.Add(this.label4);
            this.groupBox1.Controls.Add(this.clientUserID);
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Controls.Add(this.clientPort);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.clientIP);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Dock = System.Windows.Forms.DockStyle.Top;
            this.groupBox1.Location = new System.Drawing.Point(743, 3);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(294, 327);
            this.groupBox1.TabIndex = 1;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "groupBox1";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(57, 33);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(17, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "IP";
            // 
            // clientIP
            // 
            this.clientIP.Location = new System.Drawing.Point(93, 29);
            this.clientIP.Name = "clientIP";
            this.clientIP.Size = new System.Drawing.Size(146, 20);
            this.clientIP.TabIndex = 1;
            // 
            // clientPort
            // 
            this.clientPort.Location = new System.Drawing.Point(93, 64);
            this.clientPort.Name = "clientPort";
            this.clientPort.Size = new System.Drawing.Size(146, 20);
            this.clientPort.TabIndex = 3;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(57, 68);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(26, 13);
            this.label2.TabIndex = 2;
            this.label2.Text = "Port";
            // 
            // clientUserID
            // 
            this.clientUserID.Location = new System.Drawing.Point(92, 100);
            this.clientUserID.Name = "clientUserID";
            this.clientUserID.Size = new System.Drawing.Size(146, 20);
            this.clientUserID.TabIndex = 5;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(54, 103);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(29, 13);
            this.label3.TabIndex = 4;
            this.label3.Text = "User";
            // 
            // clientPassword
            // 
            this.clientPassword.Location = new System.Drawing.Point(92, 137);
            this.clientPassword.Name = "clientPassword";
            this.clientPassword.Size = new System.Drawing.Size(146, 20);
            this.clientPassword.TabIndex = 7;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(33, 140);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(53, 13);
            this.label4.TabIndex = 6;
            this.label4.Text = "Password";
            // 
            // clientCH
            // 
            this.clientCH.Location = new System.Drawing.Point(92, 174);
            this.clientCH.Name = "clientCH";
            this.clientCH.Size = new System.Drawing.Size(146, 20);
            this.clientCH.TabIndex = 9;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(57, 177);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(22, 13);
            this.label5.TabIndex = 8;
            this.label5.Text = "CH";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(19, 215);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(67, 13);
            this.label6.TabIndex = 10;
            this.label6.Text = "Stream Type";
            // 
            // clientStreamType
            // 
            this.clientStreamType.Location = new System.Drawing.Point(92, 212);
            this.clientStreamType.Name = "clientStreamType";
            this.clientStreamType.Size = new System.Drawing.Size(146, 20);
            this.clientStreamType.TabIndex = 11;
            // 
            // clientDeviceType
            // 
            this.clientDeviceType.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.clientDeviceType.FormattingEnabled = true;
            this.clientDeviceType.Items.AddRange(new object[] {
            "IPCAM",
            "NVR"});
            this.clientDeviceType.Location = new System.Drawing.Point(92, 249);
            this.clientDeviceType.Name = "clientDeviceType";
            this.clientDeviceType.Size = new System.Drawing.Size(146, 21);
            this.clientDeviceType.TabIndex = 12;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(19, 253);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(68, 13);
            this.label7.TabIndex = 13;
            this.label7.Text = "Device Type";
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(93, 286);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 23);
            this.button1.TabIndex = 14;
            this.button1.Text = "Login";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.OnLogInOut);
            // 
            // panel1
            // 
            this.panel1.Controls.Add(this.srcCam);
            this.panel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel1.Location = new System.Drawing.Point(3, 3);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(734, 663);
            this.panel1.TabIndex = 2;
            // 
            // srcCam
            // 
            this.srcCam.Location = new System.Drawing.Point(9, 9);
            this.srcCam.Name = "srcCam";
            this.srcCam.Size = new System.Drawing.Size(722, 645);
            this.srcCam.TabIndex = 1;
            this.srcCam.Resize += new System.EventHandler(this.OnResize);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1040, 669);
            this.Controls.Add(this.tableLayoutPanel1);
            this.Name = "Form1";
            this.Text = "Form1";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.OnFormClose);
            this.Load += new System.EventHandler(this.OnFormLoad);
            this.Resize += new System.EventHandler(this.OnResize);
            this.tableLayoutPanel1.ResumeLayout(false);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.panel1.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.ComboBox clientDeviceType;
        private System.Windows.Forms.TextBox clientStreamType;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.TextBox clientCH;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TextBox clientPassword;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox clientUserID;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox clientPort;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox clientIP;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Panel srcCam;
    }
}

