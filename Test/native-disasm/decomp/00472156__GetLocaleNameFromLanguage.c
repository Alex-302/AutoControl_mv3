// _GetLocaleNameFromLanguage @ 00472156 size=91 callers=2

/* Library Function - Single Match
    _GetLocaleNameFromLanguage
   
   Library: Visual Studio 2015 Release */

void __cdecl _GetLocaleNameFromLanguage(undefined4 *param_1)

{
  short *psVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  short *psVar5;
  
  iVar4 = 2;
  psVar5 = (short *)*param_1;
  psVar1 = psVar5 + 1;
  do {
    sVar2 = *psVar5;
    psVar5 = psVar5 + 1;
  } while (sVar2 != 0);
  uVar3 = (uint)((int)psVar5 - (int)psVar1 >> 1 == 3);
  param_1[4] = uVar3;
  if (uVar3 == 0) {
    iVar4 = _GetPrimaryLen((ushort *)*param_1);
  }
  param_1[3] = iVar4;
  ___acrt_EnumSystemLocalesEx_16(FUN_004724cf,3,0,0);
  if ((*(byte *)(param_1 + 2) & 4) == 0) {
    param_1[2] = 0;
  }
  return;
}


