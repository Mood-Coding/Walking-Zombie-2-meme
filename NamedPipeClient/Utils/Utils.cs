#define DEBUG_UNITY_DLL

using System;
using UnityEngine;

namespace mrBump
{
    public static class Utils
    {
        // Searches the source for the first character that matches any of the characters specified in chars
        public static int FindFirstOf(this string source, string chars, int pos = 0)
        {
            if (source == null) throw new ArgumentNullException("source");
            if (chars == null) throw new ArgumentNullException("chars");
            if (source.Length == 0) return -1;
            if (chars.Length == 0) return -1;

            for (int i = pos; i < source.Length; ++i)
            {
                if (chars.IndexOf(source[i]) != -1)
                {
                    return i;
                }
            }

            return -1;
        }

        // Searches the source for the first character that does not match any of the characters specified in chars.
        public static int FindFirstNotOf(this string source, string chars, int pos = 0)
        {
            if (source == null) throw new ArgumentNullException("source");
            if (chars == null) throw new ArgumentNullException("chars");
            if (source.Length == 0) return -1;
            if (chars.Length == 0) return -1;

            for (int i = pos; i < source.Length; ++i)
            {
                if (chars.IndexOf(source[i]) == -1)
                {
                    return i;
                }
            }

            return -1;
        }

        public static void Log(object format, params object[] args)
        {
#if DEBUG_UNITY_DLL
            if (args is null)
            {
                Debug.Log(format.ToString());
            }
            else
            {
                Debug.Log(string.Format(format.ToString(), args));
            }
#else
            if (args is null)
            {
                Debug.Log(format.ToString());
            }
            else
            {
                Debug.Log(string.Format(format.ToString(), args));       
            }
#endif
        }
    }
}
