
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
        private System.Int32 _x;
        private System.Int32 _y;
        private System.Int32[] m_box;
        public void makeSBox(string obscure)
        {
            m_box = new System.Int32[256];
            _x = 0;
            _y = 0;
            for (System.Int32 i = 0; i < 256; i++)
            {
                m_box[i] = i;
            }
            if (obscure.Length > 0)
            {
                System.Int32 j = 0;
                System.Int32 k = 0;
                System.Char[] obs = obscure.ToCharArray();
                System.Int32 lenth = obs.Length;
                for (System.Int32 i = 0; i < 256; i++)
                {
                    System.Int32 tmp = m_box[i];
                    j = (System.Byte)(j + tmp + (System.Byte)obs[k]);
                    m_box[i] = m_box[j];
                    m_box[j] = tmp;
                    if (++k >= lenth)
                    {
                        k = 0;
                    }
                }
            }
        }

        public void encryption(System.Byte[] data, System.Int32 length)
        {
            System.Int32  x, y;

            x = _x;
            y = _y;

            for (System.Int32 i = 0; i < length; i++)
            {
                x = (System.Byte)(x + 1);
                System.Int32 a = m_box[x];
                y = (System.Byte)(y + a);
                System.Int32 b = m_box[x] = m_box[y];
                m_box[y] = a;
                data[i] ^= (System.Byte)m_box[(System.Byte)(a + b)];
            }

            _x = x;
            _y = y;
        }



       
    }

    interface IProtoObject
    {
        System.Collections.Generic.List<System.Byte> __encode();
        System.Int32 __decode(System.Byte[] binData, ref System.Int32 pos);
    }
    sealed class BaseProtoObject
    {
        static public System.Collections.Generic.List<System.Byte> encodeI8(System.Char v)
        {
            System.Byte[] bin = new System.Byte[1];
            bin[0] = (System.Byte)v;
            var ret = new System.Collections.Generic.List<System.Byte>(bin);
            return ret;
        }
        static public System.Char decodeI8(System.Byte[] binData, ref System.Int32 pos)
        {
            System.Char v = (System.Char)binData[pos];
            pos += 1;
            return v;
        }
        static public System.Collections.Generic.List<System.Byte> encodeUI8(System.Byte v)
        {
            System.Byte[] bin = new System.Byte[1];
            bin[0] = v;
            var ret = new System.Collections.Generic.List<System.Byte>(bin);
            return ret;
        }
        static public System.Byte decodeUI8(System.Byte[] binData, ref System.Int32 pos)
        {
            System.Byte v = binData[pos];
            pos += 1;
            return v;
        }

        static public System.Collections.Generic.List<System.Byte> encodeI16(System.Int16 v)
        {
            System.Byte[] bin = System.BitConverter.GetBytes(v);
            var ret = new System.Collections.Generic.List<System.Byte>(bin);
            if (!System.BitConverter.IsLittleEndian)
                ret.Reverse();
            return ret;
        }
        static public System.Int16 decodeI16(System.Byte[] binData, ref System.Int32 pos)
        {
            System.Int16 v;
            if (System.BitConverter.IsLittleEndian)
            {
                v = System.BitConverter.ToInt16(binData, pos);
            }
            else
            {
                System.Byte[] reverBin = { binData[pos + 1], binData[pos] };
                v = System.BitConverter.ToInt16(reverBin, 0);
            }
            pos += 2;
            return v;
        }
        static public System.Collections.Generic.List<System.Byte> encodeUI16(System.UInt16 v)
        {
            System.Byte[] bin = System.BitConverter.GetBytes(v);
            var ret = new System.Collections.Generic.List<System.Byte>(bin);
            if (!System.BitConverter.IsLittleEndian)
                ret.Reverse();
            return ret;
        }
        static public System.UInt16 decodeUI16(System.Byte[] binData, ref System.Int32 pos)
        {
            System.UInt16 v;
            if (System.BitConverter.IsLittleEndian)
            {
                v = System.BitConverter.ToUInt16(binData, pos);
            }
            else
            {
                System.Byte[] reverBin = { binData[pos + 1], binData[pos] };
                v = System.BitConverter.ToUInt16(reverBin, 0);
            }
            pos += 2;
            return v;
        }

        static public System.Collections.Generic.List<System.Byte> encodeI32(System.Int32 v)
        {
            System.Byte[] bin = System.BitConverter.GetBytes(v);
            var ret = new System.Collections.Generic.List<System.Byte>(bin);
            if (!System.BitConverter.IsLittleEndian)
                ret.Reverse();
            return ret;
        }
        static public System.Int32 decodeI32(System.Byte[] binData, ref System.Int32 pos)
        {
            System.Int32 v;
            if (System.BitConverter.IsLittleEndian)
            {
                v = System.BitConverter.ToInt32(binData, pos);
            }
            else
            {
                System.Byte[] reverBin = { binData[pos + 3], binData[pos +2], binData[pos +1], binData[pos] };
                v = System.BitConverter.ToInt32(reverBin, 0);
            }
            pos += 4;
            return v;
        }
        static public System.Collections.Generic.List<System.Byte> encodeUI32(System.UInt32 v)
        {
            System.Byte[] bin = System.BitConverter.GetBytes(v);
            var ret = new System.Collections.Generic.List<System.Byte>(bin);
            if (!System.BitConverter.IsLittleEndian)
                ret.Reverse();
            return ret;
        }
        static public System.UInt32 decodeUI32(System.Byte[] binData, ref System.Int32 pos)
        {
            System.UInt32 v;
            if (System.BitConverter.IsLittleEndian)
            {
                v = System.BitConverter.ToUInt32(binData, pos);
            }
            else
            {
                System.Byte[] reverBin = { binData[pos + 3], binData[pos + 2], binData[pos + 1], binData[pos] };
                v = System.BitConverter.ToUInt32(reverBin, 0);
            }
            pos += 4;
            return v;
        }

        static public System.Collections.Generic.List<System.Byte> encodeI64(System.Int64 v)
        {
            System.Byte[] bin = System.BitConverter.GetBytes(v);
            var ret = new System.Collections.Generic.List<System.Byte>(bin);
            if (!System.BitConverter.IsLittleEndian)
                ret.Reverse();
            return ret;
        }
        static public System.Int64 decodeI64(System.Byte[] binData, ref System.Int32 pos)
        {
            System.Int64 v;
            if (System.BitConverter.IsLittleEndian)
            {
                v = System.BitConverter.ToInt64(binData, pos);
            }
            else
            {
                System.Byte[] reverBin = { binData[pos + 7], binData[pos + 6], binData[pos + 5], binData[pos + 4], binData[pos + 3], binData[pos + 2], binData[pos + 1], binData[pos] };
                v = System.BitConverter.ToInt64(reverBin, 0);
            }
            pos += 8;
            return v;
        }
        static public System.Collections.Generic.List<System.Byte> encodeUI64(System.UInt64 v)
        {
            System.Byte[] bin = System.BitConverter.GetBytes(v);
            var ret = new System.Collections.Generic.List<System.Byte>(bin);
            if (!System.BitConverter.IsLittleEndian)
                ret.Reverse();
            return ret;
        }
        static public System.UInt64 decodeUI64(System.Byte[] binData, ref System.Int32 pos)
        {
            System.UInt64 v;
            if (System.BitConverter.IsLittleEndian)
            {
                v = System.BitConverter.ToUInt64(binData, pos);
            }
            else
            {
                System.Byte[] reverBin = { binData[pos + 7], binData[pos + 6], binData[pos + 5], binData[pos + 4], binData[pos + 3], binData[pos + 2], binData[pos + 1], binData[pos] };
                v = System.BitConverter.ToUInt64(reverBin, 0);
            }
            pos += 8;
            return v;
        }

        static public System.Collections.Generic.List<System.Byte> encodeSingle(System.Single v)
        {
            System.Byte[] bin = System.BitConverter.GetBytes(v);
            var ret = new System.Collections.Generic.List<System.Byte>(bin);
            if (!System.BitConverter.IsLittleEndian)
                ret.Reverse();
            return ret;
        }
        static public System.Single decodeSingle(System.Byte[] binData, ref System.Int32 pos)
        {
            System.Single v;
            if (System.BitConverter.IsLittleEndian)
            {
                v = System.BitConverter.ToSingle(binData, pos);
            }
            else
            {
                System.Byte[] reverBin = { binData[pos + 3], binData[pos + 2], binData[pos + 1], binData[pos] };
                v = System.BitConverter.ToSingle(reverBin, 0);
            }
            pos += 4;
            return v;
        }

        static public System.Collections.Generic.List<System.Byte> encodeDouble(System.Double v)
        {
            System.Byte[] bin = System.BitConverter.GetBytes(v);
            var ret = new System.Collections.Generic.List<System.Byte>(bin);
            if (!System.BitConverter.IsLittleEndian)
                ret.Reverse();
            return ret;
        }
        static public System.Double decodeDouble(System.Byte[] binData, ref System.Int32 pos)
        {
            System.Double v;
            if (System.BitConverter.IsLittleEndian)
            {
                v = System.BitConverter.ToDouble(binData, pos);
            }
            else
            {
                System.Byte[] reverBin = { binData[pos + 7], binData[pos + 6], binData[pos + 5], binData[pos + 4], binData[pos + 3], binData[pos + 2], binData[pos + 1], binData[pos] };
                v = System.BitConverter.ToDouble(reverBin, 0);
            }
            pos += 8;
            return v;
        }

        static public System.Collections.Generic.List<System.Byte> encodeString(System.String v)
        {
            var ret = new System.Collections.Generic.List<System.Byte>();
            System.Int32 len = System.Text.Encoding.UTF8.GetByteCount(v);
            System.Byte[] str = System.Text.Encoding.UTF8.GetBytes(v);
            ret.AddRange(encodeI32(len));
            ret.AddRange(str);
            return ret;
        }
        static public System.String decodeString(System.Byte[] binData, ref System.Int32 pos)
        {
            System.Int32 len = decodeI32(binData, ref pos);
            System.String v = System.Text.Encoding.UTF8.GetString(binData, pos, len);
            pos += len;
            return v;
        }
    }
}

