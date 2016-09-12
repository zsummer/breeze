
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
        dockerListenHost="::",
        dockerPubHost="127.0.0.1",
        dockerListenPort=16001,
        clientPubHost="127.0.0.1",
        clientPubPort=26000,
        services={"STLogDBMgr", "STAvatarMgr", "STAvatar", "STInfoDBMgr"},
        dockerID = 1,
    },
    {
        dockerListenHost="::",
        dockerPubHost="127.0.0.1",
        dockerListenPort=16002,
        clientPubHost="127.0.0.1",
        clientPubPort=26001,
        webPubHost="127.0.0.1",
        webPort=26080,
        services={"STWebAgent", "STOfflineMgr", "STMinitorMgr", "STAvatar"},
        dockerID = 2,
    },

    {
        desc="异构服务器, 注释掉该配置则起服忽略该服务的存在.",
        dockerListenHost="::",
        dockerPubHost="127.0.0.1",
        dockerListenPort=16099,
        dockerWhite={"192.168.", "127.0."},
        services={"STWorldMgr"},
        dockerID = 3,
    }, 
}




config.world = 
{
    dockerListenHost="::",
    dockerListenPort=16099,
    sceneListenHost="::",
    scenePubHost="127.0.0.1",
    sceneListenPort=16088,
}




config.scenes = 
{
    {
        sceneID = 1,
        supportSceneTypes = {1}, --该项不存在则代表支持主城以外的所有场景类型, 如果有该类型 则仅仅支持枚举到的场景类型. 1是主城  
        clientListenHost="::",
        clientPubHost="127.0.0.1",
        clientListenPort=17101,
    },
    {
        sceneID = 2,
        supportSceneTypes = {1},
        clientListenHost="::",
        clientPubHost="127.0.0.1",
        clientListenPort=17102,
    },
    {
        sceneID = 3,
        --supportSceneTypes = {1}, 
        clientListenHost="::",
        clientPubHost="127.0.0.1",
        clientListenPort=17103,
    },
    {
        sceneID = 4,
        --supportSceneTypes = {1},
        clientListenHost="::",
        clientPubHost="127.0.0.1",
        clientListenPort=17104,
    },

}





return config