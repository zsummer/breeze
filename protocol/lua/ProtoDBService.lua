 
Proto4z.DBStringArray = {}  
Proto4z.DBStringArray.__protoName = "DBStringArray" 
Proto4z.DBStringArray.__protoDesc = "array" 
Proto4z.DBStringArray.__protoTypeV = "string" 
 
Proto4z.register(3000,"DBDataResult") 
Proto4z.DBDataResult = {}  
Proto4z.DBDataResult.__protoID = 3000 
Proto4z.DBDataResult.__protoName = "DBDataResult" 
Proto4z.DBDataResult[1] = {name="qc", type="ui16" }  
Proto4z.DBDataResult[2] = {name="errMsg", type="string" }  
Proto4z.DBDataResult[3] = {name="sql", type="string" }  
Proto4z.DBDataResult[4] = {name="affected", type="ui64" }  
Proto4z.DBDataResult[5] = {name="fields", type="DBStringArray" }  
 
Proto4z.DBDataResultArray = {}  
Proto4z.DBDataResultArray.__protoName = "DBDataResultArray" 
Proto4z.DBDataResultArray.__protoDesc = "array" 
Proto4z.DBDataResultArray.__protoTypeV = "DBDataResult" 
 
Proto4z.register(3001,"DBQueryReq") 
Proto4z.DBQueryReq = {} --通用SQL语句执行协议 
Proto4z.DBQueryReq.__protoID = 3001 
Proto4z.DBQueryReq.__protoName = "DBQueryReq" 
Proto4z.DBQueryReq[1] = {name="sql", type="string" }  
 
Proto4z.register(3002,"DBQueryResp") 
Proto4z.DBQueryResp = {} --通用SQL语句执行协议返回,DBDataResult可以借助dbHepler进行构建DBResult 
Proto4z.DBQueryResp.__protoID = 3002 
Proto4z.DBQueryResp.__protoName = "DBQueryResp" 
Proto4z.DBQueryResp[1] = {name="retCode", type="ui16" }  
Proto4z.DBQueryResp[2] = {name="result", type="DBDataResult" }  
 
Proto4z.register(3003,"DBQueryArrayReq") 
Proto4z.DBQueryArrayReq = {} --通用批量SQL语句执行协议 
Proto4z.DBQueryArrayReq.__protoID = 3003 
Proto4z.DBQueryArrayReq.__protoName = "DBQueryArrayReq" 
Proto4z.DBQueryArrayReq[1] = {name="sqls", type="DBStringArray" }  
 
Proto4z.register(3004,"DBQueryArrayResp") 
Proto4z.DBQueryArrayResp = {} --通用批量SQL语句执行协议 
Proto4z.DBQueryArrayResp.__protoID = 3004 
Proto4z.DBQueryArrayResp.__protoName = "DBQueryArrayResp" 
Proto4z.DBQueryArrayResp[1] = {name="retCode", type="ui16" }  
Proto4z.DBQueryArrayResp[2] = {name="results", type="DBDataResultArray" } --批量返回,注意不要超出协议包最大长度 
