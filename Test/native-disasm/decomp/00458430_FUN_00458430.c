// FUN_00458430 @ 00458430 size=146 callers=1

int FUN_00458430(undefined4 *param_1,undefined4 *param_2,undefined4 *param_3)

{
  undefined4 *this;
  int iVar1;
  undefined4 *puVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047ed11;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  iVar1 = FUN_00448fb0(param_1,param_2);
  this = (undefined4 *)(iVar1 + 8);
  local_8 = 1;
  if (this != (undefined4 *)0x0) {
    *(undefined4 *)(iVar1 + 0x1c) = 0xf;
    *(undefined4 *)(iVar1 + 0x18) = 0;
    puVar2 = this;
    if (0xf < *(uint *)(iVar1 + 0x1c)) {
      puVar2 = (undefined4 *)*this;
    }
    *(undefined1 *)puVar2 = 0;
    FUN_0043ade0(this,param_3,0,0xffffffff);
    *(undefined2 *)(iVar1 + 0x20) = *(undefined2 *)(param_3 + 6);
  }
  ExceptionList = local_10;
  return iVar1;
}


