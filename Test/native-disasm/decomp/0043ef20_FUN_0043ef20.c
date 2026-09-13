// FUN_0043ef20 @ 0043ef20 size=113 callers=11

void __thiscall FUN_0043ef20(void *this,uint param_1,undefined4 *param_2)

{
  undefined4 *puVar1;
  void *pvVar2;
  
  *(undefined4 *)this = 0;
  *(undefined4 *)((int)this + 4) = 0;
  *(undefined4 *)((int)this + 8) = 0;
  if (param_1 != 0) {
    if (0x3fffffff < param_1) {
                    /* WARNING: Subroutine does not return */
      FUN_00458ec4("vector<T> too long");
    }
    pvVar2 = FUN_0043f960(param_1);
    *(void **)this = pvVar2;
    *(void **)((int)this + 4) = pvVar2;
    *(uint *)((int)this + 8) = *(int *)this + param_1 * 4;
    puVar1 = *(undefined4 **)this;
    FUN_00448200(puVar1,param_1,param_2);
    *(undefined4 **)((int)this + 4) = puVar1 + param_1;
  }
  return;
}


