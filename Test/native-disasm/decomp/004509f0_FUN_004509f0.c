// FUN_004509f0 @ 004509f0 size=147 callers=1

void __fastcall FUN_004509f0(float *param_1)

{
  int *piVar1;
  int *piVar2;
  float fVar3;
  float fVar4;
  int local_8 [2];
  
  fVar3 = param_1[7];
  fVar4 = (float)((double)(int)param_1[2] + (double)(&DAT_0048f2d0)[-((int)param_1[2] >> 0x1f)]) /
          (float)((double)(int)fVar3 + (double)(&DAT_0048f2d0)[-((int)fVar3 >> 0x1f)]);
  if (*param_1 <= fVar4 && fVar4 != *param_1) {
    if ((uint)fVar3 < 0x200) {
      fVar3 = (float)((int)fVar3 << 3);
    }
    else if ((uint)fVar3 < 0x1fffffff) {
      fVar3 = (float)((int)fVar3 * 2);
    }
    FUN_00435e50(param_1,(int)fVar3);
    piVar1 = (int *)param_1[1];
    if ((int *)*piVar1 != piVar1) {
      piVar1 = (int *)piVar1[1];
      do {
        piVar2 = *(int **)param_1[1];
        FUN_0044f650(param_1,local_8,(byte *)(piVar2 + 2),piVar2);
      } while (piVar2 != piVar1);
    }
  }
  return;
}


