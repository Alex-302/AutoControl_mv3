// FUN_0043e700 @ 0043e700 size=169 callers=3

void __fastcall FUN_0043e700(int *param_1)

{
  int *piVar1;
  void *pvVar2;
  uint uVar3;
  void *_Memory;
  uint *puVar4;
  int *_Memory_00;
  
  piVar1 = (int *)*param_1;
  _Memory_00 = (int *)*piVar1;
  *piVar1 = (int)piVar1;
  *(int *)(*param_1 + 4) = *param_1;
  param_1[1] = 0;
  if (_Memory_00 != (int *)*param_1) {
    do {
      puVar4 = (uint *)(_Memory_00 + 2);
      piVar1 = (int *)*_Memory_00;
      if ((HANDLE)_Memory_00[8] != (HANDLE)0x0) {
        CloseHandle((HANDLE)_Memory_00[8]);
      }
      if (7 < (uint)_Memory_00[7]) {
        pvVar2 = (void *)*puVar4;
        uVar3 = _Memory_00[7] + 1;
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
      }
      _Memory_00[7] = 7;
      _Memory_00[6] = 0;
      if (7 < (uint)_Memory_00[7]) {
        puVar4 = (uint *)*puVar4;
      }
      *(undefined2 *)puVar4 = 0;
      FID_conflict__free(_Memory_00);
      _Memory_00 = piVar1;
    } while (piVar1 != (int *)*param_1);
  }
  return;
}


