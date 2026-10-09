// FUN_00457c20 @ 00457c20 size=114 callers=1

void __thiscall FUN_00457c20(void *this,char *param_1,char *param_2)

{
  void *pvVar1;
  undefined1 *puVar2;
  uint uVar3;
  
  *(undefined4 *)this = 0;
  *(undefined4 *)((int)this + 4) = 0;
  *(undefined4 *)((int)this + 8) = 0;
  uVar3 = (int)param_2 - (int)param_1;
  if (uVar3 != 0) {
    if (0xfffffff < uVar3) {
                    /* WARNING: Subroutine does not return */
      FUN_00458ec4("vector<T> too long");
    }
    pvVar1 = FUN_0043fde0(uVar3);
    *(void **)this = pvVar1;
    *(void **)((int)this + 4) = pvVar1;
    *(uint *)((int)this + 8) = uVar3 * 0x10 + *(int *)this;
    puVar2 = FUN_004582f0(param_1,param_2,*(undefined1 **)this);
    *(undefined1 **)((int)this + 4) = puVar2;
  }
  return;
}


