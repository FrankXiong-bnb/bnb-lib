//=============================================================================
// _game_server.h
//
// Exception :
//      ���������������ͺͽṹ���������˻��ࡣ
//
//=============================================================================
#ifndef ____ZJY_Server_Define_H_
#define ____ZJY_Server_Define_H_

#ifndef _zjy_not_game_log
#include <io.h>
#include <direct.h>
#include <time.h>
#include <fstream>
#include "../standard/_definition.h"
#include "../standard/_tydef.h"
#include "../windows/_convert_character.h"
#include "../games/zjy/_game_log.h"
#endif  // #ifndef _zjy_not_game_log

_zjy_space_in

// typedef
//-----------------------------------------------------------------------------

typedef ServerDllInfoStruct sdis_t;
typedef UserInfoForGame_t   uifg_t;
typedef IGameMainManager    mgr_t;
typedef TaskDaily_Game_t    tdg_t;
typedef TaskDaily_plate_t   tdp_t;

// �������˶�ʱ����
typedef _game_timer<mgr_t>  stimer_t;

// ��Է���˶Զ�ʱ�������ͽ�������������
//-----------------------------------------------------------------------------

template<> bool stimer_t::Start(int interval)
{
    if (!!!_playing && _operator)
    {
        _operator->SetGameTimer((int)_param, _timer_id, interval);
        _playing = true;
        _last_time = GetCurTime();

        return true;
    }

    return false;
}

template<> bool stimer_t::Stop()
{
    if (_playing && _operator)
    {
        _operator->KillGameTimer((int)_param, _timer_id);
        _playing = false;

        return true;
    }

    return false;
}

#define _Max_Power_Value    10              // �ۻ���Ҫ��ֵ
#define _Max_Task           16              // ����������
#define _all_tip            -1              // �����˶���̨��(Ĭ��)
#define _nall_tip           -100            // �����˶�����̨��(��Ҫ�Լ�����)
#define _self_tip           100             // �Զ������
#define _nobasepoint        100             // ��������Ϸ�׷�
#define _basepoint          -1

// �û���Ϣ
//-----------------------------------------------------------------------------

typedef struct _user_info {
    bool    m_bIsConnect;                   // �Ƿ�����
    bool    m_bIsPlaying;                   // �Ƿ�����Ϸ��
    cdt_t   m_uComeTime;                    // �û�������ʱ��
    state_t m_eState;                       // ״̬

    int     m_iUserID;                      // �û�ID
    int     m_iLevel;                       // vip����
    int     m_iSunshine;                    // ����ֵ
    int     m_iActivity;                    // ����ֵ
    int     m_iTip;                         // ����ķ���
    money_t m_iOwnMoney;                    // �û�ӵ�е�Ǯ
    money_t m_iChangeMoney;                 // �û��䶯��Ǯ
    bool    m_bIsCalculate;                 // �Ƿ�������
    bool    m_bIsRobot;                     // �Ƿ������
    void*   m_pUser;                        // �û�����
    unsigned int m_uSocketIndex;            // socket index

    _user_info() { Clear(); }

    void Clear() {
        m_eState        = 0;
        m_uComeTime     = 0;
        m_iUserID       = 0;
        m_iLevel        = 0;
        m_iSunshine     = 0;
        m_iActivity     = 0;
        m_iOwnMoney     = 0;
        m_iChangeMoney  = 0;
        m_iTip          = 0;
        m_uSocketIndex  = 0;
        m_bIsConnect    = false;
        m_bIsCalculate  = false;
        m_bIsPlaying    = false;
        m_bIsRobot      = false;
        m_pUser         = nullptr;
    }

    void Reset() {
        m_eState        = 0;
        m_iChangeMoney  = 0;
        m_iTip          = 0;
        m_uComeTime     = stimer_t::GetCurTime();
        m_bIsCalculate  = false;
        m_bIsPlaying    = false;
    }

    // �� UserInfoForGame_t ת��Ϊ _user_info
    void Assign(const uifg_t& info)
    {
        m_iUserID       = info._dwUserID;
        m_iOwnMoney     = info._iUserMoney;
        m_iChangeMoney  = info._i64Money;
        m_iTip          = info._iTax;
        m_bIsCalculate  = info._bIsCalc;
        m_uSocketIndex  = info._SocketIndex;
        m_pUser         = info._pUserInfo;
        m_bIsRobot      = info._bIsRobot;
        m_iSunshine     = info._iSunshineVal;
        m_iActivity     = info._iActiveVal;
        m_iLevel        = info.iUserVipLevel;
    }

    // �� _user_info ת��Ϊ UserInfoForGame_t
    void ConvertTo(uifg_t& info) const
    {
        info._dwUserID      = m_iUserID;
        info._pUserInfo     = m_pUser;
        info._iUserMoney    = (int)m_iOwnMoney;
        info._nPoint        = (int)m_iChangeMoney;
        info._iTax          = m_iTip;
        info._bIsCalc       = m_bIsCalculate;
        info._SocketIndex   = m_uSocketIndex;
        // info._bIsWinner     = m_iChangMoney > 0;
        info._dWinLost      = m_iChangeMoney > 0 ? 1 : m_iChangeMoney < 0 ? 3 : 2;
        info._bIsRobot      = m_bIsRobot;
        info.bIsWatch       = false;
        info._iActiveVal    = m_iActivity;
        info._iSunshineVal  = m_iSunshine;
        info.iUserVipLevel  = m_iLevel;
    }

} user_t;

// �������Ϣ
//-----------------------------------------------------------------------------

typedef struct _server_info {

    int         m_iRoomID;                  // �����
    int         m_iTableID;                 // ���Ӻ�
    state_t     m_eGameState;               // ��Ϸ״̬
    bool        m_bIsPlaying;               // ��Ϸ�Ƿ��ڽ�����

    tdg_t       m_TaskList[_Max_Task];      // �����б�
    int         m_nTask;                    // ��������
    int         m_iMaxSunshine;             // �������ֵ
    int         m_iMaxActivity;             // ������ֵ

    user_t      user[_player_max];          // �û���Ϣ

    void _Reset() {
        m_eGameState = 0;
        m_bIsPlaying = false;
        for (int i=0; i<_player_max; user[i++].Clear());
    }

    _server_info()
        : m_iRoomID(0)
        , m_iTableID(0)
        , m_eGameState(0)
        , m_bIsPlaying(false)
        , m_nTask(0)
        , m_iMaxActivity(_Max_Power_Value)
        , m_iMaxSunshine(_Max_Power_Value)
    {
        for (int i = 0; i < _Max_Task; ++i)
        {
            m_TaskList[i].iGameBase = 1;
            m_TaskList[i].iTaskType = 0;
            m_TaskList[i].iTaskID = 0;
        }
    }

private:

    // �ǿ�����
    _server_info(const _server_info&);
    _server_info& operator=(const _server_info&);

} server_t;

//=============================================================================
// class __zjy_server_interface_base
//
// Exception :
//      �̳���IGameDesk��ʵ�������麯�������ṩ���ֳ��ò����ӿڡ�
//      ���������û�ֱ��ʹ�ø��࣬��Ҫ�̳в��ṩ�Զ��������
//
//
//=============================================================================
class __zjy_server_interface_base : public ::IGameDesk
{

#ifndef _zjy_not_game_log
    typedef _game_log   log_t;
#define _zjy_log    _logMgr
#else
#define _zjy_log
#endif

public:

    // һ�θ�д����ӿ�
    virtual int InitialDesk(int iDeskNo, int, mgr_t* pMgr) {
        _gmMgr = pMgr;

        _Info.m_iTableID = iDeskNo;
        _Info.m_iRoomID  = _gmMgr->GetRoomID();

#ifndef _zjy_not_game_log
        _logMgr.SetIntKey(_Info.m_iRoomID, _Info.m_iTableID);
#endif

        __Init_Instance_Config();
        __Init_Instance_Timer();

        _Initialize();

        return hr_success;
    }

    virtual int SetTaskDaily(tdg_t* pTask, int n) {
        for (_Info.m_nTask = 0; _Info.m_nTask < n && _Info.m_nTask < _Max_Task; ++_Info.m_nTask)
            _Info.m_TaskList[_Info.m_nTask] = pTask[_Info.m_nTask];

        return _Info.m_nTask;
    }

    virtual int  HandleNotifyMessage(int, UINT, BYTE*, int) { return hr_success; }
    virtual bool IsPlayingByGameStation()           { return _IsPlaying();  }
    virtual bool IsPlayGame(int pos)                { return _IsPlaying(pos); }
    virtual int  GetCurGameStation()                { return _GetCurState(); }
    virtual int  ForceQuit()                        { return hr_success; }
    virtual int  OnGameTimer(int)                   { return hr_success; }
    virtual int  OnGetGameStation(int pos, uifg_t&) { if (!_CheckPlayer(pos)) return hr_fail; return _EventState(pos); }  
    virtual int  UserAgreeGame(int pos, uifg_t&)    { if (!_CheckPlayer(pos)) return hr_fail; return _EventAgree(pos); }

    virtual int  UpdateUserInfo(int pos, uifg_t& info) {
        if (!_CheckPlayer(pos) || 0 == info._dwUserID) return hr_fail;
        
        _Info.user[pos].Assign(info);

        return _EventUpdate(pos);
    }

    virtual int  UserReCome(int pos, uifg_t& info) {
        if (_IsPlaying()
            && pos >= 0
            && pos < _player_max
            && info._dwUserID > 0
            && _Info.user[pos].m_iUserID == info._dwUserID
            && !_Info.user[pos].m_bIsConnect) {
            _Info.user[pos].m_bIsConnect = true;
            _Info.user[pos].m_uComeTime = stimer_t::GetCurTime();
            _Info.user[pos].Assign(info);

            return _EventRecome(pos);
        }

        return hr_fail;
    }

    virtual int  UserSitDesk(int pos, uifg_t& info) {
        if (pos < 0 || pos >= _player_max || 0 == info._dwUserID)
            return hr_fail;

        _Info.user[pos].Clear();
        _Info.user[pos].m_uComeTime = stimer_t::GetCurTime();
        _Info.user[pos].m_bIsConnect = true;
        _Info.user[pos].Assign(info);

        /* if (_Info.m_eGameState < _gs_wait)
            _Info.m_eGameState = _gs_wait; */

        return _EventSitDown(pos);
    }

    virtual int  UserNetCut(int pos, uifg_t&) {
        if (!_CheckPlayer(pos)) return hr_fail;

        if (_IsPlaying(pos))
            _Info.user[pos].m_bIsConnect = false;
        else
            _Info.user[pos].Clear();

        return _EventCutNet(pos);
    }

    virtual int  UserLeftDesk(int pos, uifg_t&) {
        _Info.user[pos].Clear();

        return _EventLeave(pos);
    }

    // ���θ�д�ӿ�
    virtual result_t _EventAgree(int)    { return hr_success; }
    virtual result_t _EventState(int)    { return hr_success; }
    virtual result_t _EventCutNet(int)   { return hr_success; }
    virtual result_t _EventLeave(int)    { return hr_success; }
    virtual result_t _EventSitDown(int)  { return hr_success; }
    virtual result_t _EventUpdate(int)   { return hr_success; }
    virtual result_t _EventRecome(int)   { return hr_success; }

protected:

    // �ܱ����Ĺ��캯�����⽫���²������û������������
    __zjy_server_interface_base() : _gmMgr(nullptr) { }

    // �����Ҫ�Զ����ʼ�������������Լ�ʵ�֡�
    virtual void _Initialize() { }
    virtual void __Init_Instance_Timer() { }
    virtual void __Init_Instance_Config() { }

//-----------------------------------------------------------------------------
// 1��int _SendMsg(int pos, int msg, buf_t data, int len) const
// 2��int _SendMsg(int msg, buf_t data, int len) const
// 3��template<typename _Ty> int _SendMsg(int pos, int msg, _Ty data) const
// 4��template<typename _Ty> int _SendMsg(int msg, _Ty buf) const
//      ������Ϸ��Ϣ��������ͻ���ͨ�š�
//
// Return:
//      �汾1/3����IGameMainManager::SendGameData���õĽ����
//      �汾2/4���ط�����ҵ�����
//
// Parameter:
//      pos     - ָ��Ҫ���͵����
//      msg     - ��ʶ���͵���Ϣ��
//      buf     - Ҫ���͵�����
//      len     - Ҫ���͵����ݳ���
//
// Exception:
//      ����3/4���ص�ģ��汾�����͵�����buf�����ǽṹ��ָ�룬��Ҫ���͵�
//      ���ݶ����ַ�����Ҳ���Ҫ�������ݳ��ȡ�
//      ����2/4���صİ汾������ָ�����͵���ң��ᷢ�͸������������ߵ���ҡ�
//
    int _SendMsg(int pos, int msg, buf_t data, int len) const {
        return _gmMgr->SendGameData(_Info.m_iTableID, pos, msg, data, len);
    }
    int _SendMsg(int msg, buf_t data, int len) const {
        int count = 0;
        for (int i = 0; i < _player_max; ++i) {
            if (_Info.user[i].m_bIsConnect) {
                _SendMsg(i, msg, data, len);
                ++count;
            }
        }
        
        return count;
    }
    template<typename _Ty>
    int _SendMsg(int pos, int msg, _Ty data) const {
        static_assert(std::is_pointer<_Ty>::value, "send the type of data must be a pointer");
        return _SendMsg(pos, msg, reinterpret_cast<buf_t>(data), sizeof(decltype(*data)));
    }
    template<typename _Ty>
    int _SendMsg(int msg, _Ty data) const {
        static_assert(std::is_pointer<_Ty>::value, "send the type of data must be a pointer");
        return _SendMsg(msg, reinterpret_cast<buf_t>(data), sizeof(decltype(*data)));
    }

//-----------------------------------------------------------------------------
// int _GetCurState() const
//      ��ȡ��Ϸ״̬
//
// Return:
//      ��ǰ��Ϸ״̬
//
// Parameter:
//      void
//
// Exception:
//      ��Ϸ״̬��ֵ�������û��Լ�����
//
    int _GetCurState() const { return (_Info.m_eGameState); }

//-----------------------------------------------------------------------------
// void _SetCurState(int state)
//      ������Ϸ״̬
//
// Return:
//      void
//
// Parameter:
//      state   - Ҫ���õ�״̬
//
// Exception:
//      ��Ϸ״̬��ֵ�������û��Լ����塣
//
    void _SetCurState(int state) {
        _Info.m_eGameState = state;
        _msg_stoc_update data;
        data.m_eState = _Info.m_eGameState;
        _SendMsg(_gm_update, &data);
    }

//-----------------------------------------------------------------------------
// void _SetPlayerState(int pos, int state)
//      �������״̬
//
// Return:
//      void
//
// Parameter:
//      pos     - Ҫ���õ����
//      state   - Ҫ���õ�״̬
//
// Exception:
//      �û�״̬��ֵ�������Լ����塣
//
    void _SetPlayerState(int pos, int state) { _Info.user[pos].m_eState |= state; }

//-----------------------------------------------------------------------------
// void _ErasePlayerState(int pos)
// void _ErasePlayerState(int pos, int state)
//      ������״̬
//
// Return:
//      void
//
// Parameter:
//      pos     - Ҫ��������
//      state   - Ҫ�����״̬
//
// Exception:
//      �û�״̬��ֵ�������Լ����塣
//
    void _ErasePlayerState(int pos) { _Info.user[pos].m_eState = 0; }
    void _ErasePlayerState(int pos, int state) { _Info.user[pos].m_eState &= ~state; }

//-----------------------------------------------------------------------------
// bool _CheckPlayerState(int pos, int state) const
//      ������״̬
//
// Return:
//      �������Ұ���ָ����״̬����true�����򷵻�false��
//
// Parameter:
//      pos     - ָ��Ҫ�������
//      state   - ָ��Ҫ����״̬
//
// Exception:
//
    bool _CheckPlayerState(int pos, int state) const { return (state == (_Info.user[pos].m_eState & state)); }

//-----------------------------------------------------------------------------
// 1��bool _IsPlaying() const
// 2��bool _IsPlaying(int pos) const
//      �汾1���ж���Ϸ�Ƿ��ڽ�����
//      �汾2���ж�ָ��λ���Ƿ�����Ϸ��
//
// Return:
//      ���������Ϸ�����з���true�����򷵻�false��
//
// Parameter:
//      pos     - ָ��Ҫ����λ��
//
// Exception:
//
    bool _IsPlaying() const { return _Info.m_bIsPlaying; }
    bool _IsPlaying(int pos) const { return (_CheckPlayer(pos) && _IsPlaying() && _Info.user[pos].m_bIsPlaying); }

//-----------------------------------------------------------------------------
// bool _CheckPos(int pos) const
//      ���ָ��λ�õ���Ч��
//
// Return:
//      �����λ����Ч����true�����򷵻�false��
//
// Parameter:
//      pos     - ָ��Ҫ����λ��
//
// Exception:
//      �����λ�úϷ������û�ID��Ч�����λ����Ч��
//
    bool _CheckPlayer(int pos) const { return (0 <= pos && pos < _player_max && 0 < _Info.user[pos].m_iUserID); }

//-----------------------------------------------------------------------------
// bool _CheckConnect(int pos) const
//      �������Ƿ�����
//
// Return:
//      �����λ��������Ч����true�����򷵻�false��
//
// Parameter:
//      pos     - ָ��Ҫ�������
//
// Exception:
//
    bool _CheckConnect(int pos) const { return (_CheckPlayer(pos) && _Info.user[pos].m_bIsConnect); }

//-----------------------------------------------------------------------------
// bool _CheckAllLeave() const
//      ����Ƿ������˶��뿪
//
// Return:
//      ��������˶��뿪����Ϸ������true�����򷵻�false��
//
// Parameter:
//      void
//
// Exception:
//
    bool _CheckAllLeave() const {
        for (int i = 0; i < _player_max; ++i)
            if (0 < _Info.user[i].m_iUserID && _Info.user[i].m_bIsConnect)
                return false;

        return true;
    }

//-----------------------------------------------------------------------------
// const char* _GetNickName(int pos) const
//      ��ȡ����ǳ�
//
// Return:
//      ���ض�Ӧλ�õ�����ǳ�
//
// Parameter:
//      pos     - Ҫ��ȡ�ǳƵ����λ��
//
// Exception:
//
    const char* _GetNickName(int pos) const
    {
        /*CGameUserInfo *pUser = reinterpret_cast<CGameUserInfo*>(_Info.user[pos].m_pUser);
        return pUser->GetNickName();*/
        return nullptr;
    }

    int _AddSunshine(int pos, int v) {
        int _last = _Info.user[pos].m_iSunshine;

        _Info.user[pos].m_iSunshine += v;

        if (_Info.user[pos].m_iSunshine > _Info.m_iMaxSunshine)
            _Info.user[pos].m_iSunshine = _Info.m_iMaxSunshine;

        return (_Info.user[pos].m_iSunshine - _last);
    }

    int _AddActivity(int pos, int v) {
        int _last = _Info.user[pos].m_iActivity;

        _Info.user[pos].m_iActivity += v;

        if (_Info.user[pos].m_iActivity > _Info.m_iMaxActivity)
        {
            _Info.user[pos].m_iActivity = 0;    // �������ֵ

            _gmMgr->ActiveReward(0, _Info.user[pos].m_iUserID);

            return (_Info.m_iMaxActivity - _last);
        }

        return (_Info.user[pos].m_iActivity - _last);
    }

//-----------------------------------------------------------------------------
// void _Settlement()
//      ��Ϸ����
//
// Return:
//      void
//
// Parameter:
//      void
//
// Exception:
//      ���ݱ����������ݽ��н��㣬�ڴ�֮ǰ��Ҫ�û����������ݼ��������
//
    void _Settlement(int tipIndex = _all_tip, int taskIndex = _basepoint) {
        uifg_t info[_player_max];
        for (int i = 0; i < _player_max; ++i)
            _Info.user[i].ConvertTo(info[i]);

        ResultInfo_t res;
        res._nCount = _player_max;
        res._nDeskIndex = _Info.m_iTableID;
        res._nTaxIndex = tipIndex;
        res._nTaskIndex = taskIndex;

        _gmMgr->ChangeUserPoint(res, info);

        for (int i = 0; i < _player_max; ++i)
            _Info.user[i].Assign(info[i]);
    }

//-----------------------------------------------------------------------------
// void _GameStarted()
//      ��Ϸ��ʼ
//
// Return:
//      void
//
// Parameter:
//      void
//
// Exception:
//      ��Ϸ��ʼ����Ҫ���øú���
//
    void _GameStarted() {
        _Info.m_bIsPlaying = true;
        _gmMgr->OnGameBegin(_Info.m_iTableID);

        _zjy_log("===========<Game Start>===========");
    }

//-----------------------------------------------------------------------------
// void _GameOver()
//      ��Ϸ����
//
// Return:
//      void
//
// Parameter:
//      void
//
// Exception:
//      ��Ϸ��������Ҫ���øú���
//
    void _GameOver() {
        _Info.m_bIsPlaying = false;

        for (int i = 0; i < _player_max; ++i)
            _Info.user[i].Reset();

        _gmMgr->OnGameFinish(_Info.m_iTableID);

        _zjy_log("===========<Game Over>===========\n");
    }

    server_t    _Info;
    mgr_t*      _gmMgr;

#ifndef _zjy_not_game_log
    log_t       _logMgr;
#endif

}; // class __zjy_server_interface_base

_zjy_space_out

#endif

//                                                      2014-9 by Frank
//-----------------------------------------------------------------------------