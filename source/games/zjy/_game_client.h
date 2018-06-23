//=============================================================================
// _game_client.h
//
// Exception :
//      定义客户端数据类型和结构，定义客户端基类。
//
//=============================================================================
#ifndef ____ZJY_Client_Define_H_
#define ____ZJY_Client_Define_H_

_zjy_space_in

// typedef
//-----------------------------------------------------------------------------

typedef IGameImplement  implement_t;
typedef IGameBase       gbase_t;
typedef IUserInterface  uimgr_t;
typedef TUIMessage      uimsg_t;
typedef GameInfoForGame gifg_t;
typedef IBCInterFace    ctrlbase_t;
typedef unsigned int    ctrlid_t;
typedef COLORREF        color_t;

// 定义客户端定时器类
typedef _game_timer<gbase_t> ctimer_t;

// 定义客户端数据结构
//-----------------------------------------------------------------------------

typedef struct _client_info {
    int     m_iRoomID;              // 所在房间ID
    int     m_iTableID;             // 所在桌子ID
    int     m_iPos;                 // 桌子中的序号
    state_t m_eGameState;           // 游戏的状态
    state_t m_eMyState;             // 自己的状态
    state_t m_eRole;                // 自己的角色
    bool    m_bPlaying;             // 是否正在游戏

    // 本局所有玩家昵称
    wchar_t m_strName[_player_max][_size_nick_name];

    _client_info () : m_iRoomID(0), m_iTableID(0), m_iPos(0) { _Reset(); }

    void _Reset() {
        m_eGameState    = 0;
        m_bPlaying      = false;
        m_eMyState      = 0;
        m_eRole         = 0;

        for (int i = 0; i < _player_max; ++i)
            wmemset(m_strName[i], 0, _size_nick_name);
    }

} client_t; // struct _client_info

//=============================================================================
// class __zjy_client_interface_base
//
// Exception :
//      继承自IGameImplement，实现所有虚函数，并提供部分常用操作接口。
//      但不允许用户直接使用该类，需要继承并提供自定义操作。
//
//=============================================================================
class __zjy_client_interface_base : public implement_t
{
public:

    // 一次改写基类接口
    virtual int  Initial(wchar_t* file, bool)               { return _LoadCtrl(file); }
    virtual int  InitUI()                                   { __Init_Instance_Config(); _Initialize(); return hr_success; }
    virtual int  GameUserLeft(int pos)                      { return _EventLeave(pos); }
    virtual int  GameUserCome()                             { return _EventEnter(); }
    virtual int  HandleGameMessage(WORD, WORD, BYTE*, int)  { return hr_success; }
    virtual int  OnUIMessage(uimsg_t*)                      { return hr_success; }
    virtual int  ResetGameFrame()                           { return hr_success; }
    virtual int  GameUserOffLine()                          { return hr_success; }
    virtual void OnTimer(int)                               { }
    virtual void GameInfoChange(TGameInfo)                  { }
    virtual bool IsPlayingGame()                            { return _IsPlaying(); }
    
    // 初始化客户端管理者
    void __InitMgr(gbase_t* pgb, uimgr_t* pui) { _gbMgr = pgb; _uiMgr = pui; __Init_Instance_Timer(); }

    // 访问界面管理者和终端管理者
    uimgr_t* GetUiMgr() const { return _uiMgr; }
    gbase_t* GetBaseMgr() const { return _gbMgr; }

protected:

    // 受保护的构造函数，这将导致不允许用户创建基类对象。
    __zjy_client_interface_base() : _gbMgr(nullptr), _uiMgr(nullptr) { }

    // 二次改写接口，如果有需要可以自己实现。
    virtual void __Init_Instance_Config() { }
    virtual void __Init_Instance_Timer() { }
    virtual void _Initialize() { }  // 如果需要在客户端启动的时候操作，可以重写该函数。
    virtual result_t  _EventLeave(int) { return hr_success; }    // 响应用户离开事件
    virtual result_t  _EventEnter() { return hr_success; }      // 响应用户进入事件

//-----------------------------------------------------------------------------
// virtual int _LoadCtrl(const wchar_t*) const
//      加载ui资源文件
//
// Return:
//      返回由IUserInterface::LoadData函数加载ui资源文件的结果
//
// Parameter:
//      可以忽略
//
// Exception:
//      该函数加载ui资源文件，如果自定义加载方式需要重写。
//      函数以默认在游戏ID命名的目录下命名的文件作为ui文件路径。
//      如果定义了宏_game_ui_dat，则使用该宏定义的路径作为ui文件路径。
//
    virtual int  _LoadCtrl(const wchar_t*) const {
        wchar_t path[1024] = { 0 };
#ifdef _game_ui_dat
        wcscpy_s(path, _game_ui_dat);
#else
        swprintf_s(path, L"%d\\%d_ui.dat", _game_id, _game_id);
#endif
        return _uiMgr->LoadData(path);
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
    void _SetCurState(int state) { _Info.m_eGameState = state; }

//-----------------------------------------------------------------------------
// void _SetPlayerState(int state)
//      设置玩家状态
//
// Return:
//      void
//
// Parameter:
//      state   - 要设置的状态
//
// Exception:
//      用户状态的值可以由自己定义。
//
    void _SetPlayerState(int state) { _Info.m_eMyState |= state; }

//-----------------------------------------------------------------------------
// void _ErasePlayerState()
// void _ErasePlayerState(int state)
//      清除玩家状态
//
// Return:
//      void
//
// Parameter:
//      state   - 要清除的状态
//
// Exception:
//      用户状态的值可以由自己定义。
//
    void _ErasePlayerState() { _Info.m_eMyState = 0; }
    void _ErasePlayerState(int state) { _Info.m_eMyState &= ~state; }

//-----------------------------------------------------------------------------
// bool _CheckPlayerState(int state) const
//      检测玩家状态
//
// Return:
//      如果玩家包含指定的状态返回true，否则返回false。
//
// Parameter:
//      state   - 指定要检测的状态
//
// Exception:
//
    bool _CheckPlayerState(int state) const { return (state == (_Info.m_eMyState & state)); }


//-----------------------------------------------------------------------------
// bool _IsPlaying() const
//      判断游戏是否进行中
//
// Return:
//      如果正在游戏进行中返回true，否则返回false。
//
// Parameter:
//      void
//
// Exception:
//
    bool _IsPlaying() const { return _Info.m_bPlaying; }

//-----------------------------------------------------------------------------
// void _SaveNickName()
//      保存本桌玩家昵称
//
// Return:
//      void
//
// Parameter:
//      void
//
// Exception:
//      需要在游戏开始之后调用，否则本桌玩家人数不能确定。
//
    void _SaveNickName() {
        wchar_t* ptr = nullptr;
        for (int i = 0; i < _player_max; ++i)
            if (ptr = _gbMgr->GetUserNickName(i))
                wcscpy_s(_Info.m_strName[i], ptr);
    }

//-----------------------------------------------------------------------------
// const wchar_t* _GetNickName(int pos) const
//      按位置获取玩家昵称
//
// Return:
//      要获取的玩家昵称
//
// Parameter:
//      pos     - 玩家位置号
//
// Exception:
//      如果位置非法，返回nullptr。
//
    const wchar_t* _GetNickName(int pos) const {
        if (pos >= 0 && pos < _player_max)
            return _Info.m_strName[pos];

        return nullptr;
    }

//-----------------------------------------------------------------------------
// const wchar_t* _GetMoneyName() const
//      获取金币名称
//
// Return:
//      金币名称
//
// Parameter:
//      void
//
// Exception:
//    
    const wchar_t* _GetMoneyName() const {
        return _gbMgr->GetMoneyType()->_virtualMoney.c_str();
    }

//-----------------------------------------------------------------------------
// bool _IsAuotSitRoom() const
//      判断是否搓桌场
//
// Return:
//      如果是搓桌场返回true，否则返回false。
//
// Parameter:
//      void
//
// Exception:
//
    bool _IsAuotSitRoom() const {
        gifg_t uGameData = { 0 };
        _gbMgr->GetGameBaseInfo(uGameData);

        return (bool)((uGameData.dwGameRule & GRR_AUTO_SIT_DESK)
            || (uGameData.dwGameRule & GRR_MATCH_REG)
            || (uGameData.dwGameRule & GRR_QUEUE_GAME));
    }

    int _GetVipLevel(int pos ) const {
        UserInfoForGame info = { 0 };
        _gbMgr->GetUserInfo(pos, info);

        return info.iUserVipLevel;
    }
    int _GetVipLevel() const { return _GetVipLevel(_Info.m_iPos); }

//-----------------------------------------------------------------------------
// 1：bool _SendMsg( int msg, void* buf, int len ) const
// 2：template<typename _Ty> bool _SendMsg( int msg, _Ty buf ) const
//      发送游戏消息，用于与服务端通信。
//
// Return:
//      如果平台提供给客户端的管理者指针有效返回true，否则返回false。
//
// Parameter:
//      msg     - 标识发送的消息号
//      buf     - 要发送的数据
//      len     - 要发送的数据长度
//
// Exception:
//      对于第二个重载的模板版本，发送的数据buf必须是结构体指针，即要发送的
//      数据对象地址，并且不需要传递数据长度。
//
    bool _SendMsg( int msg, void* buf, int len ) const {
        if (!!!_gbMgr) return false;

        _gbMgr->SendGameData(msg, buf, len);
        return true;
    }
    template<typename _Ty>
    bool _SendMsg( int msg, _Ty buf ) const {
        static_assert(std::is_pointer<_Ty>::value, "send the type of data must be a pointer");
        return _SendMsg(msg, buf, sizeof(decltype(*buf)));
    }

result_t _OnReceiveUpdate(buf_t buf, int len)
{
    if (sizeof(_msg_stoc_update) != len)
        return hr_fail;

    _msg_stoc_update* pMsg = reinterpret_cast<_msg_stoc_update*>(buf);

    _SetCurState(pMsg->m_eState);

    return hr_success;
}

//-----------------------------------------------------------------------------
// bool _PlaySound(int pos, int sid) const
// bool _PlaySound(int sid) const
//      播放声音
//
// Return:
//      返回播放是否成功
//
// Parameter:
//      pos     - 要播放的位置
//      sid     - 声音文件ID
//
// Exception:
//      第2个版本默认播放自己位置的声音
//
    bool _PlaySound(int pos, int sid) const {
        char path[1024] = { 0 };
        _gbMgr->GetAudioPath(pos, path, 1024);

        sprintf_s(path, "%s\\%s", path, _GetSoundPath(sid));

        return _gbMgr->PlaySound(path);
    }
    bool _PlaySound(int sid) const {
        return _PlaySound(_Info.m_iPos, sid);
    }

//-----------------------------------------------------------------------------
// bool _SetCtrlVisible(int id, bool bv) const
//      设置控件是否可见
//
// Return:
//      返回设置是否成功
//
// Parameter:
//      id      - 要设置的控件ID
//      bv      - 如果传true，则将控件置为可见，否则将隐藏控件。
//
// Exception:
//
    bool _SetCtrlVisible(ctrlid_t id, bool bv) const {
        ctrlbase_t* pCtrl = _uiMgr->GetIControlbyID(id);
        if (!pCtrl) return false;

        pCtrl->SetControlVisible(bv);
        return true;
    }

//-----------------------------------------------------------------------------
// bool _SetReadyVisible( int pos, bool bv ) const
//      设置玩家的准备图标是否可见
//
// Return:
//      返回设置是否成功
//
// Parameter:
//      pos     - 要设置的玩家位置号，函数会自动将位置号转化为对应的控件ID。
//      bv      - 如果传true，则将该玩家的准备图标置为可见，否则将隐藏准备图标。
//
// Exception:
//      需要事先在ui资源中添加准备图片控件
//
    bool _SetReadyVisible( int pos, bool bv ) const {
        return _SetCtrlVisible(_gbMgr->DeskStation2View(pos) + _id_image_ready0, bv);
    }

//-----------------------------------------------------------------------------
// bool _SetCtrlPos(int id, int x, int y) const
//      设置控件位置
//
// Return:
//      返回设置是否成功
//
// Parameter:
//      id      - 要设置的控件ID
//      x       - 要设置的x坐标
//      y       - 要设置的y坐标
//
// Exception:
//
    bool _SetCtrlPos(ctrlid_t id, int x, int y) const {
        ctrlbase_t* pCtrl = _uiMgr->GetIControlbyID(id);
        if (!pCtrl) return false;

        pCtrl->SetGameXY(x, y);
        return true;
    }

//-----------------------------------------------------------------------------
// bool _SetBtnEnable(int id, bool be) const
//      设置按钮是否激活
//
// Return:
//      返回设置是否成功
//
// Parameter:
//      id      - 要设置的按钮ID
//      be      - 如果传true，则将按钮置为激活状态，否则置为不激活状态。
//
// Exception:
//      参数id标识的控件类型必须是按钮控件
//
    bool _SetBtnEnable(ctrlid_t id, bool be) const {
        IButton* pButton = dynamic_cast<IButton*>(_uiMgr->GetIControlbyID(id));
        if (!pButton) return false;

        pButton->SetEnable(be);
        return true;            
    }

//-----------------------------------------------------------------------------
// 1：bool _SetCtrlText(int id, bool bv, const wchar_t* text) const
// 2：bool _SetCtrlText(int id, bool bv, const wchar_t* text, color_t clr) const
//      设置文字控件
//
// Return:
//      返回设置是否成功
//
// Parameter:
//      id      - 要设置的文字控件ID
//      bv      - 指示文字控件是否可见
//      text    - 要显示的文字
//      clr     - 指示文字的颜色
//
// Exception:
//      参数id标识的控件类型必须是文字控件
//      如果参数bv为false，将隐藏文字控件，并忽略参数text和clr。
//      如果参数text为nullptr，将只修改控件的可见状态，不修改控件的文字内容。
//
    bool _SetCtrlText(ctrlid_t id, bool bv, const wchar_t* text) const {
        IText* pText = dynamic_cast<IText*>(_uiMgr->GetIControlbyID(id));
        if (!pText) return false;

        if (bv)
            if (nullptr != text)
                pText->SetText(text);

        pText->SetControlVisible(bv);

        return true;
    }    
    bool _SetCtrlText(ctrlid_t id, bool bv, const wchar_t* text, color_t clr) const {
        IText* pText = dynamic_cast<IText*>(_uiMgr->GetIControlbyID(id));
        if (!pText) return false;

        if (bv){
            if (text)
                pText->SetText(text);

            BYTE r = GetRValue(clr), g = GetGValue(clr), b = GetBValue(clr);
            color_t rtc = RGB(b, g, r);
            pText->SetFontColor(rtc);
        }

        pText->SetControlVisible(bv);

        return true;
    }
    template<typename _DigitT>
    bool _SetCtrlText(ctrlid_t id, _DigitT digit, bool bs = false) const {
        static_assert(std::is_integral<_DigitT>::value, "The parameter must be an integer");

        return _SetCtrlText<long long>(id, digit, bs);
    }
    template<>
    bool _SetCtrlText(ctrlid_t id, long long digit, bool bs) const {
        IText* pText = dynamic_cast<IText*>(_uiMgr->GetIControlbyID(id));
        if (!pText) return false;

        wchar_t text[32] = { 0 };
        if (bs)
            swprintf_s(text, L"%+lld", digit);
        else
            swprintf_s(text, L"%lld", digit);

        pText->SetText(text);
        pText->SetControlVisible(true);

        return true;
    }

//-----------------------------------------------------------------------------
// bool _SetCtrlDigit(ctrlid_t id, bool bv, long long d) const
// bool _SetCtrlDigit(ctrlid_t id, bool bv, long long d, bool sign, const wchar_t* path) const
//      设置数字控件
//
// Return:
//      返回设置是否成功
//
// Parameter:
//      id      - 要设置的数字控件ID
//      bv      - 指示控件是否可见
//      d       - 要显示的数字
//      sign    - 指示数字是否有符号
//      path    - 指定数字控件图片路径
//
// Exception:
//      参数id标识的控件类型必须是数字控件
//      如果参数bv为false，将隐藏数字控件，并忽略参数 d / sign。
//
    bool _SetCtrlDigit(ctrlid_t id, bool bv, long long d) const {
        INum* pNumber = dynamic_cast<INum*>(_uiMgr->GetIControlbyID(id));
        if (!pNumber) return false;

        if (bv)
            pNumber->SetNum(d);

        pNumber->SetControlVisible(bv);

        return true;
    }    
    bool _SetCtrlDigit(ctrlid_t id, bool bv, long long d, bool sign, const wchar_t* path) const {
        INum* pNumber = dynamic_cast<INum*>(_uiMgr->GetIControlbyID(id));
        if (!pNumber) return false;

        if (path)
            pNumber->SetImagePath((wchar_t*)path);

        if (bv) {
            pNumber->SetHaveSymbol(sign);
            pNumber->SetNum(d);
        }
        
        pNumber->SetControlVisible(bv);

        return true;
    }

//-----------------------------------------------------------------------------
// bool _ShowDigit(ctrlid_t id, int iid, int d, bool sign) const
//      显示数字控件
//
// Return:
//      返回设置是否成功
//
// Parameter:
//      id      - 要设置的数字控件ID
//      iid     - 指定数字控件图片ID
//      d       - 要显示的数字
//      sign    - 指示数字是否有符号
//
// Exception:
//      参数id标识的控件类型必须是数字控件
//
    bool _ShowDigit(ctrlid_t id, int iid, long long d, bool sign) const {
        wchar_t path[1024] = { 0 };
        if(!_Make_Absolute_Path(iid, path))
            return false;

        // 显示筹码变更数字
        return _SetCtrlDigit(id, true, d, sign, path);
    }

//-----------------------------------------------------------------------------
// bool _SetCountDown(int id, bool bv, int maxt = 0, int mint = 0) const
//      设置时间控件
//
// Return:
//      返回设置是否成功
//
// Parameter:
//      id      - 要设置的控件ID
//      bv      - 指示控件是否可见
//      maxt    - 指示时间框起始时间
//      mint    - 指示时间框停止时间
//
// Exception:
//      参数id标识的控件类型必须是时间控件
//      如果参数bv为false，将隐藏时间框，并忽略参数maxt和mint。
//
    bool _SetCountDown(ctrlid_t id, bool bv, int maxt = 0, int mint = 0) const {
        ITime* pTimer = dynamic_cast<ITime*>(_uiMgr->GetIControlbyID(id));
        if (!pTimer) return false;

        if (bv) {
            pTimer->SetShowMaxNum(int(maxt * 0.001));
            pTimer->SetShowMinNum(int(mint * 0.001));
            pTimer->SetPLay(true);
        }

        pTimer->SetControlVisible(bv);

        return true;
    }

//-----------------------------------------------------------------------------
// bool _SetCtrlMove(int id, bool bv, int cid, bool play) const
//      设置移动控件
//
// Return:
//      返回设置是否成功
//
// Parameter:
//      id      - 要设置的移动控件ID
//      bv      - 指示移动控件是否可见
//      cid     - 指示要控制移动的控件ID
//      play    - 指示是否开始播放
//
// Exception:
//      参数id标识的控件类型必须是移动控件
//      参数bv将会同时影响参数id和cid所标识的控件的可见性
//      如果参数bv为false，将会隐藏移动控件和它要控制的控件，并忽略参数bp。
//
    bool _SetCtrlMove(ctrlid_t id, bool bv, ctrlid_t cid, bool bp) const {
        IMoveAction* pMove = dynamic_cast<IMoveAction*>(_uiMgr->GetIControlbyID(id));
        if (!pMove) return false;
        
        if (bv) pMove->SetControlingCtrlID(cid);

        _SetCtrlVisible(cid, bv);
        pMove->SetControlVisible(bv);

        if (bv) pMove->SetPlayState(bp);

        return true;
    }

//-----------------------------------------------------------------------------
// bool _SetCtrlImage(ctrlid_t id, bool bv, int xf = 0, int yf = 0, bool bc = false,, const wchar_t* path = nullptr) const
//      设置图片控件
//
// Return:
//      返回设置是否成功
//
// Parameter:
//      id      - 要设置的控件ID
//      bv      - 指定控件是否可见
//      sx      - 指定截取图片的x起始位置
//      sy      - 指定截取图片的y起始位置
//      bc      - 指定图片水平镜像绘制
//      path    - 指定图片文件路径
//
// Exception:
//      参数id标识的控件类型必须是图片控件
//      如果参数bv为false，将隐藏图片，并忽略参数 sx \ sy \ bc 。
//      函数从图片的(sx, sy)开始绘制，绘制的尺寸默认为控件的尺寸。
//
    bool _SetCtrlImage(ctrlid_t id, bool bv, int sx = 0, int sy = 0, bool bc = false, const wchar_t* path = nullptr) const {
        IImage* pImage = dynamic_cast<IImage*>(_uiMgr->GetIControlbyID(id));
        if (!pImage) return false;

        if (path)
            pImage->LoadPic((wchar_t*)path);

        /*if (bv)*/ {
            pImage->SetSrcX(sx);
            pImage->SetSrcY(sy);
            //pImage->SetSrcW(pImage->GetGameW());
            //pImage->SetSrcH(pImage->GetGameH());
            pImage->SetCrossMirror(bc);
        }

        pImage->SetControlVisible(bv);

        return true;
    }

    bool _SetCtrlImage(ctrlid_t id, bool bv, int sx, int sy, int sw, int sh, bool bc = false, const wchar_t* path = nullptr) const {
        IImage* pImage = dynamic_cast<IImage*>(_uiMgr->GetIControlbyID(id));
        if (!pImage) return false;

        if (path)
            pImage->LoadPic((wchar_t*)path);

        /*if (bv)*/ {
            pImage->SetSrcX(sx);
            pImage->SetSrcY(sy);
            pImage->SetSrcW(sw);
            pImage->SetSrcH(sh);
            pImage->SetCrossMirror(bc);
        }

        pImage->SetControlVisible(bv);

        return true;
    }

//-----------------------------------------------------------------------------
// bool _ShowImage(ctrlid_t id, int iid, int sx = 0, int sy = 0, bool bc = false) const
//      显示图片控件
//
// Return:
//      返回显示是否成功
//
// Parameter:
//      id      - 要设置的控件ID
//      iid     - 指定图片文件ID
//      sx      - 指定截取图片的x起始位置
//      sy      - 指定截取图片的y起始位置
//      bc      - 指定图片水平镜像绘制
//
// Exception:
//      参数id标识的控件类型必须是图片控件
//
    bool _ShowImage(ctrlid_t id, int iid, int sx = 0, int sy = 0, bool bc = false) const {
        wchar_t path[1024] = { 0 };
        if (!_Make_Absolute_Path(iid, path))
            return false;

        return _SetCtrlImage(id, true, sx, sy, bc, path);
    }

    bool _ShowImage(ctrlid_t id, int iid, int sx, int sy, int sw, int sh, bool bc = false) const {
        wchar_t path[1024] = { 0 };
        if (!_Make_Absolute_Path(iid, path))
            return false;

        return _SetCtrlImage(id, true, sx, sy, sw, sh, bc, path);
    }

//-----------------------------------------------------------------------------
// bool _SetCtrlAnimation(ctrlid_t id, bool bp, bool bl, int n = 1, const wchar_t* path = nullptr) const
//      设置动画控件
//
// Return:
//      返回设置是否成功
//
// Parameter:
//      id      - 要设置的动画控件ID
//      bp      - 指定控件是否播放
//      bl      - 指定控件是否循环播放
//      n       - 指定控件播放次数
//      path    - 指定动画文件路径
//
// Exception:
//      参数id标识的控件类型必须是动画控件
//      如果参数bp为false，将不会播放动画并隐藏，且忽略参数 bl \ n 。
//      如果参数bl为true，将会循环播放动画，并忽略参数 n 。
//
    bool _SetCtrlAnimation(ctrlid_t id, bool bp, bool bl, int n = 1, const wchar_t* path = nullptr) const {
        IExAnimate* pAnime = dynamic_cast<IExAnimate*>(_uiMgr->GetIControlbyID(id));
        if (!pAnime) return false;

        if (path) {
            pAnime->SetExtFilePath((wchar_t*)path);
            pAnime->LoadFromFile();
        }

        if (bp) {
            pAnime->SetIsLoop(bl);
            pAnime->SetCurveInstance(CT_NONE);

            if (!bl) pAnime->SetPlayNum(n);
        }
        
        pAnime->SetControlVisible(bp);
        pAnime->SetPlayState(bp);

        return true;
    }

//-----------------------------------------------------------------------------
// bbool _ShowAnimation(ctrlid_t id, int iid, bool bl, int n = 1) const
//      设置动画控件
//
// Return:
//      返回设置是否成功
//
// Parameter:
//      id      - 要设置的动画控件ID
//      iid     - 指定动画文件ID
//      bl      - 指定控件是否循环播放
//      n       - 指定控件播放次数
//
// Exception:
//      参数id标识的控件类型必须是动画控件
//
    bool _ShowAnimation(ctrlid_t id, int iid, bool bl, int n = 1) const {
        wchar_t path[1024] = { 0 };
        swprintf_s(path, L"%d\\%s", _game_id, _GetResPath(iid));

        return _SetCtrlAnimation(id, true, bl, n, path);
    }

//-----------------------------------------------------------------------------
// 1：bool _ShowAnimationFrame(ctrlid_t id, int z) const
// 2：bool _ShowAnimationFrame(ctrlid_t id) const
//      显示动画某一帧
//
// Return:
//      返回显示是否成功
//
// Parameter:
//      id      - 标识动画控件ID
//      z       - 指定要显示的帧
//
// Exception:
//      参数id标识的控件类型必须是动画控件
//      参数z标识的帧数从0开始，如果z大于动画的总帧数，返回false。
//      版本2不能指定帧数，默认显示动画的最后一帧。
//
    bool _ShowAnimationFrame(ctrlid_t id, int z) const {
        IExAnimate* pAnime = dynamic_cast<IExAnimate*>(_uiMgr->GetIControlbyID(id));
        
        if (pAnime) {
            if (z < pAnime->GetFrameNum()) {
                pAnime->SetShowFrame(z);
                return true;
            }
        }

        return false;
    }
    bool _ShowAnimationFrame(ctrlid_t id) const {
        IExAnimate* pAnime = dynamic_cast<IExAnimate*>(_uiMgr->GetIControlbyID(id));
        if (!pAnime) return false;
        
        pAnime->SetShowFrame(pAnime->GetFrameNum() - 1);

        return true;
    }
    /*
    bool _ShowCartoonFrame(ctrlid_t id, int z) const {
        ICartoon* pCtrl = dynamic_cast<ICartoon*>(_uiMgr->GetIControlbyID(id));
        if (!pCtrl) return false;

        z %= pCtrl->GetFrameNum();
        pCtrl->SetShowIndex(z);

        return true;
    }
    bool _ShowCartoonFrame(ctrlid_t id) const {
        ICartoon* pCtrl = dynamic_cast<ICartoon*>(_uiMgr->GetIControlbyID(id));
        if (!pCtrl) return false;

        pCtrl->SetShowIndex(pCtrl->GetFrameNum() - 1);

        return true;
    }
    */

    bool _ClearPoker(ctrlid_t id) const
    {
        ICardBase* pCard = dynamic_cast<ICardBase*>(_uiMgr->GetIControlbyID(id));
        if (pCard)
        {
            pCard->SetCardList(nullptr, 0);

            return true;
        }

        return false;
    }
    bool _SetOperatedPoker(ctrlid_t id, const unsigned char* pk, int n) const
    {
        IOperateCard* pCard = dynamic_cast<IOperateCard*>(_uiMgr->GetIControlbyID(id));
        if (!pCard) return false;

        pCard->SetControlVisible(true);
        pCard->SetCardList((unsigned char*)pk, n);

        return true;
    }

    bool _SetExplicitPoker(ctrlid_t id, const unsigned char* pk, int n) const
    {
        ILightCard* pCard = dynamic_cast<ILightCard*>(_uiMgr->GetIControlbyID(id));
        if (!pCard) return false;

        pCard->SetCardList((unsigned char*)pk, n);

        return true;
    }

    bool _SetUpListToOC(ctrlid_t id, const unsigned char* pk, int n) const
    {
        IOperateCard* pCard = dynamic_cast<IOperateCard*>(_uiMgr->GetIControlbyID(id));
        if (!pCard) return false;

        pCard->SetUpCardList((unsigned char*)pk, n);

        return true;
    }

    bool _GetUpListFromOC(ctrlid_t id, unsigned char* pk, int& n) const
    {
        IOperateCard* pCard = dynamic_cast<IOperateCard*>(_uiMgr->GetIControlbyID(id));
        if (!pCard) return false;

        n = pCard->GetUpCardList(pk);

        return true;
    }

    bool _ShowTalkEdit(bool bShow)
    {
        ITalk* pTalk = dynamic_cast<ITalk*>(_uiMgr->GetIControlbyID(_id_talk_output));
        if (!pTalk) return false;
        pTalk->SetControlVisible(bShow);

        IButton* pButton1 = dynamic_cast<IButton*>(_uiMgr->GetIControlbyID(_id_btn_talk_show));
        if (pButton1) pButton1->SetControlVisible(!bShow);

        IButton* pButton2 = dynamic_cast<IButton*>(_uiMgr->GetIControlbyID(_id_btn_talk_hide));
        if (pButton2) pButton2->SetControlVisible(bShow);

        return true;
    }

//-----------------------------------------------------------------------------

    gbase_t*    _gbMgr;         // 客户端管理者指针
    uimgr_t*    _uiMgr;         // ui控件管理者指针
    client_t    _Info;          // 客户端基本数据集

};  //  class _zjy_client_interface_base

_zjy_space_out

#endif
//  														2014-9 by Frank
//-----------------------------------------------------------------------------