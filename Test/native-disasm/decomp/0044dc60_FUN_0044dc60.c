// FUN_0044dc60 @ 0044dc60 size=139 callers=1

void __thiscall FUN_0044dc60(void *this,uint param_1)

{
  int iVar1;
  int iVar2;
  undefined8 *puVar3;
  
  puVar3 = FUN_0044dcf0(param_1);
  FUN_004561a0(*(undefined8 **)this,*(undefined8 **)((int)this + 4),puVar3);
  iVar1 = *(int *)((int)this + 4);
  iVar2 = *(int *)this;
  if (*(int *)this != 0) {
    FUN_00402430(*(void **)this,(*(int *)((int)this + 8) - *(int *)this) / 0xc,0xc);
  }
  *(uint *)((int)this + 8) = (int)puVar3 + param_1 * 0xc;
  *(int *)((int)this + 4) = (int)puVar3 + ((iVar1 - iVar2) / 0xc) * 0xc;
  *(undefined8 **)this = puVar3;
  return;
}


