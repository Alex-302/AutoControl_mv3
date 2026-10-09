// FUN_00453540 @ 00453540 size=130 callers=5

void * __thiscall FUN_00453540(void *this,int *param_1)

{
  void *pvVar1;
  undefined4 uVar2;
  uint uVar3;
  
  *(undefined4 *)this = 0;
  *(undefined4 *)((int)this + 4) = 0;
  *(undefined4 *)((int)this + 8) = 0;
  uVar3 = param_1[1] - *param_1 >> 3;
  *(undefined4 *)this = 0;
  *(undefined4 *)((int)this + 4) = 0;
  *(undefined4 *)((int)this + 8) = 0;
  if (uVar3 != 0) {
    if (0x1fffffff < uVar3) {
                    /* WARNING: Subroutine does not return */
      FUN_00458ec4("vector<T> too long");
    }
    pvVar1 = FUN_0043eb10(uVar3);
    *(void **)this = pvVar1;
    *(void **)((int)this + 4) = pvVar1;
    *(uint *)((int)this + 8) = *(int *)this + uVar3 * 8;
    uVar2 = FUN_00453290((undefined4 *)*param_1,(undefined4 *)param_1[1],*(undefined4 **)this);
    *(undefined4 *)((int)this + 4) = uVar2;
  }
  return this;
}


