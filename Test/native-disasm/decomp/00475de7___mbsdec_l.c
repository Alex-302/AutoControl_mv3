// __mbsdec_l @ 00475de7 size=141 callers=1

/* Library Function - Single Match
    __mbsdec_l
   
   Library: Visual Studio 2015 Release */

uchar * __cdecl __mbsdec_l(uchar *_Start,uchar *_Pos,_locale_t _Locale)

{
  int *piVar1;
  byte *pbVar2;
  int local_14 [2];
  int local_c;
  char local_8;
  
  if (_Start == (uchar *)0x0) {
    piVar1 = __errno();
    *piVar1 = 0x16;
    FUN_00465fa2();
  }
  else if (_Pos == (uchar *)0x0) {
    piVar1 = __errno();
    *piVar1 = 0x16;
    FUN_00465fa2();
  }
  else if (_Start < _Pos) {
    _LocaleUpdate::_LocaleUpdate((_LocaleUpdate *)local_14,(__crt_locale_pointers *)_Locale);
    if (*(int *)(local_c + 8) != 0) {
      pbVar2 = _Pos + -1;
      do {
        pbVar2 = pbVar2 + -1;
        if (pbVar2 < _Start) break;
      } while ((*(byte *)(*pbVar2 + 0x19 + local_c) & 4) != 0);
      _Pos = _Pos + -((int)_Pos - (int)pbVar2 & 1U);
    }
    if (local_8 != '\0') {
      *(uint *)(local_14[0] + 0x350) = *(uint *)(local_14[0] + 0x350) & 0xfffffffd;
      return _Pos + -1;
    }
    return _Pos + -1;
  }
  return (uchar *)0x0;
}


