// ___acrt_stdio_begin_temporary_buffering_nolock @ 0046b962 size=181 callers=1

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Library Function - Single Match
    ___acrt_stdio_begin_temporary_buffering_nolock
   
   Library: Visual Studio 2015 Release */

uint __cdecl ___acrt_stdio_begin_temporary_buffering_nolock(FILE *param_1)

{
  int *piVar1;
  int iVar2;
  FILE *pFVar3;
  LPVOID pvVar4;
  char *pcVar5;
  int *piVar6;
  
  iVar2 = __fileno(param_1);
  iVar2 = __isatty(iVar2);
  if (iVar2 == 0) {
    return 0;
  }
  pFVar3 = (FILE *)___acrt_iob_func(1);
  if (param_1 == pFVar3) {
    piVar6 = &DAT_0049fb04;
  }
  else {
    pFVar3 = (FILE *)___acrt_iob_func(2);
    if (param_1 != pFVar3) goto LAB_0046ba10;
    piVar6 = &DAT_0049fb08;
  }
  _DAT_0049f560 = _DAT_0049f560 + 1;
  piVar1 = &param_1->_flag;
  pFVar3 = (FILE *)*piVar1;
  if (((uint)pFVar3 & 0x4c0) != 0) {
LAB_0046ba10:
    return (uint)pFVar3 & 0xffffff00;
  }
  LOCK();
  *piVar1 = *piVar1 | 0x282;
  UNLOCK();
  iVar2 = *piVar6;
  if (iVar2 == 0) {
    pvVar4 = __malloc_base(0x1000);
    *piVar6 = (int)pvVar4;
    FID_conflict__free((void *)0x0);
    iVar2 = *piVar6;
    if (iVar2 == 0) {
      param_1->_base = (char *)0x2;
      param_1->_cnt = (int)&param_1->_charbuf;
      param_1->_ptr = (char *)&param_1->_charbuf;
      param_1->_bufsiz = 2;
      pcVar5 = (char *)0x0;
      goto LAB_0046ba0c;
    }
  }
  param_1->_cnt = iVar2;
  pcVar5 = (char *)*piVar6;
  param_1->_ptr = pcVar5;
  param_1->_base = &DAT_00001000;
  param_1->_bufsiz = 0x1000;
LAB_0046ba0c:
  return CONCAT31((int3)((uint)pcVar5 >> 8),1);
}


