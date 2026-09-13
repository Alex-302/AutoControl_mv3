// FUN_00432ba0 @ 00432ba0 size=77 callers=2

void * __thiscall FUN_00432ba0(void *this,uint param_1)

{
  uint uVar1;
  
  *(undefined4 *)this = 0;
  *(undefined4 *)((int)this + 4) = 0;
  *(undefined4 *)((int)this + 8) = 0;
  uVar1 = FUN_004367b0(this,param_1);
  if ((char)uVar1 != '\0') {
    FUN_00447390(*(undefined4 **)this,param_1);
    *(int *)((int)this + 4) = *(int *)((int)this + 4) + param_1 * 0x1c;
  }
  return this;
}


