

/*
* breeze License
* Copyright (C) 2014-2017 YaweiZhang <yawei.zhang@foxmail.com>.
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
#pragma comment(lib, "User32")
#pragma comment(lib, "ws2_32")
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
    
    fseek(f, (long)beginIndex, SEEK_SET);
    std::string ret;
    ret.resize(limitSize, '\0');
    size_t readLen = fread(&ret[0], 1, limitSize, f);
    fclose(f);
    if (readLen < limitSize)
    {
        return ret.substr(0, readLen);
    }
    return ret;
}
size_t writeFileContent(const std::string & filename, const char * buff, size_t buffLen, bool isAppend)
{
    std::string mod = "ab+";
    if (!isAppend)
    {
        mod = "wb+";
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

bool removeFile(const std::string &pathfile)
{
    return ::remove(pathfile.c_str()) == 0;
}
bool removeDir(const std::string &path)
{
    return ::rmdir(path.c_str()) == 0;
}
bool accessFile(const std::string &pathfile)
{
#ifdef WIN32
    return ::_access(pathfile.c_str(), 0) == 0;
#else
    return ::access(pathfile.c_str(), F_OK) == 0;
#endif
}

bool createDirectory(std::string  path)
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




std::string fixPathString(const std::string &path)
{
    if (path.empty()) return path;
    auto ret = path;
    std::for_each(ret.begin(), ret.end(), [](char &ch){ if (ch == '\\') ch = '/'; });
    if (isDirectory(path))
    {
        if (ret.back() != '/') ret += "/";
    }
    return ret;
}

static bool tmpSearchPath(std::string  path, std::vector<SearchFileInfo> & files, bool recursion)
{
    if (path.length() == 0)
    {
        return false;
    }
    path = fixPathString(path);
    auto wildcard = subString(path, "/", true, true);
    if (!wildcard.second.empty())
    {
        path = wildcard.first + "/";
    }
    

#ifdef WIN32
    WIN32_FIND_DATAA fd;
    std::string findpath = path;
    findpath.append("*");
    HANDLE hFile = FindFirstFileA(findpath.c_str(), &fd);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        return false;
    }
    SearchFileInfo file;
    do
    {
        if (fd.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
        {
            if (strcmp(fd.cFileName, ".") != 0 && strcmp(fd.cFileName, "..") != 0)
            {
                memset(&file, 0, sizeof(file));
                file.bDir = true;
                strcpy_s(file.filename, sizeof(file.filename), fd.cFileName);
                sprintf(file.fullpath, "%s%s", path.c_str(), fd.cFileName);
                if (wildcard.second.empty())
                {
                    files.push_back(file);
                }
                if (recursion)
                {
                    tmpSearchPath(fixPathString(file.fullpath) + wildcard.second, files, recursion);
                }
                
            }
        }
        else
        {
            memset(&file, 0, sizeof(file));
            file.bDir = false;
            file.filesize = fd.nFileSizeHigh;
            file.filesize = file.filesize << 32;
            file.filesize += fd.nFileSizeLow;
            strcpy_s(file.filename, sizeof(file.filename), fd.cFileName);
            sprintf(file.fullpath, "%s%s", path.c_str(), fd.cFileName);
            if (wildcard.second.empty() || compareStringWildcard(file.filename, wildcard.second))
            {
                files.push_back(file);
            }
        }
    } while (FindNextFileA(hFile, &fd));
    FindClose(hFile);

#else
    DIR *dp;
    struct dirent *entry;
    struct stat statbuf;
    if ((dp = opendir(path.c_str())) == NULL)
    {
        return false;
    }
    SearchFileInfo file;
    while ((entry = readdir(dp)) != NULL)
    {
        lstat(entry->d_name, &statbuf);
        if (S_ISDIR(statbuf.st_mode))
        {
            if (strcmp(".", entry->d_name) == 0 || strcmp("..", entry->d_name) == 0)
            {
                continue;
            }
            memset(&file, 0, sizeof(file));
            file.bDir = true;
            file.filesize = statbuf.st_size;
            strcpy(file.filename, entry->d_name);
            sprintf(file.fullpath, "%s%s", path.c_str(), entry->d_name);
            if (wildcard.second.empty())
            {
                files.push_back(file);
            }
            if (recursion)
            {
                tmpSearchPath(fixPathString(file.fullpath)+wildcard.second, files, recursion);
            }
        }
        else
        {
            memset(&file, 0, sizeof(file));
            file.bDir = false;
            file.filesize = statbuf.st_size;
            strcpy(file.filename, entry->d_name);
            file.fullpath[0] = '\0';
            if (wildcard.second.empty() || compareStringWildcard(file.filename, wildcard.second))
            {
                files.push_back(file);
            }
        }
    }
    closedir(dp);
#endif
    return true;
}

bool searchFiles(std::string path, std::vector<SearchFileInfo> & files, bool recursion)
{
    if (files.capacity() < 100)
    {
        files.reserve(100);
    }
    return tmpSearchPath(path, files, recursion);
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




std::pair<std::string,std::string> subString(const std::string & text, const std::string & deli, bool preStore, bool isGreedy)
{
    std::string::size_type pos = std::string::npos;
    if (!isGreedy)
    {
        pos = text.find(deli);
    }
    else
    {
        pos = text.rfind(deli);
    }
    if (pos == std::string::npos)
    {
        if (preStore)
        {
            return std::make_pair(text, "");
        }
        return std::make_pair("", text);
    }
    return std::make_pair(text.substr(0, pos - 0), text.substr(pos+deli.length()));
}

std::string replaceString(const std::string & text, const std::string & pattern, const std::string &rep, bool once)
{
    std::string ret;
    size_t pos = 0;
    do 
    {
        size_t next = text.find(pattern, pos);
        if (next != std::string::npos)
        {
            ret += text.substr(pos, next - pos);
            ret += rep;
            pos = next + pattern.length();
            if (once)
            {
                ret += text.substr(pos);
                pos = std::string::npos;
            }
        }
        else
        {
            ret += text.substr(pos);
            pos = std::string::npos;
        }

    } while (pos != std::string::npos);
    return ret;
}



std::string toUpperString(std::string  org)
{
    std::for_each(org.begin(), org.end(), [](char &ch){ch = toupper(ch); });
    return org;
}
std::string toLowerString(std::string  org)
{
    std::for_each(org.begin(), org.end(), [](char &ch){ch = tolower(ch); });
    return org;
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


static int compareStringWildcard(std::vector<std::pair<std::string::size_type, std::string::size_type>> & stk, const std::string &src, const std::string & md)
{
    int searchCount = 1;
    while (!stk.empty())
    {
        std::string::size_type srcBeginPos = stk.back().first;
        std::string::size_type mdBeginPos = stk.back().second;
        stk.pop_back();

        while (true)
        {
            searchCount++;
            if (mdBeginPos >= md.length() )
            {
                if (srcBeginPos >= src.length())
                {
                    return searchCount;
                }
                else
                {
                    break;
                }
            }
            auto wcFirstPos = md.find('*', mdBeginPos);
            if (wcFirstPos == std::string::npos)
            {
                if (srcBeginPos >= src.length() 
                    || md.length() - mdBeginPos != src.length() - srcBeginPos
                    || md.compare(mdBeginPos, md.length() - mdBeginPos, src.c_str(), src.length() - srcBeginPos) != 0)
                {
                    break;
                }
                return searchCount;
            }
            //pre char matching
            if (wcFirstPos != mdBeginPos)
            {
                if (srcBeginPos >= src.length() || src.length() - srcBeginPos < wcFirstPos - mdBeginPos)
                {
                    break;
                }
                if (md.compare(mdBeginPos, wcFirstPos - mdBeginPos, src.c_str(), srcBeginPos, wcFirstPos - mdBeginPos) != 0)
                {
                    break;
                }
                mdBeginPos = wcFirstPos;
                srcBeginPos = srcBeginPos + (wcFirstPos - mdBeginPos);
                continue;
            }
            //next segment matching
            else
            {
                if (md.length() == wcFirstPos + 1)
                {
                    return searchCount;
                }
                auto wcSecondPos = md.find('*', mdBeginPos+1);
                if (wcSecondPos == std::string::npos)
                {
                    wcSecondPos = md.length();
                }
                auto foundPos = src.find(md.c_str() + mdBeginPos + 1, srcBeginPos,  wcSecondPos - mdBeginPos - 1);
                if (foundPos == std::string::npos)
                {
                    break;
                }
                stk.push_back(std::make_pair(foundPos + 1, mdBeginPos));
                
                srcBeginPos = foundPos + (wcSecondPos - mdBeginPos - 1);
                mdBeginPos = wcSecondPos;
            }
        }
    }
    return 0;
}

bool compareStringWildcard(std::string source, std::string mod, bool ignCase)
{
    for (auto iter = mod.begin(); iter != mod.end();)
    {
        auto next = iter + 1;
        if (*iter == '*' && next != mod.end() && *next == '*')
        {
            iter = mod.erase(iter);
            continue;
        }
        iter++;
    }
    if (ignCase)
    {
        mod = toLowerString(mod);
        source = toLowerString(source);
    }
    std::vector<std::pair<std::string::size_type, std::string::size_type>> stk;
    stk.reserve(10);
    stk.push_back(std::make_pair(0, 0));
    return compareStringWildcard(stk, source, mod) != 0;
}
/*
Char. number range  |        UTF-8 octet sequence
(hexadecimal)    |              (binary)
--------------------+---------------------------------------------
0000 0000-0000 00F | 0xxxxxxx
0000 0080-0000 07FF | 110xxxxx 10xxxxxx
0000 0800-0000 FFFF | 1110xxxx 10xxxxxx 10xxxxxx
0001 0000-0010 FFFF | 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
*/
int getCharUTF8Count(const std::string & str)
{
    //0x7f == 0111 1111
    //0xc0 == 1100 0000
    int count = 0;
    std::for_each(str.begin(), str.end(), [&count](char ch){ if ((unsigned char)ch <= 0x7f || (unsigned char)ch >= 0xc0) count++; });
    return count;
}
int getCharASCIICount(const std::string & str)
{
    int count = 0;
    std::for_each(str.begin(), str.end(), [&count](char ch){ if ((unsigned char)ch <= 0x7f) count++; });
    return count;
}
int getCharNoASCIICount(const std::string & str)
{
    int count = 0;
    std::for_each(str.begin(), str.end(), [&count](char ch){ if ((unsigned char)ch >= 0xc0) count++; });
    return count;
}

bool hadIllegalChar(const std::string & str) // return true when have invisible char, mysql unsupport char, mysql escape char.
{
    //0x7f == 0111 1111
    //0xc0 == 1100 0000
    //0xe0 == 1110 0000
    //0xef == 1110 1111
    int cur = 0;
    for (auto ch : str)
    {
        unsigned char b = (unsigned char)ch;
        if (b > 0xef)
        {
            return true;
        }
        if (b < ' ' || b == 0x7f) //invisible
        {
            return true;
        }
        if (ch == ' ' || ch == '\"' || ch == '\'' || ch == '\\') //unsafe 
        {
            return true;
        }
        if (b >= 0xc0 && b < 0xe0 && (str.length() - cur < 2))
        {
            return true;
        }
        if (b >= 0xe0 && b < 0xf0 && (str.length() - cur < 3))
        {
            return true;
        }
    }
    return false;
}

time_t getUTCTimeFromLocalString(const std::string & str)
{
    size_t offset = 0;
    size_t len = 0;
    trim(str.c_str(), str.length(), ' ', offset, len);
    if (len == 0)
    {
        return 0;
    }
    std::tuple<std::string, std::string> ret;
    splitStringTupleImpl<std::tuple<std::string, std::string>, std::string, std::string>(ret, str.c_str()+offset, str.c_str() + offset + len, ' ');


    struct tm st;
    memset(&st, 0, sizeof(st));
    using DateFmt = std::tuple<int, int, int>;
    DateFmt dateTuple;
    DateFmt timeTuple;
    if (true)
    {
        char deli = '-';
        if (std::get<0>(ret).find('/') != std::string::npos)
        {
            deli = '/';
        }
        else if (std::get<0>(ret).find('\\') != std::string::npos)
        {
            deli = '\\';
        }
        trim(std::get<0>(ret).c_str(), std::get<0>(ret).length(), ' ', offset, len);
        splitStringTupleImpl<DateFmt, int, int, int>(dateTuple, std::get<0>(ret).c_str() + offset, std::get<0>(ret).c_str() + offset + len, deli);
    }

    trim(std::get<1>(ret).c_str(), std::get<0>(ret).length(), ' ', offset, len);
    splitStringTupleImpl<DateFmt, int, int, int>(timeTuple, std::get<1>(ret).c_str() + offset, std::get<1>(ret).c_str() + offset + len, ':');
    st.tm_year = pruning(std::get<0>(dateTuple) - 1900, 71, 135);
    st.tm_mon = pruning(std::get<1>(dateTuple) - 1, 0, 11);
    st.tm_mday = pruning(std::get<2>(dateTuple), 1, 31);
    st.tm_hour = pruning(std::get<0>(timeTuple), 0, 23);
    st.tm_min = pruning(std::get<1>(timeTuple), 0, 59);
    st.tm_sec = pruning(std::get<2>(timeTuple), 0, 59);
    return mktime(&st);
}

time_t getSecondFromTimeString(const std::string & str)
{
    auto ret = splitStringTuple<int, int, int>(str, ':');
    return pruning(std::get<0>(ret), 0, 23) * 3600 + pruning(std::get<1>(ret), 0, 59) * 60 + pruning(std::get<2>(ret), 0, 59);
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
    std::string name = "unknown";
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

thread_local std::mt19937 __genRandom;

//rand
//==========================================================================
unsigned int realRand()
{
    return __genRandom();
}
unsigned int realRand(unsigned int mi, unsigned int mx)
{
    return mi + (realRand() % (mx - mi + 1));
}
double realRandF()
{
    return (double)realRand() * 1.0 / (double)0xffffffff;
}
double realRandF(double mi, double mx)
{
    return mi + realRandF()*(mx - mi);
}


std::string getHostByName(const std::string & name, unsigned short port)
{
    auto ret = subString(name, "https://", false).second;
    ret = subString(ret, "http://", false).second;
    ret += "/";
    ret = subString(ret, "/", true).first;
    if (std::find_if(ret.begin(), ret.end(), [](char ch) {return !isdigit(ch) && ch != '.'; }) == ret.end())
    {
        return ret; //ipv4 
    }
    if (std::find_if(ret.begin(), ret.end(), [](char ch) {return !isxdigit(ch) && ch != ':'; }) == ret.end())
    {
        return ret; //ipv6 
    }
    struct addrinfo *res = nullptr;
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    if (getaddrinfo(ret.c_str(), toString(port).c_str(), &hints, &res) == 0)
    {
        char buf[100] = { 0 };
        if (res->ai_family == AF_INET)
        {
            inet_ntop(res->ai_family, &(((sockaddr_in*)res->ai_addr)->sin_addr), buf, 100);
        }
        else if (res->ai_family == AF_INET6)
        {
            inet_ntop(res->ai_family, &(((sockaddr_in6*)res->ai_addr)->sin6_addr), buf, 100);
        }
        return buf;
    }

    return "";
}

