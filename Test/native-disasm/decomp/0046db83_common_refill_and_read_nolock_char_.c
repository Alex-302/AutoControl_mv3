// common_refill_and_read_nolock<char> @ 0046db83 size=385 callers=1

/* Library Function - Single Match
    int __cdecl common_refill_and_read_nolock<char>(class __crt_stdio_stream)
   
   Library: Visual Studio 2015 Release */

int __cdecl common_refill_and_read_nolock<char>(FILE *param_1)

{
  byte bVar1;
  int *piVar2;
  int iVar3;
  char *pcVar4;
  uint uVar5;
  undefined *puVar6;
  void *_DstBuf;
  
  if (param_1 == (FILE *)0x0) {
    piVar2 = __errno();
    *piVar2 = 0x16;
    FUN_00465fa2();
  }
  else if ((((uint)param_1->_flag >> 0xd & 1) != 0) && (((uint)param_1->_flag >> 0xc & 1) == 0)) {
    if (((uint)param_1->_flag >> 1 & 1) == 0) {
      LOCK();
      param_1->_flag = param_1->_flag | 1;
      UNLOCK();
      if ((param_1->_flag & 0x4c0U) == 0) {
        ___acrt_stdio_allocate_buffer_nolock(&param_1->_ptr);
      }
      param_1->_ptr = (char *)param_1->_cnt;
      uVar5 = param_1->_bufsiz;
      _DstBuf = (void *)param_1->_cnt;
      iVar3 = __fileno(param_1);
      pcVar4 = (char *)__read(iVar3,_DstBuf,uVar5);
      param_1->_base = pcVar4;
      pcVar4 = param_1->_base;
      if ((pcVar4 != (char *)0x0) && (pcVar4 != (char *)0xffffffff)) {
        if ((param_1->_flag & 6U) == 0) {
          iVar3 = __fileno(param_1);
          if ((iVar3 == -1) || (iVar3 = __fileno(param_1), iVar3 == -2)) {
            puVar6 = &DAT_0049d1f8;
          }
          else {
            iVar3 = __fileno(param_1);
            uVar5 = __fileno(param_1);
            puVar6 = (undefined *)((uVar5 & 0x3f) * 0x30 + (&DAT_0049f8f8)[iVar3 >> 6]);
          }
          if ((puVar6[0x28] & 0x82) == 0x82) {
            LOCK();
            param_1->_flag = param_1->_flag | 0x20;
            UNLOCK();
          }
        }
        if (((param_1->_bufsiz == 0x200) && (((uint)param_1->_flag >> 6 & 1) != 0)) &&
           ((param_1->_flag & 0x100U) == 0)) {
          param_1->_bufsiz = 0x1000;
        }
        param_1->_base = param_1->_base + -1;
        bVar1 = *param_1->_ptr;
        param_1->_ptr = param_1->_ptr + 1;
        return (uint)bVar1;
      }
      LOCK();
      param_1->_flag = param_1->_flag | (uint)(pcVar4 != (char *)0x0) * 8 + 8;
      UNLOCK();
      param_1->_base = (char *)0x0;
    }
    else {
      LOCK();
      param_1->_flag = param_1->_flag | 0x10;
      UNLOCK();
    }
  }
  return -1;
}


