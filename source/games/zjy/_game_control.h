//=============================================================================
// _game_control.h
//
// Exception :
//      定义游戏默认控件ID，以及游戏控件ID定义形式。
//
//=============================================================================
#ifndef ____ZJY_Game_Control_Define_H_
#define ____ZJY_Game_Control_Define_H_

_zjy_enum_begin(_game_reserve_control)

//-----------------------------------------------------------------------------

      _id_ctrl_classroom        = 1234567           // 教室
    , _id_ctrl_frame            = 2                 // 边框
    , _id_btn_game_start        = 10001             // 开始按钮
    , _id_btn_game_bank         = 1112601           // 银行按钮

//-----------------------------------------------------------------------------

    , _id_image_game_logo       = 3                 // 游戏logo图片
    , _id_btn_game_minimize     = 10                // 最小化按钮
    , _id_btn_game_close        = 11                // 关闭按钮
    , _id_btn_game_set          = 12                // 设置按钮
    , _id_btn_game_help         = 1111030           // 帮助按钮
    , _id_btn_game_store        = 1111031           // 商城按钮
    , _id_btn_game_continue     = 1111230           // 继续按钮
    , _id_btn_game_change       = 1111231           // 换桌按钮

//-----------------------------------------------------------------------------

    , _id_container_hint        = 500               // 提示对话框
    , _id_btn_hint_ok                               // 确定按钮
    , _id_ctrl_hint_reserve0                        // 保留
    , _id_ctrl_hint_reserve1                        // 保留
    , _id_btn_hint_cancel                           // 取消按钮
    , _id_btn_hint_close                            // 关闭按钮
    , _id_text_hint_hint                            // 提示文字

//-----------------------------------------------------------------------------

    , _id_input_horn            = 700               // 喇叭信息框
    , _id_edit_horn_info                            // 信息输入框
    , _id_btn_horn_ok                               // 确定按钮
    , _id_btn_horn_cancel                           // 取消按钮
    , _id_text_horn_hint                            // 提示文字
    , _id_btn_horn_close                            // 关闭按钮

//-----------------------------------------------------------------------------

    , _id_container_talk        = 1000115           // 聊天容器
    , _id_btn_useful            = 1000215           // 常用语句按钮
    , _id_menu_useful           = 1000217           // 常用语菜单
    , _id_talk_output           = 200               // 聊天内容显示框
    , _id_edit_input                                // 聊天输入框
    , _id_btn_send                                  // 发送按钮
    , _id_container_horn        = 1110010           // 喇叭选择容器
    , _id_btn_show                                  // 当前按钮
    , _id_btn_current                               // 当前
    , _id_btn_horn_small                            // 小喇叭
    , _id_btn_horn_big                              // 大喇叭
    , _id_btn_horn_super                            // 超喇叭

//-----------------------------------------------------------------------------

    , _id_container_set         = 401               // 设置面板容器
    , _id_btn_set_close                             // 关闭按钮
    , _id_btn_set_ok                                // 确定按钮
    , _id_btn_set_cancel                            // 取消按钮
    , _id_check_set_music_ef                        // 音效单选框
    , _id_check_set_reserve                         // 保留单选框
    , _id_check_set_music_bg                        // 背景音乐单选框
    , _id_slip_set_volume                           // 音量调节滑块

//-----------------------------------------------------------------------------

    , _id_container_wait        = 450               // 排队容器
    , _id_btn_wait_back                             // 返回按钮
    , _id_anime_wait_hint                           // 排队动画
    , _id_image_wait_hint                           // 等待图片

//-----------------------------------------------------------------------------
    , _id_container_task        = 1111400           // 每日任务容器
    , _id_text_task_name1       = 1111370           // 每日任务名
    , _id_text_task_name2
    , _id_text_task_name3
    // ...
    , _id_image_task_len1       = 1111380           // 任务进度图片
    , _id_image_task_len2
    , _id_image_task_len3
    // ...
    , _id_text_task_done1       = 1111390           // 任务完成数字
    , _id_text_task_done2
    , _id_text_task_done3
    // ...

//-----------------------------------------------------------------------------

    , _id_interact_action       = 1001000           // 互动动作容器
    , _id_anime_0_start         = 1001010           // 位置0发动
    , _id_anime_1_start                             // 位置1发动
    , _id_anime_2_start                             // 位置2发动
    // ...
    , _id_anime_0_trace         = 1001020           // 位置0轨迹
    , _id_anime_1_trace                             // 位置1轨迹
    , _id_anime_2_trace                             // 位置2轨迹
    // ...
    , _id_anime_0_stop          = 1001030           // 位置0收到
    , _id_anime_1_stop                              // 位置1收到
    , _id_anime_2_stop                              // 位置2收到
    // ...

//-----------------------------------------------------------------------------

    , _id_interact_option0      = 1111210           // 互动操作容器
    , _id_btn_flirt0            = 120               // 动一下0按钮
    , _id_btn_flirt1                                // 动一下1按钮
    , _id_btn_flirt2                                // 动一下2按钮
    // ...
    , _id_btn_challenge0        = 1111120           // 挑战0按钮
    , _id_btn_challenge1                            // 挑战1按钮
    , _id_btn_challenge2                            // 挑战2按钮
    // ...

//-----------------------------------------------------------------------------

    , _id_text_player_nick0     = 70                // 玩家0昵称
    , _id_text_player_nick1                         // 玩家1昵称
    , _id_text_player_nick2                         // 玩家2昵称
    // ...
    , _id_image_nick_bg0        = 80                // 昵称底图0
    , _id_image_nick_bg1                            // 昵称底图1
    , _id_image_nick_bg2                            // 昵称底图2
    // ...
    , _id_xiu_player_xiu0       = 90                // 玩家0秀秀
    , _id_xiu_player_xiu1                           // 玩家1秀秀
    , _id_xiu_player_xiu2                           // 玩家2秀秀
    // ...    
    , _id_text_player_money0    = 100               // 玩家0金币
    , _id_text_player_money1                        // 玩家1金币
    , _id_text_player_money2                        // 玩家2金币
    // ...
    , _id_talk_player0          = 160               // 玩家0说话
    , _id_talk_player1                              // 玩家1说话
    , _id_talk_player2                              // 玩家2说话
    // ...
    , _id_image_player_di0      = 170               // 玩家0秀秀底图
    , _id_image_player_di1                          // 玩家1秀秀底图
    , _id_image_player_di2                          // 玩家2秀秀底图
    // ...
    , _id_image_talkbg0         = 180               // 位置0聊天气泡
    , _id_image_talkbg1                             // 位置1聊天气泡
    , _id_image_talkbg2                             // 位置2聊天气泡
    // ...
    , _id_image_ready0          = 20000             // 玩家0准备
    , _id_image_ready1                              // 玩家1准备
    , _id_image_ready2                              // 玩家2准备
    // ...
    
    , _id_container_active      = 1000250           // 活力容器 
    , _id_anime_active                              // 活力动画
    , _id_image_active_bg                           // 活力底图
    , _id_image_active_fill                         // 填充图片
    , _id_image_active_box                          // 宝箱图片
    , _id_move_active_flag                          // 移动标识
    , _id_text_active_add                           // 活力增加文字
    , _id_text_room_level                           // 场次等级文字
    , _id_text_odds_box1                            // 宝箱几率文字
    // ...
    , _id_text_odds_box5        = 1000265
    , _id_container_active_hint = 2000290           // 活力提示容器
    , _id_container_active_info
    , _id_digit_active_add      = 1000290           // 活力增加数字
    , _id_image_active_add                          // 活力增加图片

    , _id_btn_talk_show         = 3000020           // 显示聊天框
    , _id_btn_talk_hide         = 3000021           // 隐藏聊天框

_zjy_enum_end

_zjy_space_in

#define _T_Change_Ready         3000                // 游戏结束后换桌开始时间

#define _game_control_begin     _zjy_enum_begin(_game_custom_control) _id_ctrl_custom_begin  = 2000000,
#define _game_control_end       _game_control_max _zjy_enum_end

#define _game_res_id_begin      _zjy_enum_begin(_game_res_file_id)
#define _game_res_id_end        _grfi_max _zjy_enum_end

#define _game_sound_id_begin    _zjy_enum_begin(_game_sound_file_id)
#define _game_sound_id_end      _gsfi_max _zjy_enum_end


typedef struct _control_rect { int x, y, w, h; } _rect_t;   // 区域类型
typedef struct _control_position { int x, y; } _pos_t;      // 位置类型
typedef const wchar_t* _res_path_t;                         // 资源文件路径类型
typedef const char* _sound_path_t;                          // 声音文件路径类型

/*
 *	资源文件路径应指定为从游戏目录下的资源文件夹开始
 *  声音文件路径只需指明声音文件名即可
 */
#define _path_res_file_begin    _zjy_space_in _res_path_t _gc_resource_path[] = {
#define _path_res_file_end      }; _zjy_space_out

#define _path_sound_file_begin  _zjy_space_in _sound_path_t _gc_sound_path[] = {
#define _path_sound_file_end    }; _zjy_space_out

extern _res_path_t _gc_resource_path[];
extern _sound_path_t _gc_sound_path[];

inline _res_path_t _GetResPath(int rid) { return (_gc_resource_path[rid]); }

inline _sound_path_t _GetSoundPath(int sid) { return (_gc_sound_path[sid]); }

// 获取程序目录(非'\'结束)
//-----------------------------------------------------------------------------

inline bool _GetAppPath(wchar_t* path, int len) { return (_wgetcwd(path, len) != nullptr); }
template<int n> inline bool _GetAppPath(wchar_t (&path)[n]) { return (_GetAppPath(path, n)); }

//-----------------------------------------------------------------------------
// 1：bool _Make_Absolute_Path(const wchar_t* file, wchar_t* path, int len)
// 2：bool _Make_Absolute_Path(int pid, wchar_t* path, int len)
// 3：template<int len> bool _Make_Absolute_Path(const wchar_t* file, wchar_t (&path)[len])
// 4：template<int len> bool _Make_Absolute_Path(int pid, wchar_t (&path)[len])
//      生成文件的绝对路径
//
// Return:
//      如果生成成功返回 true ，否则返回 false 。
//
// Parameter:
//      file    - 指定文件名
//      pid     - 文件名 ID，参见：enum _res_file_id
//      path    - 生成的绝对路径缓冲区
//      len     - 缓冲区 path 的大小
//
// Exception:
//      该函数根据文件名生成与游戏对应的绝对路径
//
inline bool _Make_Absolute_Path(const wchar_t* file, wchar_t* path, int len) {
    wchar_t root[1024] = { 0 };
    if (!_GetAppPath(root)) return false;

    return !(0 > swprintf_s(path, len, L"%s\\%d\\%s", root, _game_id, file));
}

inline bool _Make_Absolute_Path(int pid, wchar_t* path, int len) {
    return _Make_Absolute_Path(_GetResPath(pid), path, len);
}

template<int len>
inline bool _Make_Absolute_Path(const wchar_t* file, wchar_t (&path)[len]) {
    return _Make_Absolute_Path(file, path, len);
}

template<int len>
inline bool _Make_Absolute_Path(int pid, wchar_t (&path)[len]) {
    return _Make_Absolute_Path(pid, path, len);
}

_zjy_space_out

#endif
//                                                         2014-9 by Frank
//-----------------------------------------------------------------------------