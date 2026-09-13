// FUN_00448170 @ 00448170 size=106 callers=2

void __fastcall FUN_00448170(void *param_1,int param_2,undefined1 *param_3)

{
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined1 local_8;
  undefined3 uStack_7;
  
  puStack_c = &LAB_0047e531;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  uStack_7 = 0;
  for (; param_2 != 0; param_2 = param_2 + -1) {
    local_8 = 1;
    if (param_1 != (void *)0x0) {
      FUN_00434940(param_1,param_3);
    }
    param_1 = (void *)((int)param_1 + 0x10);
  }
  *unaff_FS_OFFSET = local_10;
  return;
}


