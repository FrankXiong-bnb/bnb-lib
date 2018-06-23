//=============================================================================
// console
//  														2014-8 by Frank
//=============================================================================
#ifndef ____bnb_Console_H_
#define ____bnb_Console_H_

_bnb_space_in

// 文字颜色
enum _console_color_e
{
    fg_white,           // 白色   rgb(0xff, 0xff, 0xff)
    fg_black,           // 黑色   rgb(0x00, 0x00, 0x00)
    fg_silver,          // 银色   rgb(0xc0, 0xc0, 0xc0)
    fg_gray,            // 灰色   rgb(0x80, 0x80, 0x80)
    fg_red,             // 红色   rgb(0xff, 0x00, 0x00)
    fg_aqua,            // 浅绿   rgb(0x00, 0xff, 0x00)
    fg_blue,            // 蓝色   rgb(0x00, 0x00, 0xff)
    fg_darkred,         // 深红色 rgb(0x80, 0x00, 0x00)
    fg_green,           // 绿色   rgb(0x00, 0x80, 0x00)
    fg_navy,            // 海军蓝 rgb(0x00, 0x00, 0x80)
    fg_Olive,           // 橄榄色 rgb(0x80, 0x80, 0x00)
    fg_purple,          // 紫色   rgb(0x80, 0x00, 0x80)
    fg_darkcyan,        // 深青色 rgb(0x00, 0x80, 0x80)
    fg_yellow,          // 黄色   rgb(0xff, 0xff, 0x00)
    fg_magenta,         // 洋红   rgb(0xff, 0x00, 0xff)
    fg_cyan,            // 青色   rgb(0x00, 0xff, 0xff)

    clr_max,

    bg_black            = 0,
    bg_white            = 1<<4,
    bg_silver           = fg_silver<<4,
    bg_gray             = fg_gray<<4,
    bg_red              = fg_red<<4,
    bg_aqua             = fg_aqua<<4,
    bg_blue             = fg_blue<<4,
    bg_darkred          = fg_darkred<<4,
    bg_green            = fg_green<<4,
    bg_navy             = fg_navy<<4,
    bg_Olive            = fg_Olive<<4,
    bg_purple           = fg_purple<<4,
    bg_darkcyan         = fg_darkcyan<<4,
    bg_yellow           = fg_yellow<<4,
    bg_magenta          = fg_magenta<<4,
    bg_cyan             = fg_cyan<<4,

    fg_mask             = 0x0000000f,
    bg_mask             = 0x000000f0,
    clr_mask            = 0x000000ff
};

enum _console_attribute_e
{
    ca_underline        = 0x00000100,   // 下划线
    ca_reserve          = 0x00000f00,   // 保留

    console_mask        = 0x0000ff00
};

//=============================================================================
// class Console
//=============================================================================
class Console : public _log_base
{
public:

    // 获取日志对象实例
    static Console& GetInstance();

    // 设置控制台标题
    static bool SetTitle(_in const char* title);
    static bool SetTitle(_in const wchar_t* title);

    // 清空控制台
    static void ClearConsole();

    // 判定控制台是否有效
    static bool ConsoleIsValid();

    // 执行DOS命令
    static _result_t Command(_in const char* cmd);
    static _result_t Command(_in const wchar_t* cmd);

    static bool PrintError();
    static bool PrintError(_in const char* file);
    static bool PrintError(_in const wchar_t* file);

    // 初始化控制台
    bool InitConsole();

    // 释放控制台
    void FreeConsole();

    // 使用默认设置输出日志
    bool operator()(_in const char* format, _in ...) const;
    bool operator()(_in const wchar_t* format, _in ...) const;

    // 指定设置属性输出日志
    bool operator()(_in att_t attr, _in const char* format, _in ...) const;
    bool operator()(_in att_t attr, _in const wchar_t* format, _in ...) const;

    // 使用默认设置输出日志
    bool OutputText(_in const char* file, _in const char* format, _in ...) const;
    bool OutputText(_in const wchar_t* file, _in const wchar_t* format, _in ...) const;

    // 输出错误信息到控制台
    bool OutputError(_in const char* format, _in ...) const;
    bool OutputError(_in const wchar_t* format, _in ...) const;

    // 输出警告信息到控制台
    bool OutputWarning(_in const char* format, _in ...) const;
    bool OutputWarning(_in const wchar_t* format, _in ...) const;

    // 输出备注信息到控制台
    bool OutputComment(_in const char* format, _in ...) const;
    bool OutputComment(_in const wchar_t* format, _in ...) const;

protected:

    // 输出到控制台：attr 指定输出属性，strout 指定输出附加信息，text 指定输出文字。
    static bool _output_to_console(_in att_t attr, _in const char* text, _in const char* info);
    static bool _output_to_console(_in att_t attr, _in const wchar_t* text, _in const char* info);

public:

    virtual ~Console();

protected:

    Console();

private:

    Console(const Console&);
    Console& operator=(const Console&);

private:

    bool    _bconsole;                  // 标记控制台是否已经创建
    bool    _breopen;                   // 标记标准输出设备是否成功重定向
    FILE*   _hfile;                     // 缓存标准输出文件指针地址

};  // class Console

//=============================================================================
// class SingleLog
//=============================================================================
class SingleLog
{
public:
	
    explicit SingleLog(_in long str);
    explicit SingleLog(_in double str);
    explicit SingleLog(_in const char* str);
    explicit SingleLog(_in const wchar_t* str);

private:

    SingleLog(const SingleLog&);
    SingleLog& operator=(const SingleLog&);

    void _make_file_name(_out char* buf, _in _size_t size);

};  // class SingleLog

//=============================================================================
// class DoubleLog
//=============================================================================
class DoubleLog
{
public:

    ~DoubleLog();

    explicit DoubleLog(_in long str);
    explicit DoubleLog(_in double str);
    explicit DoubleLog(_in const char* str);
    explicit DoubleLog(_in const wchar_t* str);

private:

    DoubleLog(const DoubleLog&);
    DoubleLog& operator=(const DoubleLog&);

    void _make_file_name();

    std::string _str;
    std::string _file;

};  // class DoubleLog

//-----------------------------------------------------------------------------

typedef Console LogC;

#define _ConsoleInst    _bnb Console::GetInstance()

#ifdef  _bnb_console
#define _console        _bnb Console::GetInstance()
#define _outputext      _bnb Console::GetInstance().OutputText
#define _doublelog(x)   _bnb DoubleLog _double_log_nemo_obj(x)
#define _singlelog(x)   _bnb SingleLog(x)
#else
#define _console        _bnb_null_statement
#define _outputext      _bnb_null_statement
#define _doublelog(x)   _bnb_null_statement
#define _singlelog(x)   _bnb_null_statement
#endif  // #ifdef  _bnb_console

#define _func_log       _doublelog(__FUNCTION__)
#define _line_log       _singlelog((long)__LINE__)
#define _file_log       _singlelog(__FILE__)

//-----------------------------------------------------------------------------

#ifndef _console_api
#define _console_api    _declare_inline
#include "../windows/_console.inl"
#undef  _console_api
#endif  // #ifndef _console_api

_bnb_space_out

#endif