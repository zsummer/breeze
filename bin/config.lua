
local config = {}

config.traits = {platid = 1000, areaid = 1000}


config.db = 
{
	--info = {ip = "192.168.15.216", port = 3306, db = "db_info", user = "root", pwd = "123456"},
	--log = {ip = "192.168.15.216", port = 3306, db = "db_log", user = "root", pwd = "123456"},
	info = {ip = "127.0.0.1", port = 3306, db = "db_info", user = "root", pwd = "123456"},
	log = {ip = "127.0.0.1", port = 3306, db = "db_log", user = "root", pwd = "123456"},
}



config.listen = 
{
	logic= 
		{
			{
				ip = "0.0.0.0", 
				port=8081,
				white={"192.168.", "127.0."},
				wip="0.0.0.0", 
				wport=20000,
				index = 0
			},
		},
}


config.connect = 
{
	stress =
		{
			{dstType = "logic", ip="127.0.0.1", port=20000, index = 0},
		},
}


return config