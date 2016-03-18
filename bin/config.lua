
local config = {}

config.areaid = 1000


config.db = 
{
	DictDBMgr = {ip = "127.0.0.1", port = 3306, db = "db_info", user = "root", pwd = "123456"},
	InfoDBMgr = {ip = "127.0.0.1", port = 3306, db = "db_info", user = "root", pwd = "123456"},
    LogDBMgr = {ip = "127.0.0.1", port = 3306, db = "db_info", user = "root", pwd = "123456"},
}

config.cluster = 
{
    {
        serviceBindIP="0.0.0.0",
        serviceIP="127.0.0.1",
        servicePort=16000,
        serviceWhite={"192.168.", "127.0."},
        wideIP="127.0.0.1",
        widePort=26000,
        services={"DictDBMgr", "UserMgr"},
        cluster = 1,
    },
    {
        serviceBindIP="0.0.0.0",
        serviceIP="127.0.0.1",
        servicePort=16001,
        serviceWhite={"192.168.", "127.0."},
        wideIP="127.0.0.1",
        widePort=26001,
        services={"InfoDBMgr"},
        cluster = 2,
    },


}



return config