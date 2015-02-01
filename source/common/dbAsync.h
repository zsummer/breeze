
/*
* mini-breeze License
* Copyright (C) 2014 YaweiZhang <yawei_zhang@foxmail.com>.
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

/*
*  file desc
*  asynchronous operate db via multi-thread.
*  利用线程异步化DB操作。
*  
*/


#ifndef _DB_ASNYNC_H_
#define _DB_ASNYNC_H_
#include <innerDefined.h>
#include <messageHandler.h>
#include <single.h>
#include <serverConfig.h>
#include <dbhelper/DBHelper.h>

namespace  zsummer
{
	namespace mysql
	{

		class DBAsync : public Singleton<DBAsync>
		{
		public:
			DBAsync();
			~DBAsync();
			bool start();
			bool stop();
		public:

			inline const std::atomic_ullong & getPostCount(){ return _uPostCount; }
			inline const std::atomic_ullong & getFinalCount(){ return _uFinalCount; }
		public:
			void asyncQuery(DBHelperPtr &dbhelper, const string &sql,
				const std::function<void(DBResultPtr)> & handler);
		protected:
			void _asyncQuery(DBHelperPtr &dbhelper, const string &sql,
				const std::function<void(DBResultPtr)> & handler);

			inline void run();

		private:
			std::shared_ptr<std::thread> _thread;
			zsummer::network::ZSummerPtr _summer;
			bool _bRuning = false;
			std::atomic_ullong _uPostCount;
			std::atomic_ullong _uFinalCount;
		};


	}
}
















#endif
