//=============================================================================
// log base
//  														2014-8 by Frank
//=============================================================================
#ifndef ____bnb_Log_Base_H_
#define ____bnb_Log_Base_H_

_bnb_space_in

enum _out_info_e {
        out_none            = 0x00000000,   // 不输出
        out_time            = 0x01000000,   // 输出日期
        out_tick            = 0x02000000,   // 输出tick
        out_tid             = 0x04000000,   // 输出线程ID
        out_pid             = 0x08000000,   // 输出进程ID
        out_mask            = 0x0f000000
};

//-----------------------------------------------------------------------------
// 将变参格式转化到buf中
#define _make_buf_with_format(_buf, _bufsize, _format) {                \
va_list args;                                                           \
va_start(args, _format);                                                \
int ret = _vsnprintf_s(_buf, _bufsize, _TRUNCATE, _format, args);       \
va_end(args);                                                           \
if (ret < 0) return false; }

#define _make_wbuf_with_format(_buf, _bufsize, _format) {               \
va_list args;                                                           \
va_start(args, _format);                                                \
int ret = _vsnwprintf_s(_buf, _MaxLogLen, _TRUNCATE, _format, args);    \
va_end(args);                                                           \
if (ret < 0) return false; }

class _log_base
{
public:

    enum {
        _MaxLogLen = 0x0400,            // 单条日志最大字符数
        _MaxBufLen = 0x0400             // 缓冲区最大长度
    };

    typedef unsigned long   att_t;
    typedef std::string     str_t;
    typedef std::wstring    wstr_t;

public:

    // 修改和访问设置属性
    void  SetAttribute(_in att_t attr) { _attribute = attr; }
    att_t GetAttribute() const { return _attribute; }

protected:

    // 输出日志和附加信息到指定文件
    static bool _output_to_file(_in const char* file, _in const char* text, _in const char* info)
    {
        std::ofstream fout;
        fout.open(file, std::ios::out | std::ios::app);

        if (fout.is_open())
        {
            if (*info) fout<<info<<std::endl;
            
            fout<<text<<std::endl;
            fout.close();

            return true;
        }

        return false;
    }

    static bool _output_to_file(_in const wchar_t* file, _in const wchar_t* text, _in const char* info)
    {
        char path[_MaxBufLen] = { 0 };
        if (!WideStringToMultiString(path, file)) return false;

        char buf[_MaxBufLen] = { 0 };
        if (!WideStringToMultiString(buf, text)) return false;

        return _output_to_file(path, buf, info);
    }

    static bool _output_to_file(_in const char* file, _in const wchar_t* text, _in const char* info)
    {
        char buf[_MaxBufLen] = { 0 };
        if (!WideStringToMultiString(buf, text)) return false;

        return _output_to_file(file, buf, info);
    }

    // 根据属性生成日志附加输出信息
    static bool _get_out_info(_in att_t attr, _out str_t& info)
    {
        if (out_time == (out_time & attr))
        {
            time_t tnow = 0; tm t;
            if (0 > (tnow = time(nullptr)))  return false;
            if (0 != localtime_s(&t, &tnow)) return false;

            char buf[64] = { 0 };
            if(0 > sprintf_s(buf
                , " %04d-%02d-%02d %02d:%02d:%02d"
                , t.tm_year+1900
                , t.tm_mon+1
                , t.tm_mday
                , t.tm_hour
                , t.tm_min
                , t.tm_sec)) return false;

            info += buf;
        }

        if (out_tick == (out_tick & attr))
        {
            char buf[64] = { 0 };
            if(0 > sprintf_s(buf, " tick:%d", clock())) return false;

            info += buf;
        }

        if (out_tid == (out_tid & attr))
        {
            char buf[64] = { 0 };
            if(0 > sprintf_s(buf, " tid:%d", GetCurrentThreadId())) return false;

            info += buf;
        }

        if (out_pid == (out_pid & attr))
        {
            char buf[64] = { 0 };
            if(0 > sprintf_s(buf, " pid:%d", GetCurrentProcessId())) return false;

            info += buf;
        }

        if (info.size() > 0)
            info = '[' + info + ' ' + ']';

        return true;
    }

public:

    virtual ~_log_base() = 0 { }

protected:

    explicit _log_base(_in att_t attr = 0) : _attribute(attr) { }

private:

    _log_base(const _log_base&);
    _log_base& operator=(const _log_base&);

protected:

    att_t   _attribute;                 // 日志设置属性

};  // class _log_base

//-----------------------------------------------------------------------------
        
#define _log_def_dir        "_Log/"
#define _log_def_name       "_log.log"
#define _log_def_suffix     ".log"

_bnb_space_out

#endif