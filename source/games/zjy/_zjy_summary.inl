//=============================================================================
// ZJY Summary
//=============================================================================
#ifdef ____zjy_summary_inl_

//=============================================================================
// Gist : �ڴ����ʱ��ֻ��Ҫ������ʲô��������Ҫ���Ǹ�ʲôʱ������
//=============================================================================
// 1���Է���˺Ϳͻ����ṩ�Ľӿڷ�װ��
// 2��ʵ�ֲ��ֳ��ù����ṩͳһ�ӿڡ�
// 3���Խӿڵĵ��ú�ʵ�ֹ淶����

// �⽫����Ϸ�����Ĵ������������ҽ����Ӱ�ȫ��

//=============================================================================
// File Location : sdk\bnb_lib\source\games\zjy\
//=============================================================================
_game_def.h
// �涨��Ϸ������Ϣ�Ͷ�����ʽ��

_game_server.h
// �������˻���__zjy_server_interface_base���̳���ƽ̨�ṩ��IGameDesk��
// ��Է���˸�д��ʱ����������д���ֳ��ò��������ṩ���θ�д�ӿڡ�

_game_client.h
// ����ͻ��˻���__zjy_client_interface_base���̳���ƽ̨�ṩ��IGameImplement��
// ʵ�������麯�������ṩ���ֳ��ò����ӿڡ�

_game_timer.h
// ������Ϸ��ʱ������_game_timer���Լ���ʱ��������_timer_manager��
// ʹ��ģ��Ϊ��Ϸ����˺Ϳͻ����ṩ��ʱ��������ͳһ�ӿڡ����ṩ�ӳٵ��ù��ܡ�

_game_config.h
// ������Ϸ������Ϣ����config_base���Լ����ù�����_config_info��
// ��Ҫ�û��̳в��ṩ�Զ�����ط������ڲ���map�����������ݡ�

_game_control.h
// ������Ϸ���ÿؼ�ID�����涨�ؼ�ID������ʽ��

ServerInterface.h
// �������������ͷ�ļ����ڷ����ֻ�������ͷ�ļ���
// �������˽ӿں꣬�淶������˶�����ʽ�����ṩ�򵥻��������塣

ClientInterface.h
// �����ͻ�������ͷ�ļ����ڿͻ���ֻ�������ͷ�ļ���
// ����ͻ��˽ӿں꣬�淶���ͻ��˶�����ʽ�����ṩ�򵥻��������塣

//=============================================================================
// Remark
//=============================================================================
// ��Ҫָ�����������ļ�����·������� "..\..\..\sdk\bnb_lib\source\include\" ���ɡ�
// Ϊ�˲����û����������Ƴ�ͻ��zjy�����е����ƶ�������һ��"_"��ͷ��
// �������е����ݺͶ��嶼�ṩ��Ĭ�Ϸ�ʽ����Ҳ�ṩ���Զ��巽ʽ���⽫�ڸ���ͷ�ļ��н�һ��˵����
// Ĭ���������ж��嶼�������������ռ�zjy�У���Ҳ����ʹ�ø������ռ䣬�μ�_game_def.h��
// ��Ϸ���붨��ĺ꣺_game_id(��ʶ��ϷID)/_game_name(��ʶ��Ϸ����)/_player_max(��ʶ��Ϸ����)��

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