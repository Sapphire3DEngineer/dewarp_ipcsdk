using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.IO;
using Microsoft.Win32;

namespace DewarpGUI
{
   
    public partial class Form1 : Form
    {
        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.None)]
        public struct sClientInfo
        {
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 128)]
            public char[] host;
            public int port;
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
            public char[] username;

            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
            public char[] password;
            public byte model;                         //device type. must be 0
            public int channel;                        //must be 0
            public int streamtype;                 //stream type. 0 main stream 1 second stream
            public IntPtr hwnd;							//handle is used to play
        }
        public int logId=-1;
        public int playId=-1;
        public Form1()
        {
            this.logId = -1;
            InitializeComponent();

            clientIP.Text = "96.71.29.17";
            clientPort.Text = "1029";
            clientUserID.Text = "admin";
            clientPassword.Text = "admin1234";
            clientCH.Text = "1";
            clientStreamType.Text = "1"; //1 second
            clientDeviceType.SelectedIndex = 0;

        }

        private void OnFormLoad(object sender, EventArgs e)
        {
            NativeMethods.IPC_StartUp();
        }

        private void OnLogInOut(object sender, EventArgs e)
        {
            
            sClientInfo clientinfo = new sClientInfo();

            clientinfo.host = new char[128];
            Array.Clear(clientinfo.host, 0, 128);
            string host = clientIP.Text;
            host.CopyTo(0, clientinfo.host, 0, host.Length);

            int.TryParse(clientPort.Text, out clientinfo.port);

            clientinfo.username = new char[32];
            Array.Clear(clientinfo.username, 0, 32);
            string username = clientUserID.Text;
            username.CopyTo(0, clientinfo.username, 0, username.Length);

            clientinfo.password = new char[32];
            Array.Clear(clientinfo.password, 0, 32);
            string password = clientPassword.Text;
            password.CopyTo(0, clientinfo.password, 0, password.Length);

            int.TryParse(clientCH.Text, out clientinfo.channel);
            int.TryParse(clientStreamType.Text, out clientinfo.streamtype);

            clientinfo.channel = 1;
            clientinfo.streamtype = 0;
            clientinfo.model = (byte)clientDeviceType.SelectedIndex;

            clientinfo.hwnd = srcCam.Handle;

            IntPtr pPreset = Marshal.AllocHGlobal(Marshal.SizeOf(clientinfo));

            Marshal.StructureToPtr(clientinfo, pPreset, false);

            this.logId= NativeMethods.IPC_Login(pPreset);

            Marshal.FreeHGlobal(pPreset);

            if (this.logId == -1) MessageBox.Show("Login Fail");
            else
            {
                this.playId = NativeMethods.IPC_ClientPlay(this.logId, srcCam.Handle);
                MessageBox.Show("Login Success");
            }
               
            
        }

        private void OnFormClose(object sender, FormClosedEventArgs e)
        {
            if(this.logId>0)
            {
                NativeMethods.IPC_Logout(this.logId);
            }
        }

        private void OnResize(object sender, EventArgs e)
        {
            if(this.playId>0)
            {
                NativeMethods.IPC_ClientRefreshWnd(this.playId);
            }
        }
    }
}
