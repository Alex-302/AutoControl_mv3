// __isleadbyte_l @ 0046a38f size=57 callers=5

/* Library Function - Single Match
    __isleadbyte_l
   
   Library: Visual Studio 2015 Release */

int __cdecl __isleadbyte_l(int _C,_locale_t _Locale)

{
  ushort uVar1;
  int local_14;
  int *local_10;
  char local_8;
  
  _LocaleUpdate::_LocaleUpdate((_LocaleUpdate *)&local_14,(__crt_locale_pointers *)_Locale);
  uVar1 = *(ushort *)(*local_10 + (_C & 0xffU) * 2);
  if (local_8 != '\0') {
    *(uint *)(local_14 + 0x350) = *(uint *)(local_14 + 0x350) & 0xfffffffd;
  }
  return uVar1 & 0x8000;
}


