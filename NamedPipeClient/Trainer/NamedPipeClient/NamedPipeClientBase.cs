using System;
using System.IO.Pipes;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using UnityEngine;

namespace mrBump.Trainer
{
    public static partial class NamedPipeClient
    {
        public const string pipename = "WalkingZombie2";

        private static NamedPipeClientStream PipeClient;
        private static Thread PipeThread;

        private static int bytesRead = 0;

        [DllImport("kernel32")]
        static extern bool AllocConsole(int pid);

        public static bool Setup()
        {
            AllocConsole(-1);
            var stdout = Console.OpenStandardOutput();
            var sw = new System.IO.StreamWriter(stdout, Encoding.Default)
            {
                AutoFlush = true
            };
            Console.SetOut(sw);
            Console.SetError(sw);

            PipeClient = new NamedPipeClientStream(pipename);

            try
            {
                Debug.Log("Connecting to server pipe " + pipename);
                PipeClient.Connect(10000);
            }
            catch (Exception e)
            {
                Debug.Log("[NamedPipeClientStream.Connect] " + e.ToString());
                return false;
            }

            PipeThread = new Thread(new ThreadStart(UpdateThreadFunc));
            PipeThread.Start();

            return true;
        }

        public static void Unload()
        {
            PipeThread.Abort();

            try
            {
                Debug.Log("Closing pipe");
                PipeClient.Close();
            }
            catch (Exception e)
            {
                Debug.Log("[Stream.Close] " + e.ToString());
            }
        }

        public static bool ReadPipe(out byte[] buf, int buf_size)
        {
            buf = new byte[buf_size];
            bytesRead = PipeClient.Read(buf, 0, buf_size);
            Console.WriteLine("[NamedPipeClient.ReadPipe] Read {0} bytes", bytesRead);

            if (bytesRead == buf_size)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        // Convert byte[] to struct
        // For single value, use BitConverter
        private static T Deserialize<T>(byte[] raw_data, int raw_size)
        {
            if (raw_size > raw_data.Length)
            {
                Debug.Log("[Deserialize] raw_size > rawdatas.Length");
                return default;
            }

            GCHandle handle = GCHandle.Alloc(raw_data, GCHandleType.Pinned);
            IntPtr buffer = handle.AddrOfPinnedObject();
            object retobj = Marshal.PtrToStructure(buffer, typeof(T));
            handle.Free();

            return (T)retobj;
        }

        private static byte[] Serialize(object obj, int rawsize)
        {
            var rv = new byte[rawsize];

            // Allocates memory from the unmanaged memory of the process.
            IntPtr ptr = Marshal.AllocHGlobal(rawsize);

            // Marshals data from a managed object to an unmanaged block of memory.
            Marshal.StructureToPtr(obj, ptr, true);

            // Copies data from an unmanaged memory pointer to a managed 8-bit unsigned integer array.
            Marshal.Copy(ptr, rv, 0, rawsize);

            // Frees memory previously allocated from the unmanaged memory of the process.
            Marshal.FreeHGlobal(ptr);

            return rv;
        }
    }
}
