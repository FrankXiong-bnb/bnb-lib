#ifdef _console_api

//-----------------------------------------------------------------------------
// 文字前景色
const unsigned short _gc_fgColor[clr_max] = {
    /* fg_white     */  FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
    /* fg_black     */  0,
    /* fg_silver    */  FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
    /* fg_gray      */  FOREGROUND_INTENSITY,
    /* fg_red       */  FOREGROUND_RED | FOREGROUND_INTENSITY,
    /* fg_aqua      */  FOREGROUND_GREEN | FOREGROUND_INTENSITY,
    /* fg_blue      */  FOREGROUND_BLUE | FOREGROUND_INTENSITY,
    /* fg_darkred   */  FOREGROUND_RED,
    /* fg_green     */  FOREGROUND_GREEN,
    /* fg_navy      */  FOREGROUND_BLUE,
    /* fg_Olive     */  FOREGROUND_RED | FOREGROUND_GREEN,
    /* fg_purple    */  FOREGROUND_RED | FOREGROUND_BLUE,
    /* fg_darkcyan  */  FOREGROUND_GREEN | FOREGROUND_BLUE,
    /* fg_yellow    */  FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,
    /* fg_magenta   */  FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
    /* fg_cyan      */  FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY
};

//-----------------------------------------------------------------------------
// 文字背景色
const unsigned short _gc_bgColor[clr_max] = {
    /* bg_black     */  0,
    /* bg_white     */  BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY,
    /* bg_silver    */  BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE,
    /* bg_gray      */  BACKGROUND_INTENSITY,
    /* bg_red       */  BACKGROUND_RED | BACKGROUND_INTENSITY,
    /* bg_aqua      */  BACKGROUND_GREEN | BACKGROUND_INTENSITY,
    /* bg_blue      */  BACKGROUND_BLUE | BACKGROUND_INTENSITY,
    /* bg_darkred   */  BACKGROUND_RED,
    /* bg_green     */  BACKGROUND_GREEN,
    /* bg_navy      */  BACKGROUND_BLUE,
    /* bg_Olive     */  BACKGROUND_RED | BACKGROUND_GREEN,
    /* bg_purple    */  BACKGROUND_RED | BACKGROUND_BLUE,
    /* bg_darkcyan  */  BACKGROUND_GREEN | BACKGROUND_BLUE,
    /* bg_yellow    */  BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY,
    /* bg_magenta   */  BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_INTENSITY,
    /* bg_cyan      */  BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY
};

//=============================================================================
// The implementation of class Console
//=============================================================================
//-----------------------------------------------------------------------------

_console_api bool Console::_output_to_console( _in att_t attr, _in const char* text, const char* info )
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

    if (INVALID_HANDLE_VALUE != handle && NULL != handle)
    {
        CONSOLE_SCREEN_BUFFER_INFO coninfo;

        if (TRUE == GetConsoleScreenBufferInfo(handle, &coninfo))
        {
            if (*info)
                std::cout<<info<<std::endl;

            unsigned short color = _gc_fgColor[attr & fg_mask] | _gc_bgColor[(attr & bg_mask)>>4];
            unsigned short unline = (ca_underline == (attr & ca_underline)) ? COMMON_LVB_UNDERSCORE : 0;

            SetConsoleTextAttribute(handle, color | unline);
            std::cout<<text<<std::endl;
            SetConsoleTextAttribute(handle, coninfo.wAttributes);

            return true;
        }
    }

    return false;
}

//-----------------------------------------------------------------------------

_console_api bool Console::_output_to_console( _in att_t attr, _in const wchar_t* text, const char* info )
{
    char buf[_MaxBufLen] = { 0 };
    if (!WideStringToMultiString(buf, text)) return false;

    return _output_to_console(attr, buf, info);
}

//-----------------------------------------------------------------------------

_console_api Console& Console::GetInstance()
{
    static Console _log_console;
    return _log_console;
}

//-----------------------------------------------------------------------------

_console_api Console::~Console()
{
    FreeConsole();
}

//-----------------------------------------------------------------------------

_console_api Console::Console()
    : _log_base(0)
    , _bconsole(false)
    , _breopen(false)
    , _hfile(nullptr)
{
    InitConsole();
}

//-----------------------------------------------------------------------------

_console_api bool Console::SetTitle( _in const char* title )
{
    return (TRUE == SetConsoleTitleA(title));
}

//-----------------------------------------------------------------------------

_console_api bool Console::SetTitle( _in const wchar_t* title )
{
    return (TRUE == SetConsoleTitleW(title));
}

//-----------------------------------------------------------------------------

_console_api bool Console::ConsoleIsValid()
{
    HANDLE handle = ::GetStdHandle(STD_OUTPUT_HANDLE);

    return (INVALID_HANDLE_VALUE != handle && NULL != handle);
}

//-----------------------------------------------------------------------------

_console_api _result_t Console::Command( const char* cmd )
{
    return system(cmd);
}

//-----------------------------------------------------------------------------

_console_api _result_t Console::Command( const wchar_t* cmd )
{
    return _wsystem(cmd);
}

//-----------------------------------------------------------------------------

_console_api void Console::ClearConsole()
{
    Command("cls");
}

//-----------------------------------------------------------------------------

_console_api bool Console::PrintError()
{
    unsigned long err = GetLastError();

    char buf[_MaxBufLen] = { 0 };
    if (0 != strerror_s(buf, err))
        return false;

    char text[_MaxLogLen] = { 0 };
    if (0 > sprintf_s(text, "[error code: %lu] %s", err, buf))
        return false;

    str_t strout;
    _get_out_info(out_pid | out_time | out_tick | out_tid, strout);

    return _output_to_console(fg_red | ca_underline, text, strout.c_str());
}

//-----------------------------------------------------------------------------

_console_api bool Console::PrintError( _in const char* file )
{
    unsigned long err = GetLastError();

    char buf[_MaxBufLen] = { 0 };
    if (0 != strerror_s(buf, err))
        return false;

    char text[_MaxLogLen] = { 0 };
    if (0 > sprintf_s(text, "[error code: %lu] %s", err, buf))
        return false;

    str_t strout;
    _get_out_info(out_pid | out_time | out_tick | out_tid, strout);

    _output_to_file(file, text, strout.c_str());

    return _output_to_console(fg_red | ca_underline, text, strout.c_str());
}

//-----------------------------------------------------------------------------

_console_api bool Console::PrintError( _in const wchar_t* file )
{
    unsigned long err = GetLastError();

    char buf[_MaxBufLen] = { 0 };
    if (0 != strerror_s(buf, err))
        return false;

    char text[_MaxLogLen] = { 0 };
    if (0 > sprintf_s(text, "[error code: %lu] %s", err, buf))
        return false;

    str_t strout;
    _get_out_info(out_pid | out_time | out_tick | out_tid, strout);

    if (WideStringToMultiString(buf, file))
        _output_to_file(buf, text, strout.c_str());

    return _output_to_console(fg_red | ca_underline, text, strout.c_str());
}

//-----------------------------------------------------------------------------

_console_api bool Console::InitConsole()
{
    if ( !!!_bconsole )
    {
        if(TRUE == ::AllocConsole())
        {
            _bconsole = true;

            if ( !!!_breopen )
            {
                if (0 == ::freopen_s(&_hfile, "CONOUT$", "w+t", stdout))
                {
                    _breopen = true;

                    return true;
                }
            }
        }
    }

    return false;
}

//-----------------------------------------------------------------------------

_console_api void Console::FreeConsole()
{
    if (_bconsole)
    {
        if (_breopen)
        {
            ::fclose(_hfile);
            _hfile = nullptr;
            _breopen = false;
        }

        ::FreeConsole();
        _bconsole = false;
    }
}

//-----------------------------------------------------------------------------

_console_api bool Console::operator()( _in const char* format, _in ... ) const
{
    char buf[_MaxLogLen] = { 0 };
    _make_buf_with_format(buf, _MaxLogLen, format)

    str_t strout;
    _get_out_info(_attribute, strout);

    return _output_to_console(_attribute, buf, strout.c_str());
}

//-----------------------------------------------------------------------------

_console_api bool Console::operator()( _in const wchar_t* format, _in ... ) const
{
    wchar_t buf[_MaxLogLen] = { 0 };
    _make_wbuf_with_format(buf, _MaxLogLen, format)

    str_t strout;
    _get_out_info(_attribute, strout);

    return _output_to_console(_attribute, buf, strout.c_str());
}

//-----------------------------------------------------------------------------

_console_api bool Console::operator()( _in att_t attr, _in const char* format, _in ... ) const
{
    char buf[_MaxLogLen] = { 0 };
    _make_buf_with_format(buf, _MaxLogLen, format)

    str_t strout;
    _get_out_info(attr, strout);

    return _output_to_console(attr, buf, strout.c_str());
}

//-----------------------------------------------------------------------------

_console_api bool Console::operator()( _in att_t attr, _in const wchar_t* format, _in ... ) const
{
    wchar_t buf[_MaxLogLen] = { 0 };
    _make_wbuf_with_format(buf, _MaxLogLen, format)

    str_t strout;
    _get_out_info(attr, strout);

    return _output_to_console(attr, buf, strout.c_str());
}

//-----------------------------------------------------------------------------

_console_api bool Console::OutputText( _in const char* file, _in const char* format, _in ... ) const
{
    char buf[_MaxLogLen] = { 0 };
    _make_buf_with_format(buf, _MaxLogLen, format)

    str_t strout;
    _get_out_info(_attribute, strout);

    _output_to_file(file, buf, strout.c_str());

    return _output_to_console(_attribute, buf, strout.c_str());
}

//-----------------------------------------------------------------------------

_console_api bool Console::OutputText( _in const wchar_t* file, _in const wchar_t* format, _in ... ) const
{
    wchar_t buf[_MaxLogLen] = { 0 };
    _make_wbuf_with_format(buf, _MaxLogLen, format)

    str_t strout;
    _get_out_info(_attribute, strout);

    _output_to_file(file, buf, strout.c_str());

    return _output_to_console(_attribute, buf, strout.c_str());
}

//-----------------------------------------------------------------------------

_console_api bool Console::OutputError( _in const char* format, _in ... ) const
{
    char buf[_MaxLogLen] = { 0 };
    _make_buf_with_format(buf, _MaxLogLen, format)

    str_t strout;
    _get_out_info(_attribute, strout);

    str_t text("Error: ");
    text += buf;

    return _output_to_console(fg_red, text.c_str(), strout.c_str());
}

//-----------------------------------------------------------------------------

_console_api bool Console::OutputError( _in const wchar_t* format, _in ... ) const
{
    wchar_t buf[_MaxLogLen] = { 0 };
    _make_wbuf_with_format(buf, _MaxLogLen, format)

    str_t strout;
    _get_out_info(_attribute, strout);

    wstr_t text(L"Error: ");
    text += buf;

    return _output_to_console(fg_red, text.c_str(), strout.c_str());
}

//-----------------------------------------------------------------------------

_console_api bool Console::OutputWarning( _in const char* format, _in ... ) const
{
    char buf[_MaxLogLen] = { 0 };
    _make_buf_with_format(buf, _MaxLogLen, format)

    str_t strout;
    _get_out_info(_attribute, strout);

    str_t text("Warning: ");
    text += buf;

    return _output_to_console(fg_yellow, text.c_str(), strout.c_str());
}

//-----------------------------------------------------------------------------

_console_api bool Console::OutputWarning( _in const wchar_t* format, _in ... ) const
{
    wchar_t buf[_MaxLogLen] = { 0 };
    _make_wbuf_with_format(buf, _MaxLogLen, format)

    str_t strout;
    _get_out_info(_attribute, strout);

    wstr_t text(L"Warning: ");
    text += buf;

    return _output_to_console(fg_yellow, text.c_str(), strout.c_str());
}

//-----------------------------------------------------------------------------

_console_api bool Console::OutputComment( _in const char* format, _in ... ) const
{
    char buf[_MaxLogLen] = { 0 };
    _make_buf_with_format(buf, _MaxLogLen, format)

    str_t strout;
    _get_out_info(_attribute, strout);

    str_t text("Comment: ");
    text += buf;

    return _output_to_console(fg_green, text.c_str(), strout.c_str());
}

//-----------------------------------------------------------------------------

_console_api bool Console::OutputComment( _in const wchar_t* format, _in ... ) const
{
    wchar_t buf[_MaxLogLen] = { 0 };
    _make_wbuf_with_format(buf, _MaxLogLen, format)

    str_t strout;
    _get_out_info(_attribute, strout);

    wstr_t text(L"Comment: ");
    text += buf;

    return _output_to_console(fg_green, text.c_str(), strout.c_str());
}

//=============================================================================

static inline bool _MakeOutputTime(_out std::string& str)
{
    time_t tnow = 0; tm t;
    if (0 > (tnow = time(nullptr)))  return false;
    if (0 != localtime_s(&t, &tnow)) return false;

    char buf[64] = { 0 };
    if(0 > sprintf_s(buf
        , "[%04d-%02d-%02d %02d:%02d:%02d] "
        , t.tm_year+1900
        , t.tm_mon+1
        , t.tm_mday
        , t.tm_hour
        , t.tm_min
        , t.tm_sec)) return false;

    str = buf;

    return true;
}

template<typename _Ty>
static inline bool _OutputToConsoleByTime(const char* format, const _Ty& data)
{
    std::string str;
    if (!_MakeOutputTime(str)) return false;

    if (format) str += format;

    return _ConsoleInst(str.c_str(), data);
}

static inline bool _OutputToConsoleByTime(const char* format, const wchar_t* data)
{
    std::string str;
    if (!_MakeOutputTime(str)) return false;

    if (format) str += format;

    char text[_log_base::_MaxLogLen] = { 0 };
    WideStringToMultiString(text, data);

    return _ConsoleInst(str.c_str(), text);
}

//=============================================================================
// The implementation of class SingleLog
//=============================================================================
//-----------------------------------------------------------------------------

_console_api void SingleLog::_make_file_name( _out char* buf, _in _size_t size )
{
    if(0 > sprintf_s(buf, size, "%d%s", GetCurrentProcessId(), _log_def_suffix))
        strcpy_s(buf, size, _log_def_name);
}

//-----------------------------------------------------------------------------

_console_api SingleLog::SingleLog( _in long str )
{
    char buf[_log_base::_MaxBufLen] = { 0 };
    _make_file_name(buf, _log_base::_MaxBufLen);

    // _ConsoleInst.OutputText(buf, "[tick:%08lx tid:%08lx]<-> %ld", ::clock(), ::GetCurrentThreadId(), str);
    _OutputToConsoleByTime("<-> %ld", str);
}

//-----------------------------------------------------------------------------

_console_api SingleLog::SingleLog( _in double str )
{
    char buf[_log_base::_MaxBufLen] = { 0 };
    _make_file_name(buf, _log_base::_MaxBufLen);

    // _ConsoleInst.OutputText(buf, "[tick:%08lx tid:%08lx]<-> %lf", ::clock(), ::GetCurrentThreadId(), str);
    _OutputToConsoleByTime("<-> %lf", str);
}

//-----------------------------------------------------------------------------

_console_api SingleLog::SingleLog( _in const char* str )
{
    char buf[_log_base::_MaxBufLen] = { 0 };
    _make_file_name(buf, _log_base::_MaxBufLen);

    // _ConsoleInst.OutputText(buf, "[tick:%08lx tid:%08lx]<-> %s", ::clock(), ::GetCurrentThreadId(), str);
    _OutputToConsoleByTime("<-> %s", str);
}

//-----------------------------------------------------------------------------

_console_api SingleLog::SingleLog( _in const wchar_t* str )
{
    char buf[_log_base::_MaxBufLen] = { 0 };
    _make_file_name(buf, _log_base::_MaxBufLen);

    // char text[_log_base::_MaxLogLen] = { 0 };
    // WideStringToMultiString(text, str);

    // _ConsoleInst.OutputText(buf, "[tick:%08lx tid:%08lx]<-> %s", ::clock(), ::GetCurrentThreadId(), text);
    _OutputToConsoleByTime("<-> %s", str);
}

//=============================================================================
// The implementation of class DoubleLog
//=============================================================================
//-----------------------------------------------------------------------------

_console_api void DoubleLog::_make_file_name()
{
    char buf[_log_base::_MaxBufLen] = { 0 };
    if(0 > sprintf_s(buf, "%d%s", GetCurrentProcessId(), _log_def_suffix))
        _file = _log_def_name;
    else
        _file = buf;
}

//-----------------------------------------------------------------------------

_console_api DoubleLog::~DoubleLog()
{
    // _ConsoleInst.OutputText(_file.c_str(), "[tick:%08lx tid:%08lx]<-- %s", ::clock(), ::GetCurrentThreadId(), _str.c_str());
    _OutputToConsoleByTime("<-- %s", _str.c_str());
}

//-----------------------------------------------------------------------------

_console_api DoubleLog::DoubleLog( _in long str )
{
    _make_file_name();

    char buf[_log_base::_MaxBufLen] = { 0 };
    if(0 > sprintf_s(buf, "%ld", str))
        _str = buf;

    // _ConsoleInst.OutputText(_file.c_str(), "[tick:%08lx tid:%08lx]--> %s", ::clock(), ::GetCurrentThreadId(), _str.c_str());
    _OutputToConsoleByTime("--> %s", _str.c_str());
}

//-----------------------------------------------------------------------------

_console_api DoubleLog::DoubleLog( _in double str )
{
    _make_file_name();

    char buf[_log_base::_MaxBufLen] = { 0 };
    if(0 > sprintf_s(buf, "%lf", str))
        _str = buf;

    // _ConsoleInst.OutputText(_file.c_str(), "[tick:%08lx tid:%08lx]--> %s", ::clock(), ::GetCurrentThreadId(), _str.c_str());

    _OutputToConsoleByTime("--> %s", _str.c_str());
}

//-----------------------------------------------------------------------------

_console_api DoubleLog::DoubleLog( _in const char* str ) : _str(str)
{
    _make_file_name();

    // _ConsoleInst.OutputText(_file.c_str(), "[tick:%08lx tid:%08lx]--> %s", ::clock(), ::GetCurrentThreadId(), _str.c_str());
    _OutputToConsoleByTime("--> %s", _str.c_str());
}

//-----------------------------------------------------------------------------

_console_api DoubleLog::DoubleLog( _in const wchar_t* str )
{
    _make_file_name();

    char buf[_log_base::_MaxLogLen] = { 0 };
    if (WideStringToMultiString(buf, str))
        _str = buf;

    // _ConsoleInst.OutputText(_file.c_str(), "[tick:%08lx tid:%08lx]--> %s", ::clock(), ::GetCurrentThreadId(), _str.c_str());
    _OutputToConsoleByTime("--> %s", _str.c_str());
}

#endif