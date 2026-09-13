// FUN_00416ab0 @ 00416ab0 size=44 callers=2

uint __thiscall FUN_00416ab0(void *this,uint *param_1,uint param_2,int param_3)

{
  uint in_EAX;
  ulonglong uVar1;
  
  if (*(int *)((int)this + 4) != 0) {
    uVar1 = FUN_0045c870((uint *)(param_3 + *(int *)((int)this + 4)),param_1,param_2);
    return (uint)((int)uVar1 != 0);
  }
  return in_EAX & 0xffffff00;
}


