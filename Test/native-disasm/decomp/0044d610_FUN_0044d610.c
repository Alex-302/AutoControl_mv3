// FUN_0044d610 @ 0044d610 size=95 callers=1

void __thiscall FUN_0044d610(void *this,uint param_1)

{
  uint uVar1;
  
  uVar1 = *(int *)((int)this + 4) - *(int *)this >> 3;
  if (param_1 < uVar1) {
    *(uint *)((int)this + 4) = *(int *)((int)this + 4) + (param_1 - uVar1) * 8;
    return;
  }
  if (uVar1 < param_1) {
    FUN_0044d990(this,param_1 - uVar1);
    FUN_00453370(*(undefined8 **)((int)this + 4),
                 param_1 - ((int)*(undefined8 **)((int)this + 4) - *(int *)this >> 3));
    *(int *)((int)this + 4) =
         *(int *)((int)this + 4) + (param_1 - (*(int *)((int)this + 4) - *(int *)this >> 3)) * 8;
  }
  return;
}


