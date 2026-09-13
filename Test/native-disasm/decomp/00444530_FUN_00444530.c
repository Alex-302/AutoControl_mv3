// FUN_00444530 @ 00444530 size=164 callers=1

void __thiscall FUN_00444530(void *this,uint param_1)

{
  int *piVar1;
  int iVar2;
  void *pvVar3;
  
  pvVar3 = FUN_0043ffd0(param_1);
  FUN_00453250(*(undefined4 **)this,*(undefined4 **)((int)this + 4),pvVar3);
  piVar1 = *(int **)this;
  iVar2 = *(int *)((int)this + 4);
  if (piVar1 != (int *)0x0) {
    FUN_00447eb0(piVar1,*(int **)((int)this + 4));
    FUN_00402430(*(void **)this,(*(int *)((int)this + 8) - (int)*(void **)this) / 0x18,0x18);
  }
  *(void **)((int)this + 8) = (void *)((int)pvVar3 + param_1 * 0x18);
  *(void **)((int)this + 4) = (void *)((int)pvVar3 + ((iVar2 - (int)piVar1) / 0x18) * 0x18);
  *(void **)this = pvVar3;
  return;
}


