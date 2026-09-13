// fp_format_f_internal @ 0046c2a2 size=215 callers=2

/* Library Function - Single Match
    int __cdecl fp_format_f_internal(char * const,unsigned int,int,struct _strflt *
   const,bool,struct __crt_locale_pointers * const)
   
   Library: Visual Studio 2015 Release */

int __cdecl
fp_format_f_internal
          (char *param_1,uint param_2,int param_3,_strflt *param_4,bool param_5,
          __crt_locale_pointers *param_6)

{
  int iVar1;
  int iVar2;
  char *pcVar3;
  int local_14;
  int local_10;
  char local_8;
  
  _LocaleUpdate::_LocaleUpdate((_LocaleUpdate *)&local_14,param_6);
  iVar1 = *(int *)(param_4 + 4);
  if ((param_5) && (iVar1 + -1 == param_3)) {
    iVar2 = *(int *)param_4;
    (param_1 + (uint)(iVar2 == 0x2d) + iVar1 + -1)[0] = '0';
    (param_1 + (uint)(iVar2 == 0x2d) + iVar1 + -1)[1] = '\0';
  }
  pcVar3 = param_1;
  if (*(int *)param_4 == 0x2d) {
    *param_1 = '-';
    pcVar3 = param_1 + 1;
  }
  if (*(int *)(param_4 + 4) < 1) {
    shift_bytes(param_1,param_2,pcVar3,1);
    *pcVar3 = '0';
    pcVar3 = pcVar3 + 1;
  }
  else {
    pcVar3 = pcVar3 + *(int *)(param_4 + 4);
  }
  if (0 < param_3) {
    shift_bytes(param_1,param_2,pcVar3,1);
    *pcVar3 = *(char *)**(undefined4 **)(local_10 + 0x88);
    iVar1 = *(int *)(param_4 + 4);
    if (iVar1 < 0) {
      if ((param_5) || (-iVar1 < param_3)) {
        param_3 = -iVar1;
      }
      shift_bytes(param_1,param_2,pcVar3 + 1,param_3);
      _memset(pcVar3 + 1,0x30,param_3);
    }
  }
  if (local_8 != '\0') {
    *(uint *)(local_14 + 0x350) = *(uint *)(local_14 + 0x350) & 0xfffffffd;
  }
  return 0;
}


