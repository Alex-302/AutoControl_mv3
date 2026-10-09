// FUN_00443b80 @ 00443b80 size=44 callers=3

void __fastcall FUN_00443b80(int param_1)

{
  int *piVar1;
  
  FUN_0040da40(param_1 + 0x34);
  piVar1 = *(int **)(param_1 + 0x2c);
  if (piVar1 != (int *)0x0) {
    (**(code **)(*piVar1 + 0x10))(piVar1 != (int *)(param_1 + 8));
    *(undefined4 *)(param_1 + 0x2c) = 0;
  }
  return;
}


