//=============================================================================
// _game_timer.h
//
// Exception :
//      ���嶨ʱ���࣬��ʱ�������࣬�ṩ��Ϸ��ʱ��ͳһ�ӿڡ�
//
//=============================================================================
#ifndef ____ZJY_Game_Timer_H_
#define ____ZJY_Game_Timer_H_

#ifndef _zjy_cs_type
#error  Please make sure the _zjy_cs_type already defined
#endif  // _zjy_cs_type

_zjy_space_in

// ���嶨ʱ����ʼID
//-----------------------------------------------------------------------------

#define _timer_reserve          10
#define _tid_begin              (_timer_reserve + 1)

// �淶��ʱ��ID���巽ʽ
//-----------------------------------------------------------------------------

#define _DeclareTimerBegin      _zjy_enum_begin(_timer_id_e) _tid_def = _tid_begin + _tid_def_value - 1,
#define _DeclareTimerEnd        _tid_max _zjy_enum_end

// ���嶨ʱ��Ĭ��ʱ����
//-----------------------------------------------------------------------------
// Ĭ��ʱ����������_timer_def_interval�ı䣬���û�δ����ú꣬��Ĭ�Ͼ���Ϊ10��
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
//      _OperatorT   - ��ʱ��ʵ�ֲ�������
//                     ��_OperatorT�����У�Ӧ�����ṩ��ʱ�����������Ľӿڡ�
//
// Exception :
//      ����һ���ǿ����࣬���������û����ж���Ŀ����͸�ֵ������
//
//      _game_timer �ṩ��ʱ�������Ļ���ͳһ�ӿڣ�����������ʱ������ʵ�֡�
//      �ڲ�����_OperatorTʵ�ֶ�ʱ�����������Բ����Ľӿ�ͳһ�͹淶����
//      �����Ѿ��ṩĬ��ʵ�֣������ض����͵Ķ�ʱ��ʵ�ֿ��ܻ���Ҫ������������д��
//
//      Ĭ�϶�ʱ����ʱ��ʽʹ�ñ�׼���е�clock()�����������Ҫʵ���Լ��ļ�ʱ��ʽ
//      ��ʱ�侫�ȣ�����������GetCurTime()�ӿڣ�ֱ�ӷ��ط������Լ���Ҫ��ʱ�䡣
//
//=============================================================================
template<typename _OperatorT>
class _game_timer
{
private:
    typedef _game_timer<_OperatorT> _MyT;

    // ˽�еĲ���δʵ�ֵĿ������캯���͸�ֵ���������غ���
    _game_timer(const _MyT&);
    _MyT& operator=(const _MyT&);

public:

    // �ڶ������ٵ�ʱ����ȷ����ʱ���ر�
    ~_game_timer() { Stop(); }

    explicit _game_timer(int tid = 0)
        : _operator(nullptr)
        , _playing(false)
        , _timer_id(tid)
        , _last_time(0)
        , _param(0)
    { }

    // �ж϶�ʱ���Ƿ�������
    bool IsStarted() const { return _playing; }

//-----------------------------------------------------------------------------
// bool Start(int interval = _timer_interval)
//      ������ʱ��
//
// Return:
//      �ɹ���������true�����򷵻�false��
//
// Parameter:
//      interval    - ʱ�侫��
//
// Exception:
//      �ú���������ʱ���������ʱ���Ѿ������У���ֱ�ӷ���false��
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
//      ֹͣ��ʱ��
//
// Return:
//      ���Ժ���
//
// Parameter:
//      void
//
// Exception:
//      �����ʱ��δ���У���ֱ�ӷ��ز����κβ�����
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
//      ���ö�ʱ����ʼ��ʱʱ��
//
// Return:
//      void
//
// Parameter:
//      void
//
// Exception:
//      �����ʱ��δ���У��ò�����Ч��
//
    void Recycle()
    {
        if (_playing)
            _last_time = GetCurTime();
    }

//-----------------------------------------------------------------------------
// void Restart(int interval = _timer_interval)
//      ������ʱ��
//
// Return:
//      void
//
// Parameter:
//      interval    - ָ������ʱ��ʱ��ʱ�侫��
//
// Exception:
//      �ú����ȹرն�ʱ�����ٰ���ָ����ʱ�侫��������ʱ����
//
    void Restart(int interval = _timer_interval)
    {
        Stop();
        Start(interval);
    }

//-----------------------------------------------------------------------------
// unsigned int GetElapsed() const
//      ��ȡ��ʱ�����е�ʱ��
//
// Return:
//      ���ض�ʱ���������󾭹���ʱ��
//
// Parameter:
//      void
//
// Exception:
//      �����ʱ��δ���У���ֱ�ӷ���0��
//      ����ڶ�ʱ�����еĹ����е�����Reset()�������򷵻ص��ǵ�ǰ����˵��þ�����ʱ�䡣
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
//      ���ö�ʱ��ID
//
// Return:
//      ���������Ƿ�ɹ�
//
// Parameter:
//      id      - Ҫָ���Ķ�ʱ��ID
//
// Exception:
//      Ӧ���ڶ����ʶ�Ķ�ʱ��ֹͣ��ʱ��ָ����ʱ��ID�����򽫺��Ըò�����
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
//      ���ö�ʱ�����Ӳ���
//
// Return:
//      ���������Ƿ�ɹ�
//
// Parameter:
//      param   - Ҫָ���ĸ��Ӳ���
//
// Exception:
//      ÿ����ʱ��������Թ���һ���������ݣ��������һ���붨ʱ����ص����ݡ�
//      Ӧ���ڶ����ʶ�Ķ�ʱ��ֹͣ��ʱ��ָ�����Ӳ��������򽫺��Ըò�����
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
//      ָ����ʱ��������ָ��
//
// Return:
//      ����ָ���Ƿ�ɹ�
//
// Parameter:
//      op      - Ҫָ���Ĳ�����ָ��
//
// Exception:
//      ���ָ�����ṩ��ʱ������ʵ�ֵĶ��󣬶�ʱ������������ʵ�ֶ���������ָ�롣
//      Ӧ���ڶ����ʶ�Ķ�ʱ��ֹͣ��ʱ��ָ�������ߣ����򽫺��Ըò�����
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
//      ��ȡ��ǰʱ��
//
// Return:
//      ���ص�ǰʱ��
//
// Parameter:
//      void
//
// Exception:
//      ����������ص�ʱ�佫���ڶ�ʱ���ڲ���ʱ�ͼ���ʱ��
//      �û��ɸ�д�ú���������һ���Լ���Ҫ�ͷ���ʵ�ʵ�ʱ�䡣
//
    static unsigned int GetCurTime() { return ((unsigned int)clock()); }

private:

    _OperatorT*         _operator;

    bool                _playing;
    unsigned int        _timer_id;
    unsigned int        _last_time;
    unsigned long       _param;

};  // class _game_timer

// ����Ĭ�϶�ʱ������
//-----------------------------------------------------------------------------
// ��ʱ��Ĭ������������ _timer_def_count �ı䣬���û�δ����ú꣬��ָ��Ĭ��ֵ��
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
//      _Ty         - ��ʱ������������
//      _OperatorT  - ��ʱ�����������ͣ��μ� _game_timer˵����
//      _timer_max  - ��ʱ��������������Ĭ�ϰ�����������_timer_reserve��
//                    ���ʾʵ�ʿ��õĶ�ʱ������Ϊ��_timer_max - _timer_reserve
//
// Excetion :
//      ��ʹ�ù涨����ʽ��_DeclareTimerBegin �� _DeclareTimerEnd �����嶨ʱ��ID
//      �����ֱ��ʹ��_tid_max���_timer_max����������ʹ�ô˷�ʽ��
//
//      ��ʱ���������ڲ������������ʽ����ʱ�����󣬽����ݺ�_tid_def_value��
//      �����ֵ��ȷ������ʹ�õ�Ĭ�϶�ʱ����������Щ��ʱ�����󽫶��û����ɼ���
//      ֻ��ʹ��Ĭ���ӳٵ��ò��������Ѿ���ID�������ʶ�Ķ�ʱ������ſ��Բ�����
//
//      Ĭ�϶�ʱ����������ڶ��ض��Ĳ������ж�ʱ�ӳٵ���һ�Σ��趨��ʱ�䵽���
//      ����ִ�а󶨵Ĳ��������йرա�����ض��Ĳ���������һ��_Ty���Ա������
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
//      ���ص��±������
//
// Return:
//      ��Ӧ�Ķ�ʱ�����������
//
// Parameter:
//      tid     - Ҫ���ʵĶ�ʱ��ID
//
// Exception:
//      ��Ӧ��ʹ���±����������Ĭ�϶�ʱ����Ҫ����Ĭ�϶�ʱ����ʹ�ã�CallDefTimer��
//
    timer_t& operator [] (int tid) { return _timer[tid - _tid_begin]; }
    const timer_t& operator [] (int tid) const { return _timer[tid - _tid_begin]; }
    
//-----------------------------------------------------------------------------
// result_t CallDefTimer(int i, _Ty* caller)
//      ����Ĭ�϶�ʱ��
//
// Return:
//      ���õĽ��
//
// Parameter:
//      i       - Ĭ�϶�ʱ������
//      caller  - �ص������ĵ�����
//
// Exception:
//      ����Ĭ�϶�ʱ�����һ��_Ty��Ա�����󶨣����Ҫ���øó�Ա������Ҫһ��_Ty���͵Ķ���
//      ���ö���ĵ�ַ�ɲ���callerָ����������õ�ʱ�䵽����ɹ����ð󶨵ĺ������򷵻�
//      �ú����ĵ��ý������������Ĭ�Ϸ��سɹ���ʶ��
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
//      ���һ����ʱ���ò���
//
// Return:
//      ��������Ƿ�ɹ�
//
// Parameter:
//      delay       - �ӳ�ʱ�䣬���ʱ��ľ���Ӧ���Ǻ�_game_timer::GetCurTime()ƥ�䡣
//      pf          - ָ��Ҫ��ӵĲ������μ� _TimerFunT ���塣
//      lparam      - ���ݸ�pf�Ĳ���
//      wparam      - ���ݸ�pf�Ĳ���
//
// Exception:
//      �ú���������һ�����е�Ĭ�϶�ʱ�����������ͺ���pf���а󶨣����û���ҵ�����false��
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