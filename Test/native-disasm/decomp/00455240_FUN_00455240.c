// FUN_00455240 @ 00455240 size=68 callers=1

int FUN_00455240(undefined4 *param_1,undefined4 *param_2,undefined4 param_3,undefined4 *param_4)

{
  undefined1 *this;
  uint *puVar1;
  int iVar2;
  
  iVar2 = FUN_00448fb0(param_1,param_2);
  this = (undefined1 *)(iVar2 + 8);
  if (this != (undefined1 *)0x0) {
    puVar1 = (uint *)*param_4;
    *(undefined4 *)(iVar2 + 0x1c) = 0xf;
    *(undefined4 *)(iVar2 + 0x18) = 0;
    *this = 0;
    FUN_0043b1c0(this,puVar1);
    *(undefined2 *)(iVar2 + 0x20) = 0;
  }
  return iVar2;
}


