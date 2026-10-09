// FUN_0043e640 @ 0043e640 size=86 callers=3

void __fastcall FUN_0043e640(int *param_1)

{
  int *piVar1;
  int *piVar2;
  int *_Memory;
  
  piVar1 = (int *)*param_1;
  _Memory = (int *)*piVar1;
  *piVar1 = (int)piVar1;
  *(int *)(*param_1 + 4) = *param_1;
  param_1[1] = 0;
  if (_Memory != (int *)*param_1) {
    do {
      piVar1 = (int *)_Memory[0xd];
      piVar2 = (int *)*_Memory;
      if (piVar1 != (int *)0x0) {
        (**(code **)(*piVar1 + 0x10))(piVar1 != _Memory + 4);
        _Memory[0xd] = 0;
      }
      FID_conflict__free(_Memory);
      _Memory = piVar2;
    } while (piVar2 != (int *)*param_1);
  }
  return;
}


