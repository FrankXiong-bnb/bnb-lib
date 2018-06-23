//=============================================================================
// _game_server.h
//
// Exception :
//      定义服务端数据类型和结构，定义服务端基类。
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

// 定义服务端定时器类
typedef _game_timer<mgr_t>  stimer_t;

// 针对服务端对定时器启动和结束方法特例化
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

#define _Max_Power_Value    10              // 累积需要的值
#define _Max_Task           16              // 最任务数量
#define _all_tip            -1              // 所有人都算台费(默认)
#define _nall_tip           -100            // 所有人都不算台费(需要自己计算)
#define _self_tip           100             // 自定义计算
#define _nobasepoint        100             // 不乘以游戏底分
#define _basepoint          -1

// 用户信息
//-----------------------------------------------------------------------------

typedef struct _user_info {
    bool    m_bIsConnect;                   // 是否连接
    bool    m_bIsPlaying;                   // 是否在游戏中
    cdt_t   m_uComeTime;                    // 用户进来的时间
    state_t m_eState;                       // 状态

    int     m_iUserID;                      // 用户ID
    int     m_iLevel;                       // vip级别
    int     m_iSunshine;                    // 阳光值
    int     m_iActivity;                    // 活力值
    int     m_iTip;                         // 额外的费用
    money_t m_iOwnMoney;                    // 用户拥有的钱
    money_t m_iChangeMoney;                 // 用户变动的钱
    bool    m_bIsCalculate;                 // 是否加入结算
    bool    m_bIsRobot;                     // 是否机器人
    void*   m_pUser;                        // 用户数据
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

    // 将 UserInfoForGame_t 转化为 _user_info
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

    // 将 _user_info 转化为 UserInfoForGame_t
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

// 服务端信息
//-----------------------------------------------------------------------------

typedef struct _server_info {

    int         m_iRoomID;                  // 房间号
    int         m_iTableID;                 // 桌子号
    state_t     m_eGameState;               // 游戏状态
    bool        m_bIsPlaying;               // 游戏是否在进行中

    tdg_t       m_TaskList[_Max_Task];      // 任务列表
    int         m_nTask;                    // 任务数量
    int         m_iMaxSunshine;             // 最大阳光值
    int         m_iMaxActivity;             // 最大活力值

    user_t      user[_player_max];          // 用户信息

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

    // 非拷贝类
    _server_info(const _server_info&);
    _server_info& operator=(const _server_info&);

} server_t;

//=============================================================================
// class __zjy_server_interface_base
//
// Exception :
//      继承自IGameDesk，实现所有虚函数，并提供部分常用操作接口。
//      但不允许用户直接使用该类，需要继承并提供自定义操作。
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

    // 一次改写基类接口
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

    // 二次改写接口
    virtual result_t _EventAgree(int)    { return hr_success; }
    virtual result_t _EventState(int)    { return hr_success; }
    virtual result_t _EventCutNet(int)   { return hr_success; }
    virtual result_t _EventLeave(int)    { return hr_success; }
    virtual result_t _EventSitDown(int)  { return hr_success; }
    virtual result_t _EventUpdate(int)   { return hr_success; }
    virtual result_t _EventRecome(int)   { return hr_success; }

protected:

    // 受保护的构造函数，这将导致不允许用户创建基类对象。
    __zjy_server_interface_base() : _gmMgr(nullptr) { }

    // 如果需要自定义初始化操作，可以自己实现。
    virtual void _Initialize() { }
    virtual void __Init_Instance_Timer() { }
    virtual void __Init_Instance_Config() { }

//-----------------------------------------------------------------------------
// 1：int _SendMsg(int pos, int msg, buf_t data, int len) const
// 2：int _SendMsg(int msg, buf_t data, int len) const
// 3：template<typename _Ty> int _SendMsg(int pos, int msg, _Ty data) const
// 4：template<typename _Ty> int _SendMsg(int msg, _Ty buf) const
//      发送游戏消息，用于与客户端通信。
//
// Return:
//      版本1/3返回IGameMainManager::SendGameData调用的结果。
//      版本2/4返回发送玩家的数量
//
// Parameter:
//      pos     - 指定要发送的玩家
//      msg     - 标识发送的消息号
//      buf     - 要发送的数据
//      len     - 要发送的数据长度
//
// Exception:
//      对于3/4重载的模板版本，发送的数据buf必须是结构体指针，即要发送的
//      数据对象地址，并且不需要传递数据长度。
//      对于2/4重载的版本，不能指定发送的玩家，会发送给本桌所有在线的玩家。
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
//      获取游戏状态
//
// Return:
//      当前游戏状态
//
// Parameter:
//      void
//
// Exception:
//      游戏状态的值可以由用户自己定义
//
    int _GetCurState() const { return (_Info.m_eGameState); }

//-----------------------------------------------------------------------------
// void _SetCurState(int state)
//      设置游戏状态
//
// Return:
//      void
//
// Parameter:
//      state   - 要设置的状态
//
// Exception:
//      游戏状态的值可以由用户自己定义。
//
    void _SetCurState(int state) {
        _Info.m_eGameState = state;
        _msg_stoc_update data;
        data.m_eState = _Info.m_eGameState;
        _SendMsg(_gm_update, &data);
    }

//-----------------------------------------------------------------------------
// void _SetPlayerState(int pos, int state)
//      设置玩家状态
//
// Return:
//      void
//
// Parameter:
//      pos     - 要设置的玩家
//      state   - 要设置的状态
//
// Exception:
//      用户状态的值可以由自己定义。
//
    void _SetPlayerState(int pos, int state) { _Info.user[pos].m_eState |= state; }

//-----------------------------------------------------------------------------
// void _ErasePlayerState(int pos)
// void _ErasePlayerState(int pos, int state)
//      清除玩家状态
//
// Return:
//      void
//
// Parameter:
//      pos     - 要清除的玩家
//      state   - 要清除的状态
//
// Exception:
//      用户状态的值可以由自己定义。
//
    void _ErasePlayerState(int pos) { _Info.user[pos].m_eState = 0; }
    void _ErasePlayerState(int pos, int state) { _Info.user[pos].m_eState &= ~state; }

//-----------------------------------------------------------------------------
// bool _CheckPlayerState(int pos, int state) const
//      检测玩家状态
//
// Return:
//      如果该玩家包含指定的状态返回true，否则返回false。
//
// Parameter:
//      pos     - 指定要检测的玩家
//      state   - 指定要检测的状态
//
// Exception:
//
    bool _CheckPlayerState(int pos, int state) const { return (state == (_Info.user[pos].m_eState & state)); }

//-----------------------------------------------------------------------------
// 1：bool _IsPlaying() const
// 2：bool _IsPlaying(int pos) const
//      版本1：判断游戏是否在进行中
//      版本2：判断指定位置是否在游戏中
//
// Return:
//      如果正在游戏进行中返回true，否则返回false。
//
// Parameter:
//      pos     - 指定要检查的位置
//
// Exception:
//
    bool _IsPlaying() const { return _Info.m_bIsPlaying; }
    bool _IsPlaying(int pos) const { return (_CheckPlayer(pos) && _IsPlaying() && _Info.user[pos].m_bIsPlaying); }

//-----------------------------------------------------------------------------
// bool _CheckPos(int pos) const
//      检查指定位置的有效性
//
// Return:
//      如果该位置有效返回true，否则返回false。
//
// Parameter:
//      pos     - 指定要检查的位置
//
// Exception:
//      如果该位置合法，且用户ID有效，则该位置有效。
//
    bool _CheckPlayer(int pos) const { return (0 <= pos && pos < _player_max && 0 < _Info.user[pos].m_iUserID); }

//-----------------------------------------------------------------------------
// bool _CheckConnect(int pos) const
//      检查玩家是否在线
//
// Return:
//      如果该位置连接有效返回true，否则返回false。
//
// Parameter:
//      pos     - 指定要检查的玩家
//
// Exception:
//
    bool _CheckConnect(int pos) const { return (_CheckPlayer(pos) && _Info.user[pos].m_bIsConnect); }

//-----------------------------------------------------------------------------
// bool _CheckAllLeave() const
//      检查是否所有人都离开
//
// Return:
//      如果所有人都离开了游戏，返回true，否则返回false。
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
//      获取玩家昵称
//
// Return:
//      返回对应位置的玩家昵称
//
// Parameter:
//      pos     - 要获取昵称的玩家位置
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
            _Info.user[pos].m_iActivity = 0;    // 清零活力值

            _gmMgr->ActiveReward(0, _Info.user[pos].m_iUserID);

            return (_Info.m_iMaxActivity - _last);
        }

        return (_Info.user[pos].m_iActivity - _last);
    }

//-----------------------------------------------------------------------------
// void _Settlement()
//      游戏结算
//
// Return:
//      void
//
// Parameter:
//      void
//
// Exception:
//      根据本局现有数据进行结算，在此之前需要用户将所有数据计算出来。
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
//      游戏开始
//
// Return:
//      void
//
// Parameter:
//      void
//
// Exception:
//      游戏开始后需要调用该函数
//
    void _GameStarted() {
        _Info.m_bIsPlaying = true;
        _gmMgr->OnGameBegin(_Info.m_iTableID);

        _zjy_log("===========<Game Start>===========");
    }

//-----------------------------------------------------------------------------
// void _GameOver()
//      游戏结束
//
// Return:
//      void
//
// Parameter:
//      void
//
// Exception:
//      游戏结束后需要调用该函数
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