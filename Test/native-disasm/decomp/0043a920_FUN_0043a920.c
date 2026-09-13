// FUN_0043a920 @ 0043a920 size=105 callers=9

void __thiscall FUN_0043a920(void *this,uint *param_1)

{
  if (param_1[5] < 8) {
    if (param_1[4] + 1 != 0) {
      FUN_0045b0e0(this,param_1,(param_1[4] + 1) * 2);
    }
  }
  else {
    if (this != (void *)0x0) {
      *(uint *)this = *param_1;
    }
    *param_1 = 0;
  }
  *(uint *)((int)this + 0x10) = param_1[4];
  *(uint *)((int)this + 0x14) = param_1[5];
  param_1[5] = 7;
  param_1[4] = 0;
  if (7 < param_1[5]) {
    *(undefined2 *)*param_1 = 0;
    return;
  }
  *(undefined2 *)param_1 = 0;
  return;
}


