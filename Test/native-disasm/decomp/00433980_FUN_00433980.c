// FUN_00433980 @ 00433980 size=86 callers=3

int * __thiscall FUN_00433980(void *this,int *param_1)

{
  uint uVar1;
  int iVar2;
  
  uVar1 = *(uint *)((int)this + 0xc);
  iVar2 = *(int *)this;
  *param_1 = iVar2;
  param_1[1] = 0;
  if (uVar1 != 0) {
    if (((int)uVar1 < 0) && (uVar1 != 0)) {
      *param_1 = iVar2 - ((~uVar1 >> 5) * 4 + 4);
      param_1[1] = uVar1 & 0x1f;
      return param_1;
    }
    param_1[1] = uVar1 & 0x1f;
    *param_1 = iVar2 + (uVar1 >> 5) * 4;
  }
  return param_1;
}


