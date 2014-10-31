/*
 * genProto License
 * -----------
 * 
 * genProto is licensed under the terms of the MIT license reproduced below.
 * This means that genProto is free software and can be used for both academic
 * and commercial purposes at absolutely no cost.
 * 
 * 
 * ===============================================================================
 * 
 * Copyright (C) 2014 YaweiZhang <yawei_zhang@foxmail.com>.
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



#include "utility.h"
#include "log4z.h"
#include "tinyxml2.h"
#include "genProto.h"













using namespace zsummer::utility;

int main(int argc, char *argv[])
{
	zsummer::log4z::ILog4zManager::GetInstance()->Start();
	std::vector<_FileInfo> files;
	if (!SearchFiles("./", files))
	{
		LOGE("SearchFiles error.");
		return 0;
	}
	LOGA("FOUND FILE COUNT = " << files.size());
	std::cout << "\r\n" << std::endl;


	
	for (auto & file : files)
	{
		std::string filename = file.filename;
		if (filename.size() <= 4)
		{
			continue;
		}
		std::string xmlattr = filename.substr(filename.length() - 4, 4);
		if (xmlattr != ".xml")
		{
			continue;
		}
		filename = filename.substr(0, filename.size() - 4);
		
		genProto gen(filename);
		ParseCode pc = gen.ParseCache();
		if (pc == PC_ERROR)
		{
			LOGE("LoadCache Error. filename=" << filename);
			return 0;
		}
		zsummer::utility::SleepMillisecond(150);
		pc = gen.ParseConfig();
		if (pc == PC_ERROR)
		{
			LOGE("LoadConfig Error. filename=" << filename);
			return 0;
		}
		zsummer::utility::SleepMillisecond(120);

		pc = gen.GenCode();
		if (pc == PC_ERROR)
		{
			LOGE("GenCPP Error. filename=" << filename);
			return 0;
		}
		else if (pc == PC_NEEDSKIP)
		{
			LOGD("SKIP WriteCache. filename=" << filename);
			zsummer::utility::SleepMillisecond(120);
			continue;
		}
		zsummer::utility::SleepMillisecond(120);

		pc = gen.WriteCache();
		if (pc == PC_ERROR)
		{
			LOGE("WriteNoCache Error. filename=" << filename);
			return 0;
		}
		std::cout << "\r\n\r\n" << std::endl;
		zsummer::utility::SleepMillisecond(222);

	}
	
	LOGA("All Success..");
	zsummer::utility::SleepMillisecond(2000);

	return 0;
}






