// FUN_00456100 @ 00456100 size=145 callers=2

void * __thiscall FUN_00456100(void *this,int *param_1)

{
  int *piVar1;
  undefined4 uVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0047eb40;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  *(undefined ***)this = &PTR_LAB_0048ec98;
  *(undefined4 *)((int)this + 0x2c) = 0;
  local_8 = 1;
  piVar1 = (int *)param_1[9];
  if (piVar1 != (int *)0x0) {
    if (piVar1 == param_1) {
      uVar2 = (**(code **)(*piVar1 + 4))((int)this + 8);
      *(undefined4 *)((int)this + 0x2c) = uVar2;
      piVar1 = (int *)param_1[9];
      if (piVar1 == (int *)0x0) {
        ExceptionList = local_10;
        return this;
      }
      (**(code **)(*piVar1 + 0x10))(piVar1 != param_1);
    }
    else {
      *(int **)((int)this + 0x2c) = piVar1;
    }
    param_1[9] = 0;
  }
  ExceptionList = local_10;
  return this;
}


