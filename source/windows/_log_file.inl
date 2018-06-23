#ifdef _log_api

//=============================================================================
// The implementation of class LogFile
//=============================================================================
//-----------------------------------------------------------------------------

__declspec(selectany) const char* LogFile::_DefLogDir  = _log_def_dir;
__declspec(selectany) const char* LogFile::_DefLogName = _log_def_name;
__declspec(selectany) const char* LogFile::_LogSuffix  = _log_def_suffix;

//-----------------------------------------------------------------------------

_log_api bool LogFile::_make_filename( _out str_t& strfile, _in att_t attr )
{
    time_t tnow = 0;
    tm t;

    if ((with_time_mask & attr) > 0)
    {
        if (0 > (tnow = time(nullptr)))
            return false;

        if (0 != localtime_s(&t, &tnow))
            return false;
    }

    char name[256] = { 0 };

    switch (attr & with_time_mask)
    {
    case with_date:
        sprintf_s(name, "%04d-%02d-%02d", t.tm_year+1900, t.tm_mon+1, t.tm_mday);
        break;
    case with_hour:
        sprintf_s(name, "%04d-%02d-%02d %02d", t.tm_year+1900, t.tm_mon+1, t.tm_mday, t.tm_hour);
        break;
    case with_minitue:
        sprintf_s(name, "%04d-%02d-%02d %02d-%02d", t.tm_year+1900, t.tm_mon+1, t.tm_mday, t.tm_hour, t.tm_min);
        break;
    case with_second:
        sprintf_s(name, "%04d-%02d-%02d %02d-%02d-%02d", t.tm_year+1900, t.tm_mon+1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
        break;
    default:
        break;
    }

    strfile = name;

    name[0] = '\0';
    switch (with_attr_mask & attr)
    {
    case with_thread:
        sprintf_s(name, "%d", GetCurrentThreadId());
        break;
    case with_process:
        sprintf_s(name, "%d", GetCurrentProcessId());
        break;
    default:
        break;
    }

    if (strfile.size() > 0 && strlen(name) > 0)
        strfile += ' ';

    strfile += name;

    if (strfile.size() > 0)
        strfile = '[' + strfile + ']';

    return true;
}

//-----------------------------------------------------------------------------

_log_api bool LogFile::_get_filename( _out str_t& strfile, _in att_t attr ) const
{
    if (with_default == (attr & filename_mask))
    {
        strfile = _log_name;
        return true;
    }

    if (_make_filename(strfile, attr))
    {
        if (strfile.size() == 0)
            strfile = "_log";

        if (_check_directory(_log_dir.c_str()))
        {
            if (_log_dir.at(_log_dir.size() - 1) != '\\' || _log_dir.at(_log_dir.size() - 1) != '/')
                strfile = '\\' + strfile;

            strfile = _log_dir + strfile;
            strfile += _LogSuffix;

            return true;
        }
    }    

    return false;
}

//-----------------------------------------------------------------------------

_log_api bool LogFile::_check_directory( _in const char* dir )
{
    return (_access_s(dir, 0) == 0 || _mkdir(dir) == 0);
}

//-----------------------------------------------------------------------------

_log_api LogFile::LogFile( _in att_t attr /*= 0*/ )
    : _log_base(attr)
    , _log_dir(_DefLogDir)
    , _log_name(_DefLogName)
{
    _check_directory(_log_dir.c_str());
}


//-----------------------------------------------------------------------------

_log_api LogFile::LogFile( _in const char* dir, _in att_t attr /*= 0*/ )
    : _log_base(attr)
    , _log_dir(dir)
    , _log_name(_DefLogName)
{
    if (!!!_check_directory(_log_dir.c_str()))
        if (_check_directory(_DefLogDir))
            _log_dir = _DefLogDir;
}

//-----------------------------------------------------------------------------

_log_api LogFile::LogFile( _in const wchar_t* dir, _in att_t attr /*= 0*/ )
    : _log_base(attr)
    , _log_name(_DefLogName)
{
    char buf[_MaxBufLen] = { 0 };

    if(WideStringToMultiString(buf, dir) && _check_directory(buf))
        _log_dir = buf;
    else
        if (_check_directory(_DefLogDir))
            _log_dir = _DefLogDir;
}

//-----------------------------------------------------------------------------

_log_api LogFile::LogFile( _in const char* dir, _in const char* file, _in att_t attr /*= 0*/ )
    : _log_base(attr)
    , _log_dir(dir)
    , _log_name(file)
{
    if (!!!_check_directory(_log_dir.c_str()))
        if (_check_directory(_DefLogDir))
            _log_dir = _DefLogDir;
}

//-----------------------------------------------------------------------------

_log_api LogFile::LogFile( _in const wchar_t* dir, _in const wchar_t* file, _in att_t attr /*= 0*/ )
    : _log_base(attr)
{
    char buf[_MaxBufLen] = { 0 };

    if(WideStringToMultiString(buf, dir) && _check_directory(buf))
        _log_dir = buf;
    else
        if (_check_directory(_DefLogDir))
            _log_dir = _DefLogDir;

    if(WideStringToMultiString(buf, file))
        _log_name = buf;
    else
        _log_name = _DefLogName;
}

//-----------------------------------------------------------------------------

_log_api void LogFile::SetLogDirectory( _in const char* dir )
{
    if (_check_directory(dir))
        _log_dir = dir;
}

//-----------------------------------------------------------------------------

_log_api void LogFile::SetLogDirectory( _in const wchar_t* dir )
{
    char buf[_MaxBufLen] = { 0 };

    if(WideStringToMultiString(buf, dir))
        SetLogDirectory(buf);
}

//-----------------------------------------------------------------------------

_log_api void LogFile::SetLogFilename( _in const char* file )
{
    _log_name = file;
}

//-----------------------------------------------------------------------------

_log_api void LogFile::SetLogFilename( _in const wchar_t* file )
{
    char buf[_MaxBufLen] = { 0 };

    if(WideStringToMultiString(buf, file))
        _log_name = buf;
}

//-----------------------------------------------------------------------------

_log_api char* LogFile::GetLogDirectory( _out char* buf, _in _size_t size ) const
{
    if (_check_directory(_log_dir.c_str()))
        return _fullpath(buf, _log_dir.c_str(), size);

    return nullptr;
}

//-----------------------------------------------------------------------------

_log_api const char* LogFile::GetLogFilename() const
{
    return _log_name.c_str();
}

//-----------------------------------------------------------------------------

_log_api bool LogFile::operator()( _in const char* format, _in ... ) const
{
    char buf[_MaxLogLen] = { 0 };
    _make_buf_with_format(buf, _MaxLogLen, format)

    str_t strout;
    _get_out_info(_attribute, strout);

    str_t strfile;
    if (_get_filename(strfile, _attribute))
        return _output_to_file(strfile.c_str(), buf, strout.c_str());

    return false;
}

//-----------------------------------------------------------------------------

_log_api bool LogFile::operator()( _in const wchar_t* format, _in ... ) const
{
    wchar_t buf[_MaxLogLen] = { 0 };
    _make_wbuf_with_format(buf, _MaxLogLen, format)

    str_t strout;
    _get_out_info(_attribute, strout);

    str_t strfile;
    if (_get_filename(strfile, _attribute))
        return _output_to_file(strfile.c_str(), buf, strout.c_str());

    return false;
}

//-----------------------------------------------------------------------------

_log_api bool LogFile::operator()( _in att_t attr, _in const char* format, _in ... ) const
{
    char buf[_MaxLogLen] = { 0 };
    _make_buf_with_format(buf, _MaxLogLen, format)

    str_t strout;
    _get_out_info(attr, strout);

    str_t strfile;
    if (_get_filename(strfile, attr))
        _output_to_file(strfile.c_str(), buf, strout.c_str());

    return false;
}

//-----------------------------------------------------------------------------

_log_api bool LogFile::operator()( _in att_t attr, _in const wchar_t* format, _in ... ) const
{
    wchar_t buf[_MaxLogLen] = { 0 };
    _make_wbuf_with_format(buf, _MaxLogLen, format)

    str_t strout;
    _get_out_info(attr, strout);

    str_t strfile;
    if (_get_filename(strfile, attr))
        _output_to_file(strfile.c_str(), buf, strout.c_str());

    return false;
}

//-----------------------------------------------------------------------------

_log_api bool LogFile::OutputText( _in const char* file, _in const char* format, _in ... ) const
{
    char buf[_MaxLogLen] = { 0 };
    _make_buf_with_format(buf, _MaxLogLen, format)

    str_t strout;
    _get_out_info(_attribute, strout);

    return _output_to_file(file, buf, strout.c_str()); 
}

//-----------------------------------------------------------------------------

_log_api bool LogFile::OutputText( _in const wchar_t* file, _in const wchar_t* format, _in ... ) const
{
    wchar_t buf[_MaxLogLen] = { 0 };
    _make_wbuf_with_format(buf, _MaxLogLen, format)

    str_t strout;
    _get_out_info(_attribute, strout);

    return _output_to_file(file, buf, strout.c_str());
}

#endif