//=============================================================================
// ServerInterface.h
//
// Exception :
//      ����������غ꣬�򻯷����ʵ�֡�
//
//=============================================================================
#ifndef ____ZJY_Server_Interface_H_
#define ____ZJY_Server_Interface_H_

// Include Headers
//-----------------------------------------------------------------------------
#include <time.h>
#include <ObjBase.h>

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include "../../../../sdk/include/Game/Server/IGameMainManager.h"
#include "../../../../sdk/include/common/comstruct.h"
//#include "../../../../ServerPlatform/NewServer_Change/GameManager/UserInfo.h"

#ifndef GAMESERVER_EXPORTS
#define GAMESERVER_EXPORTS
#endif

#include "../../../../sdk/include/Game/Server/IGameDesk.h"

#ifdef  WIN32_LEAN_AND_MEAN
#undef  WIN32_LEAN_AND_MEAN
#endif

#include "../games/zjy/_game_def.h"

// �ڴ�֮ǰ���붨���: _game_id / _game_name / _player_max
//-----------------------------------------------------------------------------

#ifndef _game_id
#error  _game_id also isn't defined, please defined _game_id. Example: #define _game_id 12345678
#endif

#ifndef _game_name
#error  _game_name also isn't defined, please defined _game_name. Example: #define _game_name "name"
#endif

#ifndef _player_max
#error  _player_max also isn't defined, please defined _player_max. Example: #define _player_max 4
#endif

#ifndef _zjy_cs_type
#define _zjy_cs_type    _zjy_server
#else
#error  _zjy_cs_type should be undefined
#endif

#include "../games/zjy/_game_timer.h"
#include "../games/zjy/_game_config.h"
#include "../games/zjy/_game_server.h"

//=============================================================================
// ����˽ӿں궨��
//=============================================================================
//-----------------------------------------------------------------------------
// ����˽ӿں꣬ʹ�øöԺ����ֱ�Ӽ̳з���˻��࣬��Ҫ�ṩ�Լ���������
#define _DefineServerInterfaceBegin(clsname) _zjy_space_in class clsname : public __zjy_server_interface_base {  \
    typedef __zjy_server_interface_base _BaseClassT; typedef clsname _MyClassT;
#define _DefineServerInterfaceEnd   }; _zjy_space_out

//-----------------------------------------------------------------------------
// ��Ϣӳ��꣬����ʹ��_AddProcMsg����ϢID�ʹ������󶨡�
#define _HandleMessageBegin     virtual int HandleNotifyMessage(int pos, msg_t msg, buf_t buf, int len) {   \
                                    if (!_CheckPlayer(pos)) return hr_fail; switch (msg) {
#define _HandleMessageEnd       case 0: default: break; } return hr_success; }
#define _AddProcMsg(msg, proc)  case msg: return proc(pos, buf, len);

//-----------------------------------------------------------------------------
// ʹ����������
#define _CallConfig _cfg_t::GetInstance()[_Info.m_iRoomID]

// �������ã����ṩ�������ݳ�ʼ���ͼ���ʵ�֣���Ҫ�ṩ��������������
#define _DeclareServerConfigHandle(clsname) typedef _zjy _config_info<clsname> _cfg_t;          \
    virtual void __Init_Instance_Config() {                                                     \
        if (!(_cfg_t::GetInstance().IsKey(_Info.m_iRoomID))) {                                  \
            _cfg_t::GetInstance()[_Info.m_iRoomID].SetIKey(_Info.m_iRoomID, _Info.m_iTableID);  \
            _cfg_t::GetInstance()[_Info.m_iRoomID].LoadConfig();                                \
        } else {                                                                                \
            if (_Info.m_iTableID == _cfg_t::GetInstance()[_Info.m_iRoomID].GetTableID())        \
                _cfg_t::GetInstance()[_Info.m_iRoomID].LoadConfig();                            \
    } }
    
//-----------------------------------------------------------------------------
// ���ݶ�ʱ��IDʹ�ö�ʱ��
#define _CallTimer(tid)             _TimerMgr[tid]

// ������ʱ�������ߣ����ṩ��ʱ����ʼ��ʵ�֡�
#define _DeclareServerTimerHandle mutable _timer_manager<_MyClassT, mgr_t, _tid_max> _TimerMgr; \
    virtual void __Init_Instance_Timer() {                                                      \
        for (int i = _tid_begin; i < _tid_max; ++i) {                                           \
            _CallTimer(i).SetParam(_Info.m_iTableID);                                           \
            _CallTimer(i).Appoint(_gmMgr);                                                      \
    } }

// �ӳٵ���
#define _DelayCall(s, pf, p1, p2)  _TimerMgr.AddDelayCall(s, &_MyClassT::pf, p1, p2)

// ��ʱ��ӳ��꣬����ʹ��_AddProcTimer����ʱ��ID�ʹ�������
#define _HandleTimerBegin   virtual int OnGameTimer(int timerid) {                              \
                                if (_tid_def_value + _tid_begin > timerid)                      \
                                    return _TimerMgr.CallDefTimer(timerid - _tid_begin, this);  \
                                switch (timerid) {
#define _HandleTimerEnd         case _tid_max: default: break; } return hr_success; }
#define _AddProcTimer(tid, pf)  case tid: return pf(_CallTimer(tid).GetElapsed());

//=============================================================================
// �����ʵ������Ĵ������ͷ�
//=============================================================================
#define _DefineServerInstanceHandle(clsname) extern "C" {                   \
_game_interface bool CreateGameServer(IGameDesk **ppIGameDesk)              \
{                                                                           \
    if (nullptr != ppIGameDesk)                                             \
    {                                                                       \
        *ppIGameDesk = new clsname;                                         \
        return (nullptr != *ppIGameDesk);                                   \
    }                                                                       \
                                                                            \
    return false;                                                           \
}                                                                           \
_game_interface void DestroyGameServer(IGameDesk** ppIGameDesk)             \
{                                                                           \
    if (ppIGameDesk)                                                        \
    {                                                                       \
        if (*ppIGameDesk)                                                   \
        {                                                                   \
            delete *ppIGameDesk;                                            \
            *ppIGameDesk = nullptr;                                         \
        }                                                                   \
    }                                                                       \
}                                                                           \
_game_interface BOOL GetServiceInfo(_zjy sdis_t* info, UINT ver)            \
{                                                                           \
    if ((1 != ver) || (nullptr == info))                                    \
        return FALSE;                                                       \
                                                                            \
    memset(info, 0, sizeof(_zjy sdis_t));                                   \
                                                                            \
    info->uServiceVer               = 1;                                    \
    info->uNameID                   = _game_id;                             \
    info->uDeskPeople               = _player_max;                          \
    info->uSupportType              = 1 | 2 | 4;                            \
    strcpy_s(info->szGameName,      _game_name);                            \
    strcpy_s(info->szWriter,        "Frank");                               \
    strcpy_s(info->szDllNote,       "Frank in ZYL");                        \
    sprintf_s(info->szDLLFileName,  "%d.dll", _game_id);                    \
                                                                            \
    return TRUE;                                                            \
} }

#endif

//  														2014-9 by Frank
//-----------------------------------------------------------------------------