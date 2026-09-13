// FUN_004479e0 @ 004479e0 size=140 callers=5

void __fastcall FUN_004479e0(uint *param_1,uint *param_2)

{
  void *pvVar1;
  uint uVar2;
  uint *puVar3;
  void *_Memory;
  uint *puVar4;
  
  if (param_1 != param_2) {
    puVar4 = param_1 + 5;
    do {
      if ((undefined4 *)puVar4[1] != (undefined4 *)0x0) {
        (*(code *)**(undefined4 **)puVar4[1])(1);
      }
      if (7 < *puVar4) {
        pvVar1 = (void *)puVar4[-5];
        uVar2 = *puVar4 + 1;
        if ((0x7fffffff < uVar2) ||
           ((_Memory = pvVar1, 0xfff < uVar2 * 2 &&
            ((((((uint)pvVar1 & 0x1f) != 0 ||
               (_Memory = *(void **)((int)pvVar1 - 4), pvVar1 <= _Memory)) ||
              ((uint)((int)pvVar1 - (int)_Memory) < 4)) ||
             (0x23 < (uint)((int)pvVar1 - (int)_Memory))))))) {
                    /* WARNING: Subroutine does not return */
          FUN_00465fb2();
        }
        FID_conflict__free(_Memory);
      }
      *puVar4 = 7;
      puVar4[-1] = 0;
      if (*puVar4 < 8) {
        puVar3 = puVar4 + -5;
      }
      else {
        puVar3 = (uint *)puVar4[-5];
      }
      *(undefined2 *)puVar3 = 0;
      puVar3 = puVar4 + 5;
      puVar4 = puVar4 + 10;
    } while (puVar3 != param_2);
  }
  return;
}


