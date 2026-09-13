// FUN_0044b1b0 @ 0044b1b0 size=74 callers=1

void __fastcall FUN_0044b1b0(int *param_1)

{
  int *piVar1;
  code *pcVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_004791b6;
  local_10 = ExceptionList;
  local_8 = 0;
  piVar1 = *(int **)(*(int *)(*(int *)*param_1 + 4) + 0x38 + *param_1);
  if ((piVar1 != (int *)0x0) && (pcVar2 = *(code **)(*piVar1 + 8), pcVar2 != guard_check_icall)) {
    ExceptionList = &local_10;
    (*pcVar2)();
  }
  ExceptionList = local_10;
  return;
}


