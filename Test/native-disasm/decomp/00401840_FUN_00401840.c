// FUN_00401840 @ 00401840 size=162 callers=1

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00401840(void)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0047ae86;
  local_10 = ExceptionList;
  local_8 = 6;
  ExceptionList = &local_10;
  FUN_00443cb0(&DAT_004a270c);
  _DAT_004a2720 = 7;
  _DAT_004a271c = 0;
  _DAT_004a270c = 0;
  FUN_0043a650(&DAT_004a270c,(uint *)&DAT_0048d5bc,0);
  _DAT_004a2724 = _DAT_0048f310;
  uRam004a2728 = _UNK_0048f314;
  uRam004a272c = _UNK_0048f318;
  uRam004a2730 = _UNK_0048f31c;
  _DAT_004a2744 = 0x80000000;
  _DAT_004a2734 = _DAT_0048f300;
  uRam004a2738 = _UNK_0048f304;
  uRam004a273c = _UNK_0048f308;
  uRam004a2740 = _UNK_0048f30c;
  _atexit(FUN_0047f3a0);
  ExceptionList = local_10;
  return;
}


