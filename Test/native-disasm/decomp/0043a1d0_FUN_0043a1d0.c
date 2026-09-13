// FUN_0043a1d0 @ 0043a1d0 size=115 callers=1

int __thiscall FUN_0043a1d0(void *this,undefined4 param_1,undefined4 param_2,int param_3)

{
  short *psVar1;
  short *psVar2;
  void *pvVar3;
  int iVar4;
  
  if (*(int *)((int)this + 0x10) != 0) {
    pvVar3 = this;
    if (7 < *(uint *)((int)this + 0x14)) {
      pvVar3 = *(void **)this;
    }
    psVar1 = this;
    if (7 < *(uint *)((int)this + 0x14)) {
      psVar1 = *(short **)this;
    }
    for (; psVar1 < (short *)((int)pvVar3 + *(int *)((int)this + 0x10) * 2); psVar1 = psVar1 + 1) {
      if (param_3 == 0) {
LAB_0043a21d:
        if (7 < *(uint *)((int)this + 0x14)) {
          this = *(void **)this;
        }
        return (int)psVar1 - (int)this >> 1;
      }
      psVar2 = &DAT_0048cc44;
      iVar4 = param_3;
      while (*psVar2 != *psVar1) {
        psVar2 = psVar2 + 1;
        iVar4 = iVar4 + -1;
        if (iVar4 == 0) goto LAB_0043a21d;
      }
    }
  }
  return -1;
}


