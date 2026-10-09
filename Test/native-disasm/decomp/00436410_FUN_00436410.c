// FUN_00436410 @ 00436410 size=153 callers=3

undefined4 * __thiscall FUN_00436410(void *this,undefined4 *param_1,int *param_2,int *param_3)

{
  int *piVar1;
  void **ppvVar2;
  void *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_004791a6;
  local_10 = ExceptionList;
  ppvVar2 = &local_10;
  local_14 = this;
  if ((param_2 == (int *)**(int **)((int)this + 4)) &&
     (ppvVar2 = &local_10, param_3 == *(int **)((int)this + 4))) {
    local_8 = 0;
    ExceptionList = &local_10;
    FUN_004362e0((int *)((int)this + 4));
    FUN_00435e50(this,8);
    *param_1 = **(undefined4 **)((int)this + 4);
    ExceptionList = local_10;
    return param_1;
  }
  while (ExceptionList = ppvVar2, param_2 != param_3) {
    piVar1 = (int *)*param_2;
    FUN_0043c440(this,(int *)&local_14,param_2);
    ppvVar2 = ExceptionList;
    param_2 = piVar1;
  }
  *param_1 = param_2;
  ExceptionList = local_10;
  return param_1;
}


