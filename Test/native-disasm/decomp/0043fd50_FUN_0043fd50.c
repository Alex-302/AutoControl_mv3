// FUN_0043fd50 @ 0043fd50 size=140 callers=2

void FUN_0043fd50(int *param_1)

{
  char cVar1;
  int *piVar2;
  void *pvVar3;
  void *_Memory;
  uint *puVar4;
  
  cVar1 = *(char *)((int)param_1 + 0xd);
  do {
    if (cVar1 != '\0') {
      return;
    }
    FUN_0043fd50((int *)param_1[2]);
    puVar4 = (uint *)(param_1 + 4);
    piVar2 = (int *)*param_1;
    if (0xf < (uint)param_1[9]) {
      pvVar3 = (void *)*puVar4;
      _Memory = pvVar3;
      if ((0xfff < param_1[9] + 1U) &&
         ((((((uint)pvVar3 & 0x1f) != 0 ||
            (_Memory = *(void **)((int)pvVar3 - 4), pvVar3 <= _Memory)) ||
           ((uint)((int)pvVar3 - (int)_Memory) < 4)) || (0x23 < (uint)((int)pvVar3 - (int)_Memory)))
         )) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
      FID_conflict__free(_Memory);
    }
    param_1[9] = 0xf;
    param_1[8] = 0;
    if (0xf < (uint)param_1[9]) {
      puVar4 = (uint *)*puVar4;
    }
    *(undefined1 *)puVar4 = 0;
    FID_conflict__free(param_1);
    cVar1 = *(char *)((int)piVar2 + 0xd);
    param_1 = piVar2;
  } while( true );
}


