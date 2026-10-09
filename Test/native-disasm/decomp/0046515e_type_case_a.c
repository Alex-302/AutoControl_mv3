// type_case_a @ 0046515e size=346 callers=1

/* Library Function - Multiple Matches With Same Base Name
    private: bool __thiscall __crt_stdio_output::output_processor<char,class
   __crt_stdio_output::console_output_adapter<char>,class
   __crt_stdio_output::format_validation_base<char,class
   __crt_stdio_output::console_output_adapter<char> > >::type_case_a(void)
    private: bool __thiscall __crt_stdio_output::output_processor<char,class
   __crt_stdio_output::console_output_adapter<char>,class
   __crt_stdio_output::standard_base<char,class __crt_stdio_output::console_output_adapter<char> >
   >::type_case_a(void)
    private: bool __thiscall __crt_stdio_output::output_processor<char,class
   __crt_stdio_output::stream_output_adapter<char>,class
   __crt_stdio_output::format_validation_base<char,class
   __crt_stdio_output::stream_output_adapter<char> > >::type_case_a(void)
    private: bool __thiscall __crt_stdio_output::output_processor<char,class
   __crt_stdio_output::stream_output_adapter<char>,class
   __crt_stdio_output::standard_base<char,class __crt_stdio_output::stream_output_adapter<char> >
   >::type_case_a(void)
     6 names - too many to list
   
   Library: Visual Studio 2015 Release */

undefined4 __fastcall type_case_a(uint *param_1)

{
  formatting_buffer *this;
  char *pcVar1;
  char cVar2;
  bool bVar3;
  uint uVar4;
  formatting_buffer *pfVar5;
  int iVar6;
  char *pcVar7;
  uint uVar8;
  char *pcVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  __crt_locale_pointers *p_Var13;
  uint *local_c;
  uint *local_8;
  
  param_1[8] = param_1[8] | 0x10;
  if ((int)param_1[10] < 0) {
    if ((*(char *)((int)param_1 + 0x31) == 'a') || (*(char *)((int)param_1 + 0x31) == 'A')) {
      param_1[10] = 0xd;
    }
    else {
      param_1[10] = 6;
    }
  }
  else if ((param_1[10] == 0) &&
          ((*(char *)((int)param_1 + 0x31) == 'g' || (*(char *)((int)param_1 + 0x31) == 'G')))) {
    param_1[10] = 1;
  }
  this = (formatting_buffer *)(param_1 + 0x10);
  local_c = param_1;
  local_8 = param_1;
  bVar3 = __crt_stdio_output::formatting_buffer::ensure_buffer_is_big_enough<char>
                    (this,param_1[10] + 0x15d);
  if (!bVar3) {
    uVar4 = __crt_stdio_output::formatting_buffer::count<char>(this);
    param_1[10] = uVar4 - 0x15d;
  }
  pfVar5 = (formatting_buffer *)param_1[0x111];
  if ((formatting_buffer *)param_1[0x111] == (formatting_buffer *)0x0) {
    pfVar5 = this;
  }
  param_1[0xd] = (uint)pfVar5;
  param_1[5] = param_1[5] + 8;
  local_c = *(uint **)(param_1[5] - 8);
  local_8 = *(uint **)(param_1[5] - 4);
  uVar4 = __crt_stdio_output::formatting_buffer::count<char>(this);
  pfVar5 = (formatting_buffer *)param_1[0x111];
  if ((formatting_buffer *)param_1[0x111] == (formatting_buffer *)0x0) {
    pfVar5 = this;
  }
  p_Var13 = (__crt_locale_pointers *)param_1[2];
  iVar6 = (int)*(char *)((int)param_1 + 0x31);
  uVar12 = param_1[1];
  uVar11 = *param_1;
  uVar10 = param_1[10];
  pcVar7 = __crt_stdio_output::formatting_buffer::scratch_data<char>(this);
  uVar8 = __crt_stdio_output::formatting_buffer::count<char>(this);
  ___acrt_fp_format((double *)&local_c,(char *)pfVar5,uVar8,pcVar7,uVar4,iVar6,uVar10,uVar11,uVar12,
                    p_Var13);
  if (((param_1[8] >> 5 & 1) != 0) && (param_1[10] == 0)) {
    __crt_stdio_output::force_decimal_point
              ((char *)param_1[0xd],(__crt_locale_pointers *)param_1[2]);
  }
  if (((*(char *)((int)param_1 + 0x31) == 'g') || (*(char *)((int)param_1 + 0x31) == 'G')) &&
     ((param_1[8] >> 5 & 1) == 0)) {
    __crt_stdio_output::crop_zeroes((char *)param_1[0xd],(__crt_locale_pointers *)param_1[2]);
  }
  pcVar7 = (char *)param_1[0xd];
  if (*pcVar7 == '-') {
    param_1[8] = param_1[8] | 0x40;
    pcVar7 = pcVar7 + 1;
    param_1[0xd] = (uint)pcVar7;
  }
  pcVar9 = (char *)param_1[0xd];
  cVar2 = *pcVar9;
  if (((cVar2 == 'i') || (cVar2 == 'I')) || ((cVar2 == 'n' || (cVar2 == 'N')))) {
    *(undefined1 *)((int)param_1 + 0x31) = 0x73;
  }
  pcVar1 = pcVar9 + 1;
  do {
    cVar2 = *pcVar9;
    pcVar9 = pcVar9 + 1;
  } while (cVar2 != '\0');
  param_1[0xe] = (int)pcVar9 - (int)pcVar1;
  return CONCAT31((int3)((uint)pcVar7 >> 8),1);
}


