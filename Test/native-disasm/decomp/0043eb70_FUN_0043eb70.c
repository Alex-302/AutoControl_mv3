// FUN_0043eb70 @ 0043eb70 size=145 callers=3

void __fastcall FUN_0043eb70(int *param_1)

{
  int *piVar1;
  void *pvVar2;
  void *_Memory;
  uint uVar3;
  int *_Memory_00;
  
  piVar1 = (int *)*param_1;
  _Memory_00 = (int *)*piVar1;
  *piVar1 = (int)piVar1;
  *(int *)(*param_1 + 4) = *param_1;
  param_1[1] = 0;
  if (_Memory_00 != (int *)*param_1) {
    do {
      pvVar2 = (void *)_Memory_00[3];
      piVar1 = (int *)*_Memory_00;
      if (pvVar2 != (void *)0x0) {
        uVar3 = _Memory_00[5] - (int)pvVar2 >> 1;
        if ((0x7fffffff < uVar3) ||
           ((_Memory = pvVar2, 0xfff < uVar3 * 2 &&
            ((((((uint)pvVar2 & 0x1f) != 0 ||
               (_Memory = *(void **)((int)pvVar2 - 4), pvVar2 <= _Memory)) ||
              ((uint)((int)pvVar2 - (int)_Memory) < 4)) ||
             (0x23 < (uint)((int)pvVar2 - (int)_Memory))))))) {
                    /* WARNING: Subroutine does not return */
          FUN_00465fb2();
        }
        FID_conflict__free(_Memory);
        _Memory_00[3] = 0;
        _Memory_00[4] = 0;
        _Memory_00[5] = 0;
      }
      FID_conflict__free(_Memory_00);
      _Memory_00 = piVar1;
    } while (piVar1 != (int *)*param_1);
  }
  return;
}


