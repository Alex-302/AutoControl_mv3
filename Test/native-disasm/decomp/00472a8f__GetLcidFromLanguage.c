// _GetLcidFromLanguage @ 00472a8f size=97 callers=2

/* Library Function - Single Match
    _GetLcidFromLanguage
   
   Library: Visual Studio 2015 Release */

void __cdecl _GetLcidFromLanguage(byte *param_1)

{
  short *psVar1;
  short sVar2;
  __acrt_ptd *p_Var3;
  uint uVar4;
  int iVar5;
  short *psVar6;
  
  p_Var3 = FUN_0046aa74();
  iVar5 = 2;
  psVar6 = *(short **)(p_Var3 + 0x50);
  psVar1 = psVar6 + 1;
  do {
    sVar2 = *psVar6;
    psVar6 = psVar6 + 1;
  } while (sVar2 != 0);
  uVar4 = (uint)((int)psVar6 - (int)psVar1 >> 1 == 3);
  *(uint *)(p_Var3 + 0x60) = uVar4;
  if (uVar4 == 0) {
    iVar5 = _GetPrimaryLen(*(ushort **)(p_Var3 + 0x50));
  }
  *(int *)(p_Var3 + 0x5c) = iVar5;
  EnumSystemLocalesW(_LanguageEnumProc_4,1);
  if ((*param_1 & 4) == 0) {
    param_1[0] = 0;
    param_1[1] = 0;
    param_1[2] = 0;
    param_1[3] = 0;
  }
  return;
}


