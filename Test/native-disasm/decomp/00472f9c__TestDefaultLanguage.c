// _TestDefaultLanguage @ 00472f9c size=112 callers=3

/* Library Function - Single Match
    _TestDefaultLanguage
   
   Library: Visual Studio 2015 Release */

undefined4 __cdecl _TestDefaultLanguage(uint param_1,int param_2)

{
  short *psVar1;
  short sVar2;
  __acrt_ptd *p_Var3;
  int iVar4;
  undefined4 uVar5;
  short *psVar6;
  uint local_8;
  
  p_Var3 = FUN_0046aa74();
  iVar4 = GetLocaleInfoW(param_1 & 0x3ff | 0x400,0x20000001,(LPWSTR)&local_8,2);
  if (iVar4 == 0) {
LAB_00472fd2:
    uVar5 = 0;
  }
  else {
    if ((param_1 != local_8) && (param_2 != 0)) {
      psVar6 = *(short **)(p_Var3 + 0x50);
      psVar1 = psVar6 + 1;
      do {
        sVar2 = *psVar6;
        psVar6 = psVar6 + 1;
      } while (sVar2 != 0);
      iVar4 = _GetPrimaryLen(*(ushort **)(p_Var3 + 0x50));
      if (iVar4 == (int)psVar6 - (int)psVar1 >> 1) goto LAB_00472fd2;
    }
    uVar5 = 1;
  }
  return uVar5;
}


