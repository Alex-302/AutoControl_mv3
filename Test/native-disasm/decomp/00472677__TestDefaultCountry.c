// _TestDefaultCountry @ 00472677 size=75 callers=2

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* Library Function - Single Match
    _TestDefaultCountry
   
   Library: Visual Studio 2015 Release */

bool __cdecl _TestDefaultCountry(wchar_t *param_1)

{
  int iVar1;
  bool bVar2;
  WCHAR local_1c [10];
  uint local_8;
  
  local_8 = DAT_0049d070 ^ (uint)&stack0xfffffffc;
  iVar1 = ___acrt_GetLocaleInfoEx_16(param_1,0x59,local_1c,9);
  bVar2 = false;
  if (iVar1 != 0) {
    iVar1 = _wcsncmp(local_1c,param_1,9);
    bVar2 = iVar1 == 0;
  }
  return bVar2;
}


