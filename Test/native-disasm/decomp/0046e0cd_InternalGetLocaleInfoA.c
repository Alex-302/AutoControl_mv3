// InternalGetLocaleInfoA @ 0046e0cd size=251 callers=3

/* WARNING: Function: __alloca_probe_16 replaced with injection: alloca_probe */
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* Library Function - Single Match
    int __cdecl InternalGetLocaleInfoA(struct __crt_locale_pointers * const,wchar_t const *
   const,unsigned long,char * const,int)
   
   Library: Visual Studio 2015 Release */

int __cdecl
InternalGetLocaleInfoA
          (__crt_locale_pointers *param_1,wchar_t *param_2,ulong param_3,char *param_4,int param_5)

{
  uint uVar1;
  int iVar2;
  undefined4 *puVar3;
  LPWSTR lpWideCharStr;
  int iVar4;
  int local_1c;
  int local_18;
  char local_10;
  UINT local_c;
  uint local_8;
  
  local_8 = DAT_0049d070 ^ (uint)&stack0xfffffffc;
  _LocaleUpdate::_LocaleUpdate((_LocaleUpdate *)&local_1c,param_1);
  iVar4 = 0;
  local_c = *(UINT *)(local_18 + 8);
  iVar2 = ___acrt_GetLocaleInfoEx_16(param_2,param_3,(LPWSTR)0x0,0);
  if (iVar2 == 0) goto LAB_0046e1a2;
  uVar1 = iVar2 * 2;
  if ((uVar1 + 8 & -(uint)(uVar1 < uVar1 + 8)) == 0) {
    lpWideCharStr = (LPWSTR)0x0;
LAB_0046e169:
    if ((lpWideCharStr != (LPWSTR)0x0) &&
       (iVar2 = ___acrt_GetLocaleInfoEx_16(param_2,param_3,lpWideCharStr,iVar2), iVar2 != 0)) {
      iVar4 = WideCharToMultiByte(local_c,0,lpWideCharStr,-1,
                                  (LPSTR)(-(uint)(param_5 != 0) & (uint)param_4),param_5,(LPCSTR)0x0
                                  ,(LPBOOL)0x0);
    }
  }
  else if ((-(uint)(uVar1 < uVar1 + 8) & uVar1 + 8) < 0x401) {
    puVar3 = (undefined4 *)&stack0xffffffd8;
    lpWideCharStr = (LPWSTR)&stack0xffffffd8;
    if (&stack0x00000000 != (undefined1 *)0x28) {
LAB_0046e162:
      lpWideCharStr = (LPWSTR)(puVar3 + 2);
      goto LAB_0046e169;
    }
  }
  else {
    puVar3 = __malloc_base(-(uint)(uVar1 < uVar1 + 8) & uVar1 + 8);
    lpWideCharStr = (LPWSTR)0x0;
    if (puVar3 != (undefined4 *)0x0) {
      *puVar3 = 0xdddd;
      goto LAB_0046e162;
    }
  }
  __freea_crt((int)lpWideCharStr);
LAB_0046e1a2:
  if (local_10 != '\0') {
    *(uint *)(local_1c + 0x350) = *(uint *)(local_1c + 0x350) & 0xfffffffd;
  }
  return iVar4;
}


