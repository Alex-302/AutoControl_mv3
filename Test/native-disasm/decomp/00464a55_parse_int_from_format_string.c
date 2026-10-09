// parse_int_from_format_string @ 00464a55 size=92 callers=2

/* Library Function - Multiple Matches With Same Base Name
    private: bool __thiscall __crt_stdio_output::output_processor<char,class
   __crt_stdio_output::console_output_adapter<char>,class
   __crt_stdio_output::format_validation_base<char,class
   __crt_stdio_output::console_output_adapter<char> > >::parse_int_from_format_string(int * const)
    private: bool __thiscall __crt_stdio_output::output_processor<char,class
   __crt_stdio_output::console_output_adapter<char>,class
   __crt_stdio_output::standard_base<char,class __crt_stdio_output::console_output_adapter<char> >
   >::parse_int_from_format_string(int * const)
    private: bool __thiscall __crt_stdio_output::output_processor<char,class
   __crt_stdio_output::stream_output_adapter<char>,class
   __crt_stdio_output::format_validation_base<char,class
   __crt_stdio_output::stream_output_adapter<char> > >::parse_int_from_format_string(int * const)
    private: bool __thiscall __crt_stdio_output::output_processor<char,class
   __crt_stdio_output::stream_output_adapter<char>,class
   __crt_stdio_output::standard_base<char,class __crt_stdio_output::stream_output_adapter<char> >
   >::parse_int_from_format_string(int * const)
     6 names - too many to list
   
   Library: Visual Studio 2015 Release */

uint __thiscall parse_int_from_format_string(void *this,long *param_1)

{
  int *piVar1;
  int iVar2;
  long lVar3;
  uint uVar4;
  int *piVar5;
  int *local_8;
  
  piVar1 = *(int **)((int)this + 0xc);
  iVar2 = *piVar1;
  *piVar1 = 0;
  local_8 = (int *)0x0;
  lVar3 = _strtol((char *)(*(int *)((int)this + 0x10) + -1),(char **)&local_8,10);
  *param_1 = lVar3;
  piVar5 = *(int **)((int)this + 0xc);
  if ((**(int **)((int)this + 0xc) == 0x22) ||
     (piVar5 = local_8, local_8 < *(int **)((int)this + 0x10))) {
    uVar4 = (uint)piVar5 & 0xffffff00;
  }
  else {
    *(int **)((int)this + 0x10) = local_8;
    uVar4 = CONCAT31((int3)((uint)local_8 >> 8),1);
  }
  if ((*piVar1 == 0) && (iVar2 != 0)) {
    *piVar1 = iVar2;
  }
  return uVar4;
}


