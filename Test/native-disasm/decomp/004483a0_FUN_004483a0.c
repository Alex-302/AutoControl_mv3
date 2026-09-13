// FUN_004483a0 @ 004483a0 size=53 callers=11

void __fastcall FUN_004483a0(int param_1)

{
  void *pvVar1;
  
  pvVar1 = *(void **)(param_1 + 4);
  if (pvVar1 != (void *)0x0) {
    FUN_00402430(pvVar1,*(int *)(param_1 + 0xc) - (int)pvVar1 >> 2,4);
    *(undefined4 *)(param_1 + 4) = 0;
    *(undefined4 *)(param_1 + 8) = 0;
    *(undefined4 *)(param_1 + 0xc) = 0;
  }
  return;
}


