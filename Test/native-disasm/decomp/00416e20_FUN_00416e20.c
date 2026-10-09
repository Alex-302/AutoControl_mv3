// FUN_00416e20 @ 00416e20 size=91 callers=1

undefined4 __fastcall FUN_00416e20(byte *param_1)

{
  uint *puVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  byte *pbVar5;
  
  uVar3 = DAT_004a26e8;
  uVar4 = *(uint *)(param_1 + 0x18);
  if (uVar4 == DAT_004a26f0) {
    puVar1 = (uint *)(param_1 + 0x10);
    pbVar5 = (byte *)&DAT_004a26d8;
    if (0xf < DAT_004a26ec) {
      pbVar5 = DAT_004a26d8;
    }
    if (0xf < *(uint *)(param_1 + 0x14)) {
      param_1 = *(byte **)param_1;
    }
    uVar2 = *puVar1;
    uVar4 = DAT_004a26e8;
    if (uVar2 < DAT_004a26e8) {
      uVar4 = uVar2;
    }
    uVar4 = FUN_004023d0(param_1,pbVar5,uVar4);
    if (uVar4 == 0) {
      if ((uVar3 <= uVar2) && (uVar2 == uVar3)) {
        return 0;
      }
    }
  }
  return CONCAT31((int3)(uVar4 >> 8),1);
}


