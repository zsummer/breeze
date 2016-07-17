using UnityEngine;
using Proto4z;
using System;
using System.Net;
using System.Net.Sockets;
using System.Threading;


class Client
{
    class NetHeader : IProtoObject
    {
        public uint packLen;
        public ushort reserve;
        public ushort protoID;
        public System.Collections.Generic.List<byte> __encode()
        {
            var ret = new System.Collections.Generic.List<byte>();
            ret.AddRange(BaseProtoObject.encodeUI32(packLen));
            ret.AddRange(BaseProtoObject.encodeUI16(reserve));
            ret.AddRange(BaseProtoObject.encodeUI16(protoID));
            return ret;
        }
        public System.Int32 __decode(byte[] binData, ref System.Int32 pos)
        {
            packLen = BaseProtoObject.decodeUI32(binData, ref pos);
            reserve = BaseProtoObject.decodeUI16(binData, ref pos);
            protoID = BaseProtoObject.decodeUI16(binData, ref pos);
            return pos;
        }
    }


    public void Run()
    {
        RC4Encryption rc4Server = new RC4Encryption();
        RC4Encryption rc4Client = new RC4Encryption();
        rc4Server.makeSBox("zhangyawei");
        rc4Client.makeSBox("zhangyawei");

        IPAddress ip = IPAddress.Parse("127.0.0.1");
        Socket clientSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
        try
        {
            clientSocket.Connect(new IPEndPoint(ip, 26001));
            Debug.logger.Log("connect Success.");
        }
        catch
        {
            Debug.logger.Log("connect Failed");
            return;
        }
        if(true)
        {
            ClientAuthReq req = new ClientAuthReq("test", "123");
            var binData = req.__encode().ToArray();
            //binData = rc4Client.encryption(binData, binData.Length());

            var sendData = new System.Collections.Generic.List<byte>();

            NetHeader head = new NetHeader();
            head.packLen = (UInt32)(4 + 2 + 2 + binData.Length);
            head.protoID = Proto4z.ClientAuthReq.getProtoID();
            sendData.AddRange(head.__encode());
            sendData.AddRange(binData);
            clientSocket.Send(sendData.ToArray());

            var recvBytes = new byte[2000];
            uint curLen = 0;
            uint needLen = 4 + 2 + 2; //暂时分两段读 后面要改buff接收提高效率 
            uint recvLen = 0;
            NetHeader recvHead = new NetHeader();
            do
            {
                recvLen = (uint)clientSocket.Receive(recvBytes, (int)curLen, (int)needLen, System.Net.Sockets.SocketFlags.None);//第一段 
                if (recvLen == 0)
                {
                    // remote close socket.
                    return;
                }
                curLen += recvLen;
                needLen -= recvLen;
                if (needLen == 0 && curLen == 4 + 2 + 2) ////第一段 完成 
                {
                    int pos = 0;
                    recvHead.__decode(recvBytes, ref pos);
                    needLen = recvHead.packLen - 4 - 2 - 2; //设置第二段 
                }
                else if (needLen == 0) //第二段完成 
                {
                    if (recvHead.protoID == Proto4z.ClientAuthResp.getProtoID())
                    {
                        ClientAuthResp result = new ClientAuthResp();
                        int pos = 4 + 2 + 2;
                        result.__decode(recvBytes, ref pos);

                        Debug.logger.Log("ClientAuthResp: account=" + result.account + ", token=" + result.token + ",retCode=" + result.retCode);
                        int t = 0;
                        t++;
                    }
                    else if(true) //other proto 
                    {

                    }
                    break; //一个协议接收处理完毕后break 
                }
                recvLen = 0; 
            } while (true);


        } 

    }
}


public class socketClient : MonoBehaviour
{

    void Start () {
        Client client = new Client();
        client.Run();
    }
   
	// Update is called once per frame
	void Update () {
	
	}
}
