// FUN_00434900 @ 00434900 size=55 callers=15

void * __thiscall FUN_00434900(void *this,undefined1 *param_1)

{
  *(undefined1 *)this = *param_1;
  *(undefined4 *)((int)this + 8) = *(undefined4 *)(param_1 + 8);
  *(undefined4 *)((int)this + 0xc) = *(undefined4 *)(param_1 + 0xc);
  *(undefined4 *)(param_1 + 8) = 0;
  *(undefined4 *)(param_1 + 0xc) = 0;
  *param_1 = 0;
  return this;
}


