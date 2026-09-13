// FUN_00441c30 @ 00441c30 size=63 callers=1

undefined2 * __fastcall FUN_00441c30(undefined2 *param_1,void *param_2)

{
  uint *puVar1;
  
  puVar1 = FUN_0043a870(param_2,1,0);
  *(undefined4 *)(param_1 + 10) = 7;
  *(undefined4 *)(param_1 + 8) = 0;
  *param_1 = 0;
  FUN_0043a920(param_1,puVar1);
  return param_1;
}


