// __fread_nolock_s @ 00465af8 size=460 callers=1

/* Library Function - Single Match
    __fread_nolock_s
   
   Library: Visual Studio 2015 Release */

size_t __cdecl
__fread_nolock_s(void *_DstBuf,size_t _DstSize,size_t _ElementSize,size_t _Count,FILE *_File)

{
  int *piVar1;
  char *_MaxCount;
  int iVar2;
  char *_DstSize_00;
  char *pcVar3;
  undefined1 *_DstBuf_00;
  uint uVar4;
  char *local_18;
  char *local_10;
  undefined1 *local_8;
  
  if ((_ElementSize != 0) && (_Count != 0)) {
    if (_DstBuf != (void *)0x0) {
      if ((_File != (FILE *)0x0) && (_Count <= (uint)(0xffffffff / (ulonglong)_ElementSize))) {
LAB_00465b6a:
        piVar1 = &_File->_flag;
        if ((*piVar1 & 0x4c0U) == 0) {
          local_10 = &DAT_00001000;
        }
        else {
          local_10 = (char *)_File->_bufsiz;
        }
        local_8 = _DstBuf;
        _DstSize_00 = (char *)_DstSize;
        pcVar3 = (char *)(_ElementSize * _Count);
        do {
          while( true ) {
            if (pcVar3 == (char *)0x0) {
              return _Count;
            }
            if ((_File->_flag & 0x4c0U) != 0) break;
LAB_00465bee:
            if (pcVar3 < local_10) {
              iVar2 = FUN_0046dd04();
              if (iVar2 == -1) goto LAB_00465cb2;
              if (_DstSize_00 == (char *)0x0) goto LAB_00465c86;
              *local_8 = (char)iVar2;
              local_8 = local_8 + 1;
              pcVar3 = pcVar3 + -1;
              _DstSize_00 = _DstSize_00 + -1;
              local_10 = (char *)_File->_bufsiz;
            }
            else {
              local_18 = pcVar3;
              if ((char *)0x7fffffff < pcVar3) {
                local_18 = (char *)0x7fffffff;
              }
              if (local_10 != (char *)0x0) {
                local_18 = local_18 + -((uint)local_18 % (uint)local_10);
              }
              if (_DstSize_00 < local_18) goto LAB_00465c86;
              _DstBuf_00 = local_8;
              iVar2 = __fileno(_File);
              iVar2 = __read_nolock(iVar2,_DstBuf_00,(uint)local_18);
              if (iVar2 == 0) {
                uVar4 = 8;
                goto LAB_00465cab;
              }
              if (iVar2 < 0) goto LAB_00465ca9;
              pcVar3 = pcVar3 + -iVar2;
              local_8 = local_8 + iVar2;
              _DstSize_00 = _DstSize_00 + -iVar2;
            }
          }
          _MaxCount = _File->_base;
          if (_MaxCount == (char *)0x0) goto LAB_00465bee;
          if ((int)_MaxCount < 0) {
LAB_00465ca9:
            uVar4 = 0x10;
LAB_00465cab:
            LOCK();
            *piVar1 = *piVar1 | uVar4;
            UNLOCK();
LAB_00465cb2:
            return (uint)((int)(_ElementSize * _Count) - (int)pcVar3) / _ElementSize;
          }
          if (pcVar3 < _MaxCount) {
            _MaxCount = pcVar3;
          }
          if (_DstSize_00 < _MaxCount) {
LAB_00465c86:
            if (_DstSize != 0xffffffff) {
              _memset(_DstBuf,0,_DstSize);
            }
            piVar1 = __errno();
            *piVar1 = 0x22;
            goto LAB_00465b22;
          }
          _memcpy_s(local_8,(rsize_t)_DstSize_00,_File->_ptr,(rsize_t)_MaxCount);
          pcVar3 = pcVar3 + -(int)_MaxCount;
          local_8 = local_8 + (int)_MaxCount;
          _File->_base = _File->_base + -(int)_MaxCount;
          _File->_ptr = _MaxCount + (int)_File->_ptr;
          _DstSize_00 = _DstSize_00 + -(int)_MaxCount;
        } while( true );
      }
      if (_DstSize != 0xffffffff) {
        _memset(_DstBuf,0,_DstSize);
      }
      if ((_File != (FILE *)0x0) && (_Count <= (uint)(0xffffffff / (ulonglong)_ElementSize)))
      goto LAB_00465b6a;
    }
    piVar1 = __errno();
    *piVar1 = 0x16;
LAB_00465b22:
    FUN_00465fa2();
  }
  return 0;
}


