// FUN_0041eea0 @ 0041eea0 size=135 callers=1

undefined4 FUN_0041eea0(void)

{
  undefined **local_3c [9];
  undefined ***local_18;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047afd8;
  local_10 = ExceptionList;
  DAT_004a250c = DAT_004a250c + -4;
  ExceptionList = &local_10;
  if (DAT_004a2426 != '\0') {
    ExceptionList = &local_10;
    FUN_0041ebf0();
  }
  if (DAT_004a2436 != '\0') {
    local_18 = local_3c;
    local_3c[0] = &PTR_LAB_0048ea68;
    local_8 = 0;
    FUN_0040f6b0(DAT_004a23dc,(int *)local_18,0);
    if (local_18 != (undefined ***)0x0) {
      (*(code *)(*local_18)[4])(local_18 != local_3c);
    }
  }
  ExceptionList = local_10;
  return 0;
}


