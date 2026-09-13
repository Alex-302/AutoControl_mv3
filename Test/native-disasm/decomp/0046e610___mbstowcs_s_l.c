// __mbstowcs_s_l @ 0046e610 size=227 callers=1

/* Library Function - Single Match
    __mbstowcs_s_l
   
   Library: Visual Studio 2015 Release */

errno_t __cdecl
__mbstowcs_s_l(size_t *_PtNumOfCharConverted,wchar_t *_DstBuf,size_t _SizeInWords,char *_SrcBuf,
              size_t _MaxCount,_locale_t _Locale)

{
  int *piVar1;
  size_t sVar2;
  uint uVar3;
  int iVar4;
  int local_14;
  __crt_locale_pointers local_10 [8];
  char local_8;
  
  iVar4 = 0;
  if (_DstBuf == (wchar_t *)0x0) {
    if (_SizeInWords != 0) {
LAB_0046e631:
      piVar1 = __errno();
      *piVar1 = 0x16;
      FUN_00465fa2();
      return 0x16;
    }
  }
  else {
    if (_SizeInWords == 0) goto LAB_0046e631;
    *_DstBuf = L'\0';
  }
  if (_PtNumOfCharConverted != (size_t *)0x0) {
    *_PtNumOfCharConverted = 0;
  }
  _LocaleUpdate::_LocaleUpdate((_LocaleUpdate *)&local_14,(__crt_locale_pointers *)_Locale);
  sVar2 = _SizeInWords;
  if (_MaxCount <= _SizeInWords) {
    sVar2 = _MaxCount;
  }
  if (sVar2 < 0x80000000) {
    uVar3 = _mbstowcs_l_helper(_DstBuf,_SrcBuf,sVar2,local_10);
    if (uVar3 == 0xffffffff) {
      if (_DstBuf != (wchar_t *)0x0) {
        *_DstBuf = L'\0';
      }
      piVar1 = __errno();
      iVar4 = *piVar1;
      goto LAB_0046e6da;
    }
    uVar3 = uVar3 + 1;
    if (_DstBuf != (wchar_t *)0x0) {
      if (_SizeInWords < uVar3) {
        if (_MaxCount != 0xffffffff) {
          *_DstBuf = L'\0';
          piVar1 = __errno();
          iVar4 = 0x22;
          goto LAB_0046e6bb;
        }
        iVar4 = 0x50;
        uVar3 = _SizeInWords;
      }
      _DstBuf[uVar3 - 1] = L'\0';
    }
    if (_PtNumOfCharConverted != (size_t *)0x0) {
      *_PtNumOfCharConverted = uVar3;
    }
  }
  else {
    piVar1 = __errno();
    iVar4 = 0x16;
LAB_0046e6bb:
    *piVar1 = iVar4;
    FUN_00465fa2();
  }
LAB_0046e6da:
  if (local_8 == '\0') {
    return iVar4;
  }
  *(uint *)(local_14 + 0x350) = *(uint *)(local_14 + 0x350) & 0xfffffffd;
  return iVar4;
}


