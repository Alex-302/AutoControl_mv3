// FUN_00441300 @ 00441300 size=101 callers=2

undefined1 * __fastcall FUN_00441300(undefined1 *param_1,uint *param_2,uint *param_3)

{
  uint *puVar1;
  undefined8 uVar2;
  
  if ((param_2[5] - param_2[4] < param_3[4]) && (param_2[4] <= param_3[5] - param_3[4])) {
    uVar2 = FUN_00445190(param_3,param_2,param_3,param_2,0,0xffffffff);
    puVar1 = (uint *)uVar2;
  }
  else {
    uVar2 = FUN_0043b0c0(param_2,param_3,0,0xffffffff);
    puVar1 = (uint *)uVar2;
  }
  *(undefined4 *)(param_1 + 0x14) = 0xf;
  *(undefined4 *)(param_1 + 0x10) = 0;
  *param_1 = 0;
  FUN_0043b1c0(param_1,puVar1);
  return param_1;
}


