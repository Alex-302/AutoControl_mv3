// FUN_0043b330 @ 0043b330 size=223 callers=1

int * __fastcall FUN_0043b330(int *param_1)

{
  int *piVar1;
  int *piVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0047de4a;
  local_10 = ExceptionList;
  piVar1 = param_1 + 4;
  ExceptionList = &local_10;
  *param_1 = (int)&DAT_0048eeb8;
  *piVar1 = (int)&DAT_0048e7e8;
  param_1[0x1a] = (int)&PTR_FUN_0048e888;
  local_8 = 0;
  piVar2 = param_1 + 6;
  FUN_0043f780(param_1,piVar2);
  *(undefined ***)((int)piVar1 + *(int *)(*piVar1 + 4)) = &PTR_LAB_0048f09c;
  *(int *)(*(int *)(*piVar1 + 4) + -4 + (int)piVar1) = *(int *)(*piVar1 + 4) + -8;
  *(undefined ***)((int)param_1 + *(int *)(*param_1 + 4)) = &PTR_LAB_0048e968;
  *(int *)(*(int *)(*param_1 + 4) + -4 + (int)param_1) = *(int *)(*param_1 + 4) + -0x20;
  local_8 = 4;
  *(undefined ***)((int)param_1 + *(int *)(*param_1 + 4)) = &PTR_LAB_0048eb44;
  *(int *)(*(int *)(*param_1 + 4) + -4 + (int)param_1) = *(int *)(*param_1 + 4) + -0x68;
  FUN_0043f820(piVar2);
  *piVar2 = (int)&PTR_FUN_0048e984;
  param_1[0x14] = 0;
  param_1[0x15] = 0;
  ExceptionList = local_10;
  return param_1;
}


