// FUN_0043be50 @ 0043be50 size=131 callers=1

void * __thiscall FUN_0043be50(void *this,byte param_1)

{
  void *pvVar1;
  undefined4 *puVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_004791b6;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  *(undefined ***)this = &PTR_FUN_0048e984;
  FUN_0043df60((int)this);
  pvVar1 = *(void **)((int)this + 0x34);
  *(undefined ***)this = &PTR_FUN_0048e3e8;
  if (pvVar1 != (void *)0x0) {
    local_8 = 0;
    if (*(int **)((int)pvVar1 + 4) != (int *)0x0) {
      puVar2 = (undefined4 *)(**(code **)(**(int **)((int)pvVar1 + 4) + 8))();
      if (puVar2 != (undefined4 *)0x0) {
        (**(code **)*puVar2)(1);
      }
    }
    FUN_0045a6a4(pvVar1);
  }
  if ((param_1 & 1) != 0) {
    FUN_0045a6a4(this);
  }
  ExceptionList = local_10;
  return this;
}


