#include "application.h"
#include "userMgr.h"
#include <ProtoCommon.h>
#include <ProtoDBService.h>
#include <ProtoUser.h>



UserMgr::~UserMgr()
{
    
}

void UserMgr::onTick()
{
    time_t now = getNowTime();
    if (now - _lastTime > 10)
    {
        _lastTime = now;
        LOGA("UserMgr::onTick");
    }
}

void  UserMgr::process(const Tracing & trace, const char * block, unsigned int len)
{
    if (trace._toService == ServiceUserMgr)
    {
        Service::process(trace, block, len);
        return;
    }
    if (trace._toService == ServiceUser || trace._toService == ServiceClient)
    {
        auto founder = _userShells.find(trace._toServiceID);
        if (founder == _userShells.end())
        {
            LOGE("UserMgr not found the user/client id trace=" << trace);
            return;
        }
        const ServiceUserShell & shell = founder->second;
        if (shell._uID != trace._toServiceID)
        {
            LOGF("UserMgr found the user/client id, but user shell store service id not user id or cluster id invalid. trace=" << trace
                <<", shell.uID=" << shell._uID << ", shell.cltID=" << shell._cltID);
            return;
        }
        
        try
        {
            WriteStream ws(ClusterClientForward::getProtoID());
            ws << trace;
            ws.appendOriginalData(block, len);
            Application::getRef().callOtherCluster(shell._cltID, ws.getStream(), ws.getStreamLen());
        }
        catch (std::runtime_error e)
        {
            LOGE("UserMgr::process catch except error. e=" << e.what());
        }
        return;
    }
    LOGF("UserMgr::process trace=" << trace);
}
void UserMgr::onStop()
{
    setWorked(false);
}

void UserMgr::onBuildDB(ReadStream & rs, bool isLast)
{
    SQLQueryResp resp;
    rs >> resp;
    if (resp.retCode == EC_SUCCESS)
    {
        DBResult result;
        result.buildResult((QueryErrorCode)resp.result.qc, resp.result.errMsg, resp.result.sql, resp.result.affected, resp.result.fields);
        if (result.getErrorCode() == QEC_SUCCESS)
        {
            if (isLast)
            {
                setWorked(true);
                LOGI("build usermgr success");
            }
            return;
        }
        else
        {
            if (isLast)
            {
                LOGE("build usermgr error");
                Application::getRef().stop();
            }
            
            LOGE("resp:" << result.getErrorMsg());
        }
    }

    
}
bool UserMgr::onInit()
{
    const auto  & config = ServerConfig::getRef().getClusterConfig();
    for (const auto & cluster : config)
    {
        if (!cluster._wideIP.empty() && cluster._widePort != 0)
        {
            _balance.enableNode(cluster._cluster);
        }
    }

    auto builds = UserBaseInfo().getDBBuild();
    for (auto iter = builds.begin(); iter != builds.end(); ++iter)
    {
        SQLQueryReq req;
        DBQuery q(*iter);
        req.sql = q.pickSQL();
        WriteStream ws(SQLQueryReq::getProtoID());
        ws << req;
        if (iter + 1 != builds.end())
        {
            globalCall(ServiceInfoDBMgr, InvalidServiceID, ws.getStream(), ws.getStreamLen(), std::bind(&UserMgr::onBuildDB, std::static_pointer_cast<UserMgr>(shared_from_this()), _1, false));
        }
        else
        {
            globalCall(ServiceInfoDBMgr, InvalidServiceID, ws.getStream(), ws.getStreamLen(), std::bind(&UserMgr::onBuildDB, std::static_pointer_cast<UserMgr>(shared_from_this()), _1, true));
        }
    }
    

    return true;
}

UserMgr::UserMgr()
{
    slotting<UserAuthReq>(std::bind(&UserMgr::onUserAuthReq, this, _1, _2));
}



void UserMgr::onUserAuthReq(const Tracing & trace, zsummer::proto4z::ReadStream &rs)
{
    UserAuthReq req;
    rs >> req;
    UserAuthResp resp;
    resp.account = req.account;
    resp.token = req.token;
    resp.previews.clear();
    resp.clientClusterID = req.clientClusterID;
    resp.clientSessionID = req.clientSessionID;
    resp.retCode = EC_SUCCESS;

    auto founder = _accountCache.find(req.account);
    if (founder == _accountCache.end())
    {
        return;
    }

    
    
    WriteStream ws(UserAuthResp::getProtoID());
    ws << resp;

    WriteStream wsf(ClusterClientForward::getProtoID());
    wsf << trace;
    wsf.appendOriginalData(ws.getStream(), ws.getStreamLen());
    Application::getRef().callOtherCluster(resp.clientClusterID, wsf.getStream(), wsf.getStreamLen());
}

