using System.IO;

namespace WebAPI
{
    public class EndianIO
    {
        private readonly EndianStyle endianStyle;
        private readonly string filePath;
        private readonly bool isFile;

        public EndianIO(Stream stream, EndianStyle endianstyle)
        {
            this.filePath = string.Empty;
            this.endianStyle = endianstyle;
            this.Stream = stream;
            this.isFile = false;
            this.Open();
        }

        public EndianIO(string filepath, EndianStyle endianstyle)
        {
            this.filePath = string.Empty;
            this.endianStyle = endianstyle;
            this.filePath = filepath;
            this.isFile = true;
            this.Open();
        }

        public EndianIO(byte[] buffer, EndianStyle endianstyle)
        {
            this.filePath = string.Empty;
            this.endianStyle = endianstyle;
            this.Stream = new MemoryStream(buffer);
            this.isFile = false;
            this.Open();
        }

        public EndianIO(string filepath, EndianStyle endianstyle, FileMode filemode)
        {
            this.filePath = string.Empty;
            this.endianStyle = endianstyle;
            this.filePath = filepath;
            this.isFile = true;
            this.Open(filemode);
        }

        public void Open()
        {
            this.Open(FileMode.Open);
        }

        public void Open(FileMode filemode)
        {
            if (!this.Opened)
            {
                if (this.isFile) this.Stream = new FileStream(this.filePath, filemode, FileAccess.ReadWrite);
                this.Reader = new EndianReader(this.Stream, this.endianStyle);
                this.Writer = new EndianWriter(this.Stream, this.endianStyle);
                this.Opened = true;
            }
        }

        public byte[] ToArray()
        {
            return ((MemoryStream)this.Stream).ToArray();
        }

        public long Position
        {
            get { return this.Stream.Position; }
            set { this.Stream.Position = value; }
        }

        public bool Opened { get; set; }

        public EndianReader Reader { get; set; }

        public EndianWriter Writer { get; set; }

        public Stream Stream { get; set; }
    }
}
