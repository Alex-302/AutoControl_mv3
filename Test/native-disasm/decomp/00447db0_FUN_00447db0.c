// FUN_00447db0 @ 00447db0 size=116 callers=6

void __fastcall FUN_00447db0(uint *param_1,uint *param_2)

{
  void *pvVar1;
  uint *puVar2;
  void *_Memory;
  uint *puVar3;
  
  if (param_1 != param_2) {
    puVar3 = param_1 + 5;
    do {
      if (0xf < *puVar3) {
        pvVar1 = (void *)puVar3[-5];
        _Memory = pvVar1;
        if ((0xfff < *puVar3 + 1) &&
           ((((((uint)pvVar1 & 0x1f) != 0 ||
              (_Memory = *(void **)((int)pvVar1 - 4), pvVar1 <= _Memory)) ||
             ((uint)((int)pvVar1 - (int)_Memory) < 4)) ||
            (0x23 < (uint)((int)pvVar1 - (int)_Memory))))) {
                    /* WARNING: Subroutine does not return */
          FUN_00465fb2();
        }
        FID_conflict__free(_Memory);
      }
      *puVar3 = 0xf;
      puVar3[-1] = 0;
      if (*puVar3 < 0x10) {
        puVar2 = puVar3 + -5;
      }
      else {
        puVar2 = (uint *)puVar3[-5];
      }
      *(undefined1 *)puVar2 = 0;
      puVar2 = puVar3 + 2;
      puVar3 = puVar3 + 7;
    } while (puVar2 != param_2);
  }
  return;
}


