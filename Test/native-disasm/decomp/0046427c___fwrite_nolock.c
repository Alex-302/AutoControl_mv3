// __fwrite_nolock @ 0046427c size=377 callers=1

/* Library Function - Single Match
    __fwrite_nolock
   
   Library: Visual Studio 2015 Release */

size_t __cdecl __fwrite_nolock(void *_DstBuf,size_t _Size,size_t _Count,FILE *_File)

{
  int *piVar1;
  char *pcVar2;
  int iVar3;
  char *pcVar4;
  char *pcVar5;
  uint *_Buf;
  char *local_c;
  char *local_8;
  
  if ((_Size != 0) && (_Count != 0)) {
    if ((_File != (FILE *)0x0) &&
       ((_DstBuf != (void *)0x0 && (_Count <= (uint)(0xffffffff / (ulonglong)_Size))))) {
      piVar1 = &_File->_flag;
      if ((*piVar1 & 0x4c0U) == 0) {
        local_8 = &DAT_00001000;
      }
      else {
        local_8 = (char *)_File->_bufsiz;
      }
      pcVar5 = (char *)(_Size * _Count);
      do {
        while( true ) {
          if (pcVar5 == (char *)0x0) {
            return _Count;
          }
          if ((_File->_flag & 0xc0U) != 0) break;
LAB_00464330:
          if (local_8 <= pcVar5) {
            if (((_File->_flag & 0xc0U) != 0) &&
               (iVar3 = ___acrt_stdio_flush_nolock(_File), iVar3 != 0)) goto LAB_004643e7;
            local_c = pcVar5;
            if (local_8 != (char *)0x0) {
              local_c = pcVar5 + -((uint)pcVar5 % (uint)local_8);
            }
            if (local_c == (char *)0xffffffff) {
              local_c = (char *)0xffffffff;
            }
            _Buf = _DstBuf;
            pcVar2 = local_c;
            iVar3 = __fileno(_File);
            pcVar4 = (char *)__write(iVar3,_Buf,(uint)pcVar2);
            if (pcVar4 != (char *)0xffffffff) {
              pcVar2 = local_c;
              if (pcVar4 <= local_c) {
                pcVar2 = pcVar4;
              }
              pcVar5 = pcVar5 + -(int)pcVar2;
              if (local_c <= pcVar4) goto LAB_004643a0;
            }
            goto LAB_004643de;
          }
          iVar3 = FUN_0046b957();
          if (iVar3 == -1) goto LAB_004643e7;
          local_8 = (char *)_File->_bufsiz;
          _DstBuf = (void *)((int)_DstBuf + 1);
          pcVar5 = pcVar5 + -1;
          if ((int)local_8 < 1) {
            local_8 = (char *)0x1;
          }
        }
        pcVar2 = _File->_base;
        if (pcVar2 == (char *)0x0) goto LAB_00464330;
        if ((int)pcVar2 < 0) {
LAB_004643de:
          LOCK();
          *piVar1 = *piVar1 | 0x10;
          UNLOCK();
LAB_004643e7:
          return (uint)((int)(_Size * _Count) - (int)pcVar5) / _Size;
        }
        if (pcVar5 < pcVar2) {
          pcVar2 = pcVar5;
        }
        FUN_0045c870((uint *)_File->_ptr,_DstBuf,(uint)pcVar2);
        _File->_base = _File->_base + -(int)pcVar2;
        pcVar5 = pcVar5 + -(int)pcVar2;
        _File->_ptr = pcVar2 + (int)_File->_ptr;
LAB_004643a0:
        _DstBuf = (void *)((int)_DstBuf + (int)pcVar2);
      } while( true );
    }
    piVar1 = __errno();
    *piVar1 = 0x16;
    FUN_00465fa2();
  }
  return 0;
}


