// FUN_00441f50 @ 00441f50 size=67 callers=3

undefined2 * __fastcall FUN_00441f50(undefined2 *param_1,void *param_2,undefined4 *param_3)

{
  undefined8 uVar1;
  
  uVar1 = FUN_0043dd10(param_2,param_3,0,0xffffffff);
  *(undefined4 *)(param_1 + 10) = 7;
  *(undefined4 *)(param_1 + 8) = 0;
  *param_1 = 0;
  FUN_0043a920(param_1,(uint *)uVar1);
  return param_1;
}


