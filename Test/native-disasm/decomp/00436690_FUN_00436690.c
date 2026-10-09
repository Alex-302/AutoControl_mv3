// FUN_00436690 @ 00436690 size=86 callers=1

uint __thiscall FUN_00436690(void *this,uint param_1)

{
  uint in_EAX;
  void *pvVar1;
  int iVar2;
  
  *(undefined4 *)this = 0;
  *(undefined4 *)((int)this + 4) = 0;
  *(undefined4 *)((int)this + 8) = 0;
  if (param_1 == 0) {
    return in_EAX & 0xffffff00;
  }
  if (param_1 < 0xfc0fc1) {
    pvVar1 = FUN_0043e5e0(param_1);
    *(void **)this = pvVar1;
    *(void **)((int)this + 4) = pvVar1;
    iVar2 = param_1 * 0x104 + *(int *)this;
    *(int *)((int)this + 8) = iVar2;
    return CONCAT31((int3)((uint)iVar2 >> 8),1);
  }
                    /* WARNING: Subroutine does not return */
  FUN_00458ec4("vector<T> too long");
}


