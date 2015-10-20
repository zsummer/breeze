
/*
* proto4z License
* -----------
*
* proto4z is licensed under the terms of the MIT license reproduced below.
* This means that proto4z is free software and can be used for both academic
* and commercial purposes at absolutely no cost.
*
*
* ===============================================================================
*
* Copyright (C) 2013-2015 YaweiZhang <yawei.zhang@foxmail.com>.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*
* ===============================================================================
*
* (end of COPYRIGHT)
*/




namespace Proto4z
{
    sealed  class RC4Encryption //rc4 encrypt
    {
        private int _x;
        private int _y;
        private int[] m_box;
        public void makeSBox(string obscure)
        {
            m_box = new int[256];
            _x = 0;
            _y = 0;
            for (int i = 0; i < 256; i++)
            {
                m_box[i] = i;
            }
            if (obscure.Length > 0)
            {
                int j = 0;
                int k = 0;
                char[] obs = obscure.ToCharArray();
                int lenth = obs.Length;
                for (int i = 0; i < 256; i++)
                {
                    int tmp = m_box[i];
                    j = (byte)(j + tmp + (byte)obs[k]);
                    m_box[i] = m_box[j];
                    m_box[j] = tmp;
                    if (++k >= lenth)
                    {
                        k = 0;
                    }
                }
            }
        }

        public void encryption(byte[] data, int length)
        {
            int  x, y;

            x = _x;
            y = _y;

            for (int i = 0; i < length; i++)
            {
                x = (byte)(x + 1);
                int a = m_box[x];
                y = (byte)(y + a);
                int b = m_box[x] = m_box[y];
                m_box[y] = a;
                data[i] ^= (byte)m_box[(byte)(a + b)];
            }

            _x = x;
            _y = y;
        }



       
    }

    interface IProtoObject
    {
        System.Collections.Generic.List<byte> __encode();
        int __decode(byte[] binData, ref int pos);
    }
    sealed class BaseProtoObject
    {
        static public System.Collections.Generic.List<byte> encodeI8(char v)
        {
            byte[] bin = new byte[1];
            bin[0] = (byte)v;
            var ret = new System.Collections.Generic.List<byte>(bin);
            return ret;
        }
        static public char decodeI8(byte[] binData, ref int pos)
        {
            char v = (char)binData[pos];
            pos += 1;
            return v;
        }
        static public System.Collections.Generic.List<byte> encodeUI8(byte v)
        {
            byte[] bin = new byte[1];
            bin[0] = v;
            var ret = new System.Collections.Generic.List<byte>(bin);
            return ret;
        }
        static public byte decodeUI8(byte[] binData, ref int pos)
        {
            byte v = binData[pos];
            pos += 1;
            return v;
        }

        static public System.Collections.Generic.List<byte> encodeI16(short v)
        {
            byte[] bin = System.BitConverter.GetBytes(v);
            var ret = new System.Collections.Generic.List<byte>(bin);
            if (!System.BitConverter.IsLittleEndian)
                ret.Reverse();
            return ret;
        }
        static public short decodeI16(byte[] binData, ref int pos)
        {
            short v;
            if (System.BitConverter.IsLittleEndian)
            {
                v = System.BitConverter.ToInt16(binData, pos);
            }
            else
            {
                byte[] reverBin = { binData[pos + 1], binData[pos] };
                v = System.BitConverter.ToInt16(reverBin, 0);
            }
            pos += 2;
            return v;
        }
        static public System.Collections.Generic.List<byte> encodeUI16(ushort v)
        {
            byte[] bin = System.BitConverter.GetBytes(v);
            var ret = new System.Collections.Generic.List<byte>(bin);
            if (!System.BitConverter.IsLittleEndian)
                ret.Reverse();
            return ret;
        }
        static public ushort decodeUI16(byte[] binData, ref int pos)
        {
            ushort v;
            if (System.BitConverter.IsLittleEndian)
            {
                v = System.BitConverter.ToUInt16(binData, pos);
            }
            else
            {
                byte[] reverBin = { binData[pos + 1], binData[pos] };
                v = System.BitConverter.ToUInt16(reverBin, 0);
            }
            pos += 2;
            return v;
        }

        static public System.Collections.Generic.List<byte> encodeI32(int v)
        {
            byte[] bin = System.BitConverter.GetBytes(v);
            var ret = new System.Collections.Generic.List<byte>(bin);
            if (!System.BitConverter.IsLittleEndian)
                ret.Reverse();
            return ret;
        }
        static public int decodeI32(byte[] binData, ref int pos)
        {
            int v;
            if (System.BitConverter.IsLittleEndian)
            {
                v = System.BitConverter.ToInt32(binData, pos);
            }
            else
            {
                byte[] reverBin = { binData[pos + 3], binData[pos +2], binData[pos +1], binData[pos] };
                v = System.BitConverter.ToInt32(reverBin, 0);
            }
            pos += 4;
            return v;
        }
        static public System.Collections.Generic.List<byte> encodeUI32(uint v)
        {
            byte[] bin = System.BitConverter.GetBytes(v);
            var ret = new System.Collections.Generic.List<byte>(bin);
            if (!System.BitConverter.IsLittleEndian)
                ret.Reverse();
            return ret;
        }
        static public uint decodeUI32(byte[] binData, ref int pos)
        {
            uint v;
            if (System.BitConverter.IsLittleEndian)
            {
                v = System.BitConverter.ToUInt32(binData, pos);
            }
            else
            {
                byte[] reverBin = { binData[pos + 3], binData[pos + 2], binData[pos + 1], binData[pos] };
                v = System.BitConverter.ToUInt32(reverBin, 0);
            }
            pos += 4;
            return v;
        }

        static public System.Collections.Generic.List<byte> encodeI64(long v)
        {
            byte[] bin = System.BitConverter.GetBytes(v);
            var ret = new System.Collections.Generic.List<byte>(bin);
            if (!System.BitConverter.IsLittleEndian)
                ret.Reverse();
            return ret;
        }
        static public long decodeI64(byte[] binData, ref int pos)
        {
            long v;
            if (System.BitConverter.IsLittleEndian)
            {
                v = System.BitConverter.ToInt64(binData, pos);
            }
            else
            {
                byte[] reverBin = { binData[pos + 7], binData[pos + 6], binData[pos + 5], binData[pos + 4], binData[pos + 3], binData[pos + 2], binData[pos + 1], binData[pos] };
                v = System.BitConverter.ToInt64(reverBin, 0);
            }
            pos += 8;
            return v;
        }
        static public System.Collections.Generic.List<byte> encodeUI64(ulong v)
        {
            byte[] bin = System.BitConverter.GetBytes(v);
            var ret = new System.Collections.Generic.List<byte>(bin);
            if (!System.BitConverter.IsLittleEndian)
                ret.Reverse();
            return ret;
        }
        static public ulong decodeUI64(byte[] binData, ref int pos)
        {
            ulong v;
            if (System.BitConverter.IsLittleEndian)
            {
                v = System.BitConverter.ToUInt64(binData, pos);
            }
            else
            {
                byte[] reverBin = { binData[pos + 7], binData[pos + 6], binData[pos + 5], binData[pos + 4], binData[pos + 3], binData[pos + 2], binData[pos + 1], binData[pos] };
                v = System.BitConverter.ToUInt64(reverBin, 0);
            }
            pos += 8;
            return v;
        }

        static public System.Collections.Generic.List<byte> encodeSingle(float v)
        {
            byte[] bin = System.BitConverter.GetBytes(v);
            var ret = new System.Collections.Generic.List<byte>(bin);
            if (!System.BitConverter.IsLittleEndian)
                ret.Reverse();
            return ret;
        }
        static public float decodeSingle(byte[] binData, ref int pos)
        {
            float v;
            if (System.BitConverter.IsLittleEndian)
            {
                v = System.BitConverter.ToSingle(binData, pos);
            }
            else
            {
                byte[] reverBin = { binData[pos + 3], binData[pos + 2], binData[pos + 1], binData[pos] };
                v = System.BitConverter.ToSingle(reverBin, 0);
            }
            pos += 4;
            return v;
        }

        static public System.Collections.Generic.List<byte> encodeDouble(double v)
        {
            byte[] bin = System.BitConverter.GetBytes(v);
            var ret = new System.Collections.Generic.List<byte>(bin);
            if (!System.BitConverter.IsLittleEndian)
                ret.Reverse();
            return ret;
        }
        static public double decodeDouble(byte[] binData, ref int pos)
        {
            double v;
            if (System.BitConverter.IsLittleEndian)
            {
                v = System.BitConverter.ToDouble(binData, pos);
            }
            else
            {
                byte[] reverBin = { binData[pos + 7], binData[pos + 6], binData[pos + 5], binData[pos + 4], binData[pos + 3], binData[pos + 2], binData[pos + 1], binData[pos] };
                v = System.BitConverter.ToDouble(reverBin, 0);
            }
            pos += 8;
            return v;
        }

        static public System.Collections.Generic.List<byte> encodeString(string v)
        {
            var ret = new System.Collections.Generic.List<byte>();
            int len = System.Text.Encoding.UTF8.GetByteCount(v);
            byte[] str = System.Text.Encoding.UTF8.GetBytes(v);
            ret.AddRange(encodeI32(len));
            ret.AddRange(str);
            return ret;
        }
        static public string decodeString(byte[] binData, ref int pos)
        {
            int len = decodeI32(binData, ref pos);
            string v = System.Text.Encoding.UTF8.GetString(binData, pos, len);
            pos += len;
            return v;
        }
    }
}

