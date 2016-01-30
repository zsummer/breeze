

/*
* breeze License
* Copyright (C) 2014-2016 YaweiZhang <yawei.zhang@foxmail.com>.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#include "utls.h"
#include "md5/md5.h"
#ifdef WIN32
#pragma comment(lib, "shlwapi")
#pragma comment(lib, "User32.lib")
#endif // WIN32


std::string readFileContent(const std::string & filename, bool isBinary, size_t limitSize, size_t beginIndex)
{
    FILE * f = fopen(filename.c_str(), "rb");
    if (f == NULL)
    {
        return "";
    }
    size_t fileLen = 0;
    fseek(f, 0, SEEK_SET);
    fileLen = ftell(f);
    fseek(f, 0, SEEK_END);
    fileLen = ftell(f) - fileLen;
    if (fileLen >= 3 && !isBinary && beginIndex == 0)
    {
        char buff[3];
        fread(buff, 1, 3, f);
        if ((unsigned char)buff[0] == 0xef
            && (unsigned char)buff[1] == 0xbb
            && (unsigned char)buff[2] == 0xbf)
        {
            beginIndex = 3;
        }
    }
    if (beginIndex >= fileLen)
    {
        fclose(f);
        return "";
    }
    if (limitSize > fileLen - beginIndex)
    {
        limitSize = fileLen - beginIndex;
    }
    
    fseek(f, beginIndex, SEEK_SET);
    std::string ret;
    ret.resize(limitSize, '\0');
    size_t readLen = fread(&ret[0], 1, limitSize, f);
    fclose(f);
    if (readLen < limitSize)
    {
        return ret.substr(0, readLen);
    }
    return std::move(ret);
}
size_t writeFileContent(const std::string & filename, const char * buff, size_t buffLen, bool isAppend)
{
    std::string mod = "b+";
    if (!isAppend)
    {
        mod = "w+";
    }
    
    FILE * f = fopen(filename.c_str(), mod.c_str());
    if (f == NULL)
    {
        return 0;
    }
    size_t writeLen = fwrite(buff, 1, buffLen, f);
    fclose(f);
    return writeLen;
}

void fixPath(std::string &path)
{
    if (path.empty()){ return; }
    for (std::string::iterator iter = path.begin(); iter != path.end(); ++iter)
    {
        if (*iter == '\\'){*iter = '/';}
    }
    if (path.at(path.length()-1) != '/'){path.append("/");}
}

bool isDirectory(const std::string & path)
{
#ifdef WIN32
    return PathIsDirectoryA(path.c_str()) ? true : false;
#else
    DIR * pdir = opendir(path.c_str());
    if (pdir == NULL)
    {
        return false;
    }
    else
    {
        closedir(pdir);
        pdir = NULL;
        return true;
    }
#endif
}

bool createRecursionDir(std::string  path)
{
    if (path.empty()) return false;
    std::string sub;
    for (std::string::iterator iter = path.begin(); iter != path.end(); ++iter)
    {
        if (*iter == '\\'){ *iter = '/'; }
    }
    if (path.at(path.length() - 1) != '/'){ path.append("/"); }

    std::string::size_type pos = path.find('/');
    while (pos != std::string::npos)
    {
        std::string cur = path.substr(0, pos - 0);
        if (cur.length() > 0 && !isDirectory(cur))
        {
            bool ret = false;
#ifdef WIN32
            ret = CreateDirectoryA(cur.c_str(), NULL) ? true : false;
#else
            ret = (mkdir(cur.c_str(), S_IRWXU | S_IRWXG | S_IRWXO) == 0);
#endif
            if (!ret)
            {
                return false;
            }
        }
        pos = path.find('/', pos + 1);
    }
    return true;
}

std::string genFileMD5(std::string filename)
{
    MD5Data md5;
    std::string file;
    size_t lastReadSize = 0;
    size_t limitSize = 1024 * 1024;
    do 
    {
        file = readFileContent(filename, true, limitSize, lastReadSize);
        if (file.empty())
        {
            break;
        }
        lastReadSize += file.length();
        md5 << file;
        if (file.size() < limitSize)
        {
            break;
        }
    } while (true);
    return md5.genMD5();
}

void sleepMillisecond(unsigned int ms)
{
#ifdef WIN32
    ::Sleep(ms);
#else
    usleep(1000 * ms);
#endif
}

void trim(std::string &str, std::string ign, int both)
{
    if (str.empty() || ign.empty()){ return; }
    size_t length = str.length();
    size_t posBegin = 0;
    size_t posEnd = 0;

    //trim character 
    for (size_t i = posBegin; i < length; i++)
    {
        bool bCheck = false;
        for (size_t j = 0; j < ign.length(); j++)
        {
            if (str[i] == ign[j])
            {
                bCheck = true;
            }
        }
        if (bCheck)
        {
            if (i == posBegin)
            {
                posBegin++;
            }
        }
        else
        {
            posEnd = i + 1;
        }
    }
    if (both == 1)
    {
        posEnd = length;
    }
    else if (both == 2)
    {
        posBegin = 0;
    }
    
    if (posBegin < posEnd)
    {
        str = str.substr(posBegin, posEnd - posBegin);
    }
    else
    {
        str.clear();
    }
}
std::vector<std::string> splitString(const std::string & text, std::string deli, std::string ign)
{
    std::vector<std::string> ret;
    if (deli.empty())
    {
        ret.push_back(text);
        trim(ret.back(), ign);
        return std::move(ret);
    }
    size_t beginPos = 0;
    std::string matched;
    for (size_t i = 0; i < text.length(); i++)
    {
        if ((matched.empty() && text[i] == deli[0]) || !matched.empty() )
        {
            matched.push_back(text[i]);
        }
        if (matched == deli)
        {
            ret.push_back(text.substr(beginPos, i + 1 - deli.length() - beginPos));
            trim(ret.back(), ign);
            beginPos = i + 1;
            matched.clear();
        }
    }
    ret.push_back(text.substr(beginPos, text.length() - beginPos));
    trim(ret.back(), ign);
    return std::move(ret);
}

std::string toUpperString(std::string  org)
{
    std::for_each(org.begin(), org.end(), [](char &ch){ch = toupper(ch); });
    return std::move(org);
}
std::string toLowerString(std::string  org)
{
    std::for_each(org.begin(), org.end(), [](char &ch){ch = tolower(ch); });
    return std::move(org);
}

bool compareStringIgnCase(const std::string & left, const std::string & right, bool canTruncate)
{
    if (left.length() > right.length())
    {
        return false;
    }
    if (left.length() != right.length() && ! canTruncate)
    {
        return false;
    }

    for (size_t i = 0; i < left.length(); i++)
    {
        if (toupper(left[i]) != toupper(right[i]))
        {
            return false;
        }
    }
    return true;
    
}

std::string getProcessID()
{
    std::string pid = "0";
    char buf[260] = { 0 };
#ifdef WIN32
    DWORD winPID = GetCurrentProcessId();
    sprintf(buf, "%06u", winPID);
    pid = buf;
#else
    sprintf(buf, "%06d", getpid());
    pid = buf;
#endif
    return pid;
}


std::string getProcessName()
{
    std::string name = LOG4Z_MAIN_LOGGER_KEY;
    char buf[260] = { 0 };
#ifdef WIN32
    if (GetModuleFileNameA(NULL, buf, 259) > 0)
    {
        name = buf;
    }
    std::string::size_type pos = name.rfind("\\");
    if (pos != std::string::npos)
    {
        name = name.substr(pos + 1, std::string::npos);
    }
    pos = name.rfind(".");
    if (pos != std::string::npos)
    {
        name = name.substr(0, pos - 0);
    }

#elif defined(__APPLE__)

    proc_name(getpid(), buf, 260);
    name = buf;
    return name;;
#else
    sprintf(buf, "/proc/%d/cmdline", (int)getpid());
    name = readFileContent(buf, true, 500, 0);
    std::string::size_type pos = name.rfind("/");
    if (pos != std::string::npos)
    {
        name = name.substr(pos + 1, std::string::npos);
    }
#endif


    return name;
}




