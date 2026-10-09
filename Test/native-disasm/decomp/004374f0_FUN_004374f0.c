// FUN_004374f0 @ 004374f0 size=164 callers=2

void __thiscall FUN_004374f0(void *this,uint param_1)

{
  uint *puVar1;
  int iVar2;
  void *pvVar3;
  
  pvVar3 = FUN_0043ec10(param_1);
  FUN_0044fcf0(*(undefined4 **)this,*(undefined4 **)((int)this + 4),pvVar3);
  puVar1 = *(uint **)this;
  iVar2 = *(int *)((int)this + 4);
  if (puVar1 != (uint *)0x0) {
    FUN_00447f50(puVar1,*(uint **)((int)this + 4));
    FUN_00402430(*(void **)this,(*(int *)((int)this + 8) - (int)*(void **)this) / 0x24,0x24);
  }
  *(void **)((int)this + 8) = (void *)((int)pvVar3 + param_1 * 0x24);
  *(void **)((int)this + 4) = (void *)((int)pvVar3 + ((iVar2 - (int)puVar1) / 0x24) * 0x24);
  *(void **)this = pvVar3;
  return;
}


