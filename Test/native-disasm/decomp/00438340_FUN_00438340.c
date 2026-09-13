// FUN_00438340 @ 00438340 size=83 callers=9

uint FUN_00438340(byte *param_1,byte *param_2)

{
  uint *puVar1;
  uint *puVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  
  puVar1 = (uint *)(param_2 + 0x10);
  if (0xf < *(uint *)(param_2 + 0x14)) {
    param_2 = *(byte **)param_2;
  }
  puVar2 = (uint *)(param_1 + 0x10);
  if (0xf < *(uint *)(param_1 + 0x14)) {
    param_1 = *(byte **)param_1;
  }
  uVar3 = *puVar1;
  uVar4 = *puVar2;
  uVar5 = uVar3;
  if (uVar4 < uVar3) {
    uVar5 = uVar4;
  }
  uVar5 = FUN_004023d0(param_1,param_2,uVar5);
  if (uVar5 == 0) {
    if (uVar4 < uVar3) {
      return 1;
    }
    uVar5 = 0;
  }
  return uVar5 >> 0x1f;
}


