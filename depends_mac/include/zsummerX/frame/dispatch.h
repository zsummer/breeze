/*
 * zsummerX License
 * -----------
 *
 * zsummerX is licensed under the terms of the MIT license reproduced below.
 * This means that zsummerX is free software and can be used for both academic
 * and commercial purposes at absolutely no cost.
 *
 *
 * ===============================================================================
 *
 * Copyright (C) 2010-2015 YaweiZhang <yawei.zhang@foxmail.com>.
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




#ifndef ZSUMMER_MESSAGE_DISPATCHER_H_
#define ZSUMMER_MESSAGE_DISPATCHER_H_
#include "session.h"
namespace zsummer
{
    namespace network
    {
        /*
            MessageDispatcher 是一个协议消息派发器, 是一个单例singleton.
            消息派发分两种类型, 均需要使用者先调用对应的registerXXX系列接口进行注册.
            第一类是事件类型的通知, 即连接建立, 连接断开, 连接的定时检测回调.
            第二类为消息类型的处理通知,  消息处理通知分TCP和HTTP,  TCP有三种, 分别是预处理通知,具体协议处理和默认协议处理. HTTP只有一个消息处理回调. 
             具体使用参见代码,注释和示例.
        */
       
        //!register message 
        using OnMessageFunction = std::function < void(TcpSessionPtr&, zsummer::proto4z::ReadStream &) >;


        using ProtoID = zsummer::proto4z::ProtoInteger;
        const ProtoID InvalidProtoID = -1;

        class MessageDispatcher
        {
        private:
            MessageDispatcher(){}
            using MapProtoDispatch = std::unordered_map<unsigned short, std::vector<OnMessageFunction> >;
        public:
            static MessageDispatcher & getRef();
            inline static MessageDispatcher * getPtr(){ return &getRef(); }
            ~MessageDispatcher(){};
            //注册消息处理handler, 这个是针对消息ID进行注册, 回调参数是包含已经处理得到的协议ID以及attach好的ReadStream. 可以直接使用ReadStream流出对应的协议数据.
            inline void registerSessionMessage(ProtoID protoID, const OnMessageFunction & msgfun){ _mapSessionDispatch[protoID].push_back(msgfun); }
            void dispatchSessionMessage(TcpSessionPtr  &session, ProtoID pID, zsummer::proto4z::ReadStream & msg);
        private:
            //!message
            MapProtoDispatch _mapSessionDispatch;
        };
    }
}

#endif


