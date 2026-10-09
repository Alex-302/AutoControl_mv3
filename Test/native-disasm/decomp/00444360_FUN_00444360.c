// FUN_00444360 @ 00444360 size=123 callers=8

uint __thiscall FUN_00444360(void *this,ushort *param_1)

{
  uint *puVar1;
  ushort uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  ushort *puVar6;
  
  if (*param_1 == 0) {
    uVar5 = 0;
  }
  else {
    puVar6 = param_1;
    do {
      uVar2 = *puVar6;
      puVar6 = puVar6 + 1;
    } while (uVar2 != 0);
    uVar5 = (int)puVar6 - (int)(param_1 + 1) >> 1;
  }
  puVar1 = (uint *)((int)this + 0x10);
  if (7 < *(uint *)((int)this + 0x14)) {
    this = *(void **)this;
  }
  uVar3 = *puVar1;
  uVar4 = uVar5;
  if (uVar3 < uVar5) {
    uVar4 = uVar3;
  }
  do {
    if (uVar4 == 0) {
      uVar4 = 0;
LAB_0044439f:
      if (uVar4 == 0) {
        if (uVar3 < uVar5) {
          return 0xffffffff;
        }
        uVar4 = (uint)(uVar5 < uVar3);
      }
      return uVar4;
    }
    if (*(ushort *)this != *param_1) {
      uVar4 = (-(uint)(*(ushort *)this < *param_1) & 0xfffffffe) + 1;
      goto LAB_0044439f;
    }
    this = (void *)((int)this + 2);
    param_1 = param_1 + 1;
    uVar4 = uVar4 - 1;
  } while( true );
}


