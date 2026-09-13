// FUN_0043a160 @ 0043a160 size=110 callers=2

int __thiscall FUN_0043a160(void *this,short *param_1,undefined4 param_2,int param_3)

{
  void *pvVar1;
  short *psVar2;
  int iVar3;
  short *psVar4;
  
  if (*(int *)((int)this + 0x10) == 0) {
    return -1;
  }
  pvVar1 = this;
  if (7 < *(uint *)((int)this + 0x14)) {
    pvVar1 = *(void **)this;
  }
  psVar4 = (short *)((int)pvVar1 + (*(int *)((int)this + 0x10) + -1) * 2);
  while (param_3 != 0) {
    psVar2 = param_1;
    iVar3 = param_3;
    while (*psVar2 != *psVar4) {
      psVar2 = psVar2 + 1;
      iVar3 = iVar3 + -1;
      if (iVar3 == 0) goto LAB_0043a19f;
    }
    psVar2 = (short *)FUN_0043a000(this);
    if (psVar4 == psVar2) {
      return -1;
    }
    psVar4 = psVar4 + -1;
  }
LAB_0043a19f:
  if (7 < *(uint *)((int)this + 0x14)) {
    this = *(void **)this;
  }
  return (int)psVar4 - (int)this >> 1;
}


