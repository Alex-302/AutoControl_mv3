// type_case_integer @ 00465348 size=330 callers=3

/* Library Function - Multiple Matches With Same Base Name
    private: bool __thiscall __crt_stdio_output::output_processor<char,class
   __crt_stdio_output::console_output_adapter<char>,class
   __crt_stdio_output::format_validation_base<char,class
   __crt_stdio_output::console_output_adapter<char> > >::type_case_integer(unsigned int,bool)
    private: bool __thiscall __crt_stdio_output::output_processor<char,class
   __crt_stdio_output::console_output_adapter<char>,class
   __crt_stdio_output::standard_base<char,class __crt_stdio_output::console_output_adapter<char> >
   >::type_case_integer(unsigned int,bool)
    private: bool __thiscall __crt_stdio_output::output_processor<char,class
   __crt_stdio_output::stream_output_adapter<char>,class
   __crt_stdio_output::format_validation_base<char,class
   __crt_stdio_output::stream_output_adapter<char> > >::type_case_integer(unsigned int,bool)
    private: bool __thiscall __crt_stdio_output::output_processor<char,class
   __crt_stdio_output::stream_output_adapter<char>,class
   __crt_stdio_output::standard_base<char,class __crt_stdio_output::stream_output_adapter<char> >
   >::type_case_integer(unsigned int,bool)
     6 names - too many to list
   
   Library: Visual Studio 2015 Release */

uint __thiscall type_case_integer(void *this,uint param_1,char param_2)

{
  uint uVar1;
  int *piVar2;
  char *pcVar3;
  uint uVar4;
  int iVar5;
  bool bVar6;
  
  uVar1 = __crt_stdio_output::to_integer_size(*(length_modifier *)((int)this + 0x2c));
  if (uVar1 == 1) {
    *(int *)((int)this + 0x14) = *(int *)((int)this + 0x14) + 4;
    if ((*(uint *)((int)this + 0x20) >> 4 & 1) == 0) {
      uVar4 = (uint)*(byte *)(*(int *)((int)this + 0x14) + -4);
    }
    else {
      uVar4 = (uint)*(char *)(*(int *)((int)this + 0x14) + -4);
    }
  }
  else if (uVar1 == 2) {
    *(int *)((int)this + 0x14) = *(int *)((int)this + 0x14) + 4;
    if ((*(uint *)((int)this + 0x20) >> 4 & 1) == 0) {
      uVar4 = (uint)*(ushort *)(*(int *)((int)this + 0x14) + -4);
    }
    else {
      uVar4 = (uint)*(short *)(*(int *)((int)this + 0x14) + -4);
    }
  }
  else {
    if (uVar1 != 4) {
      if (uVar1 != 8) {
        piVar2 = __errno();
        *piVar2 = 0x16;
        uVar1 = FUN_00465fa2();
        return uVar1 & 0xffffff00;
      }
      *(int *)((int)this + 0x14) = *(int *)((int)this + 0x14) + 8;
      uVar4 = *(uint *)(*(int *)((int)this + 0x14) + -8);
      iVar5 = *(int *)(*(int *)((int)this + 0x14) + -4);
      goto LAB_004653f9;
    }
    *(int *)((int)this + 0x14) = *(int *)((int)this + 0x14) + 4;
    if ((*(uint *)((int)this + 0x20) >> 4 & 1) == 0) {
      uVar4 = *(uint *)(*(int *)((int)this + 0x14) + -4);
      iVar5 = 0;
      goto LAB_004653f9;
    }
    uVar4 = *(uint *)(*(int *)((int)this + 0x14) + -4);
  }
  iVar5 = (int)uVar4 >> 0x1f;
LAB_004653f9:
  if ((((*(uint *)((int)this + 0x20) >> 4 & 1) != 0) && (iVar5 < 1)) && (iVar5 < 0)) {
    bVar6 = uVar4 != 0;
    uVar4 = -uVar4;
    iVar5 = -(iVar5 + (uint)bVar6);
    *(uint *)((int)this + 0x20) = *(uint *)((int)this + 0x20) | 0x40;
  }
  if (*(int *)((int)this + 0x28) < 0) {
    *(undefined4 *)((int)this + 0x28) = 1;
  }
  else {
    *(uint *)((int)this + 0x20) = *(uint *)((int)this + 0x20) & 0xfffffff7;
    if (0x200 < *(int *)((int)this + 0x28)) {
      *(undefined4 *)((int)this + 0x28) = 0x200;
    }
  }
  if (uVar4 == 0 && iVar5 == 0) {
    *(uint *)((int)this + 0x20) = *(uint *)((int)this + 0x20) & 0xffffffdf;
  }
  if (uVar1 == 8) {
    type_case_integer_parse_into_buffer<>(this,CONCAT44(iVar5,uVar4),param_1,param_2);
  }
  else {
    type_case_integer_parse_into_buffer<>(this,uVar4,param_1,param_2);
  }
  pcVar3 = (char *)(*(uint *)((int)this + 0x20) >> 7);
  if ((((uint)pcVar3 & 1) != 0) &&
     ((*(int *)((int)this + 0x38) == 0 || (pcVar3 = *(char **)((int)this + 0x34), *pcVar3 != '0'))))
  {
    *(int *)((int)this + 0x34) = *(int *)((int)this + 0x34) + -1;
    **(undefined1 **)((int)this + 0x34) = 0x30;
    *(int *)((int)this + 0x38) = *(int *)((int)this + 0x38) + 1;
  }
  return CONCAT31((int3)((uint)pcVar3 >> 8),1);
}


