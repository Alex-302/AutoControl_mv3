// FUN_0044f360 @ 0044f360 size=48 callers=1

void FUN_0044f360(undefined4 *param_1,undefined4 *param_2,undefined4 *param_3,undefined4 *param_4)

{
  undefined4 uVar1;
  int iVar2;
  
  iVar2 = FUN_00448ac0(param_1,param_2);
  if ((undefined4 *)(iVar2 + 8) != (undefined4 *)0x0) {
    *(undefined4 *)(iVar2 + 8) = *param_3;
    uVar1 = *param_4;
    *param_4 = 0;
    *(undefined4 *)(iVar2 + 0xc) = uVar1;
  }
  return;
}


