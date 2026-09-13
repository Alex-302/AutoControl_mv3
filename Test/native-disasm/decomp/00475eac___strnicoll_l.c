// __strnicoll_l @ 00475eac size=202 callers=1

/* Library Function - Single Match
    __strnicoll_l
   
   Library: Visual Studio 2015 Release */

int __cdecl __strnicoll_l(char *_Str1,char *_Str2,size_t _MaxCount,_locale_t _Locale)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int local_14;
  localeinfo_struct local_10;
  char local_8;
  
  _LocaleUpdate::_LocaleUpdate((_LocaleUpdate *)&local_14,(__crt_locale_pointers *)_Locale);
  if (_MaxCount == 0) {
    iVar3 = 0;
  }
  else if ((_Str1 == (char *)0x0) || (_Str2 == (char *)0x0)) {
    piVar1 = __errno();
    *piVar1 = 0x16;
    FUN_00465fa2();
    iVar3 = 0x7fffffff;
  }
  else {
    iVar3 = 0x7fffffff;
    if (_MaxCount < 0x80000000) {
      if ((local_10.locinfo)->locale_name[1] == (wchar_t *)0x0) {
        iVar3 = __strnicmp_l(_Str1,_Str2,_MaxCount,&local_10);
      }
      else {
        iVar2 = ___acrt_CompareStringA
                          ((__crt_locale_pointers *)&local_10,(local_10.locinfo)->locale_name[1],
                           0x1001,_Str1,_MaxCount,_Str2,_MaxCount,
                           (int)(local_10.locinfo)->lc_category[0].locale);
        if (iVar2 == 0) {
          piVar1 = __errno();
          *piVar1 = 0x16;
        }
        else {
          iVar3 = iVar2 + -2;
        }
      }
    }
    else {
      piVar1 = __errno();
      *piVar1 = 0x16;
      FUN_00465fa2();
    }
  }
  if (local_8 != '\0') {
    *(uint *)(local_14 + 0x350) = *(uint *)(local_14 + 0x350) & 0xfffffffd;
  }
  return iVar3;
}


