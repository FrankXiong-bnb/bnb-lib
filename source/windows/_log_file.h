//=============================================================================
// log standard header
//  														2014-8 by Frank
//=============================================================================
#ifndef ____bnb_Log_File_H_
#define ____bnb_Log_File_H_

_bnb_space_in

// �ļ���������ʽ
enum _filename_e {
    with_default        = 0x00000000,   // ��Ĭ���ļ���
    with_date           = 0x00010000,   // ������
    with_hour           = 0x00020000,   // ��Сʱ
    with_minitue        = 0x00030000,   // ������
    with_second         = 0x00040000,   // ������
    with_reserve1       = 0x000f0000,   // ����

    with_thread         = 0x00100000,   // ���߳�
    with_process        = 0x00200000,   // ������
    with_reserve2       = 0x00f00000,   // ����

    with_time_mask      = 0x000f0000,
    with_attr_mask      = 0x00f00000,
    filename_mask       = 0x00ff0000
};

class LogFile : public _log_base
{
public:

    // ������־�ļ�Ĭ�ϴ��Ŀ¼
    void SetLogDirectory(_in const char* dir);
    void SetLogDirectory(_in const wchar_t* dir);

    // ������־�ļ�Ĭ���ļ���
    void SetLogFilename(_in const char* file);
    void SetLogFilename(_in const wchar_t* file);

    // ��ȡĬ����־���Ŀ¼���ļ���
    char* GetLogDirectory(_out char* buf, _in _size_t size) const;
    const char* GetLogFilename() const;

    // ʹ��Ĭ�����������־
    bool operator()(_in const char* format, _in ...) const;
    bool operator()(_in const wchar_t* format, _in ...) const;

    // ָ���������������־
    bool operator()(_in att_t attr, _in const char* format, _in ...) const;
    bool operator()(_in att_t attr, _in const wchar_t* format, _in ...) const;

    // �����־��ָ���ļ�
    bool OutputText(_in const char* file, _in const char* format, _in ...) const;
    bool OutputText(_in const wchar_t* file, _in const wchar_t* format, _in ...) const;

public:

    // У���ļ��У�����ļ��в����ڣ��򴴽��ļ��У��������Ҳ���ɹ�������ʧ�ܡ�
    static bool _check_directory(_in const char* dir);
    // �������������ļ�����attr ָ�����ԡ�
    static bool _make_filename(_out str_t& strfile, _in att_t attr);

protected:

    // �����������Ի�ȡ�ļ���
    bool _get_filename(_out str_t& strfile, _in att_t attr) const;

public:

    LogFile(_in att_t attr = 0);
    LogFile(_in const char* dir, _in att_t attr = 0);
    LogFile(_in const wchar_t* dir, _in att_t attr = 0);
    LogFile(_in const char* dir, _in const char* file, _in att_t attr = 0);
    LogFile(_in const wchar_t* dir, _in const wchar_t* file, _in att_t attr = 0);

private:

                str_t   _log_dir;       // ��־Ŀ¼
                str_t   _log_name;      // ��־�ļ���

    static const char*  _LogSuffix;     // Ĭ����־��׺��
    static const char*  _DefLogDir;     // Ĭ����־�ļ���
    static const char*  _DefLogName;    // Ĭ����־�ļ���

};  // class LogFile

typedef LogFile Log;
typedef LogFile LogF;

__declspec(selectany) Log _g_logfile_nemo_obj;

#define _outputfile _bnb _g_logfile_nemo_obj.OutputText

#ifdef  _bnb_log
#define _outputlog  _bnb _g_logfile_nemo_obj
#else
#define _outputlog  _bnb_null_statement
#endif

#ifndef _log_api
#define _log_api    _declare_inline
#include "../windows/_log_file.inl"
#undef  _log_api
#endif  // #ifndef _log_api

_bnb_space_out

#endif