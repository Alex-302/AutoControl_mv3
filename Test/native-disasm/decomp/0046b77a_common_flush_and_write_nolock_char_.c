// common_flush_and_write_nolock<char> @ 0046b77a size=273 callers=1

/* Library Function - Single Match
    int __cdecl common_flush_and_write_nolock<char>(int,class __crt_stdio_stream)
   
   Library: Visual Studio 2015 Release */

int __cdecl common_flush_and_write_nolock<char>(uint param_1,FILE *param_2)

{
  bool bVar1;
  int iVar2;
  int *piVar3;
  FILE *pFVar4;
  
  iVar2 = __fileno(param_2);
  if ((param_2->_flag & 6U) == 0) {
    piVar3 = __errno();
    *piVar3 = 9;
  }
  else {
    if (((uint)param_2->_flag >> 0xc & 1) == 0) {
      if ((param_2->_flag & 1U) != 0) {
        param_2->_base = (char *)0x0;
        if (((uint)param_2->_flag >> 3 & 1) == 0) goto LAB_0046b7a4;
        param_2->_ptr = (char *)param_2->_cnt;
        LOCK();
        param_2->_flag = param_2->_flag & 0xfffffffe;
        UNLOCK();
      }
      LOCK();
      param_2->_flag = param_2->_flag | 2;
      UNLOCK();
      LOCK();
      param_2->_flag = param_2->_flag & 0xfffffff7;
      UNLOCK();
      param_2->_base = (char *)0x0;
      if (((param_2->_flag & 0x4c0U) == 0) &&
         (((pFVar4 = (FILE *)___acrt_iob_func(1), param_2 != pFVar4 &&
           (pFVar4 = (FILE *)___acrt_iob_func(2), param_2 != pFVar4)) ||
          (iVar2 = __isatty(iVar2), iVar2 == 0)))) {
        ___acrt_stdio_allocate_buffer_nolock(&param_2->_ptr);
      }
      bVar1 = write_buffer_nolock<char>(param_1,param_2);
      if (!bVar1) {
        LOCK();
        param_2->_flag = param_2->_flag | 0x10;
        UNLOCK();
        return -1;
      }
      return param_1 & 0xff;
    }
    piVar3 = __errno();
    *piVar3 = 0x22;
  }
LAB_0046b7a4:
  LOCK();
  param_2->_flag = param_2->_flag | 0x10;
  UNLOCK();
  return -1;
}


