// FUN_00447eb0 @ 00447eb0 size=148 callers=3

void __fastcall FUN_00447eb0(int *param_1,int *param_2)

{
  int *piVar1;
  undefined4 *puVar2;
  int iVar3;
  void **ppvVar4;
  undefined4 *puVar5;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_004791a6;
  ppvVar4 = &local_10;
  local_10 = ExceptionList;
  for (; ExceptionList = ppvVar4, param_1 != param_2; param_1 = param_1 + 6) {
    local_8 = 0xffffffff;
    if (*param_1 != 0) {
      LOCK();
      piVar1 = (int *)(*param_1 + 0x20);
      iVar3 = *piVar1 + -1;
      *piVar1 = iVar3;
      UNLOCK();
      if (iVar3 == 0) {
        puVar5 = (undefined4 *)*param_1;
        while (puVar5 != (undefined4 *)0x0) {
          puVar2 = (undefined4 *)puVar5[3];
          puVar5[3] = 0;
          (**(code **)*puVar5)(1);
          puVar5 = puVar2;
        }
      }
    }
    *param_1 = 0;
    local_8 = 0;
    if (((int *)param_1[4] != (int *)0x0) &&
       (puVar5 = (undefined4 *)(**(code **)(*(int *)param_1[4] + 8))(), puVar5 != (undefined4 *)0x0)
       ) {
      (**(code **)*puVar5)(1);
    }
    ppvVar4 = ExceptionList;
  }
  ExceptionList = local_10;
  return;
}


