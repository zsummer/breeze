
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

    sealed class i8 : IProtoObject, System.Collections.Generic.IEqualityComparer<i8>
    {
        private char _val;
        public i8() { _val = '\0'; }
        public i8(char v) { _val = v; }
        public char val
        {
            get { return _val; }
            set { _val = value; }
        }
        public System.Collections.Generic.List<byte> __encode()
        {
            byte[] bin = new byte[1];
            bin[0] = (byte)_val;
            var ret = new System.Collections.Generic.List<byte>(bin);
            return ret;
        }
        public int __decode(byte[] binData, ref int pos)
        {
            _val = (char)binData[pos];
            pos += 1;
            return pos;
        }
        public override bool Equals(System.Object obj)
        {
            if (obj == null) return false;
            i8 child = obj as i8;
            if (child == null) return false;
            return child.val == val;
        }
        public bool Equals(i8 obj)
        {
            if ((object)obj == null)
            {
                return false;
            }
            return (obj.val == val);
        }
        public static bool operator ==(i8 a, i8 b)
        {
            if (System.Object.ReferenceEquals(a, b))
            {
                return true;
            }
            if (((object)a == null) || ((object)b == null))
            {
                return false;
            }
            return a.val == b.val;
        }

        public static bool operator !=(i8 a, i8 b)
        {
            return !(a == b);
        }
        public override int GetHashCode()
        {
            return val.GetHashCode();
        }

        public bool Equals(i8 x, i8 y)
        {
            return x == y;
        }

        public int GetHashCode(i8 obj)
        {
            return obj.val.GetHashCode();
        }

        public static implicit operator i8(char val)
        {
            return new i8(val);
        }
        public static implicit operator char(i8 val)
        {
            return val.val;
        }
    }



    sealed class ui8 : IProtoObject, System.Collections.Generic.IEqualityComparer<ui8>
    {
        private byte _val;
        public ui8() { _val = 0; }

        public ui8(byte v) { _val = v; }
        public byte val
        {
            get { return _val; }
            set { _val = value; }
        }
        public System.Collections.Generic.List<byte> __encode()
        {
            byte[] bin = new byte[1];
            bin[0] = _val;
            var ret = new System.Collections.Generic.List<byte>(bin);
            return ret;
        }
        public int __decode(byte[] binData, ref int pos)
        {
            _val = binData[pos];
            pos += 1;
            return pos;
        }
        public override bool Equals(System.Object obj)
        {
            if (obj == null) return false;
            ui8 child = obj as ui8;
            if (child == null) return false;
            return child.val == val;
        }
        public bool Equals(ui8 obj)
        {
            if ((object)obj == null)
            {
                return false;
            }
            return (obj.val == val);
        }
        public static bool operator ==(ui8 a, ui8 b)
        {
            if (System.Object.ReferenceEquals(a, b))
            {
                return true;
            }
            if (((object)a == null) || ((object)b == null))
            {
                return false;
            }
            return a.val == b.val;
        }

        public static bool operator !=(ui8 a, ui8 b)
        {
            return !(a == b);
        }
        public override int GetHashCode()
        {
            return val.GetHashCode();
        }

        public bool Equals(ui8 x, ui8 y)
        {
            return x == y;
        }

        public int GetHashCode(ui8 obj)
        {
            return obj.val.GetHashCode();
        }
        public static implicit operator ui8(byte val)
        {
            return new ui8(val);
        }
        public static implicit operator byte(ui8 val)
        {
            return val.val;
        }
    }

    sealed class i16 : IProtoObject, System.Collections.Generic.IEqualityComparer<i16>
    {
        private System.Int16 _val;
        public i16() { _val = 0; }

        public i16(System.Int16 v) { _val = v; }
        public System.Int16 val
        {
            get { return _val; }
            set { _val = value; }
        }
        public System.Collections.Generic.List<byte> __encode()
        {
            byte[] bin = System.BitConverter.GetBytes(_val);
            var ret = new System.Collections.Generic.List<byte>(bin);
            if (!System.BitConverter.IsLittleEndian)
                ret.Reverse();
            return ret;
        }
        public int __decode(byte[] binData, ref int pos)
        {
            if(System.BitConverter.IsLittleEndian)
            {
                _val = System.BitConverter.ToInt16(binData, pos);
            }
            else
            {
                byte[] reverBin = { binData[pos + 1], binData[pos] };
                _val = System.BitConverter.ToInt16(reverBin, 0);
            }
            pos += 2;
            return pos;
        }
        public override bool Equals(System.Object obj)
        {
            if (obj == null) return false;
            i16 child = obj as i16;
            if (child == null) return false;
            return child.val == val;
        }
        public bool Equals(i16 obj)
        {
            if ((object)obj == null)
            {
                return false;
            }
            return (obj.val == val);
        }
        public static bool operator ==(i16 a, i16 b)
        {
            if (System.Object.ReferenceEquals(a, b))
            {
                return true;
            }
            if (((object)a == null) || ((object)b == null))
            {
                return false;
            }
            return a.val == b.val;
        }

        public static bool operator !=(i16 a, i16 b)
        {
            return !(a == b);
        }
        public override int GetHashCode()
        {
            return val.GetHashCode();
        }

        public bool Equals(i16 x, i16 y)
        {
            return x == y;
        }

        public int GetHashCode(i16 obj)
        {
            return obj.val.GetHashCode();
        }
        public static implicit operator i16(System.Int16 val)
        {
            return new i16(val);
        }
        public static implicit operator System.Int16(i16 val)
        {
            return val.val;
        }
    }

    sealed class ui16 : IProtoObject, System.Collections.Generic.IEqualityComparer<ui16>
    {
        private System.UInt16 _val;
        public ui16() { _val = 0; }
        public ui16(System.UInt16 v) { _val = v; }
        public System.UInt16 val
        {
            get { return _val; }
            set { _val = value; }
        }
        public System.Collections.Generic.List<byte> __encode()
        {
            byte[] bin = System.BitConverter.GetBytes(_val);
            var ret = new System.Collections.Generic.List<byte>(bin);
            if (!System.BitConverter.IsLittleEndian)
                ret.Reverse();
            return ret;
        }
        public int __decode(byte[] binData, ref int pos)
        {
            if (System.BitConverter.IsLittleEndian)
            {
                _val = System.BitConverter.ToUInt16(binData, pos);
            }
            else
            {
                byte[] reverBin = { binData[pos + 1], binData[pos] };
                _val = System.BitConverter.ToUInt16(reverBin, 0);
            }
            pos += 2;
            return pos;
        }
        public override bool Equals(System.Object obj)
        {
            if (obj == null) return false;
            ui16 child = obj as ui16;
            if (child == null) return false;
            return child.val == val;
        }
        public bool Equals(ui16 obj)
        {
            if ((object)obj == null)
            {
                return false;
            }
            return (obj.val == val) ;
        }
        public static bool operator ==(ui16 a, ui16 b)
        {
            if (System.Object.ReferenceEquals(a, b))
            {
                return true;
            }
            if (((object)a == null) || ((object)b == null))
            {
                return false;
            }
            return a.val == b.val;
        }

        public static bool operator !=(ui16 a, ui16 b)
        {
            return !(a == b);
        }

        public override int GetHashCode()
        {
            return val.GetHashCode();
        }

        public bool Equals(ui16 x, ui16 y)
        {
            return x == y;
        }

        public int GetHashCode(ui16 obj)
        {
            return obj.val.GetHashCode();
        }
        public static implicit operator ui16(System.UInt16 val)
        {
            return new ui16(val);
        }
        public static implicit operator System.UInt16(ui16 val)
        {
            return val.val;
        }
    }

    sealed class i32 : IProtoObject, System.Collections.Generic.IEqualityComparer<i32>
    {
        private System.Int32 _val;
        public i32() { _val = 0; }
        public i32(System.Int32 v) { _val = v; }
        public System.Int32 val
        {
            get { return _val; }
            set { _val = value; }
        }
        public System.Collections.Generic.List<byte> __encode()
        {
            byte[] bin = System.BitConverter.GetBytes(_val);
            var ret = new System.Collections.Generic.List<byte>(bin);
            if (!System.BitConverter.IsLittleEndian)
                ret.Reverse();
            return ret;
        }
        public int __decode(byte[] binData, ref int pos)
        {
            if (System.BitConverter.IsLittleEndian)
            {
                _val = System.BitConverter.ToInt32(binData, pos);
            }
            else
            {
                byte[] reverBin = { binData[pos + 1], binData[pos] };
                _val = System.BitConverter.ToInt32(reverBin, 0);
            }
            pos += 4;
            return pos;
        }
        public override bool Equals(System.Object obj)
        {
            if (obj == null) return false;
            i32 child = obj as i32;
            if (child == null) return false;
            return child.val == val;
        }
        public bool Equals(i32 obj)
        {
            if ((object)obj == null)
            {
                return false;
            }
            return (obj.val == val);
        }
        public static bool operator ==(i32 a, i32 b)
        {
            if (System.Object.ReferenceEquals(a, b))
            {
                return true;
            }
            if (((object)a == null) || ((object)b == null))
            {
                return false;
            }
            return a.val == b.val;
        }

        public static bool operator !=(i32 a, i32 b)
        {
            return !(a == b);
        }
        public override int GetHashCode()
        {
            return val.GetHashCode();
        }

        public bool Equals(i32 x, i32 y)
        {
            return x == y;
        }

        public int GetHashCode(i32 obj)
        {
            return obj.val.GetHashCode();
        }

        public static implicit operator i32(System.Int32 val)
        {
            return new i32(val);
        }
        public static implicit operator System.Int32(i32 val)
        {
            return val.val;
        }
    }

    sealed class ui32 : IProtoObject, System.Collections.Generic.IEqualityComparer<ui32>
    {
        private System.UInt32 _val;
        public ui32() { _val = 0; }
        public ui32(System.UInt32 v) { _val = v; }
        public System.UInt32 val
        {
            get { return _val; }
            set { _val = value; }
        }
        public System.Collections.Generic.List<byte> __encode()
        {
            byte[] bin = System.BitConverter.GetBytes(_val);
            var ret = new System.Collections.Generic.List<byte>(bin);
            if (!System.BitConverter.IsLittleEndian)
                ret.Reverse();
            return ret;
        }
        public int __decode(byte[] binData, ref int pos)
        {
            if (System.BitConverter.IsLittleEndian)
            {
                _val = System.BitConverter.ToUInt32(binData, pos);
            }
            else
            {
                byte[] reverBin = { binData[pos + 1], binData[pos] };
                _val = System.BitConverter.ToUInt32(reverBin, 0);
            }
            pos += 4;
            return pos;
        }
        public override bool Equals(System.Object obj)
        {
            if (obj == null) return false;
            ui32 child = obj as ui32;
            if (child == null) return false;
            return child.val == val;
        }
        public bool Equals(ui32 obj)
        {
            if ((object)obj == null)
            {
                return false;
            }
            return (obj.val == val);
        }
        public static bool operator ==(ui32 a, ui32 b)
        {
            if (System.Object.ReferenceEquals(a, b))
            {
                return true;
            }
            if (((object)a == null) || ((object)b == null))
            {
                return false;
            }
            return a.val == b.val;
        }

        public static bool operator !=(ui32 a, ui32 b)
        {
            return !(a == b);
        }
        public override int GetHashCode()
        {
            return val.GetHashCode();
        }

        public bool Equals(ui32 x, ui32 y)
        {
            return x == y;
        }

        public int GetHashCode(ui32 obj)
        {
            return obj.val.GetHashCode();
        }

        public static implicit operator ui32(System.UInt32 val)
        {
            return new ui32(val);
        }
        public static implicit operator System.UInt32(ui32 val)
        {
            return val.val;
        }
    }

    sealed class i64 : IProtoObject, System.Collections.Generic.IEqualityComparer<i64>
    {
        private System.Int64 _val;
        public i64() { _val = 0; }
        public i64(System.Int64 v) { _val = v; }
        public System.Int64 val
        {
            get { return _val; }
            set { _val = value; }
        }
        public System.Collections.Generic.List<byte> __encode()
        {
            byte[] bin = System.BitConverter.GetBytes(_val);
            var ret = new System.Collections.Generic.List<byte>(bin);
            if (!System.BitConverter.IsLittleEndian)
                ret.Reverse();
            return ret;
        }
        public int __decode(byte[] binData, ref int pos)
        {
            if (System.BitConverter.IsLittleEndian)
            {
                _val = System.BitConverter.ToInt64(binData, pos);
            }
            else
            {
                byte[] reverBin = { binData[pos + 1], binData[pos] };
                _val = System.BitConverter.ToInt64(reverBin, 0);
            }
            pos += 8;
            return pos;
        }
        public override bool Equals(System.Object obj)
        {
            if (obj == null) return false;
            i64 child = obj as i64;
            if (child == null) return false;
            return child.val == val;
        }
        public bool Equals(i64 obj)
        {
            if ((object)obj == null)
            {
                return false;
            }
            return (obj.val == val);
        }
        public static bool operator ==(i64 a, i64 b)
        {
            if (System.Object.ReferenceEquals(a, b))
            {
                return true;
            }
            if (((object)a == null) || ((object)b == null))
            {
                return false;
            }
            return a.val == b.val;
        }

        public static bool operator !=(i64 a, i64 b)
        {
            return !(a == b);
        }
        public override int GetHashCode()
        {
            return val.GetHashCode();
        }

        public bool Equals(i64 x, i64 y)
        {
            return x == y;
        }

        public int GetHashCode(i64 obj)
        {
            return obj.val.GetHashCode();
        }

        public static implicit operator i64(System.Int64 val)
        {
            return new i64(val);
        }
        public static implicit operator System.Int64(i64 val)
        {
            return val.val;
        }
    }

    sealed class ui64 : IProtoObject, System.Collections.Generic.IEqualityComparer<ui64>
    {
        private System.UInt64 _val;
        public ui64() { _val = 0; }
        public ui64(System.UInt64 v) { _val = v; }
        public System.UInt64 val
        {
            get { return _val; }
            set { _val = value; }
        }
        public System.Collections.Generic.List<byte> __encode()
        {
            byte[] bin = System.BitConverter.GetBytes(_val);
            var ret = new System.Collections.Generic.List<byte>(bin);
            if (!System.BitConverter.IsLittleEndian)
                ret.Reverse();
            return ret;
        }
        public int __decode(byte[] binData, ref int pos)
        {
            if (System.BitConverter.IsLittleEndian)
            {
                _val = System.BitConverter.ToUInt64(binData, pos);
            }
            else
            {
                byte[] reverBin = { binData[pos + 1], binData[pos] };
                _val = System.BitConverter.ToUInt64(reverBin, 0);
            }
            pos += 8;
            return pos;
        }
        public override bool Equals(System.Object obj)
        {
            if (obj == null) return false;
            ui64 child = obj as ui64;
            if (child == null) return false;
            return child.val == val;
        }
        public bool Equals(ui64 obj)
        {
            if ((object)obj == null)
            {
                return false;
            }
            return (obj.val == val);
        }
        public static bool operator ==(ui64 a, ui64 b)
        {
            if (System.Object.ReferenceEquals(a, b))
            {
                return true;
            }
            if (((object)a == null) || ((object)b == null))
            {
                return false;
            }
            return a.val == b.val;
        }

        public static bool operator !=(ui64 a, ui64 b)
        {
            return !(a == b);
        }
        public override int GetHashCode()
        {
            return val.GetHashCode();
        }

        public bool Equals(ui64 x, ui64 y)
        {
            return x == y;
        }

        public int GetHashCode(ui64 obj)
        {
            return obj.val.GetHashCode();
        }

        public static implicit operator ui64(System.UInt64 val)
        {
            return new ui64(val);
        }
        public static implicit operator System.UInt64(ui64 val)
        {
            return val.val;
        }
    }

    sealed class Float : IProtoObject
    {
        private float _val;
        public Float() { _val = 0; }
        public Float(float v) {_val = v;}
        public float val
        {
            get { return _val; }
            set { _val = value; }
        }
        public System.Collections.Generic.List<byte> __encode()
        {
            byte[] bin = System.BitConverter.GetBytes(_val);
            var ret = new System.Collections.Generic.List<byte>(bin);
            if (!System.BitConverter.IsLittleEndian)
                ret.Reverse();
            return ret;
        }
        public int __decode(byte[] binData, ref int pos)
        {
            if (System.BitConverter.IsLittleEndian)
            {
                _val = System.BitConverter.ToSingle(binData, pos);
            }
            else
            {
                byte[] reverBin = { binData[pos + 1], binData[pos] };
                _val = System.BitConverter.ToSingle(reverBin, 0);
            }
            pos += 4;
            return pos;
        }


        public static implicit operator Float(float val)
        {
            return new Float(val);
        }
        public static implicit operator float(Float val)
        {
            return val.val;
        }
    }

    sealed class Double : IProtoObject
    {
        private double _val;
        public Double() { _val = 0; }
        public Double(double v) { _val = v; }

        public double val
        {
            get { return _val; }
            set { _val = value; }
        }
        public System.Collections.Generic.List<byte> __encode()
        {
            byte[] bin = System.BitConverter.GetBytes(_val);
            var ret = new System.Collections.Generic.List<byte>(bin);
            if (!System.BitConverter.IsLittleEndian)
                ret.Reverse();
            return ret;
        }
        public int __decode(byte[] binData, ref int pos)
        {
            if (System.BitConverter.IsLittleEndian)
            {
                _val = System.BitConverter.ToDouble(binData, pos);
            }
            else
            {
                byte[] reverBin = { binData[pos + 1], binData[pos] };
                _val = System.BitConverter.ToDouble(reverBin, 0);
            }
            pos += 8;
            return pos;
        }


        public static implicit operator Double(double val)
        {
            return new Double(val);
        }
        public static implicit operator double(Double val)
        {
            return val.val;
        }
    }

    sealed class String : IProtoObject, System.Collections.Generic.IEqualityComparer<Proto4z.String>
    {
        private string _val;
        public String() { _val = ""; }
        public String(string v) { _val = v; }
        public string val
        {
            get { return _val; }
            set { _val = value; }
        }
        public System.Collections.Generic.List<byte> __encode()
        {
            var ret = new System.Collections.Generic.List<byte>();
            ret.AddRange(new ui32((System.UInt32)_val.Length).__encode());
            foreach (char ch in _val)
            {
                ret.Add((byte)ch);
            }
            return ret;
        }
        public int __decode(byte[] binData, ref int pos)
        {
            _val = "";
            ui32 len = new ui32(0);
            len.__decode(binData, ref pos);
            if ( len > 0 )
            {
                System.Text.StringBuilder sb = new System.Text.StringBuilder();
                for (int i = pos; i < pos + len.val; i++)
                {
                    sb.Append((char)binData[i]);
                }
                pos += (int)len.val;
                _val = sb.ToString();
            }
            return pos;
        }
        public override bool Equals(System.Object obj)
        {
            if (obj == null) return false;
            String child = obj as Proto4z.String;
            if (child == null) return false;
            return child.val == val;
        }
        public bool Equals(Proto4z.String obj)
        {
            if ((object)obj == null)
            {
                return false;
            }
            return (obj.val == val);
        }
        public static bool operator ==(Proto4z.String a, Proto4z.String b)
        {
            if (System.Object.ReferenceEquals(a, b))
            {
                return true;
            }
            if (((object)a == null) || ((object)b == null))
            {
                return false;
            }
            return a.val == b.val;
        }

        public static bool operator !=(Proto4z.String a, Proto4z.String b)
        {
            return !(a == b);
        }
        public override int GetHashCode()
        {
            return val.GetHashCode();
        }

        public bool Equals(String x, String y)
        {
            return x == y;
        }

        public int GetHashCode(String obj)
        {
            return obj.val.GetHashCode();
        }

        public static implicit operator Proto4z.String(string val)
        {
            return new Proto4z.String(val);
        }
        public static implicit operator string(Proto4z.String val)
        {
            return val.val;
        }
    }
}

