//=============================================================================
// ZJY Summary
//=============================================================================
#ifdef ____zjy_summary_inl_

//=============================================================================
// Gist : 在大多数时候只需要考虑做什么，而不需要考虑该什么时候做。
//=============================================================================
// 1：对服务端和客户端提供的接口封装。
// 2：实现部分常用功能提供统一接口。
// 3：对接口的调用和实现规范化。

// 这将简化游戏开发的大量工作，并且将更加安全。

//=============================================================================
// File Location : sdk\bnb_lib\source\games\zjy\
//=============================================================================
_game_def.h
// 规定游戏基本信息和定义形式。

_game_server.h
// 定义服务端基类__zjy_server_interface_base，继承自平台提供的IGameDesk。
// 针对服务端改写定时器方法，改写部分常用操作，并提供二次改写接口。

_game_client.h
// 定义客户端基类__zjy_client_interface_base，继承自平台提供的IGameImplement。
// 实现所有虚函数，并提供部分常用操作接口。

_game_timer.h
// 定义游戏定时器类型_game_timer，以及定时器管理类_timer_manager。
// 使用模板为游戏服务端和客户端提供定时器操作的统一接口。并提供延迟调用功能。

_game_config.h
// 定义游戏配置信息基类config_base，以及配置管理类_config_info。
// 需要用户继承并提供自定义加载方法，内部以map划分配置数据。

_game_control.h
// 定义游戏常用控件ID，并规定控件ID定义形式。

ServerInterface.h
// 包含服务端所需头文件，在服务端只需包含该头文件。
// 定义服务端接口宏，规范化服务端定义形式，并提供简单化操作定义。

ClientInterface.h
// 包含客户端所需头文件，在客户端只需包含该头文件。
// 定义客户端接口宏，规范化客户端定义形式，并提供简单化操作定义。

//=============================================================================
// Remark
//=============================================================================
// 需要指定编译器的文件查找路径，添加 "..\..\..\sdk\bnb_lib\source\include\" 即可。
// 为了不与用户声明的名称冲突，zjy中所有的名称都以至少一个"_"开头。
// 几乎所有的数据和定义都提供了默认方式，但也提供了自定义方式。这将在各个头文件中进一步说明。
// 默认上述所有定义都将包含在命名空间zjy中，但也允许不使用该命名空间，参见_game_def.h。
// 游戏必须定义的宏：_game_id(标识游戏ID)/_game_name(标识游戏名称)/_player_max(标识游戏人数)。

//=============================================================================
// Example
//=============================================================================
// game_define.h :
#include "_game_def.h"

#define _game_id        12345678
#define _game_name      "gamename"
#define _player_max     4

_game_message_begin
// define message id
_game_message_end

_game_state_begin
// define state id
_game_state_end

// in server
// server.h :
#include "game_define.h"
#include "ServerInterface.h"

_DefineServerInterfaceBegin(classname)
// define what you need 
_DefineServerInterfaceEnd

// server.cpp :
_DefineServerInstanceHandle(classname)
// implementation what you need

// in client
// client.h :
#include "game_define.h"
#include "ClientInterface.h"

_DefineClientInterfaceBegin(classname)
// define what you need 
_DefineClientInterfaceEnd

// client.cpp :
_DefineClientInstanceHandle(classname)
// implementation what you need

#endif
//                                                      2014-9 by Frank
//-----------------------------------------------------------------------------