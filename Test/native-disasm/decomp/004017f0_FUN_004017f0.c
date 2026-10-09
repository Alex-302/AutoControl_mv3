// FUN_004017f0 @ 004017f0 size=70 callers=1

void FUN_004017f0(void)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_004791a6;
  local_10 = ExceptionList;
  local_8 = 0;
  ExceptionList = &local_10;
  FUN_004381d0(&DAT_004a26d0,'\0');
  _atexit(FUN_0047f360);
  ExceptionList = local_10;
  return;
}


