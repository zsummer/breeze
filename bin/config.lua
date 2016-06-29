
local config = {}

config.areaID = 1000


config.db = 
{
    STDictDBMgr = {ip = "127.0.0.1", port = 3306, db = "dict", user = "root", pwd = "123456"},
    STInfoDBMgr = {ip = "127.0.0.1", port = 3306, db = "info", user = "root", pwd = "123456"},
    STLogDBMgr = {ip = "127.0.0.1", port = 3306, db = "log", user = "root", pwd = "123456"},
}

config.docker = 
{
    {
        dockerListenHost="0.0.0.0",
        dockerPubHost="127.0.0.1",
        dockerListenPort=16000,
        dockerWhite={"192.168.", "127.0."},
        clientPubHost="127.0.0.1",
        clientPubPort=26000,
        services={"STLogDBMgr", "STUserMgr", "STUser", "STInfoDBMgr"},
        dockerID = 1,
    },
    {
        dockerListenHost="0.0.0.0",
        dockerPubHost="127.0.0.1",
        dockerListenPort=16001,
        dockerWhite={"192.168.", "127.0."},
        clientPubHost="127.0.0.1",
        clientPubPort=26001,
        webPubHost="127.0.0.1",
        webPort=26080,
        services={"STWebAgent", "STOfflineMgr", "STMinitorMgr", "STUser"},
        dockerID = 2,
    },

    {
        dockerListenHost="0.0.0.0",
        dockerPubHost="127.0.0.1",
        dockerListenPort=17001,
        dockerWhite={"192.168.", "127.0."},
        services={"STWorldMgr"},
        dockerID = 3,
    }, 
}




config.world = 
{
    worldListenHost="0.0.0.0",
    worldListenPort=17001,
    spaceListenHost="0.0.0.0",
    spacePubHost="127.0.0.1",
    spaceListenPort=17002,
}




config.spaces = 
{
    {
        clientListenHost="0.0.0.0",
        clientPubHost="127.0.0.1",
        clientListenPort=17102,
        spaceID = 1,
    },
    {
        clientListenHost="0.0.0.0",
        clientPubHost="127.0.0.1",
        clientListenPort=17102,
        spaceID = 2,
    },
    {
        clientListenHost="0.0.0.0",
        clientPubHost="127.0.0.1",
        clientListenPort=17102,
        spaceID = 3,
    },

}





return config