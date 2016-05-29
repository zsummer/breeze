 
Proto4z.SQLFieldArray = {}  
Proto4z.SQLFieldArray.__getName = "SQLFieldArray" 
Proto4z.SQLFieldArray.__getDesc = "array" 
Proto4z.SQLFieldArray.__getTypeV = "string" 
 
Proto4z.register(41000,"SQLResult") 
Proto4z.SQLResult = {}  
Proto4z.SQLResult.__getID = 41000 
Proto4z.SQLResult.__getName = "SQLResult" 
Proto4z.SQLResult[1] = {name="qc", type="ui16" }  
Proto4z.SQLResult[2] = {name="errMsg", type="string" }  
Proto4z.SQLResult[3] = {name="sql", type="string" }  
Proto4z.SQLResult[4] = {name="affected", type="ui64" }  
Proto4z.SQLResult[5] = {name="fields", type="SQLFieldArray" }  
 
Proto4z.register(41001,"SQLQueryReq") 
Proto4z.SQLQueryReq = {}  
Proto4z.SQLQueryReq.__getID = 41001 
Proto4z.SQLQueryReq.__getName = "SQLQueryReq" 
Proto4z.SQLQueryReq[1] = {name="sql", type="string" }  
 
Proto4z.register(41002,"SQLQueryResp") 
Proto4z.SQLQueryResp = {}  
Proto4z.SQLQueryResp.__getID = 41002 
Proto4z.SQLQueryResp.__getName = "SQLQueryResp" 
Proto4z.SQLQueryResp[1] = {name="retCode", type="ui16" }  
Proto4z.SQLQueryResp[2] = {name="result", type="SQLResult" }  
