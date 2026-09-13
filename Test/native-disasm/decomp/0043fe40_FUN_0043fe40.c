// FUN_0043fe40 @ 0043fe40 size=83 callers=1

uint __thiscall FUN_0043fe40(void *this,uint param_1)

{
  int iVar1;
  uint in_EAX;
  void *pvVar2;
  
  *(undefined4 *)this = 0;
  *(undefined4 *)((int)this + 4) = 0;
  *(undefined4 *)((int)this + 8) = 0;
  if (param_1 == 0) {
    return in_EAX & 0xffffff00;
  }
  if (param_1 < 0x40000000) {
    pvVar2 = FUN_0043f960(param_1);
    *(void **)this = pvVar2;
    *(void **)((int)this + 4) = pvVar2;
    iVar1 = *(int *)this + param_1 * 4;
    *(int *)((int)this + 8) = iVar1;
    return CONCAT31((int3)((uint)iVar1 >> 8),1);
  }
                    /* WARNING: Subroutine does not return */
  FUN_00458ec4("vector<T> too long");
}


