// type_case_n @ 00465492 size=116 callers=1

/* Library Function - Multiple Matches With Same Base Name
    private: bool __thiscall __crt_stdio_output::output_processor<char,class
   __crt_stdio_output::console_output_adapter<char>,class
   __crt_stdio_output::format_validation_base<char,class
   __crt_stdio_output::console_output_adapter<char> > >::type_case_n(void)
    private: bool __thiscall __crt_stdio_output::output_processor<char,class
   __crt_stdio_output::console_output_adapter<char>,class
   __crt_stdio_output::standard_base<char,class __crt_stdio_output::console_output_adapter<char> >
   >::type_case_n(void)
    private: bool __thiscall __crt_stdio_output::output_processor<char,class
   __crt_stdio_output::stream_output_adapter<char>,class
   __crt_stdio_output::format_validation_base<char,class
   __crt_stdio_output::stream_output_adapter<char> > >::type_case_n(void)
    private: bool __thiscall __crt_stdio_output::output_processor<char,class
   __crt_stdio_output::stream_output_adapter<char>,class
   __crt_stdio_output::standard_base<char,class __crt_stdio_output::stream_output_adapter<char> >
   >::type_case_n(void)
     6 names - too many to list
   
   Library: Visual Studio 2015 Release */

uint __fastcall type_case_n(int param_1)

{
  uint *puVar1;
  int iVar2;
  int *piVar3;
  uint uVar4;
  
  *(int *)(param_1 + 0x14) = *(int *)(param_1 + 0x14) + 4;
  puVar1 = *(uint **)(*(int *)(param_1 + 0x14) + -4);
  iVar2 = __get_printf_count_output();
  if (iVar2 == 0) {
LAB_004654ab:
    piVar3 = __errno();
    *piVar3 = 0x16;
    uVar4 = FUN_00465fa2();
    uVar4 = uVar4 & 0xffffff00;
  }
  else {
    uVar4 = __crt_stdio_output::to_integer_size(*(length_modifier *)(param_1 + 0x2c));
    if (uVar4 == 1) {
      uVar4 = 0;
      *(undefined1 *)puVar1 = *(undefined1 *)(param_1 + 0x18);
    }
    else if (uVar4 == 2) {
      uVar4 = (uint)*(ushort *)(param_1 + 0x18);
      *(ushort *)puVar1 = *(ushort *)(param_1 + 0x18);
    }
    else if (uVar4 == 4) {
      uVar4 = *(uint *)(param_1 + 0x18);
      *puVar1 = uVar4;
    }
    else {
      if (uVar4 != 8) goto LAB_004654ab;
      uVar4 = *(uint *)(param_1 + 0x18);
      *puVar1 = uVar4;
      puVar1[1] = (int)uVar4 >> 0x1f;
    }
    *(undefined1 *)(param_1 + 0x30) = 1;
    uVar4 = CONCAT31((int3)(uVar4 >> 8),1);
  }
  return uVar4;
}


