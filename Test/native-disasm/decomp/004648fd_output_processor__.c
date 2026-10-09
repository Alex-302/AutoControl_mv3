// output_processor<> @ 004648fd size=53 callers=1

/* Library Function - Multiple Matches With Same Base Name
    public: __thiscall __crt_stdio_output::output_processor<char,class
   __crt_stdio_output::string_output_adapter<char>,class
   __crt_stdio_output::format_validation_base<char,class
   __crt_stdio_output::string_output_adapter<char> > >::output_processor<char,class
   __crt_stdio_output::string_output_adapter<char>,class
   __crt_stdio_output::format_validation_base<char,class
   __crt_stdio_output::string_output_adapter<char> > >(class
   __crt_stdio_output::string_output_adapter<char> const &,unsigned __int64,char const *
   const,struct __crt_locale_pointers * const,char * const)
    public: __thiscall __crt_stdio_output::output_processor<char,class
   __crt_stdio_output::string_output_adapter<char>,class
   __crt_stdio_output::standard_base<char,class __crt_stdio_output::string_output_adapter<char> >
   >::output_processor<char,class __crt_stdio_output::string_output_adapter<char>,class
   __crt_stdio_output::standard_base<char,class __crt_stdio_output::string_output_adapter<char> >
   >(class __crt_stdio_output::string_output_adapter<char> const &,unsigned __int64,char const *
   const,struct __crt_locale_pointers * const,char * const)
   
   Library: Visual Studio 2015 Release */

void * __thiscall
output_processor<>(void *this,undefined4 *param_1,undefined4 param_2,undefined4 param_3,
                  undefined4 param_4,undefined4 param_5,undefined4 param_6)

{
  int *piVar1;
  
  output_adapter_data<>(this,param_1,param_2,param_3,param_4,param_5,param_6);
  *(undefined4 *)((int)this + 0x450) = 0;
  piVar1 = __errno();
  *(int **)((int)this + 0xc) = piVar1;
  return this;
}


