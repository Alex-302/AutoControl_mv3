// state_case_precision @ 00464cb4 size=40 callers=1

/* Library Function - Multiple Matches With Same Base Name
    private: bool __thiscall __crt_stdio_output::output_processor<char,class
   __crt_stdio_output::stream_output_adapter<char>,class
   __crt_stdio_output::standard_base<char,class __crt_stdio_output::stream_output_adapter<char> >
   >::state_case_precision(void)
    private: bool __thiscall __crt_stdio_output::output_processor<char,class
   __crt_stdio_output::string_output_adapter<char>,class
   __crt_stdio_output::standard_base<char,class __crt_stdio_output::string_output_adapter<char> >
   >::state_case_precision(void)
   
   Library: Visual Studio 2015 Release */

undefined4 __fastcall state_case_precision(void *param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  if (*(char *)((int)param_1 + 0x31) != '*') {
    uVar2 = parse_int_from_format_string(param_1,(long *)((int)param_1 + 0x28));
    return uVar2;
  }
  *(int *)((int)param_1 + 0x14) = *(int *)((int)param_1 + 0x14) + 4;
  iVar1 = *(int *)(*(int *)((int)param_1 + 0x14) + -4);
  *(int *)((int)param_1 + 0x28) = iVar1;
  if (iVar1 < 0) {
    *(undefined4 *)((int)param_1 + 0x28) = 0xffffffff;
  }
  return CONCAT31((int3)((uint)iVar1 >> 8),1);
}


