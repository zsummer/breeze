

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

bool removeFile(const std::string &pathfile)
{
    return ::remove(pathfile.c_str()) == 0;
}
bool removeDir(const std::string &path)
{
    return ::rmdir(path.c_str()) == 0;
}
bool hadFile(const std::string &pathfile)
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
    if (ret.back() != '/') ret += "/";
    return ret;
}

static bool tmpSearchPath(std::string  path, std::vector<SearchFileInfo> & files)
{
    if (path.length() == 0)
    {
        return false;
    }
    path = fixPathString(path);

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
                files.push_back(file);
                tmpSearchPath(file.fullpath, files);
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
            files.push_back(file);
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
            files.push_back(file);
            tmpSearchPath(file.fullpath, files);
        }
        else
        {
            memset(&file, 0, sizeof(file));
            file.bDir = false;
            file.filesize = statbuf.st_size;
            strcpy(file.filename, entry->d_name);
            file.fullpath[0] = '\0';
            files.push_back(file);
        }
    }
    closedir(dp);
#endif
    return true;
}

bool searchFiles(std::string path, std::vector<SearchFileInfo> & files)
{
    if (files.capacity() < 100)
    {
        files.reserve(100);
    }
    return tmpSearchPath(path, files);
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
std::vector<std::string> splitString(std::string text, std::string deli, std::string ign)
{
    trim(text, ign);
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



time_t getUTCTimeFromLocalString(const std::string & str)
{
    std::string sdate;
    std::string stime;
    if (str.find(' ') != std::string::npos)
    {
        auto sp = splitString(str, " ", " ");
        if (sp.size() < 2)
        {
            return 0;
        }
        sdate = sp.front();
        stime = sp.back();
    }
    else
    {
        if (str.find(':') != std::string::npos)
        {
            stime = str;
            trim(stime, " ");
        }
        else
        {
            sdate = str;
            trim(sdate, " ");
        }
    }
    struct tm st;
    memset(&st, 0, sizeof(st));
    if (!sdate.empty())
    {
        std::string deli;
        if (sdate.find('-') != std::string::npos)
        {
            deli = "-";
        }
        else if (sdate.find('/') != std::string::npos)
        {
            deli = "/";
        }
        else if (sdate.find('\\') != std::string::npos)
        {
            deli = "\\";
        }
        std::vector<std::string> spdate;
        if (!deli.empty())
        {
            spdate = splitString(sdate, deli, " ");
        }
        else if (sdate.size() == 8)
        {
            spdate.push_back(sdate.substr(0, 4));
            spdate.push_back(sdate.substr(4, 2));
            spdate.push_back(sdate.substr(6, 2));
        }
        if (!spdate.empty())
        {
            if (spdate.back().size() == 4)
            {
                st.tm_year = fromString<int>(spdate.back(), 1900) - 1900;
                if (spdate.size() >= 2)
                {
                    st.tm_mon = fromString<int>(spdate[spdate.size() - 2], 1) - 1;
                }
                if (spdate.size() >= 3)
                {
                    st.tm_mday = fromString<int>(spdate[spdate.size() - 3], 1);
                }
            }
            else
            {
                st.tm_year = fromString<int>(spdate.front(), 1900) - 1900;
                if (spdate.size() >= 2)
                {
                    st.tm_mon = fromString<int>(spdate[1], 1) - 1;
                }
                if (spdate.size() >= 3)
                {
                    st.tm_mday = fromString<int>(spdate[2], 1);
                }
            }
        }
    } //sdate
    if (!stime.empty())
    {
        auto sptime = splitString(stime, ":", " ");
        if (sptime.size() >= 1)
        {
            st.tm_hour = fromString<int>(sptime[0], 0);
        }
        if (sptime.size() >= 2)
        {
            st.tm_min = fromString<int>(sptime[1], 0);
        }
        if (sptime.size() >= 3)
        {
            st.tm_sec = fromString<int>(sptime[2], 0);
        }
    }
    st.tm_year = pruning(st.tm_year, 70, 200);
    st.tm_mon = pruning(st.tm_mon, 0, 11);
    st.tm_mday = pruning(st.tm_mday, 1, 31);
    st.tm_hour = pruning(st.tm_hour, 0, 23);
    st.tm_min = pruning(st.tm_min, 0, 59);
    st.tm_sec = pruning(st.tm_sec, 0, 59);
    return mktime(&st);
}

time_t getSecondFromTimeString(const std::string & str)
{
    auto sptime = splitString(str, ":", " ");
    int hour = 0;
    int minute = 0;
    int second = 0;
    if (sptime.size() >= 1)
    {
        hour = fromString<int>(sptime[0], 0);
    }
    if (sptime.size() >= 2)
    {
        minute = fromString<int>(sptime[1], 0);
    }
    if (sptime.size() >= 3)
    {
        second = fromString<int>(sptime[2], 0);
    }
    hour = pruning(hour, 0, 23);
    minute = pruning(minute, 0, 59);
    second = pruning(second, 0, 59);
    return hour * 3600 + minute * 60 + second;
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

#ifdef __APPLE__
//std::mt19937 __genRandom; // not thread safe - -!
#elif defined(WIN32)
//__declspec(thread) char __genRandomBacking[sizeof(std::mt19937)];
//__declspec(thread) std::mt19937* __genRandom; //vs2013 support
//__declspec(thread) bool __genRandomInited = false;
#else
thread_local std::mt19937 __genRandom; //vs2015 support
#endif
//rand
//==========================================================================
unsigned int realRand()
{
#ifdef WIN32
    return (rand() << 20) | (rand() << 8) | rand();
//    if (!__genRandomInited)
//    {
//        __genRandom = new(__genRandomBacking)std::mt19937();
//        __genRandomInited = true;
//    }
//    return (*__genRandom)();
#elif defined(__APPLE__)
    return (rand() << 20) |(rand() << 8)  | rand(); 
#else
    return __genRandom();
#endif
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



