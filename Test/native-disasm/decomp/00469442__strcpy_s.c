// _strcpy_s @ 00469442 size=90 callers=7

/* Library Function - Single Match
    _strcpy_s
   
   Libraries: Visual Studio 2015 Release, Visual Studio 2017 Release, Visual Studio 2019 Release */

errno_t __cdecl _strcpy_s(char *_Dst,rsize_t _SizeInBytes,char *_Src)

{
  char cVar1;
  int *piVar2;
  char *pcVar3;
  int iVar4;
  
  if ((_Dst != (char *)0x0) && (_SizeInBytes != 0)) {
    if (_Src != (char *)0x0) {
      pcVar3 = _Dst;
      do {
        cVar1 = pcVar3[(int)_Src - (int)_Dst];
        *pcVar3 = cVar1;
        pcVar3 = pcVar3 + 1;
        if (cVar1 == '\0') break;
        _SizeInBytes = _SizeInBytes - 1;
      } while (_SizeInBytes != 0);
      if (_SizeInBytes != 0) {
        return 0;
      }
      *_Dst = '\0';
      piVar2 = __errno();
      iVar4 = 0x22;
      goto LAB_00469467;
    }
    *_Dst = '\0';
  }
  piVar2 = __errno();
  iVar4 = 0x16;
LAB_00469467:
  *piVar2 = iVar4;
  FUN_00465fa2();
  return iVar4;
}


