// common_configure_argv<char> @ 0046736f size=292 callers=1

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Library Function - Single Match
    int __cdecl common_configure_argv<char>(enum _crt_argv_mode)
   
   Library: Visual Studio 2015 Release */

int __cdecl common_configure_argv<char>(_crt_argv_mode param_1)

{
  int *piVar1;
  char **ppcVar2;
  char *pcVar3;
  char **ppcVar4;
  int iVar5;
  uint local_10;
  char **local_c;
  uint local_8;
  
  if ((param_1 == 2) || (param_1 == 1)) {
    ___acrt_initialize_multibyte();
    iVar5 = 0;
    GetModuleFileNameA((HMODULE)0x0,&DAT_0049f6b8,0x104);
    _DAT_0049f7f0 = &DAT_0049f6b8;
    if ((DAT_0049f7e8 == (char *)0x0) || (pcVar3 = DAT_0049f7e8, *DAT_0049f7e8 == '\0')) {
      pcVar3 = &DAT_0049f6b8;
    }
    local_8 = 0;
    local_10 = 0;
    parse_command_line<char>(pcVar3,(char **)0x0,(char *)0x0,&local_8,&local_10);
    ppcVar2 = ___acrt_allocate_buffer_for_argv(local_8,local_10,1);
    ppcVar4 = ppcVar2;
    if (ppcVar2 == (char **)0x0) {
      piVar1 = __errno();
      iVar5 = 0xc;
      *piVar1 = 0xc;
    }
    else {
      parse_command_line<char>(pcVar3,ppcVar2,(char *)(ppcVar2 + local_8),&local_8,&local_10);
      if (param_1 == 1) {
        _DAT_0049f7dc = local_8 - 1;
        ppcVar4 = (char **)0x0;
        DAT_0049f7e0 = ppcVar2;
      }
      else {
        local_c = (char **)0x0;
        iVar5 = FUN_004704dd((int *)ppcVar2,&local_c);
        ppcVar2 = local_c;
        if (iVar5 == 0) {
          _DAT_0049f7dc = 0;
          pcVar3 = *local_c;
          while (pcVar3 != (char *)0x0) {
            local_c = local_c + 1;
            _DAT_0049f7dc = _DAT_0049f7dc + 1;
            pcVar3 = *local_c;
          }
          local_c = (char **)0x0;
          iVar5 = 0;
          DAT_0049f7e0 = ppcVar2;
        }
        FID_conflict__free(local_c);
        local_c = (char **)0x0;
      }
    }
    FID_conflict__free(ppcVar4);
  }
  else {
    piVar1 = __errno();
    iVar5 = 0x16;
    *piVar1 = 0x16;
    FUN_00465fa2();
  }
  return iVar5;
}


