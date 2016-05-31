 
Proto4z.SQLStringArray = {}  
Proto4z.SQLStringArray.__getName = "SQLStringArray" 
Proto4z.SQLStringArray.__getDesc = "array" 
Proto4z.SQLStringArray.__getTypeV = "string" 
 
Proto4z.register(41000,"SQLResult") 
Proto4z.SQLResult = {}  
Proto4z.SQLResult.__getID = 41000 
Proto4z.SQLResult.__getName = "SQLResult" 
Proto4z.SQLResult[1] = {name="qc", type="ui16" }  
Proto4z.SQLResult[2] = {name="errMsg", type="string" }  
Proto4z.SQLResult[3] = {name="sql", type="string" }  
Proto4z.SQLResult[4] = {name="affected", type="ui64" }  
Proto4z.SQLResult[5] = {name="fields", type="SQLStringArray" }  
 
Proto4z.register(41001,"SQLQueryReq") 
Proto4z.SQLQueryReq = {} --通用SQL语句执行协议 
Proto4z.SQLQueryReq.__getID = 41001 
Proto4z.SQLQueryReq.__getName = "SQLQueryReq" 
Proto4z.SQLQueryReq[1] = {name="sql", type="string" }  
 
Proto4z.register(41002,"SQLQueryResp") 
Proto4z.SQLQueryResp = {} --通用SQL语句执行协议返回,SQLResult可以借助dbHepler进行构建DBResult 
Proto4z.SQLQueryResp.__getID = 41002 
Proto4z.SQLQueryResp.__getName = "SQLQueryResp" 
Proto4z.SQLQueryResp[1] = {name="retCode", type="ui16" }  
Proto4z.SQLQueryResp[2] = {name="result", type="SQLResult" }  
 
Proto4z.register(41005,"SQLQueryArrayReq") 
Proto4z.SQLQueryArrayReq = {} --通用批量SQL语句执行协议 
Proto4z.SQLQueryArrayReq.__getID = 41005 
Proto4z.SQLQueryArrayReq.__getName = "SQLQueryArrayReq" 
Proto4z.SQLQueryArrayReq[1] = {name="sqls", type="SQLStringArray" }  
 
Proto4z.register(41006,"SQLQueryArrayResp") 
Proto4z.SQLQueryArrayResp = {} --通用批量SQL语句执行协议 
Proto4z.SQLQueryArrayResp.__getID = 41006 
Proto4z.SQLQueryArrayResp.__getName = "SQLQueryArrayResp" 
Proto4z.SQLQueryArrayResp[1] = {name="retCode", type="ui16" }  
Proto4z.SQLQueryArrayResp[2] = {name="result", type="SQLResult" } --只有错误时候才有数据 
