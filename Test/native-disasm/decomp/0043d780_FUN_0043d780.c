// FUN_0043d780 @ 0043d780 size=136 callers=5

void __thiscall FUN_0043d780(void *this,uint param_1)

{
  int iVar1;
  void *pvVar2;
  uint *puVar3;
  
  if (param_1 == 0) {
    puVar3 = (uint *)0x0;
  }
  else if (param_1 < 0x1000) {
    puVar3 = operator_new(param_1);
  }
  else {
    if (param_1 + 0x23 <= param_1) {
                    /* WARNING: Subroutine does not return */
      FUN_00458e6a();
    }
    pvVar2 = operator_new(param_1 + 0x23);
    puVar3 = (uint *)((int)pvVar2 + 0x23U & 0xffffffe0);
    puVar3[-1] = (uint)pvVar2;
  }
  FUN_0045b0e0(puVar3,*(uint **)this,*(int *)((int)this + 4) - (int)*(uint **)this);
  pvVar2 = *(void **)this;
  iVar1 = *(int *)((int)this + 4);
  if (pvVar2 != (void *)0x0) {
    FUN_00402430(pvVar2,*(int *)((int)this + 8) - (int)pvVar2,1);
  }
  *(uint *)((int)this + 8) = (int)puVar3 + param_1;
  *(int *)((int)this + 4) = (int)puVar3 + (iVar1 - (int)pvVar2);
  *(uint **)this = puVar3;
  return;
}


