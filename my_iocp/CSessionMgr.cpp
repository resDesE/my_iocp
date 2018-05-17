#include "stdafx.h"
#include "CSessionMgr.h"

CSessionMgr::CSessionMgr()
{
}

CSessionMgr::~CSessionMgr()
{
}

int CSessionMgr::OnAddSession(SOCKET sockSession)
{

    if (m_mapSessionInfos.find(sockSession) == m_mapSessionInfos.end())
    {
        CSession* pSession = new(std::nothrow) CSession(sockSession);
        if (nullptr != pSession)
        {
            m_mapSessionInfos.insert(std::make_pair(sockSession, pSession));
        }
    }
    else
    {
        return -1;
    }
    return 0;
}

int CSessionMgr::OnDelSession(SOCKET sock)
{
    MAPSESSIONINFO::iterator iter = m_mapSessionInfos.find(sock);
    if (iter != m_mapSessionInfos.end())
    {
        m_mapSessionInfos.erase(iter);
    }
    return 0;
}

CSession* CSessionMgr::OnGetSessionBySock(SOCKET sockSession)
{
    MAPSESSIONINFO::iterator iter = m_mapSessionInfos.find(sockSession);
    if (iter == m_mapSessionInfos.end())
    {
        return nullptr;
    }
    return iter->second;
}
