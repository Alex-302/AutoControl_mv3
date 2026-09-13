// FUN_004488f0 @ 004488f0 size=51 callers=4

undefined4 * __fastcall FUN_004488f0(undefined4 *param_1)

{
  undefined4 *puVar1;
  
  puVar1 = operator_new(0x38);
  if (puVar1 != (undefined4 *)0x0) {
    *puVar1 = *param_1;
  }
  if (puVar1 + 1 != (undefined4 *)0x0) {
    puVar1[1] = *param_1;
  }
  if (puVar1 + 2 != (undefined4 *)0x0) {
    puVar1[2] = *param_1;
  }
  return puVar1;
}


