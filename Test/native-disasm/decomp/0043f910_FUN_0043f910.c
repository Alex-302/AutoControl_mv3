// FUN_0043f910 @ 0043f910 size=67 callers=4

void __fastcall FUN_0043f910(int *param_1)

{
  int *piVar1;
  code *pcVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 uStack_8;
  
  uStack_8 = 0xffffffff;
  puStack_c = &LAB_004790f0;
  local_10 = ExceptionList;
  piVar1 = *(int **)(*(int *)(*(int *)*param_1 + 4) + 0x38 + *param_1);
  if ((piVar1 != (int *)0x0) && (pcVar2 = *(code **)(*piVar1 + 8), pcVar2 != guard_check_icall)) {
    ExceptionList = &local_10;
    (*pcVar2)();
  }
  ExceptionList = local_10;
  return;
}


