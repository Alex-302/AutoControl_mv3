// FUN_0044dac0 @ 0044dac0 size=114 callers=2

void * __thiscall FUN_0044dac0(void *this,int param_1,int param_2,uint *param_3,uint *param_4)

{
  void *pvVar1;
  
  if (param_3 != param_4) {
    pvVar1 = this;
    if (0xf < *(uint *)((int)this + 0x14)) {
      pvVar1 = *(void **)this;
    }
    FUN_00444e40(this,(void *)(param_1 - (int)pvVar1),(void *)(param_2 - param_1),param_3,
                 (void *)((int)param_4 - (int)param_3));
    return this;
  }
  if (*(uint *)((int)this + 0x14) < 0x10) {
    FUN_004354d0(this,param_1 - (int)this,param_2 - param_1);
    return this;
  }
  FUN_004354d0(this,param_1 - *(int *)this,param_2 - param_1);
  return this;
}


