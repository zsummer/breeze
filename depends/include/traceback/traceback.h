/*
* traceback License
* -----------
*
* traceback is licensed under the terms of the MIT license reproduced below.
* This means that Log4z is free software and can be used for both academic
* and commercial purposes at absolutely no cost.
*
*
* ===============================================================================
*
* Copyright (C) 2015 YaweiZhang <yawei.zhang@foxmail.com>.
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


#ifdef WIN32
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <iostream>
#include <windows.h>
#include <DbgHelp.h>
#include <string>
#pragma comment(lib, "Dbghelp")
#else
#include <execinfo.h>
#include <unistd.h>
#endif
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <algorithm>
using namespace std;

namespace  zsummer
{

    inline std::string traceback()
    {
        std::stringstream ss;
#ifdef WIN32

        SymSetOptions(SYMOPT_UNDNAME | SYMOPT_DEFERRED_LOADS);
        if (!SymInitialize(GetCurrentProcess(), NULL, TRUE))
        {
            ss << "SymInitialize returned error " << GetLastError();
            return ss.str();
        }

        //     typedef USHORT(WINAPI *CaptureStackBackTraceType)(__in ULONG, __in ULONG, __out PVOID*, __out_opt PULONG);
        //     CaptureStackBackTraceType capture = (CaptureStackBackTraceType)(GetProcAddress(LoadLibraryA("kernel32.dll"), "RtlCaptureStackBackTrace"));
        //     if (capture == NULL) return;
        const int stackMax = 128;
        void* trace[stackMax];
        //    int count = (capture)(0, stackMax, trace, NULL);
        int count = (CaptureStackBackTrace)(0, stackMax, trace, NULL);
        for (int i = 1; i < count; i++)
        {
            ULONG64 buffer[(sizeof(SYMBOL_INFO)+MAX_SYM_NAME*sizeof(TCHAR)+sizeof(ULONG64)-1) / sizeof(ULONG64)];
            PSYMBOL_INFO pSymbol = (PSYMBOL_INFO)buffer;
            pSymbol->SizeOfStruct = sizeof(SYMBOL_INFO);
            pSymbol->MaxNameLen = MAX_SYM_NAME;
            DWORD64 dwDisplacement = 0;
            if (SymFromAddr(GetCurrentProcess(), (DWORD64)trace[i], &dwDisplacement, pSymbol))
            {
                ss << "bt[" << i - 1 << "]       --[ " << pSymbol->Name << " ]--              from     ";
            }
            else
            {
                ss << "bt[" << i - 1 << "]   " << "error[" << GetLastError() << "]              from     ";
            }

            IMAGEHLP_LINE64 lineInfo = { sizeof(IMAGEHLP_LINE64) };
            DWORD dwLineDisplacement;
            if (SymGetLineFromAddr64(GetCurrentProcess(), (DWORD64)trace[i], &dwLineDisplacement, &lineInfo))
            {
                std::string pathfile = lineInfo.FileName;
                if (pathfile.empty())
                {
                    ss << "\r\n";
                    continue;
                }
                std::for_each(pathfile.begin(), pathfile.end(), [](char &ch){ if (ch == '/') ch = '\\'; });
                auto pos = pathfile.find_last_of('\\');
                if (pos != std::string::npos) pathfile[pos] = '/';
                pos = pathfile.find_last_of('\\');
                if (pos != std::string::npos) pathfile[pos] = '/'; else pos = -1;
                ss << pathfile.substr(pos + 1) << ":" << lineInfo.LineNumber;
            }
            else
            {
                ss << "------:0";
            }
            ss << "\r\n";
            if (strcmp(pSymbol->Name, "main") == 0) break;
        }
#else
        void *stack[200];
        size_t size = backtrace(stack, 200);
        char **stackSymbol = backtrace_symbols(stack, size);
        ss << "backtrace: ";
        for (size_t i = 1; i < size; i++ )
        {
            ss << stack[i] << "  ";
        }
        ss << "\r\n";
        for (size_t i = 1; i < size && stackSymbol != NULL; i++)
        {
            ss << "bt[" << i - 1 << "] " << stackSymbol[i] << "\r\n";
        }
        free(stackSymbol);
#endif
        return std::move(ss.str());
    }
}



/*
gdb info line * 0x40000000
addr2line -f -C -e ./test  0x400fce  0x401027  0x7f2bfb401b45  0x400ee9
*/



