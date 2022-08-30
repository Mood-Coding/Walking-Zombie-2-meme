using System;
using System.Runtime.InteropServices;
using System.Threading;

namespace mrBump.Trainer
{
    public static partial class NamedPipeClient
    {
        private static EventId RequestEventId = EventId.NONE;

        public static void UpdateThreadFunc()
        {
            bool isRunning = true;

            while (isRunning)
            {
                byte[] buf;

                switch (RequestEventId)
                {
                    case EventId.NONE:
                        // Receive EventID sent from Server
                        if (ReadPipe(out buf, sizeof(EventId)))
                        {
                            RequestEventId = (EventId)BitConverter.ToInt32(buf, 0);
                            Console.WriteLine("[PipeClient.UpdateThreadFunc] Receive event: {0}", RequestEventId.ToString());
                        }
                        else
                        {
                            isRunning = false;
                        }
                        break;

                    case EventId.SEND_CONFIG:
                        if (ReadPipe(out buf, Marshal.SizeOf<RequestSetConfigEvent>()))
                        {
                            SetConfigEvent = Deserialize<RequestSetConfigEvent>(buf, Marshal.SizeOf<RequestSetConfigEvent>());

                            string config = new string(SetConfigEvent.Config);
                            string value = new string(SetConfigEvent.Value);
                            Console.WriteLine("[PipeClient.UpdateThreadFunc] Receive config: " + config + " : " + value);
                            Configuration.SetConfigValue(config, value);

                            ResetRequestEventId();
                        }
                        break;
                }

                Thread.Sleep(1);
            }

            Loader.Unload();
        }

        private enum EventId
        {
            NONE = 0x1,

            SEND_CONFIG,
        };

        private static void ResetRequestEventId()
        {
            RequestEventId = EventId.NONE;
        }

        [StructLayout(LayoutKind.Sequential, Pack = 1, CharSet = CharSet.Ansi)]
        private struct RequestSetConfigEvent
        {
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 128)]
            public char[] Config;
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
            public char[] Value;
        };

        private static RequestSetConfigEvent SetConfigEvent = new RequestSetConfigEvent()
        {
            Config = new char[128],
            Value = new char[64]
        };
    }
}
