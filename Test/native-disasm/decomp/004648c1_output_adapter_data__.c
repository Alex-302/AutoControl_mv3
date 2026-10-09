// output_adapter_data<> @ 004648c1 size=60 callers=1

/* Library Function - Multiple Matches With Same Base Name
    protected: __thiscall __crt_stdio_output::output_adapter_data<char,class
   __crt_stdio_output::stream_output_adapter<char> >::output_adapter_data<char,class
   __crt_stdio_output::stream_output_adapter<char> >(class
   __crt_stdio_output::stream_output_adapter<char> const &,unsigned __int64,char const *
   const,struct __crt_locale_pointers * const,char * const)
    protected: __thiscall __crt_stdio_output::output_adapter_data<char,class
   __crt_stdio_output::string_output_adapter<char> >::output_adapter_data<char,class
   __crt_stdio_output::string_output_adapter<char> >(class
   __crt_stdio_output::string_output_adapter<char> const &,unsigned __int64,char const *
   const,struct __crt_locale_pointers * const,char * const)
   
   Library: Visual Studio 2015 Release */

void * __thiscall
output_adapter_data<>
          (void *this,undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
          undefined4 param_5,undefined4 param_6)

{
  __crt_stdio_output::common_data<char>::common_data<char>(this);
  *(undefined4 *)((int)this + 0x448) = *param_1;
  *(undefined4 *)this = param_2;
  *(undefined4 *)((int)this + 4) = param_3;
  *(undefined4 *)((int)this + 8) = param_5;
  *(undefined4 *)((int)this + 0x10) = param_4;
  *(undefined4 *)((int)this + 0x14) = param_6;
  return this;
}


