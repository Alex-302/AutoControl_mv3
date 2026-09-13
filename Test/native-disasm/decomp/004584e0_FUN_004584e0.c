// FUN_004584e0 @ 004584e0 size=115 callers=1

int FUN_004584e0(undefined4 *param_1,undefined4 *param_2,undefined2 *param_3)

{
  undefined2 *puVar1;
  int iVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047ed31;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  iVar2 = FUN_00448fe0(param_1,param_2);
  puVar1 = (undefined2 *)(iVar2 + 8);
  local_8 = 1;
  if (puVar1 != (undefined2 *)0x0) {
    *puVar1 = *param_3;
    FUN_004585e0((int *)(iVar2 + 0xc),puVar1,(int *)(param_3 + 2));
  }
  ExceptionList = local_10;
  return iVar2;
}


