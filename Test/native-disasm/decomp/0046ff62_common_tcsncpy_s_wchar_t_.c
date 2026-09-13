// common_tcsncpy_s<wchar_t> @ 0046ff62 size=205 callers=1

/* Library Function - Single Match
    int __cdecl common_tcsncpy_s<wchar_t>(wchar_t * const,unsigned int,wchar_t const *
   const,unsigned int)
   
   Library: Visual Studio 2015 Release */

int __cdecl common_tcsncpy_s<wchar_t>(wchar_t *param_1,uint param_2,wchar_t *param_3,uint param_4)

{
  wchar_t wVar1;
  int *piVar2;
  uint uVar3;
  uint uVar4;
  wchar_t *pwVar5;
  int iVar6;
  
  if (param_4 == 0) {
    if (param_1 == (wchar_t *)0x0) {
      if (param_2 == 0) {
        return 0;
      }
    }
    else {
LAB_0046ff84:
      if (param_2 != 0) {
        if (param_4 == 0) {
          *param_1 = L'\0';
          return 0;
        }
        if (param_3 != (wchar_t *)0x0) {
          uVar3 = param_4;
          uVar4 = param_2;
          pwVar5 = param_1;
          if (param_4 == 0xffffffff) {
            do {
              wVar1 = *(wchar_t *)(((int)param_3 - (int)param_1) + (int)pwVar5);
              *pwVar5 = wVar1;
              pwVar5 = pwVar5 + 1;
              if (wVar1 == L'\0') break;
              uVar4 = uVar4 - 1;
            } while (uVar4 != 0);
          }
          else {
            do {
              wVar1 = *(wchar_t *)(((int)param_3 - (int)param_1) + (int)pwVar5);
              *pwVar5 = wVar1;
              pwVar5 = pwVar5 + 1;
              if ((wVar1 == L'\0') || (uVar4 = uVar4 - 1, uVar4 == 0)) break;
              uVar3 = uVar3 - 1;
            } while (uVar3 != 0);
            if (uVar3 == 0) {
              *pwVar5 = L'\0';
            }
          }
          if (uVar4 != 0) {
            return 0;
          }
          if (param_4 == 0xffffffff) {
            param_1[param_2 - 1] = L'\0';
            return 0x50;
          }
          *param_1 = L'\0';
          piVar2 = __errno();
          iVar6 = 0x22;
          goto LAB_0046ffa9;
        }
        *param_1 = L'\0';
      }
    }
  }
  else if (param_1 != (wchar_t *)0x0) goto LAB_0046ff84;
  piVar2 = __errno();
  iVar6 = 0x16;
LAB_0046ffa9:
  *piVar2 = iVar6;
  FUN_00465fa2();
  return iVar6;
}


