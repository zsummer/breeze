
local config = {}

config.areaid = 1000


config.db = 
{
    ServiceDictDBMgr = {ip = "127.0.0.1", port = 3306, db = "db_info", user = "root", pwd = "123456"},
    ServiceInfoDBMgr = {ip = "127.0.0.1", port = 3306, db = "db_info", user = "root", pwd = "123456"},
    ServiceLogDBMgr = {ip = "127.0.0.1", port = 3306, db = "db_info", user = "root", pwd = "123456"},
}

config.docker = 
{
    {
        serviceBindIP="0.0.0.0",
        serviceIP="127.0.0.1",
        servicePort=16000,
        serviceWhite={"192.168.", "127.0."},
        wideIP="",
        widePort=0,
        services={"ServiceDictDBMgr", "ServiceLogDBMgr", "ServiceUserMgr"},
        dockerID = 1,
    },
    {
        serviceBindIP="0.0.0.0",
        serviceIP="127.0.0.1",
        servicePort=16001,
        serviceWhite={"192.168.", "127.0."},
        wideIP="",
        widePort=0,
        services={"ServiceInfoDBMgr"},
        dockerID = 2,
    },
    {
        serviceBindIP="0.0.0.0",
        serviceIP="127.0.0.1",
        servicePort=16002,
        serviceWhite={"192.168.", "127.0."},
        wideIP="",
        widePort=0,
        services={"ServiceUser"},
        dockerID = 3,
    },
    {
        serviceBindIP="0.0.0.0",
        serviceIP="127.0.0.1",
        servicePort=16003,
        serviceWhite={"192.168.", "127.0."},
        wideIP="",
        widePort=0,
        services={"ServiceUser"},
        dockerID = 4,
    },
    {
        serviceBindIP="0.0.0.0",
        serviceIP="127.0.0.1",
        servicePort=16004,
        serviceWhite={"192.168.", "127.0."},
        wideIP="",
        widePort=0,
        services={"ServiceUser"},
        dockerID = 5,
    },

    {
        serviceBindIP="0.0.0.0",
        serviceIP="127.0.0.1",
        servicePort=16005,
        serviceWhite={"192.168.", "127.0."},
        wideIP="",
        widePort=0,
        services={"ServiceUser"},
        dockerID = 6,
    },
    {
        serviceBindIP="0.0.0.0",
        serviceIP="127.0.0.1",
        servicePort=16006,
        serviceWhite={"192.168.", "127.0."},
        wideIP="127.0.0.1",
        widePort=26001,
        services={},
        dockerID = 7,
    },
    {
        serviceBindIP="0.0.0.0",
        serviceIP="127.0.0.1",
        servicePort=16007,
        serviceWhite={"192.168.", "127.0."},
        wideIP="127.0.0.1",
        widePort=26002,
        services={},
        dockerID = 8,
    },

    {
        serviceBindIP="0.0.0.0",
        serviceIP="127.0.0.1",
        servicePort=16008,
        serviceWhite={"192.168.", "127.0."},
        wideIP="127.0.0.1",
        widePort=26003,
        services={},
        dockerID = 9,
    },
    {
        serviceBindIP="0.0.0.0",
        serviceIP="127.0.0.1",
        servicePort=16009,
        serviceWhite={"192.168.", "127.0."},
        wideIP="127.0.0.1",
        widePort=26004,
        services={},
        dockerID = 10,
    },


}



return config