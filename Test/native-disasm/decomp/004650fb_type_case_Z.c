// type_case_Z @ 004650fb size=99 callers=1

/* Library Function - Multiple Matches With Same Base Name
    private: bool __thiscall __crt_stdio_output::output_processor<char,class
   __crt_stdio_output::console_output_adapter<char>,class
   __crt_stdio_output::format_validation_base<char,class
   __crt_stdio_output::console_output_adapter<char> > >::type_case_Z(void)
    private: bool __thiscall __crt_stdio_output::output_processor<char,class
   __crt_stdio_output::console_output_adapter<char>,class
   __crt_stdio_output::standard_base<char,class __crt_stdio_output::console_output_adapter<char> >
   >::type_case_Z(void)
    private: bool __thiscall __crt_stdio_output::output_processor<char,class
   __crt_stdio_output::stream_output_adapter<char>,class
   __crt_stdio_output::format_validation_base<char,class
   __crt_stdio_output::stream_output_adapter<char> > >::type_case_Z(void)
    private: bool __thiscall __crt_stdio_output::output_processor<char,class
   __crt_stdio_output::stream_output_adapter<char>,class
   __crt_stdio_output::standard_base<char,class __crt_stdio_output::stream_output_adapter<char> >
   >::type_case_Z(void)
     6 names - too many to list
   
   Libraries: Visual Studio 2015 Debug, Visual Studio 2015 Release */

undefined4 __fastcall type_case_Z(__uint64 *param_1)

{
  ushort *puVar1;
  int iVar2;
  bool bVar3;
  uint uVar4;
  
  *(int *)((int)param_1 + 0x14) = *(int *)((int)param_1 + 0x14) + 4;
  uVar4 = *(uint *)((int)param_1 + 0x14);
  puVar1 = *(ushort **)(uVar4 - 4);
  if ((puVar1 == (ushort *)0x0) || (iVar2 = *(int *)(puVar1 + 2), iVar2 == 0)) {
    *(char **)((int)param_1 + 0x34) = "(null)";
    *(undefined4 *)(param_1 + 7) = 6;
  }
  else {
    bVar3 = __crt_stdio_output::is_wide_character_specifier<char>
                      (*param_1,*(char *)((int)param_1 + 0x31),
                       *(length_modifier *)((int)param_1 + 0x2c));
    *(int *)((int)param_1 + 0x34) = iVar2;
    uVar4 = (uint)*puVar1;
    if (bVar3) {
      uVar4 = (uint)(*puVar1 >> 1);
      *(uint *)(param_1 + 7) = uVar4;
      *(undefined1 *)((int)param_1 + 0x3c) = 1;
      goto LAB_00465158;
    }
    *(uint *)(param_1 + 7) = uVar4;
  }
  *(undefined1 *)((int)param_1 + 0x3c) = 0;
LAB_00465158:
  return CONCAT31((int3)(uVar4 >> 8),1);
}


