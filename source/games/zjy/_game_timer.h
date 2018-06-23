//=============================================================================
// _game_timer.h
//
// Exception :
//      定义定时器类，定时器管理类，提供游戏定时器统一接口。
//
//=============================================================================
#ifndef ____ZJY_Game_Timer_H_
#define ____ZJY_Game_Timer_H_

#ifndef _zjy_cs_type
#error  Please make sure the _zjy_cs_type already defined
#endif  // _zjy_cs_type

_zjy_space_in

// 定义定时器起始ID
//-----------------------------------------------------------------------------

#define _timer_reserve          10
#define _tid_begin              (_timer_reserve + 1)

// 规范定时器ID定义方式
//-----------------------------------------------------------------------------

#define _DeclareTimerBegin      _zjy_enum_begin(_timer_id_e) _tid_def = _tid_begin + _tid_def_value - 1,
#define _DeclareTimerEnd        _tid_max _zjy_enum_end

// 定义定时器默认时间间隔
//-----------------------------------------------------------------------------
// 默认时间间隔可以由_timer_def_interval改变，若用户未定义该宏，则默认精度为10。
#ifndef _timer_def_interval
#define _timer_interval         10
#else
#if     _timer_def_interval < 2
#error  The default timer interval must be greater than 1
else
#define _timer_interval         _timer_def_interval
#endif
#endif  // _timer_def_interval

//=============================================================================
// template<typename _OperatorT> class _game_timer
//
//      _OperatorT   - 定时器实现操作类型
//                     在_OperatorT类型中，应该有提供定时器基本操作的接口。
//
// Exception :
//      这是一个非拷贝类，将不允许用户进行对象的拷贝和赋值操作。
//
//      _game_timer 提供定时器操作的基本统一接口，本身不包含定时器基本实现。
//      内部依赖_OperatorT实现定时器操作，但对操作的接口统一和规范化。
//      本身已经提供默认实现，对于特定类型的定时器实现可能还需要进行特例化改写。
//
//      默认定时器计时方式使用标准库中的clock()函数，如果需要实现自己的计时方式
//      和时间精度，可以特例化GetCurTime()接口，直接返回符合你自己需要的时间。
//
//=============================================================================
template<typename _OperatorT>
class _game_timer
{
private:
    typedef _game_timer<_OperatorT> _MyT;

    // 私有的并且未实现的拷贝构造函数和赋值操作符重载函数
    _game_timer(const _MyT&);
    _MyT& operator=(const _MyT&);

public:

    // 在对象销毁的时候能确保定时器关闭
    ~_game_timer() { Stop(); }

    explicit _game_timer(int tid = 0)
        : _operator(nullptr)
        , _playing(false)
        , _timer_id(tid)
        , _last_time(0)
        , _param(0)
    { }

    // 判断定时器是否在运行
    bool IsStarted() const { return _playing; }

//-----------------------------------------------------------------------------
// bool Start(int interval = _timer_interval)
//      启动定时器
//
// Return:
//      成功启动返回true，否则返回false。
//
// Parameter:
//      interval    - 时间精度
//
// Exception:
//      该函数启动定时器，如果定时器已经在运行，则直接返回false。
//
    bool Start(int interval = _timer_interval)
    {
        if (!!!_playing && _operator)
        {
            _operator->SetTimer(_timer_id, interval);
            _playing = true;
            _last_time = GetCurTime();

            return true;
        }

        return false;
    }

//-----------------------------------------------------------------------------
// bool Stop()
//      停止定时器
//
// Return:
//      可以忽略
//
// Parameter:
//      void
//
// Exception:
//      如果定时器未运行，则直接返回不做任何操作。
//
    bool Stop()
    {
        if (_playing && _operator)
        {
            _operator->KillTimer(_timer_id);
            _playing = false;
        }

        return true;
    }

//-----------------------------------------------------------------------------
// void Recycle()
//      重置定时器开始计时时间
//
// Return:
//      void
//
// Parameter:
//      void
//
// Exception:
//      如果定时器未运行，该操作无效。
//
    void Recycle()
    {
        if (_playing)
            _last_time = GetCurTime();
    }

//-----------------------------------------------------------------------------
// void Restart(int interval = _timer_interval)
//      重启定时器
//
// Return:
//      void
//
// Parameter:
//      interval    - 指定重启时定时器时间精度
//
// Exception:
//      该函数先关闭定时器，再按照指定的时间精度启动定时器。
//
    void Restart(int interval = _timer_interval)
    {
        Stop();
        Start(interval);
    }

//-----------------------------------------------------------------------------
// unsigned int GetElapsed() const
//      获取定时器运行的时间
//
// Return:
//      返回定时器自启动后经过的时间
//
// Parameter:
//      void
//
// Exception:
//      如果定时器未运行，则直接返回0。
//      如果在定时器运行的过程中调用了Reset()函数，则返回的是当前距离此调用经过的时间。
//
    unsigned int GetElapsed() const
    {
        if (!!_playing)
            return (GetCurTime() - _last_time);
        else
            return 0;
    }

//-----------------------------------------------------------------------------
// bool SetTimerID(int id)
//      设置定时器ID
//
// Return:
//      返回设置是否成功
//
// Parameter:
//      id      - 要指定的定时器ID
//
// Exception:
//      应该在对象标识的定时器停止的时候指定定时器ID，否则将忽略该操作。
//
    bool SetTimerID(int id)
    {
        if (_playing)
            return false;
        
        _timer_id = id;
        return true;
    }

//-----------------------------------------------------------------------------
// bool SetParam(unsigned long param)
//      设置定时器附加参数
//
// Return:
//      返回设置是否成功
//
// Parameter:
//      param   - 要指定的附加参数
//
// Exception:
//      每个定时器对象可以关联一个附加数据，这可能是一个与定时器相关的数据。
//      应该在对象标识的定时器停止的时候指定附加参数，否则将忽略该操作。
//
    bool SetParam(unsigned long param)
    {
        if (_playing)
            return false;

        _param = param;
        return true;
    }

//-----------------------------------------------------------------------------
// bool Appoint(_OperatorT* op)
//      指定定时器操作者指针
//
// Return:
//      返回指派是否成功
//
// Parameter:
//      op      - 要指定的操作者指针
//
// Exception:
//      这个指针是提供定时器具体实现的对象，定时器基本操作的实现都会依赖该指针。
//      应该在对象标识的定时器停止的时候指定操作者，否则将忽略该操作。
//
    bool Appoint(_OperatorT* op)
    {
        if (_playing)
            return false;

        _operator = op;
        return true;
    }

//-----------------------------------------------------------------------------
// static unsigned int GetCurTime()
//      获取当前时间
//
// Return:
//      返回当前时间
//
// Parameter:
//      void
//
// Exception:
//      这个函数返回的时间将用于定时器内部计时和计算时间差。
//      用户可改写该函数，返回一个自己需要和符合实际的时间。
//
    static unsigned int GetCurTime() { return ((unsigned int)clock()); }

private:

    _OperatorT*         _operator;

    bool                _playing;
    unsigned int        _timer_id;
    unsigned int        _last_time;
    unsigned long       _param;

};  // class _game_timer

// 定义默认定时器数量
//-----------------------------------------------------------------------------
// 定时器默认数量可以由 _timer_def_count 改变，若用户未定义该宏，则指定默认值。
#ifndef _timer_def_count
#if _zjy_cs_type == _zjy_server
#define _tid_def_value          16
#else
#define _tid_def_value          32
#endif  // #if _zjy_cs_type == _zjy_server
#else
#if     _timer_def_count > 0
#define _tid_def_value          _timer_def_count
#else
#error  The default timer number must be greater than zero
#endif  // _timer_def_count > 0
#endif  // _timer_def_count

//=============================================================================
// template<typename _Ty, typename _OperatorT, unsigned int _timer_max>
// class _timer_manager
//
//      _Ty         - 定时器关联的类名
//      _OperatorT  - 定时器操作者类型，参见 _game_timer说明。
//      _timer_max  - 定时器数量，该数量默认包括保留数量_timer_reserve。
//                    这表示实际可用的定时器数量为：_timer_max - _timer_reserve
//
// Excetion :
//      若使用规定的形式：_DeclareTimerBegin 和 _DeclareTimerEnd 来定义定时器ID
//      则可用直接使用_tid_max替代_timer_max参数，建议使用此方式。
//
//      定时器管理者内部采用数组的形式管理定时器对象，将根据宏_tid_def_value所
//      代表的值来确定可以使用的默认定时器数量，这些定时器对象将对用户不可见，
//      只能使用默认延迟调用操作，而已经用ID来具体标识的定时器对象才可以操作。
//
//      默认定时器被设计用于对特定的操作进行定时延迟调用一次，设定的时间到达后
//      将会执行绑定的操作并自行关闭。这个特定的操作必须是一个_Ty类成员函数。
//
//=============================================================================
template<typename _Ty, typename _OperatorT, unsigned int _timer_max>
class _timer_manager
{
    static_assert(_tid_begin<_timer_max, "The template parameter _timer_max must be greater than _tid_begin");

#if _zjy_cs_type == _zjy_server
    static_assert(_timer_max < 50, "The template parameter _timer_max must be greater than 50");
#endif

private:

    typedef _Ty _ClassT;
    typedef _timer_manager<_ClassT, _OperatorT, _timer_max> _MyT;
    typedef _game_timer<_OperatorT> timer_t;
    typedef result_t (_ClassT::*_TimerFunT)(param_t, param_t);

    _timer_manager(const _MyT&);
    _MyT& operator=(const _MyT&);

public:

    _timer_manager()
    {
        for (int i = _tid_begin; i < _timer_max; ++i)
            _timer[i - _tid_begin].SetTimerID(i);

        for (int i = 0; i < _tid_def_value; ++i)
            _def_arg[i].Clear();
    }

//-----------------------------------------------------------------------------
// timer_t& operator [] (int tid)
// const timer_t& operator [] (int tid) const
//      重载的下标操作符
//
// Return:
//      对应的定时器对象的引用
//
// Parameter:
//      tid     - 要访问的定时器ID
//
// Exception:
//      不应该使用下标操作符访问默认定时器，要访问默认定时器请使用：CallDefTimer。
//
    timer_t& operator [] (int tid) { return _timer[tid - _tid_begin]; }
    const timer_t& operator [] (int tid) const { return _timer[tid - _tid_begin]; }
    
//-----------------------------------------------------------------------------
// result_t CallDefTimer(int i, _Ty* caller)
//      调用默认定时器
//
// Return:
//      调用的结果
//
// Parameter:
//      i       - 默认定时器索引
//      caller  - 回调函数的调用者
//
// Exception:
//      由于默认定时器会和一个_Ty成员函数绑定，因此要调用该成员函数需要一个_Ty类型的对象。
//      调用对象的地址由参数caller指定。如果设置的时间到达，并成功调用绑定的函数，则返回
//      该函数的调用结果，否则总是默认返回成功标识。
//
    result_t CallDefTimer(int i, _Ty* caller)
    {
        _timer[i].Stop();

        _TimerFunT f = _def_arg[i]._pFun;
        param_t p1 = _def_arg[i]._lparam;
        param_t p2 = _def_arg[i]._wparam;

        _def_arg[i].Clear();

        if (f)
            return (caller->*f)(p1, p2);

        return hr_success;
    }

//-----------------------------------------------------------------------------
// bool AddDelayCall(unsigned int delay, unsigned int ms, _TimerFunT pf, param_t lparam, param_t wparam)
// bool AddDelayCall(unsigned int delay, _TimerFunT pf, param_t lparam, param_t wparam)
//      添加一个定时调用操作
//
// Return:
//      返回添加是否成功
//
// Parameter:
//      delay       - 延迟时间，这个时间的精度应该是和_game_timer::GetCurTime()匹配。
//      pf          - 指定要添加的操作，参见 _TimerFunT 定义。
//      lparam      - 传递给pf的参数
//      wparam      - 传递给pf的参数
//
// Exception:
//      该函数会搜索一个空闲的默认定时器，并将它和函数pf进行绑定，如果没有找到返回false。
//
    bool AddDelayCall(unsigned int delay, _TimerFunT pf, param_t lparam, param_t wparam)
    {
        for (int i = 0; i < _tid_def_value; ++i)
        {
            if (!_timer[i].IsStarted())
            {
                _def_arg[i]._pFun      = pf;
                _def_arg[i]._delay     = delay;
                _def_arg[i]._lparam    = lparam;
                _def_arg[i]._wparam    = wparam;

                return _timer[i].Start(delay);
            }
        }

        return false;
    }

private:

    struct {
        void Clear() {
            _lparam = 0; _wparam = 0; _delay = 0; _pFun = nullptr;
        }

        _TimerFunT      _pFun;
        unsigned int    _delay;
        param_t        _lparam;
        param_t        _wparam;

    } _def_arg[_tid_def_value];

    timer_t _timer[_timer_max - _tid_begin];

};  // class _timer_manager

_zjy_space_out

#endif

//  														2014-9 by Frank
//-----------------------------------------------------------------------------