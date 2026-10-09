// FUN_004362e0 @ 004362e0 size=66 callers=7

void __fastcall FUN_004362e0(int *param_1)

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
      if ((undefined4 *)_Memory[3] != (undefined4 *)0x0) {
        (*(code *)**(undefined4 **)_Memory[3])(1);
      }
      FID_conflict__free(_Memory);
      _Memory = piVar1;
    } while (piVar1 != (int *)*param_1);
  }
  return;
}


