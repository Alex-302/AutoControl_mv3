// FUN_0044d8d0 @ 0044d8d0 size=63 callers=1

void __thiscall FUN_0044d8d0(void *this,uint *param_1,uint *param_2)

{
  int iVar1;
  void *pvVar2;
  
  pvVar2 = this;
  if (0xf < *(uint *)((int)this + 0x14)) {
    pvVar2 = *(void **)this;
  }
  iVar1 = *(int *)((int)this + 0x10) + (int)pvVar2;
  if (*(uint *)((int)this + 0x14) < 0x10) {
    FUN_0044dac0(this,(int)this,iVar1,param_1,param_2);
    return;
  }
  FUN_0044dac0(this,*(int *)this,iVar1,param_1,param_2);
  return;
}


