// state_case_normal_tchar @ 00464c53 size=97 callers=1

/* Library Function - Multiple Matches With Same Base Name
    private: bool __thiscall __crt_stdio_output::output_processor<char,class
   __crt_stdio_output::string_output_adapter<char>,class
   __crt_stdio_output::format_validation_base<char,class
   __crt_stdio_output::string_output_adapter<char> > >::state_case_normal_tchar(char)
    private: bool __thiscall __crt_stdio_output::output_processor<char,class
   __crt_stdio_output::string_output_adapter<char>,class
   __crt_stdio_output::positional_parameter_base<char,class
   __crt_stdio_output::string_output_adapter<char> > >::state_case_normal_tchar(char)
    private: bool __thiscall __crt_stdio_output::output_processor<char,class
   __crt_stdio_output::string_output_adapter<char>,class
   __crt_stdio_output::standard_base<char,class __crt_stdio_output::string_output_adapter<char> >
   >::state_case_normal_tchar(char)
   
   Library: Visual Studio 2015 Release */

uint __fastcall state_case_normal_tchar(int param_1)

{
  int *piVar1;
  uint uVar2;
  undefined1 *puVar3;
  
  *(undefined1 *)(param_1 + 0x3c) = 0;
  puVar3 = *(undefined1 **)**(undefined4 **)(param_1 + 8);
  if ((*(ushort *)(puVar3 + (uint)*(byte *)(param_1 + 0x31) * 2) & 0x8000) != 0) {
    __crt_stdio_output::string_output_adapter<char>::write_character
              ((string_output_adapter<char> *)(param_1 + 0x448),*(byte *)(param_1 + 0x31),
               (int *)(param_1 + 0x18));
    *(undefined1 *)(param_1 + 0x31) = **(undefined1 **)(param_1 + 0x10);
    puVar3 = *(undefined1 **)(param_1 + 0x10) + 1;
    *(undefined1 **)(param_1 + 0x10) = puVar3;
    if (*(char *)(param_1 + 0x31) == '\0') {
      piVar1 = __errno();
      *piVar1 = 0x16;
      uVar2 = FUN_00465fa2();
      return uVar2 & 0xffffff00;
    }
  }
  return CONCAT31((int3)((uint)puVar3 >> 8),1);
}


