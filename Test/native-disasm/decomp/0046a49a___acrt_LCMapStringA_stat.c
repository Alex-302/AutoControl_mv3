// __acrt_LCMapStringA_stat @ 0046a49a size=541 callers=1

/* WARNING: Function: __alloca_probe_16 replaced with injection: alloca_probe */
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* Library Function - Single Match
    int __cdecl __acrt_LCMapStringA_stat(struct __crt_locale_pointers *,wchar_t const *,unsigned
   long,char const *,int,char *,int,int,int)
   
   Library: Visual Studio 2015 Release */

int __cdecl
__acrt_LCMapStringA_stat
          (__crt_locale_pointers *param_1,wchar_t *param_2,ulong param_3,char *param_4,int param_5,
          char *param_6,int param_7,int param_8,int param_9)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  LPCWSTR lpWideCharStr;
  LPCWSTR lpWideCharStr_00;
  
  iVar3 = param_5;
  if (0 < param_5) {
    iVar2 = ___strncnt(param_4,param_5);
    iVar3 = iVar2 + 1;
    if (param_5 <= iVar2) {
      iVar3 = iVar2;
    }
  }
  if (param_8 == 0) {
    param_8 = *(int *)(*(int *)param_1 + 8);
  }
  iVar2 = MultiByteToWideChar(param_8,(uint)(param_9 != 0) * 8 + 1,param_4,iVar3,(LPWSTR)0x0,0);
  if (iVar2 == 0) {
    return 0;
  }
  uVar1 = iVar2 * 2;
  if ((uVar1 + 8 & -(uint)(uVar1 < uVar1 + 8)) == 0) {
    lpWideCharStr = (LPCWSTR)0x0;
LAB_0046a567:
    if (((lpWideCharStr != (LPCWSTR)0x0) &&
        (iVar3 = MultiByteToWideChar(param_8,1,param_4,iVar3,lpWideCharStr,iVar2), iVar3 != 0)) &&
       (iVar3 = ___acrt_LCMapStringEx_36(param_2,param_3,lpWideCharStr,iVar2,(LPWSTR)0x0,0,0,0,0),
       iVar3 != 0)) {
      if ((param_3 & 0x400) == 0) {
        uVar1 = iVar3 * 2;
        if ((uVar1 + 8 & -(uint)(uVar1 < uVar1 + 8)) == 0) {
          lpWideCharStr_00 = (LPCWSTR)0x0;
LAB_0046a644:
          if ((lpWideCharStr_00 != (LPCWSTR)0x0) &&
             (iVar2 = ___acrt_LCMapStringEx_36
                                (param_2,param_3,lpWideCharStr,iVar2,lpWideCharStr_00,iVar3,0,0,0),
             iVar2 != 0)) {
            if (param_7 == 0) {
              param_7 = 0;
              param_6 = (LPSTR)0x0;
            }
            iVar3 = WideCharToMultiByte(param_8,0,lpWideCharStr_00,iVar3,param_6,param_7,(LPCSTR)0x0
                                        ,(LPBOOL)0x0);
            if (iVar3 != 0) {
              __freea_crt((int)lpWideCharStr_00);
              goto LAB_0046a689;
            }
          }
        }
        else if ((-(uint)(uVar1 < uVar1 + 8) & uVar1 + 8) < 0x401) {
          puVar4 = (undefined4 *)&stack0xffffffe8;
          lpWideCharStr_00 = (LPCWSTR)&stack0xffffffe8;
          if (&stack0x00000000 != (undefined1 *)0x18) {
LAB_0046a63d:
            lpWideCharStr_00 = (LPCWSTR)(puVar4 + 2);
            goto LAB_0046a644;
          }
        }
        else {
          puVar4 = __malloc_base(-(uint)(uVar1 < uVar1 + 8) & uVar1 + 8);
          lpWideCharStr_00 = (LPCWSTR)0x0;
          if (puVar4 != (undefined4 *)0x0) {
            *puVar4 = 0xdddd;
            goto LAB_0046a63d;
          }
        }
        __freea_crt((int)lpWideCharStr_00);
      }
      else if ((param_7 == 0) ||
              ((iVar3 <= param_7 &&
               (iVar3 = ___acrt_LCMapStringEx_36
                                  (param_2,param_3,lpWideCharStr,iVar2,(LPWSTR)param_6,param_7,0,0,0
                                  ), iVar3 != 0)))) goto LAB_0046a689;
    }
  }
  else if ((-(uint)(uVar1 < uVar1 + 8) & uVar1 + 8) < 0x401) {
    puVar4 = (undefined4 *)&stack0xffffffe8;
    lpWideCharStr = (LPCWSTR)&stack0xffffffe8;
    if (&stack0x00000000 != (undefined1 *)0x18) {
LAB_0046a560:
      lpWideCharStr = (LPCWSTR)(puVar4 + 2);
      goto LAB_0046a567;
    }
  }
  else {
    puVar4 = __malloc_base(-(uint)(uVar1 < uVar1 + 8) & uVar1 + 8);
    lpWideCharStr = (LPCWSTR)0x0;
    if (puVar4 != (undefined4 *)0x0) {
      *puVar4 = 0xdddd;
      goto LAB_0046a560;
    }
  }
  iVar3 = 0;
LAB_0046a689:
  __freea_crt((int)lpWideCharStr);
  return iVar3;
}


