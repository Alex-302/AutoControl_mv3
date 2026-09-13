// _memcpy_s @ 004753c6 size=129 callers=53

/* Library Function - Single Match
    _memcpy_s
   
   Libraries: Visual Studio 2012, Visual Studio 2015, Visual Studio 2017, Visual Studio 2019 */

errno_t __cdecl _memcpy_s(void *_Dst,rsize_t _DstSize,void *_Src,rsize_t _MaxCount)

{
  errno_t eVar1;
  int *piVar2;
  
  if (_MaxCount == 0) {
    eVar1 = 0;
  }
  else if (_Dst == (void *)0x0) {
    piVar2 = __errno();
    eVar1 = 0x16;
    *piVar2 = 0x16;
    FUN_00465fa2();
  }
  else if ((_Src == (void *)0x0) || (_DstSize < _MaxCount)) {
    _memset(_Dst,0,_DstSize);
    if (_Src == (void *)0x0) {
      piVar2 = __errno();
      eVar1 = 0x16;
    }
    else {
      if (_MaxCount <= _DstSize) {
        return 0x16;
      }
      piVar2 = __errno();
      eVar1 = 0x22;
    }
    *piVar2 = eVar1;
    FUN_00465fa2();
  }
  else {
    FUN_0045c870(_Dst,_Src,_MaxCount);
    eVar1 = 0;
  }
  return eVar1;
}


