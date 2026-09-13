// FUN_004490d0 @ 004490d0 size=91 callers=1

void __thiscall FUN_004490d0(void *this,uint param_1)

{
  void *pvVar1;
  int iVar2;
  uint *puVar3;
  
  puVar3 = FUN_0043eb10(param_1);
  FUN_0045b0e0(puVar3,*(uint **)this,*(int *)((int)this + 4) - (int)*(uint **)this);
  pvVar1 = *(void **)this;
  iVar2 = *(int *)((int)this + 4);
  if (pvVar1 != (void *)0x0) {
    FUN_00402430(pvVar1,*(int *)((int)this + 8) - (int)pvVar1 >> 3,8);
  }
  *(uint **)((int)this + 8) = puVar3 + param_1 * 2;
  *(uint **)((int)this + 4) = puVar3 + (iVar2 - (int)pvVar1 >> 3) * 2;
  *(uint **)this = puVar3;
  return;
}


