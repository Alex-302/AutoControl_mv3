// FUN_0043e400 @ 0043e400 size=94 callers=3

void __fastcall FUN_0043e400(int *param_1)

{
  int *piVar1;
  code *pcVar2;
  bool bVar3;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_004791b6;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  bVar3 = thunk_FUN_0045c732();
  if (!bVar3) {
    FUN_00440100((int *)*param_1);
  }
  local_8 = 0;
  piVar1 = *(int **)(*(int *)(*(int *)*param_1 + 4) + 0x38 + *param_1);
  if ((piVar1 != (int *)0x0) && (pcVar2 = *(code **)(*piVar1 + 8), pcVar2 != guard_check_icall)) {
    (*pcVar2)();
  }
  ExceptionList = local_10;
  return;
}


