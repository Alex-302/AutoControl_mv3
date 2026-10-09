// FUN_0043b1c0 @ 0043b1c0 size=99 callers=34

void __thiscall FUN_0043b1c0(void *this,uint *param_1)

{
  if (param_1[5] < 0x10) {
    if (param_1[4] + 1 != 0) {
      FUN_0045b0e0(this,param_1,param_1[4] + 1);
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
  param_1[5] = 0xf;
  param_1[4] = 0;
  if (0xf < param_1[5]) {
    *(undefined1 *)*param_1 = 0;
    return;
  }
  *(undefined1 *)param_1 = 0;
  return;
}


