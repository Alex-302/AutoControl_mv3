// __strnicmp_l @ 00476849 size=183 callers=2

/* Library Function - Single Match
    __strnicmp_l
   
   Library: Visual Studio 2015 Release */

int __cdecl __strnicmp_l(char *_Str1,char *_Str2,size_t _MaxCount,_locale_t _Locale)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int local_14;
  localeinfo_struct local_10;
  char local_8;
  
  if (_MaxCount == 0) {
    iVar3 = 0;
  }
  else {
    _LocaleUpdate::_LocaleUpdate((_LocaleUpdate *)&local_14,(__crt_locale_pointers *)_Locale);
    iVar3 = 0x7fffffff;
    if (((_Str1 == (char *)0x0) || (_Str2 == (char *)0x0)) || (0x7fffffff < _MaxCount)) {
      piVar1 = __errno();
      *piVar1 = 0x16;
      FUN_00465fa2();
    }
    else if ((local_10.locinfo)->locale_name[2] == (wchar_t *)0x0) {
      iVar3 = ___ascii_strnicmp(_Str1,_Str2,_MaxCount);
    }
    else {
      iVar4 = (int)_Str1 - (int)_Str2;
      do {
        iVar3 = __tolower_l((uint)(byte)_Str2[iVar4],&local_10);
        iVar2 = __tolower_l((uint)(byte)*_Str2,&local_10);
        _Str2 = _Str2 + 1;
        _MaxCount = _MaxCount - 1;
        if ((_MaxCount == 0) || (iVar3 == 0)) break;
      } while (iVar3 == iVar2);
      iVar3 = iVar3 - iVar2;
    }
    if (local_8 != '\0') {
      *(uint *)(local_14 + 0x350) = *(uint *)(local_14 + 0x350) & 0xfffffffd;
    }
  }
  return iVar3;
}


