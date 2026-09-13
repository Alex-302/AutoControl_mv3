// FUN_00455190 @ 00455190 size=55 callers=1

int FUN_00455190(undefined4 *param_1,undefined4 *param_2,undefined4 param_3,undefined4 *param_4)

{
  int iVar1;
  
  iVar1 = FUN_00448e80(param_1,param_2);
  if ((undefined4 *)(iVar1 + 8) != (undefined4 *)0x0) {
    *(undefined4 *)(iVar1 + 8) = *(undefined4 *)*param_4;
    _memset((void *)(iVar1 + 0xc),0,0x36);
  }
  return iVar1;
}


