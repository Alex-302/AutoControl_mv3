// FUN_0047f2e0 @ 0047f2e0 size=61 callers=1

void FUN_0047f2e0(void)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_004791a6;
  local_10 = ExceptionList;
  local_8 = 0;
  if (DAT_004a2840 != (int *)0x0) {
    ExceptionList = &local_10;
    (**(code **)(*DAT_004a2840 + 8))(DAT_004a2840);
  }
  ExceptionList = local_10;
  return;
}


