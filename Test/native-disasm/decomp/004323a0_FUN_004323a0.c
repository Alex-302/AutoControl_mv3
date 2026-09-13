// FUN_004323a0 @ 004323a0 size=112 callers=1

void __fastcall FUN_004323a0(int param_1)

{
  void *pvVar1;
  int *piVar2;
  int *_Memory;
  
  pvVar1 = *(void **)(param_1 + 0xc);
  if (pvVar1 != (void *)0x0) {
    FUN_00402430(pvVar1,*(int *)(param_1 + 0x14) - (int)pvVar1 >> 2,4);
    *(undefined4 *)(param_1 + 0xc) = 0;
    *(undefined4 *)(param_1 + 0x10) = 0;
    *(undefined4 *)(param_1 + 0x14) = 0;
  }
  piVar2 = *(int **)(param_1 + 4);
  _Memory = (int *)*piVar2;
  *piVar2 = (int)piVar2;
  *(int *)(*(int *)(param_1 + 4) + 4) = *(int *)(param_1 + 4);
  *(undefined4 *)(param_1 + 8) = 0;
  if (_Memory != *(int **)(param_1 + 4)) {
    do {
      piVar2 = (int *)*_Memory;
      FID_conflict__free(_Memory);
      _Memory = piVar2;
    } while (piVar2 != (int *)*(int *)(param_1 + 4));
  }
  FID_conflict__free(*(void **)(param_1 + 4));
  return;
}


