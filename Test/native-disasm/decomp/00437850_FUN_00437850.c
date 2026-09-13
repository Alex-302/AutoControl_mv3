// FUN_00437850 @ 00437850 size=101 callers=1

void * __thiscall FUN_00437850(void *this,undefined4 *param_1)

{
  void *pvVar1;
  
  if (this != param_1) {
    pvVar1 = *(void **)this;
    if (pvVar1 != (void *)0x0) {
      FUN_00402430(pvVar1,*(int *)((int)this + 8) - (int)pvVar1 >> 2,4);
      *(undefined4 *)this = 0;
      *(undefined4 *)((int)this + 4) = 0;
      *(undefined4 *)((int)this + 8) = 0;
    }
    *(undefined4 *)this = *param_1;
    *(undefined4 *)((int)this + 4) = param_1[1];
    *(undefined4 *)((int)this + 8) = param_1[2];
    *param_1 = 0;
    param_1[1] = 0;
    param_1[2] = 0;
  }
  return this;
}


