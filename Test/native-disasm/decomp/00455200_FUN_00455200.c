// FUN_00455200 @ 00455200 size=56 callers=1

void FUN_00455200(undefined4 *param_1,undefined4 *param_2,undefined4 param_3,undefined4 *param_4)

{
  int iVar1;
  
  iVar1 = FUN_00448f80(param_1,param_2);
  if ((undefined2 *)(iVar1 + 8) != (undefined2 *)0x0) {
    *(undefined2 *)(iVar1 + 8) = *(undefined2 *)*param_4;
    *(undefined4 *)(iVar1 + 0xc) = 0;
    *(undefined4 *)(iVar1 + 0x10) = 0;
    *(undefined4 *)(iVar1 + 0x14) = 0;
  }
  return;
}


