#ifndef ____zjy_Game_Log_H_
#define ____zjy_Game_Log_H_

#if _zjy_cs_type == _zjy_server
#define _game_log_dir   "GameLog"
#else
#define _game_log_dir   "GameLog"
#endif

_zjy_space_in

class _game_log
{
private:

    typedef _game_log       log_t;
    typedef unsigned long   att_t;

    enum { _path_len = 1024, _log_len = 1024 };

    static bool _check_directory( const char* dir )
    {
        return (_access_s(dir, 0) == 0 || _mkdir(dir) == 0);
    }

    static bool _output_to_file(_in const char* file, _in const char* text, _in const char* info)
    {
        std::ofstream fout;
        fout.open(file, std::ios::out | std::ios::app);

        if (fout.is_open())
        {
            fout<<info<<' '<<text<<std::endl;
            fout.close();

            return true;
        }

        return false;
    }

    bool _OutputToFile(const char* text) const
    {
        time_t tnow = 0; tm t;
        if (0 > (tnow = time(nullptr)))  return false;
        if (0 != localtime_s(&t, &tnow)) return false;

        char sdate[32] = { 0 };
        if (0 > sprintf_s(sdate, "%04d_%02d_%02d_r%d_t%d"
            , t.tm_year+1900
            , t.tm_mon+1
            , t.tm_mday
            , _key._ikey._roomID
            , _key._ikey._tableID))
            return false;

        char stime[32] = { 0 };
        if (sprintf_s(stime, "[%02d:%02d:%02d]", t.tm_hour, t.tm_min, t.tm_sec) < 0)
            return false;

        char path[_path_len] = { 0 };
        if (sprintf_s(path, "%s\\%s.log", _log_dir, sdate) < 0)
            return false;

        return _output_to_file(path, text, stime);
    }

    bool _OutputToFile(const wchar_t* text) const
    {
        char buf[_log_len] = { 0 };
        if (!_bnb WideStringToMultiString(buf, text)) return false;

        return _OutputToFile(buf);
    }

public:

    _game_log() {
        memset(this, 0, sizeof(_game_log));

        if (_getcwd(_log_dir, _path_len))
        {
            char path[_path_len] = { 0 };

            if (0 < sprintf_s(path, "%s\\%s", _log_dir, _game_log_dir) && _check_directory(path))
                if (0 < sprintf_s(path, "%s\\%s", path, _game_name) && _check_directory(path))
                    strcpy_s(_log_dir, path);
        }
    }

    bool GetLogDir(char* path, int len) const
    {
        strcpy_s(path, len, _log_dir);
    }

    void SetLongKey(param_t lp, param_t wp) { _key._lkey._lparam = lp; _key._lkey._wparam = wp; }
    void SetIntKey(int rid, int tid) { _key._ikey._roomID = rid; _key._ikey._tableID = tid; }

    bool operator () ( const char* format, ... ) const
    {
        char buf[_log_len] = { 0 };

        va_list args;
        va_start(args, format);

        if (_vsnprintf_s(buf, _TRUNCATE, format, args) < 0
            || !!!_OutputToFile(buf))
        {
            va_end(args);
            return false;
        }

        va_end(args);
        return true;
    }

    bool operator () ( const wchar_t* format, ... ) const
    {
        wchar_t buf[_log_len] = { 0 };

        va_list args;
        va_start(args, format);

        if (_vsnwprintf_s(buf, _TRUNCATE, format, args) < 0
            || !!!_OutputToFile(buf))
        {
            va_end(args);
            return false;
        }

        va_end(args);
        return true;
    }
    
private:

    char _log_dir[_path_len];
    att_t _attribute;

    union _key_t {
        struct {  param_t _lparam, _wparam; } _lkey;
        struct { int _roomID, _tableID; } _ikey;
    } _key;

    _game_log(const _game_log&);
    _game_log& operator = (const _game_log&);

};

_zjy_space_out

#endif