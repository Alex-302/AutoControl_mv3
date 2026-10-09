// FUN_00432a70 @ 00432a70 size=71 callers=1

void * __thiscall FUN_00432a70(void *this,uint param_1)

{
  uint uVar1;
  
  *(undefined4 *)this = 0;
  *(undefined4 *)((int)this + 4) = 0;
  *(undefined4 *)((int)this + 8) = 0;
  uVar1 = FUN_00436690(this,param_1);
  if ((char)uVar1 != '\0') {
    FUN_00447350(*(void **)this,param_1);
    *(int *)((int)this + 4) = *(int *)((int)this + 4) + param_1 * 0x104;
  }
  return this;
}


