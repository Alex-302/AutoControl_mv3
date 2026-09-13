// __islower_l @ 0046686b size=56 callers=1

/* Library Function - Single Match
    __islower_l
   
   Library: Visual Studio 2015 Release */

int __cdecl __islower_l(int _C,_locale_t _Locale)

{
  int iVar1;
  int local_14;
  localeinfo_struct local_10;
  char local_8;
  
  _LocaleUpdate::_LocaleUpdate((_LocaleUpdate *)&local_14,(__crt_locale_pointers *)_Locale);
  iVar1 = __ischartype_l(_C,2,&local_10);
  if (local_8 != '\0') {
    *(uint *)(local_14 + 0x350) = *(uint *)(local_14 + 0x350) & 0xfffffffd;
  }
  return iVar1;
}


