// FUN_00449010 @ 00449010 size=95 callers=3

void __thiscall FUN_00449010(void *this,uint param_1)

{
  uint uVar1;
  
  uVar1 = *(int *)((int)this + 4) - *(int *)this >> 3;
  if (param_1 < uVar1) {
    *(uint *)((int)this + 4) = *(int *)((int)this + 4) + (param_1 - uVar1) * 8;
    return;
  }
  if (uVar1 < param_1) {
    FUN_00449070(this,param_1 - uVar1);
    FUN_004473c0(*(undefined8 **)((int)this + 4),
                 param_1 - ((int)*(undefined8 **)((int)this + 4) - *(int *)this >> 3));
    *(int *)((int)this + 4) =
         *(int *)((int)this + 4) + (param_1 - (*(int *)((int)this + 4) - *(int *)this >> 3)) * 8;
  }
  return;
}


