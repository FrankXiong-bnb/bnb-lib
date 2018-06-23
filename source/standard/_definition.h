//=============================================================================
// _definition.h
//  														2014-3 by Frank
//=============================================================================
#ifndef ____bnb_Definition_H_
#define ____bnb_Definition_H_

//-----------------------------------------------------------------------------

#define _______bnb_

//-----------------------------------------------------------------------------

#define _bnb_null_statement

//-----------------------------------------------------------------------------

#ifndef _global_name
#define _global_name ::
#endif

#ifndef _global_func
#define _global_func _global_name
#endif

#ifndef _declare_global
#define _declare_global
#endif

#ifndef _declare_const
#define _declare_const const
#endif

#ifndef _declare_static
#define _declare_static static
#endif

#ifndef _declare_volatile
#define _declare_volatile volatile
#endif

#ifndef _declare_mutable
#define _declare_mutable mutable
#endif

#ifndef _declare_inline
#define _declare_inline inline
#endif

#ifndef _declare_friend
#define _declare_friend friend
#endif

#ifndef _declare_explicit
#define _declare_explicit explicit
#endif

#ifndef _declare_virtual
#define _declare_virtual virtual
#endif

#ifndef _declare_cdecl
#define _declare_cdecl __cdecl
#endif

#ifndef _declare_stdcall
#define _declare_stdcall __stdcall
#endif

#ifndef _declare_template
#define _declare_template   template
#endif

#ifndef _template_class
#define _template_class     _declare_template
#endif

#ifndef _template_function
#define _template_function  _declare_template
#endif

#ifndef __bnbcall
#define __bnbcall
#endif

//-----------------------------------------------------------------------------

#define _bnb_typedef    typedef
#define _bnb_using      using

//-----------------------------------------------------------------------------

#define _bnb_explanation(_text)
#define _bnb_declare(_symbol)               _symbol
#define _bnb_mark(mark)                     (mark)
#define _bnb_ignore(things)                 (things)
#define _bnb_ignore_parameter(param)        _bnb_ignore(param)
#define _bnb_ignore_expression(expr)        _bnb_ignore(expr)

//-----------------------------------------------------------------------------

#ifndef _exactly_version
#define _exactly_version
#endif

#ifndef _overload_version
#define _overload_version(ver_No)   _bnb_explanation(ver_No)
#endif

#ifndef _explicit_declare
#define _explicit_declare(_name)    _bnb_declare(_name)
#endif

#ifndef _implicit_declare
#define _implicit_declare(_name)    _bnb_declare(_name)
#endif

#ifndef _function_name
#define _function_name(_func)       _bnb_declare(_func)
#endif

#ifndef _return_type
#define _return_type(_type)         _bnb_declare(_type)
#endif

#ifndef _argument_list
#define _argument_list
#endif

#ifndef _in
#define _in
#endif

#ifndef _out
#define _out
#endif

#ifndef _in_out
#define _in_out
#endif

#ifndef in_
#define in_(_type)      _in
#endif

#ifndef out_
#define out_(_type)     _out
#endif

#ifndef in_out_
#define in_out_(_type)  _in_out
#endif

#ifndef _local_statement_begin
#define _local_statement_begin  do {
#endif

#ifndef _local_statement_end
#define _local_statement_end    } while (false)
#endif

#ifndef _local_statement_over
#define _local_statement_over   break
#endif

#ifndef _local_code_begin
#define _local_code_begin  [&]()mutable{
#endif

#ifndef _local_code_end
#define _local_code_end    }()
#endif

#ifndef _local_code_over
#define _local_code_over   return
#endif

//-----------------------------------------------------------------------------

#ifndef _piece_together_name
#define _piece_together_name(_prefixe, _suffixe) _prefixe##_suffixe
#endif

#ifndef _count_of_array
#define _count_of_array(_arr)   (sizeof(_arr) / sizeof(_arr[0]))
#endif

#ifndef _offset
#define _offset(ty, member) ((unsigned int)(&(reinterpret_cast<const volatile char&>((((ty*)0)->member)))))
#endif

#define _bnb_assert_action(_expr, _action)  (void)( (!!(_expr)) || (_action) )
#define _bnb_assert_return(_expr, _value)   if ( !!!(_expr) ) return (_value)

//-----------------------------------------------------------------------------

#ifndef _not_bnb_space
#define _bnb_space_in    namespace bnb {
#define _bnb_space_out   }
#define _bnb    ::bnb::
#else
#define _bnb_space_in   _bnb_null_statement
#define _bnb_space_out  _bnb_null_statement
#define _bnb            _bnb_null_statement
#endif

#endif