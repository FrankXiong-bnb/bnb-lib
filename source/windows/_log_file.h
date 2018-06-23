//=============================================================================
// log standard header
//  														2014-8 by Frank
//=============================================================================
#ifndef ____bnb_Log_File_H_
#define ____bnb_Log_File_H_

_bnb_space_in

// 文件名命名方式
enum _filename_e {
    with_default        = 0x00000000,   // 按默认文件名
    with_date           = 0x00010000,   // 按日期
    with_hour           = 0x00020000,   // 按小时
    with_minitue        = 0x00030000,   // 按分钟
    with_second         = 0x00040000,   // 按秒数
    with_reserve1       = 0x000f0000,   // 保留

    with_thread         = 0x00100000,   // 按线程
    with_process        = 0x00200000,   // 按进程
    with_reserve2       = 0x00f00000,   // 保留

    with_time_mask      = 0x000f0000,
    with_attr_mask      = 0x00f00000,
    filename_mask       = 0x00ff0000
};

class LogFile : public _log_base
{
public:

    // 设置日志文件默认存放目录
    void SetLogDirectory(_in const char* dir);
    void SetLogDirectory(_in const wchar_t* dir);

    // 设置日志文件默认文件名
    void SetLogFilename(_in const char* file);
    void SetLogFilename(_in const wchar_t* file);

    // 获取默认日志存放目录和文件名
    char* GetLogDirectory(_out char* buf, _in _size_t size) const;
    const char* GetLogFilename() const;

    // 使用默认设置输出日志
    bool operator()(_in const char* format, _in ...) const;
    bool operator()(_in const wchar_t* format, _in ...) const;

    // 指定设置属性输出日志
    bool operator()(_in att_t attr, _in const char* format, _in ...) const;
    bool operator()(_in att_t attr, _in const wchar_t* format, _in ...) const;

    // 输出日志到指定文件
    bool OutputText(_in const char* file, _in const char* format, _in ...) const;
    bool OutputText(_in const wchar_t* file, _in const wchar_t* format, _in ...) const;

public:

    // 校验文件夹，如果文件夹不存在，则创建文件夹，如果创建也不成功，返回失败。
    static bool _check_directory(_in const char* dir);
    // 根据属性生成文件名：attr 指定属性。
    static bool _make_filename(_out str_t& strfile, _in att_t attr);

protected:

    // 根据设置属性获取文件名
    bool _get_filename(_out str_t& strfile, _in att_t attr) const;

public:

    LogFile(_in att_t attr = 0);
    LogFile(_in const char* dir, _in att_t attr = 0);
    LogFile(_in const wchar_t* dir, _in att_t attr = 0);
    LogFile(_in const char* dir, _in const char* file, _in att_t attr = 0);
    LogFile(_in const wchar_t* dir, _in const wchar_t* file, _in att_t attr = 0);

private:

                str_t   _log_dir;       // 日志目录
                str_t   _log_name;      // 日志文件名

    static const char*  _LogSuffix;     // 默认日志后缀名
    static const char*  _DefLogDir;     // 默认日志文件夹
    static const char*  _DefLogName;    // 默认日志文件名

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