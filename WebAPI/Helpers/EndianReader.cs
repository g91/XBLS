using System;
using System.IO;

namespace WebAPI
{
    public class EndianReader : BinaryReader
    {
        private readonly EndianStyle endianStyle;

        public EndianReader(Stream stream, EndianStyle endianstyle)
            : base(stream)
        {
            this.endianStyle = endianstyle;
        }

        public override short ReadInt16()
        {
            return this.ReadInt16(this.endianStyle);
        }

        public short ReadInt16(EndianStyle endianstyle)
        {
            byte[] buffer = base.ReadBytes(2);
            if (endianstyle == EndianStyle.BigEndian) Array.Reverse(buffer);
            return BitConverter.ToInt16(buffer, 0);
        }

        public override ushort ReadUInt16()
        {
            return this.ReadUInt16(this.endianStyle);
        }

        public ushort ReadUInt16(EndianStyle endianstyle)
        {
            byte[] buffer = base.ReadBytes(2);
            if (endianstyle == EndianStyle.BigEndian) Array.Reverse(buffer);
            return BitConverter.ToUInt16(buffer, 0);
        }

        public override int ReadInt32()
        {
            return this.ReadInt32(this.endianStyle);
        }

        public int ReadInt32(EndianStyle endianstyle)
        {
            byte[] buffer = base.ReadBytes(4);
            if (endianstyle == EndianStyle.BigEndian) Array.Reverse(buffer);
            return BitConverter.ToInt32(buffer, 0);
        }

        public override uint ReadUInt32()
        {
            return this.ReadUInt32(this.endianStyle);
        }

        public uint ReadUInt32(EndianStyle endianstyle)
        {
            byte[] buffer = base.ReadBytes(4);
            if (endianstyle == EndianStyle.BigEndian) Array.Reverse(buffer);
            return BitConverter.ToUInt32(buffer, 0);
        }

        public override long ReadInt64()
        {
            return this.ReadInt64(this.endianStyle);
        }

        public long ReadInt64(EndianStyle endianstyle)
        {
            byte[] buffer = base.ReadBytes(8);
            if (endianstyle == EndianStyle.BigEndian) Array.Reverse(buffer);
            return BitConverter.ToInt64(buffer, 0);
        }

        public override ulong ReadUInt64()
        {
            return this.ReadUInt64(this.endianStyle);
        }

        public ulong ReadUInt64(EndianStyle endianstyle)
        {
            byte[] buffer = base.ReadBytes(8);
            if (endianstyle == EndianStyle.BigEndian) Array.Reverse(buffer);
            return BitConverter.ToUInt64(buffer, 0);
        }

        public void Seek(long position)
        {
            base.BaseStream.Position = position;
        }
    }
}
