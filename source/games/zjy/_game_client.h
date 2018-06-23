//=============================================================================
// _game_client.h
//
// Exception :
//      ����ͻ����������ͺͽṹ������ͻ��˻��ࡣ
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

// ����ͻ��˶�ʱ����
typedef _game_timer<gbase_t> ctimer_t;

// ����ͻ������ݽṹ
//-----------------------------------------------------------------------------

typedef struct _client_info {
    int     m_iRoomID;              // ���ڷ���ID
    int     m_iTableID;             // ��������ID
    int     m_iPos;                 // �����е����
    state_t m_eGameState;           // ��Ϸ��״̬
    state_t m_eMyState;             // �Լ���״̬
    state_t m_eRole;                // �Լ��Ľ�ɫ
    bool    m_bPlaying;             // �Ƿ�������Ϸ

    // ������������ǳ�
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
//      �̳���IGameImplement��ʵ�������麯�������ṩ���ֳ��ò����ӿڡ�
//      ���������û�ֱ��ʹ�ø��࣬��Ҫ�̳в��ṩ�Զ��������
//
//=============================================================================
class __zjy_client_interface_base : public implement_t
{
public:

    // һ�θ�д����ӿ�
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
    
    // ��ʼ���ͻ��˹�����
    void __InitMgr(gbase_t* pgb, uimgr_t* pui) { _gbMgr = pgb; _uiMgr = pui; __Init_Instance_Timer(); }

    // ���ʽ�������ߺ��ն˹�����
    uimgr_t* GetUiMgr() const { return _uiMgr; }
    gbase_t* GetBaseMgr() const { return _gbMgr; }

protected:

    // �ܱ����Ĺ��캯�����⽫���²������û������������
    __zjy_client_interface_base() : _gbMgr(nullptr), _uiMgr(nullptr) { }

    // ���θ�д�ӿڣ��������Ҫ�����Լ�ʵ�֡�
    virtual void __Init_Instance_Config() { }
    virtual void __Init_Instance_Timer() { }
    virtual void _Initialize() { }  // �����Ҫ�ڿͻ���������ʱ�������������д�ú�����
    virtual result_t  _EventLeave(int) { return hr_success; }    // ��Ӧ�û��뿪�¼�
    virtual result_t  _EventEnter() { return hr_success; }      // ��Ӧ�û������¼�

//-----------------------------------------------------------------------------
// virtual int _LoadCtrl(const wchar_t*) const
//      ����ui��Դ�ļ�
//
// Return:
//      ������IUserInterface::LoadData��������ui��Դ�ļ��Ľ��
//
// Parameter:
//      ���Ժ���
//
// Exception:
//      �ú�������ui��Դ�ļ�������Զ�����ط�ʽ��Ҫ��д��
//      ������Ĭ������ϷID������Ŀ¼���������ļ���Ϊui�ļ�·����
//      ��������˺�_game_ui_dat����ʹ�øú궨���·����Ϊui�ļ�·����
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
    void _SetCurState(int state) { _Info.m_eGameState = state; }

//-----------------------------------------------------------------------------
// void _SetPlayerState(int state)
//      �������״̬
//
// Return:
//      void
//
// Parameter:
//      state   - Ҫ���õ�״̬
//
// Exception:
//      �û�״̬��ֵ�������Լ����塣
//
    void _SetPlayerState(int state) { _Info.m_eMyState |= state; }

//-----------------------------------------------------------------------------
// void _ErasePlayerState()
// void _ErasePlayerState(int state)
//      ������״̬
//
// Return:
//      void
//
// Parameter:
//      state   - Ҫ�����״̬
//
// Exception:
//      �û�״̬��ֵ�������Լ����塣
//
    void _ErasePlayerState() { _Info.m_eMyState = 0; }
    void _ErasePlayerState(int state) { _Info.m_eMyState &= ~state; }

//-----------------------------------------------------------------------------
// bool _CheckPlayerState(int state) const
//      ������״̬
//
// Return:
//      �����Ұ���ָ����״̬����true�����򷵻�false��
//
// Parameter:
//      state   - ָ��Ҫ����״̬
//
// Exception:
//
    bool _CheckPlayerState(int state) const { return (state == (_Info.m_eMyState & state)); }


//-----------------------------------------------------------------------------
// bool _IsPlaying() const
//      �ж���Ϸ�Ƿ������
//
// Return:
//      ���������Ϸ�����з���true�����򷵻�false��
//
// Parameter:
//      void
//
// Exception:
//
    bool _IsPlaying() const { return _Info.m_bPlaying; }

//-----------------------------------------------------------------------------
// void _SaveNickName()
//      ���汾������ǳ�
//
// Return:
//      void
//
// Parameter:
//      void
//
// Exception:
//      ��Ҫ����Ϸ��ʼ֮����ã������������������ȷ����
//
    void _SaveNickName() {
        wchar_t* ptr = nullptr;
        for (int i = 0; i < _player_max; ++i)
            if (ptr = _gbMgr->GetUserNickName(i))
                wcscpy_s(_Info.m_strName[i], ptr);
    }

//-----------------------------------------------------------------------------
// const wchar_t* _GetNickName(int pos) const
//      ��λ�û�ȡ����ǳ�
//
// Return:
//      Ҫ��ȡ������ǳ�
//
// Parameter:
//      pos     - ���λ�ú�
//
// Exception:
//      ���λ�÷Ƿ�������nullptr��
//
    const wchar_t* _GetNickName(int pos) const {
        if (pos >= 0 && pos < _player_max)
            return _Info.m_strName[pos];

        return nullptr;
    }

//-----------------------------------------------------------------------------
// const wchar_t* _GetMoneyName() const
//      ��ȡ�������
//
// Return:
//      �������
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
//      �ж��Ƿ������
//
// Return:
//      ����Ǵ���������true�����򷵻�false��
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
// 1��bool _SendMsg( int msg, void* buf, int len ) const
// 2��template<typename _Ty> bool _SendMsg( int msg, _Ty buf ) const
//      ������Ϸ��Ϣ������������ͨ�š�
//
// Return:
//      ���ƽ̨�ṩ���ͻ��˵Ĺ�����ָ����Ч����true�����򷵻�false��
//
// Parameter:
//      msg     - ��ʶ���͵���Ϣ��
//      buf     - Ҫ���͵�����
//      len     - Ҫ���͵����ݳ���
//
// Exception:
//      ���ڵڶ������ص�ģ��汾�����͵�����buf�����ǽṹ��ָ�룬��Ҫ���͵�
//      ���ݶ����ַ�����Ҳ���Ҫ�������ݳ��ȡ�
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
//      ��������
//
// Return:
//      ���ز����Ƿ�ɹ�
//
// Parameter:
//      pos     - Ҫ���ŵ�λ��
//      sid     - �����ļ�ID
//
// Exception:
//      ��2���汾Ĭ�ϲ����Լ�λ�õ�����
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
//      ���ÿؼ��Ƿ�ɼ�
//
// Return:
//      ���������Ƿ�ɹ�
//
// Parameter:
//      id      - Ҫ���õĿؼ�ID
//      bv      - �����true���򽫿ؼ���Ϊ�ɼ����������ؿؼ���
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
//      ������ҵ�׼��ͼ���Ƿ�ɼ�
//
// Return:
//      ���������Ƿ�ɹ�
//
// Parameter:
//      pos     - Ҫ���õ����λ�úţ��������Զ���λ�ú�ת��Ϊ��Ӧ�Ŀؼ�ID��
//      bv      - �����true���򽫸���ҵ�׼��ͼ����Ϊ�ɼ�����������׼��ͼ�ꡣ
//
// Exception:
//      ��Ҫ������ui��Դ�����׼��ͼƬ�ؼ�
//
    bool _SetReadyVisible( int pos, bool bv ) const {
        return _SetCtrlVisible(_gbMgr->DeskStation2View(pos) + _id_image_ready0, bv);
    }

//-----------------------------------------------------------------------------
// bool _SetCtrlPos(int id, int x, int y) const
//      ���ÿؼ�λ��
//
// Return:
//      ���������Ƿ�ɹ�
//
// Parameter:
//      id      - Ҫ���õĿؼ�ID
//      x       - Ҫ���õ�x����
//      y       - Ҫ���õ�y����
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
//      ���ð�ť�Ƿ񼤻�
//
// Return:
//      ���������Ƿ�ɹ�
//
// Parameter:
//      id      - Ҫ���õİ�ťID
//      be      - �����true���򽫰�ť��Ϊ����״̬��������Ϊ������״̬��
//
// Exception:
//      ����id��ʶ�Ŀؼ����ͱ����ǰ�ť�ؼ�
//
    bool _SetBtnEnable(ctrlid_t id, bool be) const {
        IButton* pButton = dynamic_cast<IButton*>(_uiMgr->GetIControlbyID(id));
        if (!pButton) return false;

        pButton->SetEnable(be);
        return true;            
    }

//-----------------------------------------------------------------------------
// 1��bool _SetCtrlText(int id, bool bv, const wchar_t* text) const
// 2��bool _SetCtrlText(int id, bool bv, const wchar_t* text, color_t clr) const
//      �������ֿؼ�
//
// Return:
//      ���������Ƿ�ɹ�
//
// Parameter:
//      id      - Ҫ���õ����ֿؼ�ID
//      bv      - ָʾ���ֿؼ��Ƿ�ɼ�
//      text    - Ҫ��ʾ������
//      clr     - ָʾ���ֵ���ɫ
//
// Exception:
//      ����id��ʶ�Ŀؼ����ͱ��������ֿؼ�
//      �������bvΪfalse�����������ֿؼ��������Բ���text��clr��
//      �������textΪnullptr����ֻ�޸Ŀؼ��Ŀɼ�״̬�����޸Ŀؼ����������ݡ�
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
//      �������ֿؼ�
//
// Return:
//      ���������Ƿ�ɹ�
//
// Parameter:
//      id      - Ҫ���õ����ֿؼ�ID
//      bv      - ָʾ�ؼ��Ƿ�ɼ�
//      d       - Ҫ��ʾ������
//      sign    - ָʾ�����Ƿ��з���
//      path    - ָ�����ֿؼ�ͼƬ·��
//
// Exception:
//      ����id��ʶ�Ŀؼ����ͱ��������ֿؼ�
//      �������bvΪfalse�����������ֿؼ��������Բ��� d / sign��
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
//      ��ʾ���ֿؼ�
//
// Return:
//      ���������Ƿ�ɹ�
//
// Parameter:
//      id      - Ҫ���õ����ֿؼ�ID
//      iid     - ָ�����ֿؼ�ͼƬID
//      d       - Ҫ��ʾ������
//      sign    - ָʾ�����Ƿ��з���
//
// Exception:
//      ����id��ʶ�Ŀؼ����ͱ��������ֿؼ�
//
    bool _ShowDigit(ctrlid_t id, int iid, long long d, bool sign) const {
        wchar_t path[1024] = { 0 };
        if(!_Make_Absolute_Path(iid, path))
            return false;

        // ��ʾ����������
        return _SetCtrlDigit(id, true, d, sign, path);
    }

//-----------------------------------------------------------------------------
// bool _SetCountDown(int id, bool bv, int maxt = 0, int mint = 0) const
//      ����ʱ��ؼ�
//
// Return:
//      ���������Ƿ�ɹ�
//
// Parameter:
//      id      - Ҫ���õĿؼ�ID
//      bv      - ָʾ�ؼ��Ƿ�ɼ�
//      maxt    - ָʾʱ�����ʼʱ��
//      mint    - ָʾʱ���ֹͣʱ��
//
// Exception:
//      ����id��ʶ�Ŀؼ����ͱ�����ʱ��ؼ�
//      �������bvΪfalse��������ʱ��򣬲����Բ���maxt��mint��
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
//      �����ƶ��ؼ�
//
// Return:
//      ���������Ƿ�ɹ�
//
// Parameter:
//      id      - Ҫ���õ��ƶ��ؼ�ID
//      bv      - ָʾ�ƶ��ؼ��Ƿ�ɼ�
//      cid     - ָʾҪ�����ƶ��Ŀؼ�ID
//      play    - ָʾ�Ƿ�ʼ����
//
// Exception:
//      ����id��ʶ�Ŀؼ����ͱ������ƶ��ؼ�
//      ����bv����ͬʱӰ�����id��cid����ʶ�Ŀؼ��Ŀɼ���
//      �������bvΪfalse�����������ƶ��ؼ�����Ҫ���ƵĿؼ��������Բ���bp��
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
//      ����ͼƬ�ؼ�
//
// Return:
//      ���������Ƿ�ɹ�
//
// Parameter:
//      id      - Ҫ���õĿؼ�ID
//      bv      - ָ���ؼ��Ƿ�ɼ�
//      sx      - ָ����ȡͼƬ��x��ʼλ��
//      sy      - ָ����ȡͼƬ��y��ʼλ��
//      bc      - ָ��ͼƬˮƽ�������
//      path    - ָ��ͼƬ�ļ�·��
//
// Exception:
//      ����id��ʶ�Ŀؼ����ͱ�����ͼƬ�ؼ�
//      �������bvΪfalse��������ͼƬ�������Բ��� sx \ sy \ bc ��
//      ������ͼƬ��(sx, sy)��ʼ���ƣ����Ƶĳߴ�Ĭ��Ϊ�ؼ��ĳߴ硣
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
//      ��ʾͼƬ�ؼ�
//
// Return:
//      ������ʾ�Ƿ�ɹ�
//
// Parameter:
//      id      - Ҫ���õĿؼ�ID
//      iid     - ָ��ͼƬ�ļ�ID
//      sx      - ָ����ȡͼƬ��x��ʼλ��
//      sy      - ָ����ȡͼƬ��y��ʼλ��
//      bc      - ָ��ͼƬˮƽ�������
//
// Exception:
//      ����id��ʶ�Ŀؼ����ͱ�����ͼƬ�ؼ�
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
//      ���ö����ؼ�
//
// Return:
//      ���������Ƿ�ɹ�
//
// Parameter:
//      id      - Ҫ���õĶ����ؼ�ID
//      bp      - ָ���ؼ��Ƿ񲥷�
//      bl      - ָ���ؼ��Ƿ�ѭ������
//      n       - ָ���ؼ����Ŵ���
//      path    - ָ�������ļ�·��
//
// Exception:
//      ����id��ʶ�Ŀؼ����ͱ����Ƕ����ؼ�
//      �������bpΪfalse�������Ქ�Ŷ��������أ��Һ��Բ��� bl \ n ��
//      �������blΪtrue������ѭ�����Ŷ����������Բ��� n ��
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
//      ���ö����ؼ�
//
// Return:
//      ���������Ƿ�ɹ�
//
// Parameter:
//      id      - Ҫ���õĶ����ؼ�ID
//      iid     - ָ�������ļ�ID
//      bl      - ָ���ؼ��Ƿ�ѭ������
//      n       - ָ���ؼ����Ŵ���
//
// Exception:
//      ����id��ʶ�Ŀؼ����ͱ����Ƕ����ؼ�
//
    bool _ShowAnimation(ctrlid_t id, int iid, bool bl, int n = 1) const {
        wchar_t path[1024] = { 0 };
        swprintf_s(path, L"%d\\%s", _game_id, _GetResPath(iid));

        return _SetCtrlAnimation(id, true, bl, n, path);
    }

//-----------------------------------------------------------------------------
// 1��bool _ShowAnimationFrame(ctrlid_t id, int z) const
// 2��bool _ShowAnimationFrame(ctrlid_t id) const
//      ��ʾ����ĳһ֡
//
// Return:
//      ������ʾ�Ƿ�ɹ�
//
// Parameter:
//      id      - ��ʶ�����ؼ�ID
//      z       - ָ��Ҫ��ʾ��֡
//
// Exception:
//      ����id��ʶ�Ŀؼ����ͱ����Ƕ����ؼ�
//      ����z��ʶ��֡����0��ʼ�����z���ڶ�������֡��������false��
//      �汾2����ָ��֡����Ĭ����ʾ���������һ֡��
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

    gbase_t*    _gbMgr;         // �ͻ��˹�����ָ��
    uimgr_t*    _uiMgr;         // ui�ؼ�������ָ��
    client_t    _Info;          // �ͻ��˻������ݼ�

};  //  class _zjy_client_interface_base

_zjy_space_out

#endif
//  														2014-9 by Frank
//-----------------------------------------------------------------------------