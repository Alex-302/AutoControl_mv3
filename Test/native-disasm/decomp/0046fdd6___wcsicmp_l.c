// __wcsicmp_l @ 0046fdd6 size=224 callers=1

/* Library Function - Single Match
    __wcsicmp_l
   
   Library: Visual Studio 2015 Release */

int __cdecl __wcsicmp_l(wchar_t *_Str1,wchar_t *_Str2,_locale_t _Locale)

{
  wchar_t wVar1;
  wchar_t wVar2;
  int *piVar3;
  int iVar4;
  int local_14;
  localeinfo_struct local_10;
  char local_8;
  
  _LocaleUpdate::_LocaleUpdate((_LocaleUpdate *)&local_14,(__crt_locale_pointers *)_Locale);
  if ((_Str1 == (wchar_t *)0x0) || (_Str2 == (wchar_t *)0x0)) {
    piVar3 = __errno();
    *piVar3 = 0x16;
    FUN_00465fa2();
    iVar4 = 0x7fffffff;
  }
  else {
    if ((local_10.locinfo)->locale_name[2] == (wchar_t *)0x0) {
      iVar4 = (int)_Str1 - (int)_Str2;
      do {
        wVar1 = *(wchar_t *)(iVar4 + (int)_Str2);
        if ((0x40 < (ushort)wVar1) && ((ushort)wVar1 < 0x5b)) {
          wVar1 = wVar1 + L' ';
        }
        wVar2 = *_Str2;
        if ((0x40 < (ushort)wVar2) && ((ushort)wVar2 < 0x5b)) {
          wVar2 = wVar2 + L' ';
        }
        _Str2 = _Str2 + 1;
      } while ((wVar1 != L'\0') && (wVar1 == wVar2));
    }
    else {
      do {
        wVar1 = __towlower_l(*_Str1,&local_10);
        _Str1 = _Str1 + 1;
        wVar2 = __towlower_l(*_Str2,&local_10);
        _Str2 = _Str2 + 1;
        if (wVar1 == L'\0') break;
      } while (wVar1 == wVar2);
    }
    iVar4 = (uint)(ushort)wVar1 - (uint)(ushort)wVar2;
  }
  if (local_8 != '\0') {
    *(uint *)(local_14 + 0x350) = *(uint *)(local_14 + 0x350) & 0xfffffffd;
  }
  return iVar4;
}


