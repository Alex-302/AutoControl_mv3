// FUN_00447f50 @ 00447f50 size=118 callers=3

void __fastcall FUN_00447f50(uint *param_1,uint *param_2)

{
  void *pvVar1;
  void *_Memory;
  uint uVar2;
  
  do {
    if (param_1 == param_2) {
      return;
    }
    pvVar1 = (void *)*param_1;
    if (pvVar1 != (void *)0x0) {
      uVar2 = (int)(param_1[2] - (int)pvVar1) >> 3;
      if ((0x1fffffff < uVar2) ||
         ((_Memory = pvVar1, 0xfff < uVar2 << 3 &&
          ((((((uint)pvVar1 & 0x1f) != 0 ||
             (_Memory = *(void **)((int)pvVar1 - 4), pvVar1 <= _Memory)) ||
            ((uint)((int)pvVar1 - (int)_Memory) < 4)) || (0x23 < (uint)((int)pvVar1 - (int)_Memory))
           ))))) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
      FID_conflict__free(_Memory);
      *param_1 = 0;
      param_1[1] = 0;
      param_1[2] = 0;
    }
    param_1 = param_1 + 9;
  } while( true );
}


