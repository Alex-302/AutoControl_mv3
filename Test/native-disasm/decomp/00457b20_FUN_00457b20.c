// FUN_00457b20 @ 00457b20 size=119 callers=1

void __thiscall FUN_00457b20(void *this,int *param_1,int *param_2)

{
  void *pvVar1;
  char *pcVar2;
  uint uVar3;
  
  uVar3 = (int)param_2 - (int)param_1 >> 2;
  *(undefined4 *)this = 0;
  *(undefined4 *)((int)this + 4) = 0;
  *(undefined4 *)((int)this + 8) = 0;
  if (uVar3 != 0) {
    if (0xfffffff < uVar3) {
                    /* WARNING: Subroutine does not return */
      FUN_00458ec4("vector<T> too long");
    }
    pvVar1 = FUN_0043fde0(uVar3);
    *(void **)this = pvVar1;
    *(void **)((int)this + 4) = pvVar1;
    *(uint *)((int)this + 8) = uVar3 * 0x10 + *(int *)this;
    pcVar2 = FUN_00458200(param_1,param_2,*(char **)this);
    *(char **)((int)this + 4) = pcVar2;
  }
  return;
}


