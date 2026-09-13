// FUN_0043ca10 @ 0043ca10 size=80 callers=3

void __thiscall FUN_0043ca10(void *this,undefined4 *param_1,uint *param_2,uint *param_3)

{
  uint uVar1;
  
  if ((param_2 == *(uint **)this) && (param_3 == *(uint **)((int)this + 4))) {
    *(uint **)((int)this + 4) = *(uint **)this;
  }
  else if (param_2 != param_3) {
    uVar1 = *(int *)((int)this + 4) - (int)param_3;
    FUN_0045b0e0(param_2,param_3,uVar1);
    *(uint *)((int)this + 4) = uVar1 + (int)param_2;
    *param_1 = param_2;
    return;
  }
  *param_1 = param_2;
  return;
}


