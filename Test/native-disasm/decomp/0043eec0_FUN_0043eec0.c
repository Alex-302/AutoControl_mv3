// FUN_0043eec0 @ 0043eec0 size=86 callers=2

void __thiscall FUN_0043eec0(void *this,int *param_1,int param_2)

{
  uint uVar1;
  
  uVar1 = *(uint *)((int)this + 4);
  if ((param_2 < 0) && (uVar1 < (uint)-param_2)) {
    *param_1 = *(int *)this + (-(uVar1 + param_2) - 1 >> 5) * -4 + -4;
    param_1[1] = uVar1 + param_2 & 0x1f;
    return;
  }
  *param_1 = *(int *)this + (uVar1 + param_2 >> 5) * 4;
  param_1[1] = uVar1 + param_2 & 0x1f;
  return;
}


