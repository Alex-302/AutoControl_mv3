// __wcstombs_s_l @ 0046e994 size=205 callers=2

/* Library Function - Single Match
    __wcstombs_s_l
   
   Library: Visual Studio 2015 Release */

errno_t __cdecl
__wcstombs_s_l(size_t *_PtNumOfCharConverted,char *_Dst,size_t _DstSizeInBytes,wchar_t *_Src,
              size_t _MaxCountInBytes,_locale_t _Locale)

{
  int *piVar1;
  uint uVar2;
  size_t sVar3;
  errno_t eVar4;
  
  if (_Dst == (char *)0x0) {
    if (_DstSizeInBytes != 0) goto LAB_0046e9dd;
  }
  else if (_DstSizeInBytes == 0) {
LAB_0046e9dd:
    piVar1 = __errno();
    *piVar1 = 0x16;
    FUN_00465fa2();
    return 0x16;
  }
  if (_Dst != (char *)0x0) {
    *_Dst = '\0';
  }
  if (_PtNumOfCharConverted != (size_t *)0x0) {
    *_PtNumOfCharConverted = 0;
  }
  sVar3 = _DstSizeInBytes;
  if (_MaxCountInBytes <= _DstSizeInBytes) {
    sVar3 = _MaxCountInBytes;
  }
  if (sVar3 < 0x80000000) {
    uVar2 = _wcstombs_l_helper(_Dst,_Src,sVar3,(__crt_locale_pointers *)_Locale);
    if (uVar2 == 0xffffffff) {
      if (_Dst != (char *)0x0) {
        *_Dst = '\0';
      }
      piVar1 = __errno();
      return *piVar1;
    }
    sVar3 = uVar2 + 1;
    if (_Dst == (char *)0x0) {
      eVar4 = 0;
    }
    else {
      if (_DstSizeInBytes < sVar3) {
        if ((_MaxCountInBytes != 0xffffffff) && (*_Dst = '\0', _DstSizeInBytes <= sVar3)) {
          piVar1 = __errno();
          eVar4 = 0x22;
          goto LAB_0046ea32;
        }
        eVar4 = 0x50;
        sVar3 = _DstSizeInBytes;
      }
      else {
        eVar4 = 0;
      }
      _Dst[sVar3 - 1] = '\0';
    }
    if (_PtNumOfCharConverted != (size_t *)0x0) {
      *_PtNumOfCharConverted = sVar3;
    }
  }
  else {
    piVar1 = __errno();
    eVar4 = 0x16;
LAB_0046ea32:
    *piVar1 = eVar4;
    FUN_00465fa2();
  }
  return eVar4;
}


