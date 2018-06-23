//=============================================================================
// _game_control.h
//
// Exception :
//      ������ϷĬ�Ͽؼ�ID���Լ���Ϸ�ؼ�ID������ʽ��
//
//=============================================================================
#ifndef ____ZJY_Game_Control_Define_H_
#define ____ZJY_Game_Control_Define_H_

_zjy_enum_begin(_game_reserve_control)

//-----------------------------------------------------------------------------

      _id_ctrl_classroom        = 1234567           // ����
    , _id_ctrl_frame            = 2                 // �߿�
    , _id_btn_game_start        = 10001             // ��ʼ��ť
    , _id_btn_game_bank         = 1112601           // ���а�ť

//-----------------------------------------------------------------------------

    , _id_image_game_logo       = 3                 // ��ϷlogoͼƬ
    , _id_btn_game_minimize     = 10                // ��С����ť
    , _id_btn_game_close        = 11                // �رհ�ť
    , _id_btn_game_set          = 12                // ���ð�ť
    , _id_btn_game_help         = 1111030           // ������ť
    , _id_btn_game_store        = 1111031           // �̳ǰ�ť
    , _id_btn_game_continue     = 1111230           // ������ť
    , _id_btn_game_change       = 1111231           // ������ť

//-----------------------------------------------------------------------------

    , _id_container_hint        = 500               // ��ʾ�Ի���
    , _id_btn_hint_ok                               // ȷ����ť
    , _id_ctrl_hint_reserve0                        // ����
    , _id_ctrl_hint_reserve1                        // ����
    , _id_btn_hint_cancel                           // ȡ����ť
    , _id_btn_hint_close                            // �رհ�ť
    , _id_text_hint_hint                            // ��ʾ����

//-----------------------------------------------------------------------------

    , _id_input_horn            = 700               // ������Ϣ��
    , _id_edit_horn_info                            // ��Ϣ�����
    , _id_btn_horn_ok                               // ȷ����ť
    , _id_btn_horn_cancel                           // ȡ����ť
    , _id_text_horn_hint                            // ��ʾ����
    , _id_btn_horn_close                            // �رհ�ť

//-----------------------------------------------------------------------------

    , _id_container_talk        = 1000115           // ��������
    , _id_btn_useful            = 1000215           // ������䰴ť
    , _id_menu_useful           = 1000217           // ������˵�
    , _id_talk_output           = 200               // ����������ʾ��
    , _id_edit_input                                // ���������
    , _id_btn_send                                  // ���Ͱ�ť
    , _id_container_horn        = 1110010           // ����ѡ������
    , _id_btn_show                                  // ��ǰ��ť
    , _id_btn_current                               // ��ǰ
    , _id_btn_horn_small                            // С����
    , _id_btn_horn_big                              // ������
    , _id_btn_horn_super                            // ������

//-----------------------------------------------------------------------------

    , _id_container_set         = 401               // �����������
    , _id_btn_set_close                             // �رհ�ť
    , _id_btn_set_ok                                // ȷ����ť
    , _id_btn_set_cancel                            // ȡ����ť
    , _id_check_set_music_ef                        // ��Ч��ѡ��
    , _id_check_set_reserve                         // ������ѡ��
    , _id_check_set_music_bg                        // �������ֵ�ѡ��
    , _id_slip_set_volume                           // �������ڻ���

//-----------------------------------------------------------------------------

    , _id_container_wait        = 450               // �Ŷ�����
    , _id_btn_wait_back                             // ���ذ�ť
    , _id_anime_wait_hint                           // �ŶӶ���
    , _id_image_wait_hint                           // �ȴ�ͼƬ

//-----------------------------------------------------------------------------
    , _id_container_task        = 1111400           // ÿ����������
    , _id_text_task_name1       = 1111370           // ÿ��������
    , _id_text_task_name2
    , _id_text_task_name3
    // ...
    , _id_image_task_len1       = 1111380           // �������ͼƬ
    , _id_image_task_len2
    , _id_image_task_len3
    // ...
    , _id_text_task_done1       = 1111390           // �����������
    , _id_text_task_done2
    , _id_text_task_done3
    // ...

//-----------------------------------------------------------------------------

    , _id_interact_action       = 1001000           // ������������
    , _id_anime_0_start         = 1001010           // λ��0����
    , _id_anime_1_start                             // λ��1����
    , _id_anime_2_start                             // λ��2����
    // ...
    , _id_anime_0_trace         = 1001020           // λ��0�켣
    , _id_anime_1_trace                             // λ��1�켣
    , _id_anime_2_trace                             // λ��2�켣
    // ...
    , _id_anime_0_stop          = 1001030           // λ��0�յ�
    , _id_anime_1_stop                              // λ��1�յ�
    , _id_anime_2_stop                              // λ��2�յ�
    // ...

//-----------------------------------------------------------------------------

    , _id_interact_option0      = 1111210           // ������������
    , _id_btn_flirt0            = 120               // ��һ��0��ť
    , _id_btn_flirt1                                // ��һ��1��ť
    , _id_btn_flirt2                                // ��һ��2��ť
    // ...
    , _id_btn_challenge0        = 1111120           // ��ս0��ť
    , _id_btn_challenge1                            // ��ս1��ť
    , _id_btn_challenge2                            // ��ս2��ť
    // ...

//-----------------------------------------------------------------------------

    , _id_text_player_nick0     = 70                // ���0�ǳ�
    , _id_text_player_nick1                         // ���1�ǳ�
    , _id_text_player_nick2                         // ���2�ǳ�
    // ...
    , _id_image_nick_bg0        = 80                // �ǳƵ�ͼ0
    , _id_image_nick_bg1                            // �ǳƵ�ͼ1
    , _id_image_nick_bg2                            // �ǳƵ�ͼ2
    // ...
    , _id_xiu_player_xiu0       = 90                // ���0����
    , _id_xiu_player_xiu1                           // ���1����
    , _id_xiu_player_xiu2                           // ���2����
    // ...    
    , _id_text_player_money0    = 100               // ���0���
    , _id_text_player_money1                        // ���1���
    , _id_text_player_money2                        // ���2���
    // ...
    , _id_talk_player0          = 160               // ���0˵��
    , _id_talk_player1                              // ���1˵��
    , _id_talk_player2                              // ���2˵��
    // ...
    , _id_image_player_di0      = 170               // ���0�����ͼ
    , _id_image_player_di1                          // ���1�����ͼ
    , _id_image_player_di2                          // ���2�����ͼ
    // ...
    , _id_image_talkbg0         = 180               // λ��0��������
    , _id_image_talkbg1                             // λ��1��������
    , _id_image_talkbg2                             // λ��2��������
    // ...
    , _id_image_ready0          = 20000             // ���0׼��
    , _id_image_ready1                              // ���1׼��
    , _id_image_ready2                              // ���2׼��
    // ...
    
    , _id_container_active      = 1000250           // �������� 
    , _id_anime_active                              // ��������
    , _id_image_active_bg                           // ������ͼ
    , _id_image_active_fill                         // ���ͼƬ
    , _id_image_active_box                          // ����ͼƬ
    , _id_move_active_flag                          // �ƶ���ʶ
    , _id_text_active_add                           // ������������
    , _id_text_room_level                           // ���εȼ�����
    , _id_text_odds_box1                            // ���伸������
    // ...
    , _id_text_odds_box5        = 1000265
    , _id_container_active_hint = 2000290           // ������ʾ����
    , _id_container_active_info
    , _id_digit_active_add      = 1000290           // ������������
    , _id_image_active_add                          // ��������ͼƬ

    , _id_btn_talk_show         = 3000020           // ��ʾ�����
    , _id_btn_talk_hide         = 3000021           // ���������

_zjy_enum_end

_zjy_space_in

#define _T_Change_Ready         3000                // ��Ϸ����������ʼʱ��

#define _game_control_begin     _zjy_enum_begin(_game_custom_control) _id_ctrl_custom_begin  = 2000000,
#define _game_control_end       _game_control_max _zjy_enum_end

#define _game_res_id_begin      _zjy_enum_begin(_game_res_file_id)
#define _game_res_id_end        _grfi_max _zjy_enum_end

#define _game_sound_id_begin    _zjy_enum_begin(_game_sound_file_id)
#define _game_sound_id_end      _gsfi_max _zjy_enum_end


typedef struct _control_rect { int x, y, w, h; } _rect_t;   // ��������
typedef struct _control_position { int x, y; } _pos_t;      // λ������
typedef const wchar_t* _res_path_t;                         // ��Դ�ļ�·������
typedef const char* _sound_path_t;                          // �����ļ�·������

/*
 *	��Դ�ļ�·��Ӧָ��Ϊ����ϷĿ¼�µ���Դ�ļ��п�ʼ
 *  �����ļ�·��ֻ��ָ�������ļ�������
 */
#define _path_res_file_begin    _zjy_space_in _res_path_t _gc_resource_path[] = {
#define _path_res_file_end      }; _zjy_space_out

#define _path_sound_file_begin  _zjy_space_in _sound_path_t _gc_sound_path[] = {
#define _path_sound_file_end    }; _zjy_space_out

extern _res_path_t _gc_resource_path[];
extern _sound_path_t _gc_sound_path[];

inline _res_path_t _GetResPath(int rid) { return (_gc_resource_path[rid]); }

inline _sound_path_t _GetSoundPath(int sid) { return (_gc_sound_path[sid]); }

// ��ȡ����Ŀ¼(��'\'����)
//-----------------------------------------------------------------------------

inline bool _GetAppPath(wchar_t* path, int len) { return (_wgetcwd(path, len) != nullptr); }
template<int n> inline bool _GetAppPath(wchar_t (&path)[n]) { return (_GetAppPath(path, n)); }

//-----------------------------------------------------------------------------
// 1��bool _Make_Absolute_Path(const wchar_t* file, wchar_t* path, int len)
// 2��bool _Make_Absolute_Path(int pid, wchar_t* path, int len)
// 3��template<int len> bool _Make_Absolute_Path(const wchar_t* file, wchar_t (&path)[len])
// 4��template<int len> bool _Make_Absolute_Path(int pid, wchar_t (&path)[len])
//      �����ļ��ľ���·��
//
// Return:
//      ������ɳɹ����� true �����򷵻� false ��
//
// Parameter:
//      file    - ָ���ļ���
//      pid     - �ļ��� ID���μ���enum _res_file_id
//      path    - ���ɵľ���·��������
//      len     - ������ path �Ĵ�С
//
// Exception:
//      �ú��������ļ�����������Ϸ��Ӧ�ľ���·��
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