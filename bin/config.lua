
local config = {}

config.traits = {platid = 1000, areaid = 1000}


config.db = 
{
	info = {ip = "192.168.1.101", port = 3306, db = "db_info", user = "root", pwd = "123456"},
	log = {ip = "192.168.1.101", port = 3306, db = "db_log", user = "root", pwd = "123456"},
--	info = {ip = "127.0.0.1", port = 3306, db = "db_info", user = "root", pwd = "123456"},
--	log = {ip = "127.0.0.1", port = 3306, db = "db_log", user = "root", pwd = "123456"},
}



config.listen = 
{
	logic= 
		{
			{ip = "0.0.0.0", port=21010, index = 0},
			{ip = "0.0.0.0", port=21011, index = 1},
		},
}


config.connect = 
{
	stress =
		{
			{dstNode = "logic", ip="127.0.0.1", port=21010, index = 0},
		},
}


return config