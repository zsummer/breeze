--require
--process msg
package.path =  "../../depends/include/proto4z/?.lua;" .. package.path
local config = require("config")
require("proto4z")

dump = Proto4z.dump

dump(Scene)




