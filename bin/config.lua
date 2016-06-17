
local config = {}

config.areaid = 1000


config.db = 
{
    STDBMgr = {ip = "127.0.0.1", port = 3306, db = "db_info", user = "root", pwd = "123456"},
    STInfoDBMgr = {ip = "127.0.0.1", port = 3306, db = "db_info", user = "root", pwd = "123456"},
    STLogDBMgr = {ip = "127.0.0.1", port = 3306, db = "db_info", user = "root", pwd = "123456"},
}

config.docker = 
{
    {
        serviceBindIP="0.0.0.0",
        serviceIP="127.0.0.1",
        servicePort=16000,
        serviceWhite={"192.168.", "127.0."},
        wideIP="127.0.0.1",
        widePort=26000,
        services={"STLogDBMgr", "STUserMgr", "STUser", "STInfoDBMgr"},
        dockerID = 1,
    },
    {
        serviceBindIP="0.0.0.0",
        serviceIP="127.0.0.1",
        servicePort=16001,
        serviceWhite={"192.168.", "127.0."},
        wideIP="127.0.0.1",
        widePort=26001,
        webIP="127.0.0.1",
        webPort=26080,
        services={"STWebAgent", "STOfflineMgr", "STMinitorMgr", "STUser"},
        dockerID = 2,
    },


}



return config