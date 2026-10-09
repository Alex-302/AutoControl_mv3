// FUN_00432e10 @ 00432e10 size=104 callers=1

void * __thiscall FUN_00432e10(void *this,uint param_1)

{
  void *pvVar1;
  
  *(undefined4 *)this = 0;
  *(undefined4 *)((int)this + 4) = 0;
  *(undefined4 *)((int)this + 8) = 0;
  if (param_1 != 0) {
    if (0x1fffffff < param_1) {
                    /* WARNING: Subroutine does not return */
      FUN_00458ec4("vector<T> too long");
    }
    pvVar1 = FUN_0043eb10(param_1);
    *(void **)this = pvVar1;
    *(void **)((int)this + 4) = pvVar1;
    *(uint *)((int)this + 8) = *(int *)this + param_1 * 8;
    FUN_004473c0(*(undefined8 **)this,param_1);
    *(int *)((int)this + 4) = *(int *)((int)this + 4) + param_1 * 8;
  }
  return this;
}


