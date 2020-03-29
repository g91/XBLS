using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net.Sockets;
using System.Threading;
using System.Net;
using System.IO;
using System.Security.Cryptography;
using System.Runtime.InteropServices;

namespace WebAPI
{
    class Hex
    {
        private readonly byte[] _bytes;
        private readonly int _bytesPerLine;
        private readonly bool _showHeader;
        private readonly bool _showOffset;
        private readonly bool _showAscii;

        private readonly int _length;

        private int _index;
        private readonly StringBuilder _sb = new StringBuilder();

        private Hex(byte[] bytes, int bytesPerLine, bool showHeader, bool showOffset, bool showAscii)
        {
            _bytes = bytes;
            _bytesPerLine = bytesPerLine;
            _showHeader = showHeader;
            _showOffset = showOffset;
            _showAscii = showAscii;
            _length = bytes.Length;
        }

        public static string Dump(byte[] bytes, int bytesPerLine = 16, bool showHeader = true, bool showOffset = true, bool showAscii = true)
        {
            if (bytes == null)
            {
                return "<null>";
            }
            return (new Hex(bytes, bytesPerLine, showHeader, showOffset, showAscii)).Dump();
        }

        private string Dump()
        {
            if (_showHeader)
            {
                WriteHeader();
            }
            WriteBody();
            return _sb.ToString();
        }

        private void WriteHeader()
        {
            if (_showOffset)
            {
                _sb.Append("Offset(h)  ");
            }
            for (int i = 0; i < _bytesPerLine; i++)
            {
                _sb.Append($"{i & 0xFF:X2}");
                if (i + 1 < _bytesPerLine)
                {
                    _sb.Append(" ");
                }
            }
            _sb.AppendLine();
        }

        private void WriteBody()
        {
            while (_index < _length)
            {
                if (_index % _bytesPerLine == 0)
                {
                    if (_index > 0)
                    {
                        if (_showAscii)
                        {
                            WriteAscii();
                        }
                        _sb.AppendLine();
                    }

                    if (_showOffset)
                    {
                        WriteOffset();
                    }
                }

                WriteByte();
                if (_index % _bytesPerLine != 0 && _index < _length)
                {
                    _sb.Append(" ");
                }
            }

            if (_showAscii)
            {
                WriteAscii();
            }
        }

        private void WriteOffset()
        {
            _sb.Append($"{_index:X8}   ");
        }

        private void WriteByte()
        {
            _sb.Append($"{_bytes[_index]:X2}");
            _index++;
        }

        private void WriteAscii()
        {
            int backtrack = ((_index - 1) / _bytesPerLine) * _bytesPerLine;
            int length = _index - backtrack;

            // This is to fill up last string of the dump if it's shorter than _bytesPerLine
            _sb.Append(new string(' ', (_bytesPerLine - length) * 3));

            _sb.Append("   ");
            for (int i = 0; i < length; i++)
            {
                _sb.Append(Translate(_bytes[backtrack + i]));
            }
        }

        private string Translate(byte b)
        {
            return b < 32 ? "." : Encoding.GetEncoding(1252).GetString(new[] { b });
        }
    }

    class Program
    {
        [DllImport("XeRSA.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ComputeRSAOutput(byte[] Key, byte[] clientSession, [Out] byte[] sigOut);

        private static byte[] responseTemplate =
        {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x4E, 0x4E, 0x44, 0x97, 0x00, 0x00, 0xD8, 0x3E,
            0x07, 0x60, 0x00, 0x00, 0xDB, 0x47, 0x21, 0x0E, 0x02, 0x33, 0x89, 0xD3,
            0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x93, 0xB8, 0x32, 0xB1,
            0x92, 0x39, 0x2D, 0xE2, 0x5E, 0x2F, 0xA7, 0x8D, 0xC6, 0x6D, 0x31, 0xB3,
            0xBD, 0x3D, 0x6D, 0x57, 0x1F, 0x93, 0xA6, 0x8C, 0xB8, 0xA8, 0xA2, 0xDB,
            0xF6, 0x3C, 0x22, 0x4D, 0xD7, 0x11, 0x1B, 0xC8, 0xE3, 0x55, 0xA0, 0x03,
            0x4A, 0xC9, 0x43, 0x55, 0xFE, 0x9A, 0x9F, 0x58, 0xF0, 0x35, 0x22, 0x1B,
            0x5E, 0xD9, 0x5E, 0x2B, 0xDB, 0x07, 0xCE, 0x35, 0xD7, 0x68, 0x26, 0x9E,
            0xF5, 0x22, 0x2C, 0xB5, 0xC6, 0x88, 0x00, 0xF3, 0x88, 0xF0, 0x3C, 0x91,
            0xCE, 0x0A, 0x57, 0xD8, 0xD6, 0x8A, 0xB9, 0x0A, 0xCC, 0x5D, 0x4D, 0xA8,
            0xA6, 0x8B, 0x7E, 0x02, 0x4E, 0x1A, 0x65, 0xCD, 0x0F, 0xEA, 0x6A, 0xB4,
            0xA2, 0x8C, 0xA3, 0xB1, 0x65, 0x20, 0xAE, 0x17, 0x76, 0x6C, 0xCA, 0xAF,
            0x59, 0x16, 0x75, 0x41, 0x00, 0x6B, 0xDE, 0x50, 0xCE, 0xD1, 0x82, 0x12,
            0x37, 0xCF, 0xA2, 0x76, 0xA9, 0xF8, 0xB6, 0x4B, 0x66, 0x35, 0xBD, 0x3D,
            0x48, 0x94, 0xCD, 0x1C, 0x06, 0x49, 0x39, 0x57, 0x9B, 0xFD, 0x84, 0xD0,
            0x8A, 0xEE, 0xC5, 0xF9, 0xB9, 0xAE, 0xE3, 0x59, 0xDD, 0x01, 0xFB, 0xC9,
            0x94, 0x73, 0x3C, 0xAF, 0xA9, 0x8D, 0x0E, 0x7F, 0x01, 0xBB, 0x7F, 0xFE,
            0x81, 0xB3, 0x09, 0x87
        };

        private static string BytesToHexString(byte[] Buffer)
        {
            try
            {
                string str = "";
                for (int i = 0; i < Buffer.Length; i++)
                {
                    str = str + Buffer[i].ToString("X2");
                }
                return str;
            }
            catch (Exception ex)
            {
                Console.Write(ex.Message);
            }
            return "";
        }

        private static string HextoDecimal(string number)
        {
            try
            {
                return Convert.ToInt32(number, 16).ToString();
            }
            catch (Exception ex)
            {
                Console.Write(ex.Message);
            }
            return "";
        }

        public static byte[] StringToByteArray(string str)
        {
            return Enumerable.Range(0, str.Length).Where(x => x % 2 == 0).Select(x => Convert.ToByte(str.Substring(x, 2), 16)).ToArray();
        }

        private static int FindEncryptionKey(byte[] clientSession)
        {
            int NumberOfPairs = 6;
            int increment = 0;
            for (int i = 0; i < 0x5; ++i)
            {
                increment += clientSession[i];
                increment = increment % NumberOfPairs;
            }
            return increment;
        }


        //private static byte[] FindSaltFile(byte[] clientHvSalt, int keySelect)
        //{
        //    try
        //    {
        //        byte[] saltDump = new byte[0x40];

        //        if (clientHvSalt == null)
        //            return null;

        //        saltDump = File.ReadAllBytes("Seeds//" + keySelect + "//Salts" + "//" + "0x" + BytesToHexString(clientHvSalt) + ".bin");
        //        return saltDump;
        //    }
        //    catch (Exception ex)
        //    {
        //        Console.Write(ex.Message);
        //    }

        //    return null;
        //}

        private static byte[] FindSaltFile(byte[] clientHvSalt, int keySelect)
        {
            try
            {
                byte[] saltDump = new byte[0x2C];

                if (clientHvSalt == null)
                    return null;

                saltDump = File.ReadAllBytes("bin//data//" + keySelect + "//Salts" + "//" + BytesToHexString(clientHvSalt) + ".bin");
                return saltDump;
            }
            catch (Exception ex)
            {
                Console.Write(ex.Message);
            }

            return null;
        }

        private static byte[] FindECCSalt(byte[] clientHvSalt, int keySelect)
        {
            try
            {
                byte[] saltDump = new byte[0x2C];

                if (clientHvSalt == null)
                    return null;

                saltDump = File.ReadAllBytes("bin//data//" + keySelect + "//MySalts//0x" + BytesToHexString(clientHvSalt) + ".bin");
                return saltDump;
            }
            catch (Exception ex)
            {
                Console.Write(ex.Message);
            }

            return null;
        }

        private static byte[] ComputeECCDigest(byte[] saltChecksum, byte[] HV_DEC, byte[] HV_ENC, byte[] SoC)
        {
            try
            {
                SHA1Managed Hash = new SHA1Managed();
                Hash.TransformBlock(saltChecksum, 0, 2, null, 0);
                Hash.TransformBlock(HV_DEC, 0x34, 0xC, null, 0);
                Hash.TransformBlock(HV_ENC, 0x40, 0x30, null, 0);
                Hash.TransformBlock(HV_DEC, 0x70, 4, null, 0);
                Hash.TransformBlock(HV_DEC, 0x78, 8, null, 0);
                Hash.TransformBlock(SoC, 2, 0x3FE, null, 0);
                Hash.TransformBlock(HV_ENC, 0x100C0, 0x40, null, 0);
                Hash.TransformBlock(HV_ENC, 0x10350, 0x30, null, 0);
                Hash.TransformBlock(SoC, 0x40E, 0x17C, null, 0);
                Hash.TransformBlock(HV_ENC, 0x16280, 0x40, null, 0);
                Hash.TransformBlock(HV_ENC, 0x16EA0, 0x60, null, 0);
                Hash.TransformBlock(SoC, 0x5BC, 0x244, null, 0);
                Hash.TransformBlock(SoC, 0x800, 0x400, null, 0);
                Hash.TransformFinalBlock(SoC, 0xC00, 0x400);

                return Hash.Hash;
            }
            catch (Exception ex)
            {
                Console.Write(ex.Message);
            }

            return null;
        }
        private static byte[] ComputeHvDigest(byte[] HV_DEC, byte[] salt)
        {
            try
            {
                SHA1Managed Hash = new SHA1Managed();

                Hash.TransformBlock(salt, 0, 0x10, null, 0);
                Hash.TransformBlock(HV_DEC, 0x34, 0x40, null, 0);
                Hash.TransformBlock(HV_DEC, 0x78, 0xFF88, null, 0);
                Hash.TransformBlock(HV_DEC, 0x100C0, 0x40, null, 0);
                Hash.TransformBlock(HV_DEC, 0x10350, 0x5F70, null, 0);
                Hash.TransformBlock(HV_DEC, 0x16EA0, 0x9160, null, 0);
                Hash.TransformBlock(HV_DEC, 0x20000, 0xFFFF, null, 0);
                Hash.TransformFinalBlock(HV_DEC, 0x30000, 0xFFFF);

                return Hash.Hash;
            }
            catch (Exception ex)
            {
                Console.Write(ex.Message);
            }

            return null;
        }

        private static byte[] HvSetupShaSaltedHash(byte[] salt, int saltLength, byte[] rsaKey, int rsaKeyLength)
        {
            int num = 0;
            for (int i = 0; i < rsaKeyLength; i += 20)
            {
                int num3 = ((i + 20) > rsaKeyLength) ? (rsaKeyLength - i) : 20;
                byte[] hash = new byte[20];
                SHA1Managed managed = new SHA1Managed();
                managed.TransformBlock(salt, 0, saltLength, null, 0);
                byte[] inputBuffer = new byte[4];
                inputBuffer[3] = (byte)num;
                managed.TransformFinalBlock(inputBuffer, 0, 4);
                hash = managed.Hash;
                for (int j = 0; j < num3; j++)
                {
                    rsaKey[i + j] = (byte)(rsaKey[i + j] ^ hash[j]);
                }
                num++;
            }
            return rsaKey;
        }

        [DllImport("XeRSA.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void RSAEncryptSignature(byte[] input, [Out] byte[] sigOut);

        private static byte[] HvSetupMemEncryptionKey(byte[] memEncSeed, byte[] RandomData)
        {
            byte[] HvData = { 0xDA, 0x39, 0xA3, 0xEE, 0x5E, 0x6B, 0x4B, 0x0D, 0x32, 0x55, 0xBF, 0xEF, 0x95, 0x60, 0x18, 0x90, 0xAF, 0xD8, 0x07, 0x09 };
            byte[] Empty = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
            byte[] memoryRsaKey = new byte[0x80];

            memoryRsaKey[0] = 0;
            Buffer.BlockCopy(RandomData, 0, memoryRsaKey, 1, 0x14);
            Buffer.BlockCopy(HvData, 0, memoryRsaKey, 0x15, 0x14);
            Buffer.BlockCopy(Empty, 0, memoryRsaKey, 0x29, 0x26);

            memoryRsaKey[0x4F] = 1;
            Buffer.BlockCopy(memEncSeed, 0, memoryRsaKey, 0x50, 0x30);

            byte[] tmp = new byte[0x6B];
            Buffer.BlockCopy(memoryRsaKey, 0x15, tmp, 0, 0x6B);
            Buffer.BlockCopy(HvSetupShaSaltedHash(RandomData, 0x14, tmp, 0x6B), 0, memoryRsaKey, 0x15, 0x6B);

            Buffer.BlockCopy(memoryRsaKey, 0x15, tmp, 0, 0x6B);
            Buffer.BlockCopy(HvSetupShaSaltedHash(tmp, 0x6B, RandomData, 0x14), 0, memoryRsaKey, 1, 0x14);

            return memoryRsaKey;
        }

        private static byte[] ComputeRSAOutput2(byte[] clientSession, byte[] memEncSeed)
        {
            try
            {
                byte[] signatureEnc = new byte[0x80];
                byte[] buffer1 = new byte[20];

                buffer1[0x12] = clientSession[04];
                buffer1[0x13] = clientSession[02];
                byte[] dst = buffer1;

                Buffer.BlockCopy(clientSession, 0, dst, 0, 0x10);
                byte[] signatureDec = HvSetupMemEncryptionKey(memEncSeed, dst);
                RSAEncryptSignature(signatureDec, signatureEnc);

                if (signatureEnc.All(singleByte => singleByte == 0) || signatureEnc == signatureDec)
                    throw new Exception("Could not calculate signature!");

                Console.WriteLine("Signature [XeRSA.dll]: \n{0}", BytesToHexString(signatureEnc));
                return signatureEnc;

            }
            catch (Exception exception1)
            {
                Console.Write(exception1.Message);
            }
            return null;
        }

        public static string XKEResponse(string[] Url)
        {

            byte[] hvExecAddr = new byte[0x2];
            byte[] HvSalt = new byte[0x10];
            byte[] responseBuff = new byte[0x100];
            byte[] EccDigest = new byte[0x14];
            byte[] HvDigest = new byte[0x06];

            Console.WriteLine("CPUKey: " + Url[3]);
            Console.WriteLine("Salt: " + Url[4]);
            Console.WriteLine("Session: " + Url[5]);
            Console.WriteLine("========================================================");

            byte[] cpuKey = StringToByteArray(Url[3]);
            byte[] salt = StringToByteArray(Url[4]);
            byte[] sessionToken = StringToByteArray(Url[5]);

            // Print some info
            Console.WriteLine("Client CPUKey: {0}", BytesToHexString(cpuKey));
            Console.WriteLine("Client Salt: {0}", BytesToHexString(salt));
            Console.WriteLine("Client Session Token: {0}", BytesToHexString(sessionToken));

            // Select a memory encryption key to use
            int encryptionKeySelect = FindEncryptionKey(sessionToken);
            Console.WriteLine("Client Seed Package: {0}", encryptionKeySelect);

            // Validate the salt & session token
            if (salt != null || sessionToken != null || cpuKey != null)
            {
                // Find the ecc salt & hv executing address from salt
                byte[] saltFile = FindSaltFile(salt, encryptionKeySelect);
                if (saltFile != null)
                {
                    // Copy over data from the salt dump we are using
                    Buffer.BlockCopy(saltFile, 0, HvSalt, 0, 0x10);
                    Buffer.BlockCopy(saltFile, 0x10, EccDigest, 0, 0x14);
                    Buffer.BlockCopy(saltFile, 0x24, hvExecAddr, 0, 0x02);
                    Buffer.BlockCopy(saltFile, 0x26, HvDigest, 0, 0x06);

                    Console.WriteLine("Client hvExecAddr: {0}", BytesToHexString(hvExecAddr));
                    Console.WriteLine("Client HvDigest1: {0}", BytesToHexString(HvDigest));
                    Console.WriteLine("Client EccDigest: {0}", BytesToHexString(EccDigest));


                    // Copy the response template & HV executing address to response buffer
                    Buffer.BlockCopy(responseTemplate, 0, responseBuff, 0, 0x100);
                    Buffer.BlockCopy(hvExecAddr, 0, responseBuff, 0xF8, 0x2);

                    // Find random rsa data to use
                    byte[] memoryKey = File.ReadAllBytes("bin//data//" + encryptionKeySelect + "//Keys.bin");
                    byte[] HV_DEC = File.ReadAllBytes("bin//data//" + encryptionKeySelect + "//HV_DEC.bin");
                    byte[] HV_ENC = File.ReadAllBytes("bin//data//" + encryptionKeySelect + "//HV_ENC.bin");
                    byte[] SoC = File.ReadAllBytes("bin//data//" + encryptionKeySelect + "//Cache.bin");

                    //
                    //byte[] rsaOut = new byte[0x80];
                    //ComputeRSAOutput(memoryKey, sessionToken, rsaOut);
                    //Console.WriteLine("========================================================");
                    //Console.WriteLine("RsaOutBuff1: ");
                    //Console.WriteLine("========================================================");
                    //Console.OutputEncoding = Encoding.GetEncoding(1252);
                    //Console.WriteLine(Hex.Dump(rsaOut));
                    //Console.WriteLine("========================================================");

                    byte[] rsaOut = new byte[0x80];
                    rsaOut = ComputeRSAOutput2(sessionToken, memoryKey);
                    Console.WriteLine("========================================================");
                    Console.WriteLine("RsaOut Buff: ");
                    Console.WriteLine("========================================================");
                    Console.OutputEncoding = Encoding.GetEncoding(1252);
                    Console.WriteLine(Hex.Dump(rsaOut));
                    Console.WriteLine("========================================================");
                    if (rsaOut != null)
                    {
                        // Generate and copy ECC hash & HV hash to the response buffer
                        Buffer.BlockCopy(EccDigest, 0, responseBuff, 0x50, 0x14);
                        Buffer.BlockCopy(HvDigest, 0, responseBuff, 0xFA, 0x06);
                        Buffer.BlockCopy(rsaOut, 0, responseBuff, 0x78, 0x80);

                        //
                        Console.WriteLine("Client EccDigest1: {0}", BytesToHexString(EccDigest));

                        //
                        byte[] ECCSalt = new byte[0x02];
                        byte[] ECCSaltFile = FindECCSalt(HvSalt, encryptionKeySelect);
                        Buffer.BlockCopy(ECCSaltFile, 0x20, ECCSalt, 0x00, 0x02);
        
                        EccDigest = ComputeECCDigest(ECCSalt, HV_DEC, HV_ENC, SoC);
                        Console.WriteLine("Client EccDigest2: {0}", BytesToHexString(EccDigest));
                        //
                        byte[] Full_HvDigest = ComputeHvDigest(HV_DEC, HvSalt);
                        Console.WriteLine("Client HvDigest2: {0}", BytesToHexString(Full_HvDigest));

                        Buffer.BlockCopy(Full_HvDigest, 0x0E, HvDigest, 0, 0x06);
                        Console.WriteLine("Client HvDigest3: {0}", BytesToHexString(HvDigest));

                        Console.WriteLine("========================================================");
                        Console.WriteLine("ResponseBuff: ");
                        Console.WriteLine("========================================================");
                        Console.OutputEncoding = Encoding.GetEncoding(1252);
                        Console.WriteLine(Hex.Dump(responseBuff));
                        Console.WriteLine("========================================================");

                        // Send the response
                        return string.Format("{0}", BytesToHexString(responseBuff));
                    }
                }

            }
            return string.Format("<HTML><BODY>My web page.<br>{0}</BODY></HTML>", DateTime.Now);
        }

        public static string TitleResponse(string[] Url)
        {
            byte[] Title                = new byte[0x04];
            byte[] KVDigest             = new byte[0x14];
            byte[] TitleDigest          = new byte[0x14];
            byte[] spoofedMacAddress    = new byte[0x06];
            byte[] SerialByte           = new byte[0x01];

            Console.WriteLine("Title: " + Url[3]);
            Title               = StringToByteArray(Url[3]);

            Console.WriteLine("KVDigest: " + Url[4]);
            KVDigest            = StringToByteArray(Url[4]);

            Console.WriteLine("spoofedMacAddress: " + Url[5]);
            spoofedMacAddress   = StringToByteArray(Url[5]);

            Console.WriteLine("SerialByte: " + Url[6]);
            SerialByte          = StringToByteArray(Url[6]);
            Console.WriteLine("========================================================");

            int bConsole = 0;    //Xenon
            if (SerialByte[0] <= 0x14 && SerialByte[0] > 0x10)
                bConsole = 1;    //Zephyr
            else if (SerialByte[0] <= 0x18 && SerialByte[0] > 0x14)
                bConsole = 2;    //Falcon
            else if (SerialByte[0] <= 0x52 && SerialByte[0] > 0x18)
                bConsole = 3;    //Jasper
            else if (SerialByte[0] <= 0x58 && SerialByte[0] > 0x52)
                bConsole = 4;    //Trinity
            else if (SerialByte[0] <= 0x70 && SerialByte[0] > 0x58)
                bConsole = 5;    //Corona

            Console.WriteLine("bConsole: " + bConsole);

            byte[] SMCVersion = { 0x12, 0x62, 0x02, 0x05, 0x00 };
            if (bConsole == 0) Buffer.BlockCopy(new byte[] { 0x12, 0x31, 0x01, 0x06, 0x00 }, 0, SMCVersion, 0, 5); //Xenon
            else if (bConsole == 1) Buffer.BlockCopy(new byte[] { 0x12, 0x31, 0x01, 0x06, 0x00 }, 0, SMCVersion, 0, 5); //Zephyr
            else if (bConsole == 2) Buffer.BlockCopy(new byte[] { 0x12, 0x31, 0x01, 0x06, 0x00 }, 0, SMCVersion, 0, 5); //Falcon
            else if (bConsole == 3) Buffer.BlockCopy(new byte[] { 0x12, 0x41, 0x02, 0x03, 0x00 }, 0, SMCVersion, 0, 5); //Jasper
            else if (bConsole == 4) Buffer.BlockCopy(new byte[] { 0x12, 0x51, 0x03, 0x01, 0x00 }, 0, SMCVersion, 0, 5);

            Console.WriteLine("SMCVersion: " + BytesToHexString(SMCVersion));

            byte[] ExecutionID = null;
            byte[] TitleHeader = null;

            if (File.Exists(string.Concat(new object[] { "bin/data/xosc/", BytesToHexString(Title), ".bin" })))
            {
                ExecutionID = File.ReadAllBytes(string.Concat(new object[] { "bin/data/xosc/", BytesToHexString(Title), ".bin" })).Take(0x18).ToArray();
                TitleHeader = File.ReadAllBytes(string.Concat(new object[] { "bin/data/xosc/", BytesToHexString(Title), ".bin" })).Skip(0x18).Take(File.ReadAllBytes(string.Concat(new object[] { "bin/data/xosc/", BytesToHexString(Title), ".bin" })).Length - 0x18).ToArray();
            }
            else
            {
                ExecutionID = File.ReadAllBytes("bin/data/xosc/FFFE07D1.bin").Take(0x18).ToArray();
                TitleHeader = File.ReadAllBytes("bin/data/xosc/FFFE07D1.bin").Skip(0x18).Take(File.ReadAllBytes("bin/data/xosc/FFFE07D1.bin").Length - 0x18).ToArray();
            }

            TitleDigest = KVDigest;
            SHA1Managed SHA1 = new SHA1Managed();
            SHA1.Initialize();
            SHA1.TransformBlock(File.ReadAllBytes("bin/data/xosc/xam.bin"), 0, File.ReadAllBytes("bin/data/xosc/xam.bin").Length, null, 0);
            SHA1.TransformBlock(TitleDigest, 0, 0x14, null, 0);
            SHA1.TransformFinalBlock(Enumerable.Repeat<byte>(0, 0x10).ToArray(), 0, 0x10);
            TitleDigest = SHA1.Hash;
            Console.WriteLine("xam Digest: " + BytesToHexString(TitleDigest));

            SHA1.Initialize();
            SHA1.TransformBlock(File.ReadAllBytes("bin/data/xosc/kernel.bin"), 0, File.ReadAllBytes("bin/data/xosc/kernel.bin").Length, null, 0);
            SHA1.TransformBlock(TitleDigest, 0, 0x14, null, 0);
            SHA1.TransformFinalBlock(spoofedMacAddress, 0, 6);
            TitleDigest = SHA1.Hash;
            Console.WriteLine("kernel Digest: " + BytesToHexString(TitleDigest));

            SHA1.Initialize();
            SHA1.TransformBlock(TitleHeader, 0, TitleHeader.Length, null, 0);
            SHA1.TransformBlock(TitleDigest, 0, 0x14, null, 0);
            SHA1.TransformFinalBlock(SMCVersion, 0, 5);
            TitleDigest = SHA1.Hash;
            Console.WriteLine("Title Digest: " + BytesToHexString(TitleDigest));


            Console.WriteLine("========================================================");
            Console.WriteLine("Title Digest: ");
            Console.WriteLine("========================================================");
            Console.OutputEncoding = Encoding.GetEncoding(1252);
            Console.WriteLine(Hex.Dump(TitleDigest));
            Console.WriteLine("========================================================");

            // Send the response
            return string.Format("{0}", BytesToHexString(TitleDigest));
        }


        public static string FuseDigestResponse(string[] Url)
        {
            byte[] Title = new byte[0x04];
            byte[] KVDigest = new byte[0x14];
            byte[] TitleDigest = new byte[0x14];
            byte[] spoofedMacAddress = new byte[0x06];
            byte[] SerialByte = new byte[0x01];

 
            Console.WriteLine("KVDigest: " + Url[3]);
            KVDigest = StringToByteArray(Url[3]);

            Console.WriteLine("SerialByte: " + Url[4]);
            SerialByte = StringToByteArray(Url[4]);
            Console.WriteLine("========================================================");

            int bConsole = 0;    //Xenon
            if (SerialByte[0] <= 0x14 && SerialByte[0] > 0x10)
                bConsole = 1;    //Zephyr
            else if (SerialByte[0] <= 0x18 && SerialByte[0] > 0x14)
                bConsole = 2;    //Falcon
            else if (SerialByte[0] <= 0x52 && SerialByte[0] > 0x18)
                bConsole = 3;    //Jasper
            else if (SerialByte[0] <= 0x58 && SerialByte[0] > 0x52)
                bConsole = 4;    //Trinity
            else if (SerialByte[0] <= 0x70 && SerialByte[0] > 0x58)
                bConsole = 5;    //Corona

            Console.WriteLine("bConsole: " + bConsole);

            byte[] SMCVersion = { 0x12, 0x62, 0x02, 0x05, 0x00 };
            if (bConsole == 0) Buffer.BlockCopy(new byte[] { 0x12, 0x31, 0x01, 0x06, 0x00 }, 0, SMCVersion, 0, 5); //Xenon
            else if (bConsole == 1) Buffer.BlockCopy(new byte[] { 0x12, 0x31, 0x01, 0x06, 0x00 }, 0, SMCVersion, 0, 5); //Zephyr
            else if (bConsole == 2) Buffer.BlockCopy(new byte[] { 0x12, 0x31, 0x01, 0x06, 0x00 }, 0, SMCVersion, 0, 5); //Falcon
            else if (bConsole == 3) Buffer.BlockCopy(new byte[] { 0x12, 0x41, 0x02, 0x03, 0x00 }, 0, SMCVersion, 0, 5); //Jasper
            else if (bConsole == 4) Buffer.BlockCopy(new byte[] { 0x12, 0x51, 0x03, 0x01, 0x00 }, 0, SMCVersion, 0, 5);
            Console.WriteLine("SMCVersion: " + BytesToHexString(SMCVersion));


            byte[] XenonHash = { 0x02, 0x24, 0xEE, 0xA6, 0x1E, 0x89, 0x8B, 0xA1, 0x55, 0xB5, 0xAF, 0x74, 0xAA, 0x78, 0xAD, 0x0B };
            byte[] FalconHash = { 0x4E, 0xEA, 0xA3, 0x32, 0x3D, 0x9F, 0x40, 0xAA, 0x90, 0xC0, 0x0E, 0xFC, 0x5A, 0xD5, 0xB0, 0x00 };
            byte[] ZephyrHash = { 0x4E, 0xEA, 0xA3, 0x32, 0x3D, 0x9F, 0x40, 0xAA, 0x90, 0xC0, 0x0E, 0xFC, 0x5A, 0xD5, 0xB0, 0x00 };
            byte[] JasperHash = { 0xFF, 0x23, 0x99, 0x90, 0xED, 0x61, 0xD1, 0x54, 0xB2, 0x31, 0x35, 0x99, 0x0D, 0x90, 0xBD, 0xBC };
            byte[] TrinityHash = { 0xDB, 0xE6, 0x35, 0x87, 0x78, 0xCB, 0xFC, 0x2F, 0x52, 0xA3, 0xBA, 0xF8, 0x92, 0x45, 0x8D, 0x65 };
            byte[] CoronaHash = { 0xD1, 0x32, 0xFB, 0x43, 0x9B, 0x48, 0x47, 0xE3, 0x9F, 0xE5, 0x46, 0x46, 0xF0, 0xA9, 0x9E, 0xB1 };

            byte[] FuseDigest = { 0, 0, 0, 0, 0x1E, 0x89, 0x8B, 0xA1, 0x55, 0xB5, 0xAF, 0x74, 0xAA, 0x78, 0xAD, 0x0B };
            if (bConsole == 0) Buffer.BlockCopy(XenonHash, 4, FuseDigest, 4, 0xC);   //Xenon
            else if (bConsole == 1) Buffer.BlockCopy(ZephyrHash, 4, FuseDigest, 4, 0xC);   //Zephyr
            else if (bConsole == 2) Buffer.BlockCopy(FalconHash, 4, FuseDigest, 4, 0xC);   //Falcon
            else if (bConsole == 3) Buffer.BlockCopy(JasperHash, 4, FuseDigest, 4, 0xC);   //Jasper
            else if (bConsole == 4) Buffer.BlockCopy(TrinityHash, 4, FuseDigest, 4, 0xC);   //Trinity
            else if (bConsole == 5) Buffer.BlockCopy(CoronaHash, 4, FuseDigest, 4, 0xC);   //Corona
            Buffer.BlockCopy(KVDigest.Skip(0x10).Take(4).ToArray(), 0, FuseDigest, 0, 0x4);


            Console.WriteLine("========================================================");
            Console.WriteLine("Fuse Digest: ");
            Console.WriteLine("========================================================");
            Console.OutputEncoding = Encoding.GetEncoding(1252);
            Console.WriteLine(Hex.Dump(FuseDigest));
            Console.WriteLine("========================================================");

            // Send the response
            return string.Format("{0}", BytesToHexString(FuseDigest));
        }

        public static string SendXKEResponse(HttpListenerRequest request)
        {
            string[] Url = request.RawUrl.Split('/');
            Console.WriteLine("========================================================");
            Console.WriteLine("Url:" + request.RawUrl);

            if (Url[2] == "XKE")
                return XKEResponse(Url);  

            if (Url[2] == "Title")
                return TitleResponse(Url);

            if (Url[2] == "Fuse")
                return FuseDigestResponse(Url);

            return string.Format("<HTML><BODY>My web page.<br>{0}</BODY></HTML>", DateTime.Now);
        }


        public static string SendXOSCResponse(HttpListenerRequest request)
        {
            byte[] Title = new byte[0x04];
            byte[] cpuKey = new byte[0x10];
            byte[] KVDigest = new byte[0x14];

            byte[] SerialByte = new byte[0x01];

            byte[] ConsoleID = new byte[0x05];
            byte[] spoofedMacAddress = new byte[0x06];
            byte[] OddFeatures = new byte[0x02];   //0x1C,     0x2
            byte[] bPolicyFlashSize = new byte[0x04];   //0x24,     0x4
            byte[] ConsoleSerialNumber = new byte[0x0C];   //0xB0,     0xC
            byte[] GameRegion = new byte[0x02];   //0xC8,     0x2
            byte[] driveIndentifier1 = new byte[0x24];   //0xC8A,    0x24
            byte[] _unk2 = new byte[0x01];   //0xC89,    0x1
            byte[] uCPUKey = new byte[0x10];
            byte[] orgXOSC = new byte[0x2E0];
            byte[] cbInp0 = new byte[0x02];
            byte[] cbInp1 = new byte[0x02];
            byte[] fuseDigest = new byte[0x10];

            int Crl = 0;
            int Fcrt = 0;

            string[] Url = request.RawUrl.Split('/');
            Title = StringToByteArray(Url[2]);
            cpuKey = StringToByteArray(Url[3]);
            KVDigest = StringToByteArray(Url[4]);
            SerialByte = StringToByteArray(Url[5]);
            ConsoleID = StringToByteArray(Url[6]);
            spoofedMacAddress = StringToByteArray(Url[7]);
            OddFeatures = StringToByteArray(Url[8]);
            bPolicyFlashSize = StringToByteArray(Url[9]);
            ConsoleSerialNumber = StringToByteArray(Url[10]);
            GameRegion = StringToByteArray(Url[11]);
            driveIndentifier1 = StringToByteArray(Url[12]);
            _unk2 = StringToByteArray(Url[13]);
            uCPUKey = StringToByteArray(Url[14]);
            cbInp0 = StringToByteArray(Url[15]);
            cbInp1 = StringToByteArray(Url[16]);
            fuseDigest = StringToByteArray(Url[17]);
            Crl = System.Convert.ToInt32(Url[18]);
            Crl = System.Convert.ToInt32(Url[19]);
            orgXOSC = StringToByteArray(Url[20]);

            Console.WriteLine("========================================================");
            Console.WriteLine("-- XOSC");
            Console.WriteLine("Url:" + request.RawUrl);
            Console.WriteLine("Title:" + Title);
            Console.WriteLine("cpuKey:" + cpuKey);
            Console.WriteLine("KVDigest:" + KVDigest);
            Console.WriteLine("KVDigest:" + KVDigest);
            Console.WriteLine("========================================================");
            
            int bConsole = 0;    //Xenon
            if (SerialByte[0] <= 0x14 && SerialByte[0] > 0x10)
                bConsole = 1;    //Zephyr
            else if (SerialByte[0] <= 0x18 && SerialByte[0] > 0x14)
                bConsole = 2;    //Falcon
            else if (SerialByte[0] <= 0x52 && SerialByte[0] > 0x18)
                bConsole = 3;    //Jasper
            else if (SerialByte[0] <= 0x58 && SerialByte[0] > 0x52)
                bConsole = 4;    //Trinity
            else if (SerialByte[0] <= 0x70 && SerialByte[0] > 0x58)
                bConsole = 5;    //Corona

            byte[] XOSC = File.ReadAllBytes("bin/users/" + BytesToHexString(uCPUKey) + "/orgXOSC0.bin");
            EndianIO xoscStream = new EndianIO(XOSC, EndianStyle.BigEndian);
            byte[] ExecutionID = null;
            byte[] TitleHeader = null;

            if (File.Exists(string.Concat(new object[] { "bin/data/xosc/", BytesToHexString(Title), ".bin" })))
            {
                ExecutionID = File.ReadAllBytes(string.Concat(new object[] { "bin/data/xosc/", BytesToHexString(Title), ".bin" })).Take(0x18).ToArray();
                TitleHeader = File.ReadAllBytes(string.Concat(new object[] { "bin/data/xosc/", BytesToHexString(Title), ".bin" })).Skip(0x18).Take(File.ReadAllBytes(string.Concat(new object[] { "bin/data/xosc/", BytesToHexString(Title), ".bin" })).Length - 0x18).ToArray();
            }
            else
            {
                ExecutionID = File.ReadAllBytes("bin/data/xosc/FFFE07D1.bin").Take(0x18).ToArray();
                TitleHeader = File.ReadAllBytes("bin/data/xosc/FFFE07D1.bin").Skip(0x18).Take(File.ReadAllBytes("bin/data/xosc/FFFE07D1.bin").Length - 0x18).ToArray();
            }

            xoscStream.Writer.Seek(0x38);
            xoscStream.Writer.Write(ExecutionID);

            xoscStream.Writer.Seek(0x50);
            byte[] SMCVersion = { 0x12, 0x62, 0x02, 0x05, 0x00 };
            if (bConsole == 0) Buffer.BlockCopy(new byte[] { 0x12, 0x31, 0x01, 0x06, 0x00 }, 0, SMCVersion, 0, 5); //Xenon
            else if (bConsole == 1) Buffer.BlockCopy(new byte[] { 0x12, 0x31, 0x01, 0x06, 0x00 }, 0, SMCVersion, 0, 5); //Zephyr
            else if (bConsole == 2) Buffer.BlockCopy(new byte[] { 0x12, 0x31, 0x01, 0x06, 0x00 }, 0, SMCVersion, 0, 5); //Falcon
            else if (bConsole == 3) Buffer.BlockCopy(new byte[] { 0x12, 0x41, 0x02, 0x03, 0x00 }, 0, SMCVersion, 0, 5); //Jasper
            else if (bConsole == 4) Buffer.BlockCopy(new byte[] { 0x12, 0x51, 0x03, 0x01, 0x00 }, 0, SMCVersion, 0, 5);

            byte[] TitleDigest = KVDigest;
            SHA1Managed SHA1 = new SHA1Managed();
            SHA1.Initialize();
            SHA1.TransformBlock(File.ReadAllBytes("bin/data/xosc/xam.bin"), 0, File.ReadAllBytes("bin/data/xosc/xam.bin").Length, null, 0);
            SHA1.TransformBlock(TitleDigest, 0, 0x14, null, 0);
            SHA1.TransformFinalBlock(Enumerable.Repeat<byte>(0, 0x10).ToArray(), 0, 0x10);
            TitleDigest = SHA1.Hash;

            SHA1.Initialize();
            SHA1.TransformBlock(File.ReadAllBytes("bin/data/xosc/kernel.bin"), 0, File.ReadAllBytes("bin/data/xosc/kernel.bin").Length, null, 0);
            SHA1.TransformBlock(TitleDigest, 0, 0x14, null, 0);
            SHA1.TransformFinalBlock(spoofedMacAddress, 0, 6);
            TitleDigest = SHA1.Hash;

            SHA1.Initialize();
            SHA1.TransformBlock(TitleHeader, 0, TitleHeader.Length, null, 0);
            SHA1.TransformBlock(TitleDigest, 0, 0x14, null, 0);
            SHA1.TransformFinalBlock(SMCVersion, 0, 5);
            TitleDigest = SHA1.Hash;
            xoscStream.Writer.Write(TitleDigest);

            xoscStream.Writer.Seek(0x60);
            byte[] rawData000x10 = {
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                0x00, 0x00, 0x00, 0x00
                            };
            xoscStream.Writer.Write(rawData000x10);

            xoscStream.Writer.Seek(0x70);
            byte[] XenonHash = { 0x02, 0x24, 0xEE, 0xA6, 0x1E, 0x89, 0x8B, 0xA1, 0x55, 0xB5, 0xAF, 0x74, 0xAA, 0x78, 0xAD, 0x0B };
            byte[] FalconHash = { 0x4E, 0xEA, 0xA3, 0x32, 0x3D, 0x9F, 0x40, 0xAA, 0x90, 0xC0, 0x0E, 0xFC, 0x5A, 0xD5, 0xB0, 0x00 };
            byte[] ZephyrHash = { 0x4E, 0xEA, 0xA3, 0x32, 0x3D, 0x9F, 0x40, 0xAA, 0x90, 0xC0, 0x0E, 0xFC, 0x5A, 0xD5, 0xB0, 0x00 };
            byte[] JasperHash = { 0xFF, 0x23, 0x99, 0x90, 0xED, 0x61, 0xD1, 0x54, 0xB2, 0x31, 0x35, 0x99, 0x0D, 0x90, 0xBD, 0xBC };
            byte[] TrinityHash = { 0xDB, 0xE6, 0x35, 0x87, 0x78, 0xCB, 0xFC, 0x2F, 0x52, 0xA3, 0xBA, 0xF8, 0x92, 0x45, 0x8D, 0x65 };
            byte[] CoronaHash = { 0xD1, 0x32, 0xFB, 0x43, 0x9B, 0x48, 0x47, 0xE3, 0x9F, 0xE5, 0x46, 0x46, 0xF0, 0xA9, 0x9E, 0xB1 };

            byte[] FuseDigest = { 0, 0, 0, 0, 0x1E, 0x89, 0x8B, 0xA1, 0x55, 0xB5, 0xAF, 0x74, 0xAA, 0x78, 0xAD, 0x0B };
            if (bConsole == 0) Buffer.BlockCopy(XenonHash, 4, FuseDigest, 4, 0xC);   //Xenon
            else if (bConsole == 1) Buffer.BlockCopy(ZephyrHash, 4, FuseDigest, 4, 0xC);   //Zephyr
            else if (bConsole == 2) Buffer.BlockCopy(FalconHash, 4, FuseDigest, 4, 0xC);   //Falcon
            else if (bConsole == 3) Buffer.BlockCopy(JasperHash, 4, FuseDigest, 4, 0xC);   //Jasper
            else if (bConsole == 4) Buffer.BlockCopy(TrinityHash, 4, FuseDigest, 4, 0xC);   //Trinity
            else if (bConsole == 5) Buffer.BlockCopy(CoronaHash, 4, FuseDigest, 4, 0xC);   //Corona
            Buffer.BlockCopy(KVDigest.Skip(0x10).Take(4).ToArray(), 0, FuseDigest, 0, 0x4);
            xoscStream.Writer.Write(FuseDigest);

            xoscStream.Writer.Seek(0x83);
            xoscStream.Writer.Write(_unk2);

            xoscStream.Writer.Seek(0xF0);
            xoscStream.Writer.Write(driveIndentifier1);

            xoscStream.Writer.Seek(0x114);
            xoscStream.Writer.Write(driveIndentifier1);

            xoscStream.Writer.Seek(0x138);
            xoscStream.Writer.Write(ConsoleSerialNumber);

            xoscStream.Writer.Seek(0x146);
            xoscStream.Writer.Write((ushort)(Fcrt == 1 ? 0xD83E : 0xD81E));

            xoscStream.Writer.Seek(0x148);
            xoscStream.Writer.Write(GameRegion);

            xoscStream.Writer.Seek(0x14A);
            xoscStream.Writer.Write(OddFeatures);

            xoscStream.Writer.Seek(0x150);
            uint PolicyFlashSize = BitConverter.ToUInt32(bPolicyFlashSize, 0);
            xoscStream.Writer.Write(PolicyFlashSize != 0xFFFFFFFF ? PolicyFlashSize : 0);

            xoscStream.Writer.Seek(0x158);
            xoscStream.Writer.Write((uint)(0x23289D3 | (Crl == 1 ? 0x10000 : 0) | (Fcrt == 1 ? 0x1000000 : 0)));

            ulong PCIEHardwareFlags = 0x4158019002000380;
            uint HardwareFlags = 0x50000227;
            if (bConsole == 0) { PCIEHardwareFlags = 0x2158023102000380; HardwareFlags = 0x00000227; }          //Xenon
            else if (bConsole == 1) { PCIEHardwareFlags = 0x2158023102000380; HardwareFlags = 0x10000227; }     //Zephyr
            else if (bConsole == 2) { PCIEHardwareFlags = 0x2158023102000380; HardwareFlags = 0x20000227; }     //Falcon
            else if (bConsole == 3) { PCIEHardwareFlags = 0x3158116002000380; HardwareFlags = 0x30000227; }     //Jasper
            else if (bConsole == 4) { PCIEHardwareFlags = 0x4158016002000380; HardwareFlags = 0x40000227; }     //Trinity

            xoscStream.Writer.Seek(0x170);
            xoscStream.Writer.Write(PCIEHardwareFlags);

            byte[] FFFF_188 = {
                0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                0xFF, 0xFF, 0xFF, 0xFF
            };

            xoscStream.Writer.Seek(0x188);
            xoscStream.Writer.Write(FFFF_188);

            xoscStream.Writer.Seek(0x19C);
            xoscStream.Writer.Write(0x00000001);

            xoscStream.Writer.Seek(0x1A0);
            xoscStream.Writer.Write(ConsoleID);

            xoscStream.Writer.Seek(0x1D0);
            xoscStream.Writer.Write(HardwareFlags);

            byte[] raw2A8Data = {
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xAA, 0xAA, 0xAA, 0xAA,
                0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA,
                0x5F, 0x53, 0x47, 0x50, 0xAA, 0xAA, 0xAA, 0xAA
            };
            xoscStream.Writer.Seek(0x2A8);
            xoscStream.Writer.Write(raw2A8Data);

            Console.WriteLine("========================================================");
            Console.WriteLine("xoscStream: ");
            Console.WriteLine("========================================================");
            Console.OutputEncoding = Encoding.GetEncoding(1252);
            Console.WriteLine(Hex.Dump(XOSC));
            Console.WriteLine("========================================================");

            // Send the response
            return string.Format("{0}", BytesToHexString(XOSC));

            //dataStream.Writer.Write(TitleDigest);
            //dataStream.Writer.Write(XOSC);
            //return string.Format("<HTML><BODY>My web page.<br>{0}</BODY></HTML>", DateTime.Now);
        }

        static void Main(string[] args)
        {
            var ws = new WebServer(SendXKEResponse, "http://10.0.0.209/api/");
            ws.Run();

            //var ws1 = new WebServer(SendXOSCResponse, "http://10.0.0.206:8899/api/XOSC/");
            //ws1.Run();

            Console.WriteLine("A simple webserver. Press a key to quit.");
            Console.ReadKey();
            ws.Stop();
        }
    }
}