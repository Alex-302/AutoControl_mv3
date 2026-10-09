// FUN_00434da0 @ 00434da0 size=73 callers=1

void * __thiscall FUN_00434da0(void *this,uint param_1)

{
  void *pvVar1;
  
  *(undefined4 *)this = 0;
  *(undefined4 *)((int)this + 4) = 0;
  *(undefined4 *)((int)this + 8) = 0;
  if (param_1 != 0) {
    pvVar1 = FUN_0043d730(param_1);
    *(void **)this = pvVar1;
    *(void **)((int)this + 4) = pvVar1;
    *(uint *)((int)this + 8) = *(int *)this + param_1;
    _memset(*(void **)this,0,param_1);
    *(int *)((int)this + 4) = *(int *)((int)this + 4) + param_1;
  }
  return this;
}


