// ___acrt_GetStringTypeA @ 0046e37a size=285 callers=4

/* WARNING: Function: __alloca_probe_16 replaced with injection: alloca_probe */
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* Library Function - Single Match
    ___acrt_GetStringTypeA
   
   Library: Visual Studio 2015 Release */

BOOL __cdecl
___acrt_GetStringTypeA
          (__crt_locale_pointers *param_1,DWORD param_2,LPCSTR param_3,int param_4,LPWORD param_5,
          UINT param_6,int param_7)

{
  uint _Size;
  undefined4 *puVar1;
  int cchSrc;
  LPCWSTR lpWideCharStr;
  BOOL BVar2;
  int local_1c;
  int local_18;
  char local_10;
  int local_c;
  uint local_8;
  
  local_8 = DAT_0049d070 ^ (uint)&stack0xfffffffc;
  _LocaleUpdate::_LocaleUpdate((_LocaleUpdate *)&local_1c,param_1);
  if (param_6 == 0) {
    param_6 = *(UINT *)(local_18 + 8);
  }
  BVar2 = 0;
  local_c = MultiByteToWideChar(param_6,(uint)(param_7 != 0) * 8 + 1,param_3,param_4,(LPWSTR)0x0,0);
  if (local_c == 0) goto LAB_0046e471;
  _Size = local_c * 2;
  if ((_Size + 8 & -(uint)(_Size < _Size + 8)) == 0) {
    lpWideCharStr = (LPCWSTR)0x0;
LAB_0046e432:
    if (lpWideCharStr != (LPCWSTR)0x0) {
      _memset(lpWideCharStr,0,_Size);
      cchSrc = MultiByteToWideChar(param_6,1,param_3,param_4,lpWideCharStr,local_c);
      if (cchSrc != 0) {
        BVar2 = GetStringTypeW(param_2,lpWideCharStr,cchSrc,param_5);
      }
    }
  }
  else if ((-(uint)(_Size < _Size + 8) & _Size + 8) < 0x401) {
    puVar1 = (undefined4 *)&stack0xffffffd8;
    lpWideCharStr = (LPCWSTR)&stack0xffffffd8;
    if (&stack0x00000000 != (undefined1 *)0x28) {
LAB_0046e42b:
      lpWideCharStr = (LPCWSTR)(puVar1 + 2);
      goto LAB_0046e432;
    }
  }
  else {
    puVar1 = __malloc_base(-(uint)(_Size < _Size + 8) & _Size + 8);
    lpWideCharStr = (LPCWSTR)0x0;
    if (puVar1 != (undefined4 *)0x0) {
      *puVar1 = 0xdddd;
      goto LAB_0046e42b;
    }
  }
  __freea_crt((int)lpWideCharStr);
LAB_0046e471:
  if (local_10 != '\0') {
    *(uint *)(local_1c + 0x350) = *(uint *)(local_1c + 0x350) & 0xfffffffd;
  }
  return BVar2;
}


