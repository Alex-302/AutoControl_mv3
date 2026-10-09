// _wcstombs_l_helper @ 0046e713 size=641 callers=1

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* Library Function - Single Match
    unsigned int __cdecl _wcstombs_l_helper(char *,wchar_t const *,unsigned int,struct
   __crt_locale_pointers *)
   
   Library: Visual Studio 2015 Release */

uint __cdecl
_wcstombs_l_helper(char *param_1,wchar_t *param_2,uint param_3,__crt_locale_pointers *param_4)

{
  char cVar1;
  wchar_t wVar2;
  int *piVar3;
  wchar_t *pwVar4;
  int iVar5;
  DWORD DVar6;
  uint uVar7;
  uint uVar8;
  int local_30;
  int local_2c;
  char local_24;
  int local_20;
  char *local_1c;
  wchar_t *local_18;
  BOOL local_14;
  CHAR local_10 [8];
  uint local_8;
  
  local_8 = DAT_0049d070 ^ (uint)&stack0xfffffffc;
  uVar8 = 0;
  local_1c = param_1;
  local_14 = 0;
  local_18 = param_2;
  if ((param_1 != (char *)0x0) && (param_3 == 0)) {
    return 0;
  }
  if (param_2 == (wchar_t *)0x0) {
    piVar3 = __errno();
    *piVar3 = 0x16;
    FUN_00465fa2();
    return 0xffffffff;
  }
  _LocaleUpdate::_LocaleUpdate((_LocaleUpdate *)&local_30,param_4);
  if (local_1c == (LPSTR)0x0) {
    if (*(int *)(local_2c + 0xa8) == 0) {
      wVar2 = *param_2;
      while (wVar2 != L'\0') {
        if (0xff < (ushort)wVar2) goto LAB_0046e963;
        param_2 = param_2 + 1;
        uVar8 = uVar8 + 1;
        wVar2 = *param_2;
      }
    }
    else {
      iVar5 = WideCharToMultiByte(*(UINT *)(local_2c + 8),0,param_2,-1,(LPSTR)0x0,0,(LPCSTR)0x0,
                                  &local_14);
      if ((iVar5 == 0) || (local_14 != 0)) {
LAB_0046e963:
        piVar3 = __errno();
        uVar8 = 0xffffffff;
        *piVar3 = 0x2a;
      }
      else {
        uVar8 = iVar5 - 1;
      }
    }
  }
  else if (*(int *)(local_2c + 0xa8) == 0) {
    if (param_3 != 0) {
      do {
        if (0xff < (ushort)*param_2) goto LAB_0046e904;
        local_1c[uVar8] = (CHAR)*param_2;
        wVar2 = *param_2;
        param_2 = param_2 + 1;
      } while ((wVar2 != L'\0') && (uVar8 = uVar8 + 1, uVar8 < param_3));
    }
  }
  else {
    if (*(int *)(local_2c + 4) == 1) {
      if (param_3 != 0) {
        local_18 = (wchar_t *)param_3;
        pwVar4 = param_2;
        do {
          if (*pwVar4 == L'\0') break;
          pwVar4 = pwVar4 + 1;
          local_18 = (wchar_t *)((int)local_18 + -1);
        } while (local_18 != (wchar_t *)0x0);
        if ((local_18 != (wchar_t *)0x0) && (*pwVar4 == L'\0')) {
          param_3 = ((int)pwVar4 - (int)param_2 >> 1) + 1;
        }
      }
      uVar8 = WideCharToMultiByte(*(UINT *)(local_2c + 8),0,param_2,param_3,local_1c,param_3,
                                  (LPCSTR)0x0,&local_14);
      if ((uVar8 != 0) && (local_14 == 0)) {
        if (local_1c[uVar8 - 1] == '\0') {
          uVar8 = uVar8 - 1;
        }
        goto LAB_0046e971;
      }
    }
    else {
      iVar5 = WideCharToMultiByte(*(UINT *)(local_2c + 8),0,param_2,-1,local_1c,param_3,(LPCSTR)0x0,
                                  &local_14);
      if (iVar5 == 0) {
        if ((local_14 == 0) && (DVar6 = GetLastError(), DVar6 == 0x7a)) {
          uVar8 = 0;
          if (param_3 != 0) {
            do {
              iVar5 = *(int *)(local_2c + 4);
              if (5 < iVar5) {
                iVar5 = 5;
              }
              uVar7 = WideCharToMultiByte(*(UINT *)(local_2c + 8),0,local_18,1,local_10,iVar5,
                                          (LPCSTR)0x0,&local_14);
              if ((((uVar7 == 0) || (local_14 != 0)) || ((int)uVar7 < 0)) || (5 < uVar7))
              goto LAB_0046e963;
              if (param_3 < uVar7 + uVar8) break;
              local_20 = 0;
              if (0 < (int)uVar7) {
                do {
                  cVar1 = local_10[local_20];
                  local_1c[uVar8] = cVar1;
                  if (cVar1 == '\0') goto LAB_0046e971;
                  local_20 = local_20 + 1;
                  uVar8 = uVar8 + 1;
                } while (local_20 < (int)uVar7);
              }
              local_18 = local_18 + 1;
            } while (uVar8 < param_3);
          }
          goto LAB_0046e971;
        }
      }
      else if (local_14 == 0) {
        uVar8 = iVar5 - 1;
        goto LAB_0046e971;
      }
    }
LAB_0046e904:
    piVar3 = __errno();
    uVar8 = 0xffffffff;
    *piVar3 = 0x2a;
  }
LAB_0046e971:
  if (local_24 != '\0') {
    *(uint *)(local_30 + 0x350) = *(uint *)(local_30 + 0x350) & 0xfffffffd;
  }
  return uVar8;
}


