// FUN_00447980 @ 00447980 size=81 callers=5

void __thiscall FUN_00447980(void *this,uint *param_1,int param_2)

{
  uint *puVar1;
  void *pvVar2;
  uint uVar3;
  
  *(undefined4 *)this = 0;
  *(undefined4 *)((int)this + 4) = 0;
  *(undefined4 *)((int)this + 8) = 0;
  uVar3 = param_2 - (int)param_1;
  if (uVar3 != 0) {
    pvVar2 = FUN_0043d730(uVar3);
    *(void **)this = pvVar2;
    *(void **)((int)this + 4) = pvVar2;
    *(uint *)((int)this + 8) = *(int *)this + uVar3;
    puVar1 = *(uint **)this;
    FUN_0045b0e0(puVar1,param_1,uVar3);
    *(uint *)((int)this + 4) = uVar3 + (int)puVar1;
  }
  return;
}


