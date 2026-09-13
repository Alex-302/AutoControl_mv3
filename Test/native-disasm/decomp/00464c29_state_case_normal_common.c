// state_case_normal_common @ 00464c29 size=42 callers=1

/* Library Function - Multiple Matches With Same Base Name
    private: bool __thiscall __crt_stdio_output::output_processor<char,class
   __crt_stdio_output::string_output_adapter<char>,class
   __crt_stdio_output::format_validation_base<char,class
   __crt_stdio_output::string_output_adapter<char> > >::state_case_normal_common(void)
    private: bool __thiscall __crt_stdio_output::output_processor<char,class
   __crt_stdio_output::string_output_adapter<char>,class
   __crt_stdio_output::standard_base<char,class __crt_stdio_output::string_output_adapter<char> >
   >::state_case_normal_common(void)
   
   Library: Visual Studio 2015 Release */

uint __fastcall state_case_normal_common(int param_1)

{
  uint uVar1;
  undefined3 extraout_var;
  
  uVar1 = state_case_normal_tchar(param_1);
  if ((char)uVar1 == '\0') {
    return uVar1;
  }
  __crt_stdio_output::string_output_adapter<char>::write_character
            ((string_output_adapter<char> *)(param_1 + 0x448),*(char *)(param_1 + 0x31),
             (int *)(param_1 + 0x18));
  return CONCAT31(extraout_var,1);
}


