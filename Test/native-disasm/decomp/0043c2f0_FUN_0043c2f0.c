// FUN_0043c2f0 @ 0043c2f0 size=154 callers=1

void __thiscall FUN_0043c2f0(void *this,uint param_1)

{
  int *piVar1;
  undefined4 *puVar2;
  int iVar3;
  int *piVar4;
  
  puVar2 = FUN_0043f960(param_1);
  FUN_0044ffc0(*(uint *)this,*(uint *)((int)this + 4),puVar2);
  piVar1 = *(int **)((int)this + 4);
  piVar4 = *(int **)this;
  iVar3 = (int)piVar1 - (int)piVar4;
  if (piVar4 != (int *)0x0) {
    for (; piVar4 != piVar1; piVar4 = piVar4 + 1) {
      if ((undefined4 *)*piVar4 != (undefined4 *)0x0) {
        (*(code *)**(undefined4 **)*piVar4)(1);
      }
    }
    FUN_00402430(*(void **)this,*(int *)((int)this + 8) - (int)*(void **)this >> 2,4);
  }
  *(undefined4 **)((int)this + 8) = puVar2 + param_1;
  *(undefined4 **)((int)this + 4) = puVar2 + (iVar3 >> 2);
  *(undefined4 **)this = puVar2;
  return;
}


