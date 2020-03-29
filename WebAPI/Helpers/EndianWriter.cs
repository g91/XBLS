using System;
using System.IO;

namespace WebAPI
{
    public class EndianWriter : BinaryWriter
    {
        private readonly EndianStyle endianStyle;

        public EndianWriter(Stream stream, EndianStyle endianstyle)
            : base(stream)
        {
            this.endianStyle = endianstyle;
        }

        public override void Write(short value)
        {
            this.Write(value, this.endianStyle);
        }

        public void Write(short value, EndianStyle endianstyle)
        {
            byte[] buffer = BitConverter.GetBytes(value);
            if (endianstyle == EndianStyle.BigEndian) Array.Reverse(buffer);
            base.Write(buffer);
        }

        public override void Write(ushort value)
        {
            this.Write(value, this.endianStyle);
        }

        public void Write(ushort value, EndianStyle endianstyle)
        {
            byte[] buffer = BitConverter.GetBytes(value);
            if (endianstyle == EndianStyle.BigEndian) Array.Reverse(buffer);
            base.Write(buffer);
        }

        public override void Write(int value)
        {
            this.Write(value, this.endianStyle);
        }

        public void Write(int value, EndianStyle endianstyle)
        {
            byte[] buffer = BitConverter.GetBytes(value);
            if (endianstyle == EndianStyle.BigEndian) Array.Reverse(buffer);
            base.Write(buffer);
        }

        public override void Write(uint value)
        {
            this.Write(value, this.endianStyle);
        }

        public void Write(uint value, EndianStyle endianstyle)
        {
            byte[] buffer = BitConverter.GetBytes(value);
            if (endianstyle == EndianStyle.BigEndian) Array.Reverse(buffer);
            base.Write(buffer);
        }

        public override void Write(long value)
        {
            this.Write(value, this.endianStyle);
        }

        public void Write(long value, EndianStyle endianstyle)
        {
            byte[] buffer = BitConverter.GetBytes(value);
            if (endianstyle == EndianStyle.BigEndian) Array.Reverse(buffer);
            base.Write(buffer);
        }

        public override void Write(ulong value)
        {
            this.Write(value, this.endianStyle);
        }

        public void Write(ulong value, EndianStyle endianstyle)
        {
            byte[] buffer = BitConverter.GetBytes(value);
            if (endianstyle == EndianStyle.BigEndian) Array.Reverse(buffer);
            base.Write(buffer);
        }

        public void WriteString(string value)
        {
            char[] buffer = value.ToCharArray();
            base.Write(buffer);
        }

        public void Seek(long position)
        {
            base.BaseStream.Position = position;
        }
    }
}
