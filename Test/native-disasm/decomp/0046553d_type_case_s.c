// type_case_s @ 0046553d size=115 callers=1

/* Library Function - Multiple Matches With Same Base Name
    private: bool __thiscall __crt_stdio_output::output_processor<char,class
   __crt_stdio_output::console_output_adapter<char>,class
   __crt_stdio_output::format_validation_base<char,class
   __crt_stdio_output::console_output_adapter<char> > >::type_case_s(void)
    private: bool __thiscall __crt_stdio_output::output_processor<char,class
   __crt_stdio_output::console_output_adapter<char>,class
   __crt_stdio_output::standard_base<char,class __crt_stdio_output::console_output_adapter<char> >
   >::type_case_s(void)
    private: bool __thiscall __crt_stdio_output::output_processor<char,class
   __crt_stdio_output::stream_output_adapter<char>,class
   __crt_stdio_output::format_validation_base<char,class
   __crt_stdio_output::stream_output_adapter<char> > >::type_case_s(void)
    private: bool __thiscall __crt_stdio_output::output_processor<char,class
   __crt_stdio_output::stream_output_adapter<char>,class
   __crt_stdio_output::standard_base<char,class __crt_stdio_output::stream_output_adapter<char> >
   >::type_case_s(void)
     6 names - too many to list
   
   Libraries: Visual Studio 2015 Debug, Visual Studio 2015 Release */

undefined4 __fastcall type_case_s(__uint64 *param_1)

{
  int iVar1;
  bool bVar2;
  uint uVar3;
  
  *(int *)((int)param_1 + 0x14) = *(int *)((int)param_1 + 0x14) + 4;
  uVar3 = (uint)param_1[5];
  iVar1 = *(int *)(*(int *)((int)param_1 + 0x14) + -4);
  *(int *)((int)param_1 + 0x34) = iVar1;
  if (uVar3 == 0xffffffff) {
    uVar3 = 0x7fffffff;
  }
  bVar2 = __crt_stdio_output::is_wide_character_specifier<char>
                    (*param_1,*(char *)((int)param_1 + 0x31),
                     *(length_modifier *)((int)param_1 + 0x2c));
  if (bVar2) {
    if (iVar1 == 0) {
      *(wchar_t **)((int)param_1 + 0x34) = L"(null)";
    }
    *(undefined1 *)((int)param_1 + 0x3c) = 1;
    uVar3 = FUN_00466f34(*(short **)((int)param_1 + 0x34),uVar3);
  }
  else {
    if (iVar1 == 0) {
      *(char **)((int)param_1 + 0x34) = "(null)";
    }
    uVar3 = FUN_00466e0d(*(char **)((int)param_1 + 0x34),uVar3);
  }
  *(uint *)(param_1 + 7) = uVar3;
  return CONCAT31((int3)(uVar3 >> 8),1);
}


