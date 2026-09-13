// _wcscpy_s @ 00466da9 size=100 callers=6

/* Library Function - Single Match
    _wcscpy_s
   
   Libraries: Visual Studio 2015 Release, Visual Studio 2017 Release, Visual Studio 2019 Release */

errno_t __cdecl _wcscpy_s(wchar_t *_Dst,rsize_t _SizeInWords,wchar_t *_Src)

{
  wchar_t wVar1;
  int *piVar2;
  wchar_t *pwVar3;
  int iVar4;
  
  if ((_Dst != (wchar_t *)0x0) && (_SizeInWords != 0)) {
    if (_Src != (wchar_t *)0x0) {
      pwVar3 = _Dst;
      do {
        wVar1 = *(wchar_t *)(((int)_Src - (int)_Dst) + (int)pwVar3);
        *pwVar3 = wVar1;
        pwVar3 = pwVar3 + 1;
        if (wVar1 == L'\0') break;
        _SizeInWords = _SizeInWords - 1;
      } while (_SizeInWords != 0);
      if (_SizeInWords != 0) {
        return 0;
      }
      *_Dst = L'\0';
      piVar2 = __errno();
      iVar4 = 0x22;
      goto LAB_00466dd0;
    }
    *_Dst = L'\0';
  }
  piVar2 = __errno();
  iVar4 = 0x16;
LAB_00466dd0:
  *piVar2 = iVar4;
  FUN_00465fa2();
  return iVar4;
}


