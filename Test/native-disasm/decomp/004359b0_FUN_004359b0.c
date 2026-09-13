// FUN_004359b0 @ 004359b0 size=62 callers=1

void __fastcall FUN_004359b0(int *param_1)

{
  int *piVar1;
  int *_Memory;
  
  piVar1 = (int *)*param_1;
  _Memory = (int *)*piVar1;
  *piVar1 = (int)piVar1;
  *(int *)(*param_1 + 4) = *param_1;
  param_1[1] = 0;
  if (_Memory != (int *)*param_1) {
    do {
      piVar1 = (int *)*_Memory;
      FID_conflict__free(_Memory);
      _Memory = piVar1;
    } while (piVar1 != (int *)*param_1);
  }
  FID_conflict__free((void *)*param_1);
  return;
}


