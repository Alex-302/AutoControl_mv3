// FUN_0043c700 @ 0043c700 size=231 callers=3

undefined4 * __thiscall FUN_0043c700(void *this,undefined4 *param_1,int *param_2,int *param_3)

{
  char cVar1;
  int *piVar2;
  int *piVar3;
  void **ppvVar4;
  int *piVar5;
  void *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_004791a6;
  local_10 = ExceptionList;
  piVar2 = *(int **)this;
  ppvVar4 = &local_10;
  local_14 = this;
  piVar3 = param_2;
  if ((param_2 == (int *)*piVar2) && (ppvVar4 = &local_10, param_3 == piVar2)) {
    local_8 = 0;
    ExceptionList = &local_10;
    FUN_0043fd50((int *)piVar2[1]);
    *(int *)(*(int *)this + 4) = *(int *)this;
    *(undefined4 *)*(undefined4 *)this = *(undefined4 *)this;
    *(int *)(*(int *)this + 8) = *(int *)this;
    *(undefined4 *)((int)this + 4) = 0;
    *param_1 = **(undefined4 **)this;
    ExceptionList = local_10;
    return param_1;
  }
  while (ExceptionList = ppvVar4, piVar3 != param_3) {
    param_2 = piVar3;
    if (*(char *)((int)piVar3 + 0xd) == '\0') {
      param_2 = (int *)piVar3[2];
      if (*(char *)((int)param_2 + 0xd) == '\0') {
        cVar1 = *(char *)(*param_2 + 0xd);
        piVar2 = (int *)*param_2;
        while (cVar1 == '\0') {
          cVar1 = *(char *)(*piVar2 + 0xd);
          param_2 = piVar2;
          piVar2 = (int *)*piVar2;
        }
      }
      else {
        cVar1 = *(char *)(piVar3[1] + 0xd);
        piVar5 = (int *)piVar3[1];
        piVar2 = piVar3;
        while ((param_2 = piVar5, cVar1 == '\0' && (piVar2 == (int *)param_2[2]))) {
          cVar1 = *(char *)(param_2[1] + 0xd);
          piVar5 = (int *)param_2[1];
          piVar2 = param_2;
        }
      }
    }
    FUN_0043e830(this,&local_14,piVar3);
    ppvVar4 = ExceptionList;
    piVar3 = param_2;
  }
  *param_1 = piVar3;
  ExceptionList = local_10;
  return param_1;
}


