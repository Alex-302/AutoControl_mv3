// FUN_00448fb0 @ 00448fb0 size=46 callers=6

void FUN_00448fb0(undefined4 *param_1,undefined4 *param_2)

{
  undefined4 *puVar1;
  
  puVar1 = operator_new(0x24);
  if (param_1 == (undefined4 *)0x0) {
    param_1 = puVar1;
    param_2 = puVar1;
  }
  if (puVar1 != (void *)0x0) {
    *puVar1 = param_1;
  }
  if (puVar1 + 1 != (undefined4 *)0x0) {
    puVar1[1] = param_2;
  }
  return;
}


