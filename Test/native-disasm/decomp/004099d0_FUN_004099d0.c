// FUN_004099d0 @ 004099d0 size=151 callers=1

void FUN_004099d0(void)

{
  FILE *pFVar1;
  int iVar2;
  char *pcVar3;
  int iVar4;
  size_t sVar5;
  
  SetErrorMode(3);
  FUN_00465d74(0,1);
  FUN_00465d74(0,2);
  SetUnhandledExceptionFilter(FUN_00409800);
  iVar4 = 0x8000;
  pFVar1 = (FILE *)___acrt_iob_func(0);
  iVar2 = __fileno(pFVar1);
  __setmode(iVar2,iVar4);
  iVar4 = 0x8000;
  pFVar1 = (FILE *)___acrt_iob_func(1);
  iVar2 = __fileno(pFVar1);
  __setmode(iVar2,iVar4);
  sVar5 = 0;
  iVar2 = 4;
  pcVar3 = (char *)0x0;
  pFVar1 = (FILE *)___acrt_iob_func(0);
  _setvbuf(pFVar1,pcVar3,iVar2,sVar5);
  sVar5 = 0;
  iVar2 = 4;
  pcVar3 = (char *)0x0;
  pFVar1 = (FILE *)___acrt_iob_func(1);
  _setvbuf(pFVar1,pcVar3,iVar2,sVar5);
  return;
}


