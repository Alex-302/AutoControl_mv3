// write_stored_string_tchar @ 004655f2 size=167 callers=1

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* Library Function - Multiple Matches With Same Base Name
    private: bool __thiscall __crt_stdio_output::output_processor<char,class
   __crt_stdio_output::string_output_adapter<char>,class
   __crt_stdio_output::format_validation_base<char,class
   __crt_stdio_output::string_output_adapter<char> > >::write_stored_string_tchar(char)
    private: bool __thiscall __crt_stdio_output::output_processor<char,class
   __crt_stdio_output::string_output_adapter<char>,class
   __crt_stdio_output::standard_base<char,class __crt_stdio_output::string_output_adapter<char> >
   >::write_stored_string_tchar(char)
   
   Library: Visual Studio 2015 Release */

undefined4 __fastcall write_stored_string_tchar(int param_1)

{
  wchar_t _WCh;
  errno_t eVar1;
  errno_t extraout_EAX;
  errno_t extraout_EAX_00;
  int iVar2;
  wchar_t *pwVar3;
  int local_14;
  char local_10 [8];
  uint local_8;
  
  local_8 = DAT_0049d070 ^ (uint)&stack0xfffffffc;
  if ((*(char *)(param_1 + 0x3c) == '\0') || (*(int *)(param_1 + 0x38) < 1)) {
    __crt_stdio_output::string_output_adapter<char>::write_string
              ((string_output_adapter<char> *)(param_1 + 0x448),*(char **)(param_1 + 0x34),
               *(int *)(param_1 + 0x38),(int *)(param_1 + 0x18),*(int **)(param_1 + 0xc));
    eVar1 = extraout_EAX_00;
  }
  else {
    pwVar3 = *(wchar_t **)(param_1 + 0x34);
    iVar2 = 0;
    eVar1 = 0;
    if (*(int *)(param_1 + 0x38) != 0) {
      do {
        _WCh = *pwVar3;
        pwVar3 = pwVar3 + 1;
        local_14 = 0;
        eVar1 = _wctomb_s(&local_14,local_10,6,_WCh);
        if ((eVar1 != 0) || (local_14 == 0)) {
          *(undefined4 *)(param_1 + 0x18) = 0xffffffff;
          break;
        }
        __crt_stdio_output::string_output_adapter<char>::write_string
                  ((string_output_adapter<char> *)(param_1 + 0x448),local_10,local_14,
                   (int *)(param_1 + 0x18),*(int **)(param_1 + 0xc));
        iVar2 = iVar2 + 1;
        eVar1 = extraout_EAX;
      } while (iVar2 != *(int *)(param_1 + 0x38));
    }
  }
  return CONCAT31((int3)((uint)eVar1 >> 8),1);
}


