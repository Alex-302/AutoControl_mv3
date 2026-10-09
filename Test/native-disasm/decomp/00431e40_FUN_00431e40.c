// FUN_00431e40 @ 00431e40 size=90 callers=2

void __fastcall FUN_00431e40(undefined4 *param_1)

{
  int *piVar1;
  int *piVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 uStack_8;
  
  uStack_8 = 0xffffffff;
  puStack_c = &LAB_004790f0;
  local_10 = ExceptionList;
  piVar2 = (int *)*param_1;
  if (piVar2 != (int *)0x0) {
    if ((undefined **)*piVar2 == &PTR_FUN_0048ece8) {
      piVar1 = piVar2 + 1;
      ExceptionList = &local_10;
      *piVar1 = *piVar1 + -1;
      if (*piVar1 == 0) {
        FUN_0045a6a4(piVar2);
        ExceptionList = local_10;
        return;
      }
    }
    else {
      ExceptionList = &local_10;
      (*(code *)((undefined **)*piVar2)[2])(piVar2);
    }
  }
  ExceptionList = local_10;
  return;
}


