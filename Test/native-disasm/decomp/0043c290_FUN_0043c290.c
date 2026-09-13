// FUN_0043c290 @ 0043c290 size=91 callers=2

void __thiscall FUN_0043c290(void *this,uint param_1)

{
  void *pvVar1;
  int iVar2;
  uint *puVar3;
  
  puVar3 = FUN_0043f960(param_1);
  FUN_0045b0e0(puVar3,*(uint **)this,*(int *)((int)this + 4) - (int)*(uint **)this);
  pvVar1 = *(void **)this;
  iVar2 = *(int *)((int)this + 4);
  if (pvVar1 != (void *)0x0) {
    FUN_00402430(pvVar1,*(int *)((int)this + 8) - (int)pvVar1 >> 2,4);
  }
  *(uint **)((int)this + 8) = puVar3 + param_1;
  *(uint **)((int)this + 4) = puVar3 + (iVar2 - (int)pvVar1 >> 2);
  *(uint **)this = puVar3;
  return;
}


