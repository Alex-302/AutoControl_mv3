// FUN_0043e460 @ 0043e460 size=136 callers=1

void * __thiscall FUN_0043e460(void *this,int *param_1)

{
  int *piVar1;
  code *pcVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047def8;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  *(int **)this = param_1;
  piVar1 = *(int **)(*(int *)(*param_1 + 4) + 0x38 + (int)param_1);
  if ((piVar1 != (int *)0x0) && (pcVar2 = *(code **)(*piVar1 + 4), pcVar2 != guard_check_icall)) {
    (*pcVar2)();
  }
  local_8 = 0;
  if (((*(int *)(*(int *)(*param_1 + 4) + 0xc + (int)param_1) == 0) &&
      (piVar1 = *(int **)(*(int *)(*param_1 + 4) + 0x3c + (int)param_1), piVar1 != (int *)0x0)) &&
     (piVar1 != param_1)) {
    FUN_00440030(piVar1);
  }
  *(bool *)((int)this + 4) = *(int *)(*(int *)(*param_1 + 4) + 0xc + (int)param_1) == 0;
  ExceptionList = local_10;
  return this;
}


