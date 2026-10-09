// write_requires_double_translation_nolock @ 0046b113 size=118 callers=1

/* Library Function - Single Match
    bool __cdecl write_requires_double_translation_nolock(int)
   
   Library: Visual Studio 2015 Release */

bool __cdecl write_requires_double_translation_nolock(int param_1)

{
  int iVar1;
  __acrt_ptd *p_Var2;
  BOOL BVar3;
  int iVar4;
  bool bVar5;
  DWORD local_8;
  
  iVar1 = __isatty(param_1);
  if (iVar1 == 0) {
    bVar5 = false;
  }
  else {
    iVar4 = param_1 >> 6;
    iVar1 = (param_1 & 0x3fU) * 0x30;
    if (((*(byte *)((&DAT_0049f8f8)[iVar4] + 0x28 + iVar1) & 0x80) == 0) ||
       ((p_Var2 = FUN_0046aa74(), *(int *)(*(int *)(p_Var2 + 0x4c) + 0xa8) == 0 &&
        (*(char *)((&DAT_0049f8f8)[iVar4] + 0x29 + iVar1) == '\0')))) {
      bVar5 = false;
    }
    else {
      BVar3 = GetConsoleMode(*(HANDLE *)((&DAT_0049f8f8)[iVar4] + 0x18 + iVar1),&local_8);
      bVar5 = BVar3 != 0;
    }
  }
  return bVar5;
}


