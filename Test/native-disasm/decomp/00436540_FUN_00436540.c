// FUN_00436540 @ 00436540 size=141 callers=4

void __fastcall FUN_00436540(int *param_1)

{
  int *piVar1;
  void *pvVar2;
  void *_Memory;
  uint *puVar3;
  int *_Memory_00;
  
  piVar1 = (int *)*param_1;
  _Memory_00 = (int *)*piVar1;
  *piVar1 = (int)piVar1;
  *(int *)(*param_1 + 4) = *param_1;
  param_1[1] = 0;
  if (_Memory_00 != (int *)*param_1) {
    do {
      puVar3 = (uint *)(_Memory_00 + 3);
      piVar1 = (int *)*_Memory_00;
      if (0xf < (uint)_Memory_00[8]) {
        pvVar2 = (void *)*puVar3;
        _Memory = pvVar2;
        if ((0xfff < _Memory_00[8] + 1U) &&
           ((((((uint)pvVar2 & 0x1f) != 0 ||
              (_Memory = *(void **)((int)pvVar2 - 4), pvVar2 <= _Memory)) ||
             ((uint)((int)pvVar2 - (int)_Memory) < 4)) ||
            (0x23 < (uint)((int)pvVar2 - (int)_Memory))))) {
                    /* WARNING: Subroutine does not return */
          FUN_00465fb2();
        }
        FID_conflict__free(_Memory);
      }
      _Memory_00[8] = 0xf;
      _Memory_00[7] = 0;
      if (0xf < (uint)_Memory_00[8]) {
        puVar3 = (uint *)*puVar3;
      }
      *(undefined1 *)puVar3 = 0;
      FID_conflict__free(_Memory_00);
      _Memory_00 = piVar1;
    } while (piVar1 != (int *)*param_1);
  }
  return;
}


