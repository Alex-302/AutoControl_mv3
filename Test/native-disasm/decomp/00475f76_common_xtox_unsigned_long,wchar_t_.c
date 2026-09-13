// common_xtox<unsigned_long,wchar_t> @ 00475f76 size=142 callers=1

/* Library Function - Single Match
    int __cdecl common_xtox<unsigned long,wchar_t>(unsigned long,wchar_t * const,unsigned
   int,unsigned int,bool)
   
   Library: Visual Studio 2015 Release */

int __cdecl
common_xtox<unsigned_long,wchar_t>
          (ulong param_1,wchar_t *param_2,uint param_3,uint param_4,bool param_5)

{
  short sVar1;
  wchar_t *pwVar2;
  wchar_t wVar3;
  int *piVar4;
  int iVar5;
  uint uVar6;
  wchar_t *pwVar7;
  wchar_t *pwVar8;
  
  pwVar7 = param_2;
  if (param_5) {
    *param_2 = L'-';
    pwVar7 = param_2 + 1;
    param_1 = -param_1;
  }
  uVar6 = (uint)param_5;
  pwVar2 = pwVar7;
  do {
    pwVar8 = pwVar2;
    sVar1 = (short)(param_1 % param_4);
    wVar3 = sVar1 + L'W';
    if (param_1 % param_4 < 10) {
      wVar3 = sVar1 + L'0';
    }
    *pwVar8 = wVar3;
    uVar6 = uVar6 + 1;
  } while ((param_1 / param_4 != 0) &&
          (param_1 = param_1 / param_4, pwVar2 = pwVar8 + 1, uVar6 < param_3));
  if (uVar6 < param_3) {
    pwVar8[1] = L'\0';
    do {
      wVar3 = *pwVar8;
      *pwVar8 = *pwVar7;
      pwVar8 = pwVar8 + -1;
      *pwVar7 = wVar3;
      pwVar7 = pwVar7 + 1;
    } while (pwVar7 < pwVar8);
    iVar5 = 0;
  }
  else {
    *param_2 = L'\0';
    piVar4 = __errno();
    iVar5 = 0x22;
    *piVar4 = 0x22;
    FUN_00465fa2();
  }
  return iVar5;
}


