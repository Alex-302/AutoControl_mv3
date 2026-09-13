// FUN_0044f2d0 @ 0044f2d0 size=112 callers=1

int FUN_0044f2d0(undefined4 *param_1,undefined4 *param_2,undefined4 *param_3,void *param_4)

{
  int iVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047e781;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  iVar1 = FUN_00448c30(param_1,param_2);
  local_8 = 1;
  if ((undefined4 *)(iVar1 + 8) != (undefined4 *)0x0) {
    *(undefined4 *)(iVar1 + 8) = *param_3;
    FUN_004128b0((void *)(iVar1 + 0xc),param_4);
  }
  ExceptionList = local_10;
  return iVar1;
}


