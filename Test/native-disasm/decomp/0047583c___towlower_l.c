// __towlower_l @ 0047583c size=201 callers=4

/* Library Function - Single Match
    __towlower_l
   
   Library: Visual Studio 2015 Release */

wint_t __cdecl __towlower_l(wint_t _C,_locale_t _Locale)

{
  int iVar1;
  undefined2 in_stack_00000006;
  int local_1c;
  int local_18;
  char local_10;
  WCHAR local_8 [2];
  
  if (_C == 0xffff) {
    return 0xffff;
  }
  _LocaleUpdate::_LocaleUpdate((_LocaleUpdate *)&local_1c,(__crt_locale_pointers *)_Locale);
  if (*(wchar_t **)(local_18 + 0xa8) == (wchar_t *)0x0) {
    if ((ushort)(_C - 0x41) < 0x1a) {
      __C = (uint)(ushort)(_C + 0x20);
    }
  }
  else {
    if (0xff < _C) {
      iVar1 = ___acrt_LCMapStringW(*(wchar_t **)(local_18 + 0xa8),0x100,(LPCWSTR)&_C,1,local_8,1);
      if (iVar1 == 0) {
        local_8[0] = (WCHAR)__C;
      }
      goto LAB_004758f1;
    }
    iVar1 = _iswctype(_C,1);
    if (iVar1 != 0) {
      local_8[0] = (WCHAR)*(byte *)(*(int *)(local_18 + 0x94) + (__C & 0xffff));
      goto LAB_004758f1;
    }
  }
  local_8[0] = (WCHAR)__C;
LAB_004758f1:
  if (local_10 != '\0') {
    *(uint *)(local_1c + 0x350) = *(uint *)(local_1c + 0x350) & 0xfffffffd;
  }
  return local_8[0];
}


