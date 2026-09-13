// FUN_00454f20 @ 00454f20 size=40 callers=5

void FUN_00454f20(undefined4 *param_1,undefined4 *param_2,undefined4 param_3,undefined4 *param_4)

{
  int iVar1;
  
  iVar1 = FUN_00448ac0(param_1,param_2);
  if ((undefined4 *)(iVar1 + 8) != (undefined4 *)0x0) {
    *(undefined4 *)(iVar1 + 8) = *(undefined4 *)*param_4;
    *(undefined4 *)(iVar1 + 0xc) = 0;
  }
  return;
}


