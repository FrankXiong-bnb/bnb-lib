//=============================================================================
// _game_def.h
//
// Exception :
//      ������Ϸ���ֿռ䣬������Ϸ��ز������Լ����ݶ������
//
//=============================================================================
#ifndef ____zjy_Game_Difine_H_
#define ____zjy_Game_Difine_H_

// �����Ƿ�ʹ���Ͻ��������ռ�
// Ĭ�϶����Ͻ��������ռ䣺namespace zjy
// ��Ҫȡ�������ռ䣬�붨�壺#define _zjy_not_namespace
#ifndef _zjy_not_namespace
#define _zjy_space_in           namespace zjy {
#define _zjy_space_out          }
#define _zjy                    ::zjy::
#else 
#define _zjy_space_in
#define _zjy_space_out
#define _zjy
#endif  // _zjy_not_namespace

// ������Ϸ�ӿ��Ե��������ʽ
#define _game_interface         __declspec(dllexport)

#define _zjy_server             0           // �������˺�
#define _zjy_client             1           // ����ͻ��˺�

#define _size_nick_name         61          // �ǳƳ���
#define _Main_Msg_ID            180         // ����ϢID
#define _Begin_Msg_ID           51          // ��Ϸ��ʼ��Ϣ

// ������Ϸ��ʼ��ʱ������Ϣ _gm_begin
// ��Ϸ��ʼʱ���͸���ϢĬ�Ͽ���¼����
// ��Ҫȡ��¼���ܣ��붨�壺#define _zjy_not_record
#ifndef _zjy_not_record
#define _Msg_begin = _Begin_Msg_ID
#else
#define _Msg_begin
#endif  // #ifndef _zjy_not_record

// ����ö�ٶ�����ʽ
#define _zjy_enum_begin(name)   _zjy_space_in enum name {
#define _zjy_enum_end           }; _zjy_space_out

// ������Ϸ״̬������ʽ��Ĭ��״̬���壺δ֪(0)/����(1)/�ȴ�(2)
#define _game_state_begin       _zjy_enum_begin(_game_state) _gs_unknow, _gs_idle, _gs_wait,
#define _game_state_end         _gs_max _zjy_enum_end

// ������Ϸ��Ϣ������ʽ��Ĭ����Ϣ���壺δ֪��Ϣ(0)/ͬ����Ϣ(1)/״̬�·�(2)/��Ϸ��ʼ(51)
#define _game_message_begin     _zjy_enum_begin(_game_message) _gm_unknow, _gm_agree, _gm_state, _gm_update, _gm_begin _Msg_begin,
#define _game_message_end       _gm_max _zjy_enum_end

// ������Ϸ������
_zjy_enum_begin(_handle_result)
    hr_success,                 // �ɹ�
    hr_fail,                    // ʧ��
    hr_unknow
_zjy_enum_end

// ���巿������
_zjy_enum_begin(_room_type)
    rt_own_choice,              // ���г�
    rt_make_a_match,            // ��ϳ�
    rt_max
_zjy_enum_end

_zjy_space_in

// typedef
typedef unsigned char*          buf_t;      // ����������
typedef long long               money_t;    // �������
typedef unsigned long           state_t;    // ״̬����
typedef unsigned long           param_t;    // ��������
typedef unsigned int            msg_t;      // ��Ϣ����
typedef unsigned int            cdt_t;      // ��ʱ����
typedef int                     result_t;   // �������
typedef int                     pos_t;      // λ������

struct _game_msg_base { state_t m_eState; };    // ��Ϣ����

#define _Msg_base : public _game_msg_base

struct msg_client_to_server _Msg_base { };  // �ӿͻ��˷�������˵���Ϣ����
struct msg_server_to_client _Msg_base { };  // �ӷ���˷����ͻ��˵���Ϣ����

#define _Msg_stoc : public msg_server_to_client
#define _Msg_ctos : public msg_client_to_server

/*
// �û�ͬ�⿪ʼ��Ϣ
struct MSG_GR_R_UserAgree {
    unsigned char   bDeskNO;	            // ��Ϸ����
    unsigned char   bDeskStation;           // λ�ú���
    unsigned char   bAgreeGame;		        // ͬ���־
};

typedef MSG_GR_R_UserAgree msg_stoc_ready;
typedef MSG_GR_R_UserAgree msg_ctos_ready;
*/

struct _msg_stoc_ready _Msg_stoc {
    int m_table;
    int m_pos;
};

struct _msg_stoc_update _Msg_stoc { };

typedef _msg_stoc_ready msg_stoc_ready;
typedef _msg_stoc_ready msg_ctos_ready;

_zjy_space_out

#endif

//  														2014-8 by Frank
//-----------------------------------------------------------------------------