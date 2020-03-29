using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Security.Cryptography;

namespace WebAPI
{
    public class Tools
    {
        public static string CalculateMD5(byte[] byteArray)
        {
            using (var md5 = MD5.Create())
            {
                using (var stream = new MemoryStream(byteArray))
                {
                    var hash = md5.ComputeHash(stream);
                    return BitConverter.ToString(hash).Replace("-", "").ToLowerInvariant();
                }
            }
        }

        public static string BytesToString(byte[] buffer)
        {
            string str = "";
            for (int i = 0; i < buffer.Length; i++) str += buffer[i].ToString();
            return str;
        }

        public static string BytesToHexString(byte[] buffer)
        {
            string str = "";
            for (int i = 0; i < buffer.Length; i++) str += buffer[i].ToString("X2");
            return str;
        }

        public static byte[] StringToByteArray(string str)
        {
            return Enumerable.Range(0, str.Length).Where(x => x % 2 == 0).Select(x => Convert.ToByte(str.Substring(x, 2), 16)).ToArray();
        }

        public static byte[] StringToWideChar(string str)
        {
            byte[] buffer = new byte[(str.Length * 2) + 2];
            int index = 1;
            buffer[0] = 0;
            foreach (char c in str)
            {
                buffer[index] = Convert.ToByte(c);
                index += 2;
            }
            return buffer;
        }

        public static string WideCharToString(byte[] buffer)
        {
            string str = null;
            for (int i = 1; i < buffer.Length; i += 2)
            {
                if (buffer[i] == 0) return str;
                str += Convert.ToChar(buffer[i]);
            }
            return str;
        }

        public static bool CompareBytes(byte[] buffer, byte[] buffer2)
        {
            if (buffer.Length != buffer2.Length) return false;
            for (int i = 0; i < buffer.Length; i++)
            {
                if (buffer[i] != buffer2[i]) return false;
            }
            return true;
        }

        public static int RandomInt(int min, int max)
        {
            Random random = new Random();
            return random.Next(min, max);
        }

        public static byte[] CSHA(byte[] data)
        {
            SHA1Managed SHA1 = new SHA1Managed();
            return SHA1.ComputeHash(data);
        }

        public static byte[] CSHA(byte[] data, byte[] data2)
        {
            int totalsize = data.Length + data2.Length;
            byte[] buffer = new byte[totalsize];
            SHA1Managed SHA1 = new SHA1Managed();
            return SHA1.ComputeHash(buffer);
        }

        private static void Swap(byte[] s, int i, int j)
        {
            byte c = s[i];
            s[i] = s[j];
            s[j] = c;
        }

        private static byte[] RC4Initalize(byte[] key)
        {
            byte[] s = Enumerable.Range(0, 256).Select(i => (byte)i).ToArray();
            for (int i = 0, j = 0; i < 256; i++)
            {
                j = (j + key[i % key.Length] + s[i]) & 255;
                Swap(s, i, j);
            }
            return s;
        }

        private static IEnumerable<byte> RC4Output(byte[] key, IEnumerable<byte> data)
        {
            byte[] s = RC4Initalize(key);
            int i = 0, j = 0;
            return data.Select((b) =>
            {
                i = (i + 1) & 255;
                j = (j + s[i]) & 255;
                Swap(s, i, j);
                return (byte)(b ^ s[(s[i] + s[j]) & 255]);
            });
        }

        public static byte[] CRC4(byte[] key, byte[] data)
        {
            return RC4Output(key, data).ToArray();
        }

        public static void AppendText(string str, ConsoleColor color)
        {
            Console.ForegroundColor = color;
            string time = string.Format("{0:hh:mm:ss tt}", DateTime.Now.ToUniversalTime().ToLocalTime());
            Console.WriteLine(string.Concat(new object[] { "[", time, "]", " ", str }));
            File.AppendAllText("bin/Server.log", string.Concat(new object[] { "[", time, "]", " ", str }) + Environment.NewLine);
        }
    }
}
