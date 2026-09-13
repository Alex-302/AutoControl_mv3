// FUN_00454fb0 @ 00454fb0 size=118 callers=1

int FUN_00454fb0(undefined4 *param_1,undefined4 *param_2,undefined4 param_3,undefined4 *param_4)

{
  int iVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047ea51;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  iVar1 = FUN_00448bf0(param_1,param_2);
  local_8 = 1;
  if ((void *)(iVar1 + 8) != (void *)0x0) {
    param_2 = (undefined4 *)*param_4;
    FUN_00457d60((void *)(iVar1 + 8),&param_2);
  }
  ExceptionList = local_10;
  return iVar1;
}


