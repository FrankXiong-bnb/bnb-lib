//=============================================================================
// ClientInterface.h
//
// Exception :
//      ����ͻ�����غ꣬�򻯿ͻ���ʵ�֡�
//
//=============================================================================
#ifndef ____ZJY_Client_Interface_H_
#define ____ZJY_Client_Interface_H_

// Include Headers
//-----------------------------------------------------------------------------
#include <time.h>
#include <ObjBase.h>

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include "../../../../sdk/include/common/comstruct.h"
#include "../../../../sdk/include/Client/UI_ForLogic/IUserInterface.h"
#include "../../../../sdk/include/Client/Common/UIMessageDefines.h"
#include "../../../../sdk/include/Game/IGameBase.h"

#ifndef GAMEIMPLEMENT_EXPORTS
#define GAMEIMPLEMENT_EXPORTS
#endif

#include "../../../../sdk/include/Game/IGameImplement.h"

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
#define _zjy_cs_type    _zjy_client
#else
#error  _zjy_cs_type should be undefined
#endif

#include "../games/zjy/_game_timer.h"
#include "../games/zjy/_game_config.h"
#include "../games/zjy/_game_control.h"
#include "../games/zjy/_game_client.h"

//#include "../games/zjy/_control_base.h"
//#include "../games/zjy/_list_control.h"

//=============================================================================
// �ͻ��˽ӿں궨��
//=============================================================================
//-----------------------------------------------------------------------------
// �ͻ��˽ӿں꣬ʹ�øöԺ����ֱ�Ӽ̳пͻ��˻��࣬��Ҫ�ṩ�Լ���������
#define _DefineClientInterfaceBegin(clsname) _zjy_space_in class clsname : public __zjy_client_interface_base {  \
    typedef __zjy_client_interface_base _BaseClassT; typedef clsname _MyClassT;
#define _DefineClientInterfaceEnd   }; _zjy_space_out

//-----------------------------------------------------------------------------
// ���ݶ�ʱ��IDʹ�ö�ʱ��
#define _CallTimer(tid)     _TimerMgr[tid]

// ������ʱ�������ߣ����ṩ��ʱ����ʼ��ʵ�֡�
#define _DeclareClientTimerHandle mutable _timer_manager<_MyClassT, gbase_t, _tid_max> _TimerMgr;   \
    virtual void __Init_Instance_Timer() {                                                          \
        for (int i = _tid_begin; i < _tid_max; ++i)                                                 \
            _CallTimer(i).Appoint(_gbMgr);                                                          \
    }

// �ӳٵ���
#define _DelayCall(s, pf, p1, p2)  _TimerMgr.AddDelayCall(s, &_MyClassT::pf, p1, p2)

// ��ʱ��ӳ��꣬����ʹ��_AddProcTimer����ʱ��ID�ʹ�������
#define _HandleTimerBegin           virtual void OnTimer(int timerid) {                             \
            if (_tid_def_value + _tid_begin > timerid)                                              \
                { _TimerMgr.CallDefTimer(timerid - _tid_begin, this); return; }                     \
            switch (timerid) {
#define _HandleTimerEnd             case _tid_max: default: break; } }
#define _AddProcTimer(tid, proc)    case tid: proc(_CallTimer(tid).GetElapsed()); break;

//-----------------------------------------------------------------------------
// ʹ����������
#define _CallConfig _cfg_t::GetInstance()[0]

// �������ã����ṩ�������ݳ�ʼ���ͼ���ʵ�֣���Ҫ�ṩ��������������
#define _DeclareClientConfigHandle(clsname)     typedef _zjy _config_info<clsname> _cfg_t;          \
    virtual void __Init_Instance_Config() { _cfg_t::GetInstance()[0].LoadConfig(); }

//-----------------------------------------------------------------------------
// �ؼ���Ϣӳ��꣬ʹ��_AddCtrlMsg���Խ��ؼ���Ϣ�ʹ������󶨡�
#define _HandleCtrlBegin            virtual int OnUIMessage(TUIMessage* pMsg){                      \
            param_t lparam = (param_t)(((param_t)pMsg->_mouseX<<16) | ((param_t)pMsg->_mouseY));    \
            param_t wparam = pMsg->_ch;                                                             \
            switch (pMsg->_uMessageType) {
#define _HandleCtrlEnd              case 0: default: break; } return hr_success; }
#define _AddCtrlMsg(msg, proc)      case msg: return proc(pMsg->_uControlID, lparam, wparam);

//-----------------------------------------------------------------------------
// ��Ϣӳ��꣬����ʹ��_AddProcMsg����ϢID�ʹ������󶨡�
#define _HandleMessageBegin         virtual int HandleGameMessage(WORD MainID, WORD msg, buf_t buf, int len) {  \
    if (_Main_Msg_ID != MainID) return hr_fail; switch (msg) { case _gm_update: return _OnReceiveUpdate(buf, len);
#define _HandleMessageEnd           default: break; } return hr_success; }
#define _AddProcMsg(msg, proc)      case msg: return proc(buf, len);

//=============================================================================
// �ͻ��˶���Ĵ������ͷ�
//=============================================================================
#define _DefineClientInstanceHandle(clsname) extern "C" {                                   \
_game_interface _zjy implement_t* CreateGameImplement(_zjy gbase_t* base, _zjy uimgr_t* ui) \
{                                                                                           \
    clsname* pImp = new clsname;                                                            \
                                                                                            \
    if (pImp) pImp->__InitMgr(base, ui);                                                    \
                                                                                            \
    return pImp;                                                                            \
}                                                                                           \
_game_interface void DestroyGameImplement(_zjy implement_t **ppImp)                         \
{                                                                                           \
    if (ppImp)                                                                              \
    {                                                                                       \
        if (*ppImp)                                                                         \
        {                                                                                   \
            delete *ppImp;                                                                  \
            *ppImp = nullptr;                                                               \
        }                                                                                   \
    }                                                                                       \
}                                                                                           \
}

#endif

//  														2014-9 by Frank
//-----------------------------------------------------------------------------