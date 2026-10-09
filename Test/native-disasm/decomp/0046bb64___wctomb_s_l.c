// __wctomb_s_l @ 0046bb64 size=289 callers=1

/* Library Function - Single Match
    __wctomb_s_l
   
   Library: Visual Studio 2015 Release */

errno_t __cdecl
__wctomb_s_l(int *_SizeConverted,char *_MbCh,size_t _SizeInBytes,wchar_t _WCh,_locale_t _Locale)

{
  int *piVar1;
  int iVar2;
  DWORD DVar3;
  errno_t eVar4;
  int local_18;
  int local_14;
  char local_c;
  BOOL local_8;
  
  if ((_MbCh == (char *)0x0) && (_SizeInBytes != 0)) {
    if (_SizeConverted != (int *)0x0) {
      *_SizeConverted = 0;
    }
    return 0;
  }
  if (_SizeConverted != (int *)0x0) {
    *_SizeConverted = -1;
  }
  if (0x7fffffff < _SizeInBytes) {
    piVar1 = __errno();
    *piVar1 = 0x16;
    FUN_00465fa2();
    return 0x16;
  }
  _LocaleUpdate::_LocaleUpdate((_LocaleUpdate *)&local_18,(__crt_locale_pointers *)_Locale);
  eVar4 = 0;
  if (*(int *)(local_14 + 0xa8) == 0) {
    if ((ushort)_WCh < 0x100) {
      if (_MbCh != (char *)0x0) {
        if (_SizeInBytes == 0) goto LAB_0046bc71;
        *_MbCh = (char)_WCh;
      }
      if (_SizeConverted != (int *)0x0) {
        *_SizeConverted = 1;
      }
      goto LAB_0046bbf1;
    }
    if ((_MbCh != (char *)0x0) && (_SizeInBytes != 0)) {
      _memset(_MbCh,0,_SizeInBytes);
    }
  }
  else {
    local_8 = 0;
    iVar2 = WideCharToMultiByte(*(UINT *)(local_14 + 8),0,&_WCh,1,_MbCh,_SizeInBytes,(LPCSTR)0x0,
                                &local_8);
    if (iVar2 == 0) {
      DVar3 = GetLastError();
      if (DVar3 == 0x7a) {
        if ((_MbCh != (char *)0x0) && (_SizeInBytes != 0)) {
          _memset(_MbCh,0,_SizeInBytes);
        }
LAB_0046bc71:
        piVar1 = __errno();
        eVar4 = 0x22;
        *piVar1 = 0x22;
        FUN_00465fa2();
        goto LAB_0046bbf1;
      }
    }
    else if (local_8 == 0) {
      if (_SizeConverted != (int *)0x0) {
        *_SizeConverted = iVar2;
      }
      goto LAB_0046bbf1;
    }
  }
  piVar1 = __errno();
  eVar4 = 0x2a;
  *piVar1 = 0x2a;
LAB_0046bbf1:
  if (local_c != '\0') {
    *(uint *)(local_18 + 0x350) = *(uint *)(local_18 + 0x350) & 0xfffffffd;
  }
  return eVar4;
}


