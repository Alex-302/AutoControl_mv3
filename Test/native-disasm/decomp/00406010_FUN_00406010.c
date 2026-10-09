// FUN_00406010 @ 00406010 size=72 callers=3

void __fastcall FUN_00406010(int param_1)

{
  void *pvVar1;
  
  pvVar1 = *(void **)(param_1 + 0xc);
  if (pvVar1 != (void *)0x0) {
    FUN_00402430(pvVar1,*(int *)(param_1 + 0x14) - (int)pvVar1 >> 2,4);
    *(undefined4 *)(param_1 + 0xc) = 0;
    *(undefined4 *)(param_1 + 0x10) = 0;
    *(undefined4 *)(param_1 + 0x14) = 0;
  }
  FUN_0043e550((int *)(param_1 + 4));
  FID_conflict__free(*(void **)(param_1 + 4));
  return;
}


