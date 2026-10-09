// FUN_004352c0 @ 004352c0 size=117 callers=1

uint __thiscall FUN_004352c0(void *this,uint param_1,undefined4 param_2,byte *param_3)

{
  byte bVar1;
  uint uVar2;
  uint uVar3;
  byte *pbVar4;
  uint uVar5;
  
  if (*(uint *)((int)this + 0x10) < param_1) {
                    /* WARNING: Subroutine does not return */
    FUN_00458ee4("invalid string position");
  }
  if (*param_3 == 0) {
    uVar3 = 0;
  }
  else {
    pbVar4 = param_3;
    do {
      bVar1 = *pbVar4;
      pbVar4 = pbVar4 + 1;
    } while (bVar1 != 0);
    uVar3 = (int)pbVar4 - (int)(param_3 + 1);
  }
  uVar5 = *(uint *)((int)this + 0x10) - param_1;
  if (uVar5 == 0xffffffff) {
    uVar5 = 0xffffffff;
  }
  if (0xf < *(uint *)((int)this + 0x14)) {
    this = *(void **)this;
  }
  uVar2 = uVar3;
  if (uVar5 < uVar3) {
    uVar2 = uVar5;
  }
  uVar2 = FUN_004023d0((byte *)((int)this + param_1),param_3,uVar2);
  if (uVar2 == 0) {
    if (uVar5 < uVar3) {
      return 0xffffffff;
    }
    uVar2 = (uint)(uVar3 < uVar5);
  }
  return uVar2;
}


