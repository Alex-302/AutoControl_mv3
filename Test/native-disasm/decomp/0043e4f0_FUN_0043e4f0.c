// FUN_0043e4f0 @ 0043e4f0 size=93 callers=3

void __thiscall FUN_0043e4f0(void *this,uint param_1)

{
  void *pvVar1;
  int iVar2;
  undefined4 *puVar3;
  
  puVar3 = FUN_0043f960(param_1);
  FUN_00450330(*(uint *)this,*(uint *)((int)this + 4),puVar3);
  pvVar1 = *(void **)this;
  iVar2 = *(int *)((int)this + 4);
  if (pvVar1 != (void *)0x0) {
    FUN_00402430(pvVar1,*(int *)((int)this + 8) - (int)pvVar1 >> 2,4);
  }
  *(undefined4 **)((int)this + 8) = puVar3 + param_1;
  *(undefined4 **)((int)this + 4) = puVar3 + (iVar2 - (int)pvVar1 >> 2);
  *(undefined4 **)this = puVar3;
  return;
}


