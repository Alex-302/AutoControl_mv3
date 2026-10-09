// FUN_00408c40 @ 00408c40 size=77 callers=1

void __fastcall FUN_00408c40(int *param_1)

{
  int *_Memory;
  
  _Memory = (int *)param_1[9];
  if (_Memory != (int *)0x0) {
    if ((undefined **)*_Memory == &PTR_LAB_0048e4d8) {
      *_Memory = (int)&PTR_FUN_0048ed18;
      if (_Memory != param_1) {
        FID_conflict__free(_Memory);
        param_1[9] = 0;
        return;
      }
    }
    else {
      (*(code *)((undefined **)*_Memory)[4])(_Memory != param_1);
    }
    param_1[9] = 0;
  }
  return;
}


