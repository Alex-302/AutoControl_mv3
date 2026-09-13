// _GetLcidFromLangCountry @ 004729f4 size=155 callers=2

/* Library Function - Single Match
    _GetLcidFromLangCountry
   
   Library: Visual Studio 2015 Release */

void __cdecl _GetLcidFromLangCountry(uint *param_1)

{
  short *psVar1;
  short sVar2;
  uint uVar3;
  __acrt_ptd *p_Var4;
  int iVar5;
  short *psVar6;
  short *psVar7;
  
  p_Var4 = FUN_0046aa74();
  iVar5 = 2;
  psVar6 = *(short **)(p_Var4 + 0x50);
  psVar1 = psVar6 + 1;
  do {
    sVar2 = *psVar6;
    psVar6 = psVar6 + 1;
  } while (sVar2 != 0);
  psVar7 = *(short **)(p_Var4 + 0x54);
  *(uint *)(p_Var4 + 0x60) = (uint)((int)psVar6 - (int)psVar1 >> 1 == 3);
  psVar1 = psVar7 + 1;
  do {
    sVar2 = *psVar7;
    psVar7 = psVar7 + 1;
  } while (sVar2 != 0);
  *(uint *)(p_Var4 + 100) = (uint)((int)psVar7 - (int)psVar1 >> 1 == 3);
  param_1[1] = 0;
  if (*(int *)(p_Var4 + 0x60) == 0) {
    iVar5 = _GetPrimaryLen(*(ushort **)(p_Var4 + 0x50));
  }
  *(int *)(p_Var4 + 0x5c) = iVar5;
  EnumSystemLocalesW(_LangCountryEnumProc_4,1);
  uVar3 = *param_1;
  if ((uVar3 >> 8 & 1) == 0 || ((uVar3 & 7) == 0 || (uVar3 >> 9 & 1) == 0)) {
    *param_1 = 0;
  }
  return;
}


