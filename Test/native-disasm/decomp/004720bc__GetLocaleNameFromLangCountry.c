// _GetLocaleNameFromLangCountry @ 004720bc size=154 callers=2

/* Library Function - Single Match
    _GetLocaleNameFromLangCountry
   
   Library: Visual Studio 2015 Release */

void __cdecl _GetLocaleNameFromLangCountry(undefined4 *param_1)

{
  short *psVar1;
  short sVar2;
  int iVar3;
  short *psVar4;
  short *psVar5;
  uint uVar6;
  
  iVar3 = 2;
  psVar4 = (short *)*param_1;
  psVar1 = psVar4 + 1;
  do {
    sVar2 = *psVar4;
    psVar4 = psVar4 + 1;
  } while (sVar2 != 0);
  psVar5 = (short *)param_1[1];
  uVar6 = (uint)((int)psVar4 - (int)psVar1 >> 1 == 3);
  param_1[4] = uVar6;
  psVar1 = psVar5 + 1;
  do {
    sVar2 = *psVar5;
    psVar5 = psVar5 + 1;
  } while (sVar2 != 0);
  param_1[5] = (uint)((int)psVar5 - (int)psVar1 >> 1 == 3);
  if (uVar6 == 0) {
    iVar3 = _GetPrimaryLen((ushort *)*param_1);
  }
  param_1[3] = iVar3;
  ___acrt_EnumSystemLocalesEx_16(FUN_004721e5,3,0,0);
  uVar6 = param_1[2];
  if ((uVar6 >> 8 & 1) == 0 || ((uVar6 & 7) == 0 || (uVar6 >> 9 & 1) == 0)) {
    param_1[2] = 0;
  }
  return;
}


