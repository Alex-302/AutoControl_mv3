// FUN_00446660 @ 00446660 size=100 callers=1

void __fastcall FUN_00446660(undefined4 *param_1,undefined4 param_2,undefined1 param_3)

{
  int *piVar1;
  uint uVar2;
  undefined4 *puVar3;
  
  piVar1 = param_1 + 4;
  if (param_1[4] == param_1[5]) {
    uVar2 = param_1[4] + 1;
    if (uVar2 == 0xffffffff) {
                    /* WARNING: Subroutine does not return */
      FUN_00458ec4("string too long");
    }
    if ((uint)param_1[5] < uVar2) {
      FUN_0043f5f0(param_1,uVar2);
    }
    else if (uVar2 == 0) {
      *piVar1 = 0;
      puVar3 = param_1;
      if (0xf < (uint)param_1[5]) {
        puVar3 = (undefined4 *)*param_1;
      }
      *(undefined1 *)puVar3 = 0;
    }
  }
  if (0xf < (uint)param_1[5]) {
    param_1 = (undefined4 *)*param_1;
  }
  *(undefined1 *)((int)param_1 + *piVar1) = param_3;
  *piVar1 = *piVar1 + 1;
  *(undefined1 *)(*piVar1 + (int)param_1) = 0;
  return;
}


