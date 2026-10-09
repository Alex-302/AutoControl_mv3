// FUN_004443e0 @ 004443e0 size=105 callers=3

uint __thiscall FUN_004443e0(void *this,ushort *param_1)

{
  uint *puVar1;
  uint *puVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  
  puVar1 = (uint *)(param_1 + 8);
  if (7 < *(uint *)(param_1 + 10)) {
    param_1 = *(ushort **)param_1;
  }
  puVar2 = (uint *)((int)this + 0x10);
  if (7 < *(uint *)((int)this + 0x14)) {
    this = *(void **)this;
  }
  uVar3 = *puVar1;
  uVar4 = *puVar2;
  uVar5 = uVar3;
  if (uVar4 < uVar3) {
    uVar5 = uVar4;
  }
  do {
    if (uVar5 == 0) {
      uVar5 = 0;
LAB_0044440e:
      if (uVar5 == 0) {
        if (uVar4 < uVar3) {
          return 0xffffffff;
        }
        uVar5 = (uint)(uVar3 < uVar4);
      }
      return uVar5;
    }
    if (*(ushort *)this != *param_1) {
      uVar5 = (-(uint)(*(ushort *)this < *param_1) & 0xfffffffe) + 1;
      goto LAB_0044440e;
    }
    this = (void *)((int)this + 2);
    param_1 = param_1 + 1;
    uVar5 = uVar5 - 1;
  } while( true );
}


