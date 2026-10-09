// FUN_004550b0 @ 004550b0 size=155 callers=1

int FUN_004550b0(undefined4 *param_1,undefined4 *param_2,undefined4 param_3,undefined4 *param_4)

{
  undefined4 *this;
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047ea71;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  iVar2 = FUN_00448c30(param_1,param_2);
  this = (undefined4 *)(iVar2 + 8);
  local_8 = 1;
  if (this != (undefined4 *)0x0) {
    puVar1 = (undefined4 *)*param_4;
    *(undefined4 *)(iVar2 + 0x1c) = 7;
    *(undefined4 *)(iVar2 + 0x18) = 0;
    puVar3 = this;
    if (7 < *(uint *)(iVar2 + 0x1c)) {
      puVar3 = (undefined4 *)*this;
    }
    *(undefined2 *)puVar3 = 0;
    FUN_0043a750(this,puVar1,0,0xffffffff);
    *(undefined4 *)(iVar2 + 0x20) = 0;
    *(undefined4 *)(iVar2 + 0x24) = 0;
  }
  ExceptionList = local_10;
  return iVar2;
}


