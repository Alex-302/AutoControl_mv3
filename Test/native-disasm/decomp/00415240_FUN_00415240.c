// FUN_00415240 @ 00415240 size=253 callers=2

undefined4 * __fastcall FUN_00415240(POINT *param_1)

{
  IAccessible **ppIVar1;
  int local_64 [20];
  IAccessible *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047aeb8;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  if (*(int *)(*(int *)ThreadLocalStoragePointer + 8) < DAT_004a335c) {
    ExceptionList = &local_10;
    FUN_0045a219(&DAT_004a335c);
    if (DAT_004a335c == -1) {
      local_14 = (IAccessible *)0x0;
      local_8._0_1_ = 1;
      local_8._1_3_ = 0;
      FUN_00414c40(&DAT_004a2b10,&local_14);
      local_8 = CONCAT31(local_8._1_3_,2);
      if (local_14 != (IAccessible *)0x0) {
        (*local_14->lpVtbl->Release)(local_14);
      }
      _atexit(FUN_0047f3b0);
      local_8 = 0xffffffff;
      FUN_0045a1da(&DAT_004a335c);
    }
  }
  if (DAT_004a2a44 != DAT_004a26b4) {
    DAT_004a2a44 = DAT_004a26b4;
    ppIVar1 = FUN_0040b610(&local_14,param_1);
    local_8 = 3;
    FUN_00414c40(local_64,ppIVar1);
    FUN_00415340(local_64);
    FUN_004151a0(local_64);
    local_8 = 4;
    if (local_14 != (IAccessible *)0x0) {
      (*local_14->lpVtbl->Release)(local_14);
    }
  }
  ExceptionList = local_10;
  return &DAT_004a2b10;
}


