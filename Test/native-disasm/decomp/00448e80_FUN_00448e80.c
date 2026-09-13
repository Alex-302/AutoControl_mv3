// FUN_00448e80 @ 00448e80 size=46 callers=2

void FUN_00448e80(undefined4 *param_1,undefined4 *param_2)

{
  undefined4 *puVar1;
  
  puVar1 = operator_new(0x44);
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


