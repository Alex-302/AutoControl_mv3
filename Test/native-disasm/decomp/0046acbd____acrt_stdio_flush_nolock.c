// ___acrt_stdio_flush_nolock @ 0046acbd size=102 callers=5

/* Library Function - Single Match
    ___acrt_stdio_flush_nolock
   
   Library: Visual Studio 2015 Release */

undefined4 __cdecl ___acrt_stdio_flush_nolock(FILE *param_1)

{
  int *piVar1;
  int _FileHandle;
  uint uVar2;
  uint uVar3;
  char *_Buf;
  
  piVar1 = &param_1->_flag;
  if ((((byte)*piVar1 & 3) == 2) && ((*piVar1 & 0xc0U) != 0)) {
    _Buf = (char *)param_1->_cnt;
    uVar3 = (int)param_1->_ptr - (int)_Buf;
    param_1->_ptr = _Buf;
    param_1->_base = (char *)0x0;
    if (0 < (int)uVar3) {
      uVar2 = uVar3;
      _FileHandle = __fileno(param_1);
      uVar2 = __write(_FileHandle,_Buf,uVar2);
      if (uVar3 != uVar2) {
        LOCK();
        *piVar1 = *piVar1 | 0x10;
        UNLOCK();
        return 0xffffffff;
      }
      if (((uint)*piVar1 >> 2 & 1) != 0) {
        LOCK();
        *piVar1 = *piVar1 & 0xfffffffd;
        UNLOCK();
      }
    }
  }
  return 0;
}


