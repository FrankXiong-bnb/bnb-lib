//=============================================================================
// _game_def.h
//
// Exception :
//      声明游戏名字空间，定义游戏相关参数，以及数据定义规则。
//
//=============================================================================
#ifndef ____zjy_Game_Difine_H_
#define ____zjy_Game_Difine_H_

// 声明是否使用紫金游命名空间
// 默认定义紫金游命名空间：namespace zjy
// 若要取消命名空间，请定义：#define _zjy_not_namespace
#ifndef _zjy_not_namespace
#define _zjy_space_in           namespace zjy {
#define _zjy_space_out          }
#define _zjy                    ::zjy::
#else 
#define _zjy_space_in
#define _zjy_space_out
#define _zjy
#endif  // _zjy_not_namespace

// 声明游戏接口以导出库的形式
#define _game_interface         __declspec(dllexport)

#define _zjy_server             0           // 定义服务端宏
#define _zjy_client             1           // 定义客户端宏

#define _size_nick_name         61          // 昵称长度
#define _Main_Msg_ID            180         // 主消息ID
#define _Begin_Msg_ID           51          // 游戏开始消息

// 建议游戏开始的时候发送消息 _gm_begin
// 游戏开始时发送该消息默认开启录像功能
// 若要取消录像功能，请定义：#define _zjy_not_record
#ifndef _zjy_not_record
#define _Msg_begin = _Begin_Msg_ID
#else
#define _Msg_begin
#endif  // #ifndef _zjy_not_record

// 声明枚举定义形式
#define _zjy_enum_begin(name)   _zjy_space_in enum name {
#define _zjy_enum_end           }; _zjy_space_out

// 声明游戏状态定义形式，默认状态语义：未知(0)/空闲(1)/等待(2)
#define _game_state_begin       _zjy_enum_begin(_game_state) _gs_unknow, _gs_idle, _gs_wait,
#define _game_state_end         _gs_max _zjy_enum_end

// 声明游戏消息定义形式，默认消息语义：未知消息(0)/同意消息(1)/状态下发(2)/游戏开始(51)
#define _game_message_begin     _zjy_enum_begin(_game_message) _gm_unknow, _gm_agree, _gm_state, _gm_update, _gm_begin _Msg_begin,
#define _game_message_end       _gm_max _zjy_enum_end

// 定义游戏处理结果
_zjy_enum_begin(_handle_result)
    hr_success,                 // 成功
    hr_fail,                    // 失败
    hr_unknow
_zjy_enum_end

// 定义房间类型
_zjy_enum_begin(_room_type)
    rt_own_choice,              // 休闲场
    rt_make_a_match,            // 撮合场
    rt_max
_zjy_enum_end

_zjy_space_in

// typedef
typedef unsigned char*          buf_t;      // 缓冲区类型
typedef long long               money_t;    // 金币类型
typedef unsigned long           state_t;    // 状态类型
typedef unsigned long           param_t;    // 参数类型
typedef unsigned int            msg_t;      // 消息类型
typedef unsigned int            cdt_t;      // 计时类型
typedef int                     result_t;   // 结果类型
typedef int                     pos_t;      // 位置类型

struct _game_msg_base { state_t m_eState; };    // 消息基类

#define _Msg_base : public _game_msg_base

struct msg_client_to_server _Msg_base { };  // 从客户端发到服务端的消息基类
struct msg_server_to_client _Msg_base { };  // 从服务端发到客户端的消息基类

#define _Msg_stoc : public msg_server_to_client
#define _Msg_ctos : public msg_client_to_server

/*
// 用户同意开始消息
struct MSG_GR_R_UserAgree {
    unsigned char   bDeskNO;	            // 游戏桌号
    unsigned char   bDeskStation;           // 位置号码
    unsigned char   bAgreeGame;		        // 同意标志
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