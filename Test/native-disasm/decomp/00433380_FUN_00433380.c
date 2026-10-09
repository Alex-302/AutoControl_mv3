// FUN_00433380 @ 00433380 size=112 callers=3

void * __thiscall FUN_00433380(void *this,int *param_1)

{
  int *piVar1;
  undefined4 uVar2;
  
  if (this != param_1) {
    piVar1 = *(int **)((int)this + 0x24);
    if (piVar1 != (int *)0x0) {
      (**(code **)(*piVar1 + 0x10))(piVar1 != this);
      *(undefined4 *)((int)this + 0x24) = 0;
    }
    piVar1 = (int *)param_1[9];
    if (piVar1 != (int *)0x0) {
      if (piVar1 == param_1) {
        uVar2 = (**(code **)(*piVar1 + 4))(this);
        *(undefined4 *)((int)this + 0x24) = uVar2;
        piVar1 = (int *)param_1[9];
        if (piVar1 != (int *)0x0) {
          (**(code **)(*piVar1 + 0x10))(piVar1 != param_1);
          param_1[9] = 0;
          return this;
        }
      }
      else {
        *(int **)((int)this + 0x24) = piVar1;
        param_1[9] = 0;
      }
    }
  }
  return this;
}


