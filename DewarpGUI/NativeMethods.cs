using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace DewarpGUI
{
    class NativeMethods
    {
        public enum ProcessingErrorCode
        {
            PROCESSING_SUCCESS = 0,
            PROCESSING_ERROR_GENERAL = 1,
            PROCESSING_ERROR_BADIMAGE = 2,
            PROCESSING_ERROR_GPUMEMORYOUT = 3,
            PROCESSING_ERROR_BIGIMAGE = 4,
        };

        [DllImport("Processor.dll")]
        public static extern ProcessingErrorCode IPC_StartUp();

        [DllImport("Processor.dll")]
        public static extern ProcessingErrorCode IPC_CleanUp();

        [DllImport("Processor.dll")]
        public static extern int IPC_Login([In] IntPtr pParameters);

        [DllImport("Processor.dll")]
        public static extern ProcessingErrorCode IPC_Logout(int id);

        [DllImport("Processor.dll")]
        public static extern ProcessingErrorCode IPC_ClientRefreshWnd(int id);

        [DllImport("Processor.dll")]
        public static extern ProcessingErrorCode IPC_ClientSetWnd(int id, [In] IntPtr hwnd);

        [DllImport("Processor.dll")]
        public static extern int IPC_ClientPlay(int id, [In] IntPtr hwnd);
    }
}
