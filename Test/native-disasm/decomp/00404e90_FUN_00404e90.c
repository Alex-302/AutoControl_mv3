// FUN_00404e90 @ 00404e90 size=114 callers=4

bool __fastcall FUN_00404e90(HWND param_1)

{
  uint *puVar1;
  byte *pbVar2;
  uint uVar3;
  uint uVar4;
  bool bVar5;
  void *local_1c [5];
  uint local_8;
  
  pbVar2 = (byte *)FUN_00404670((int *)local_1c,param_1);
  puVar1 = (uint *)(pbVar2 + 0x10);
  if (0xf < *(uint *)(pbVar2 + 0x14)) {
    pbVar2 = *(byte **)pbVar2;
  }
  uVar4 = *puVar1;
  uVar3 = 6;
  if (uVar4 < 6) {
    uVar3 = uVar4;
  }
  uVar3 = FUN_004023d0(pbVar2,(byte *)"#32770",uVar3);
  bVar5 = false;
  if (uVar3 == 0) {
    if (uVar4 < 6) {
      uVar4 = 0xffffffff;
    }
    else {
      uVar4 = (uint)(6 < uVar4);
    }
    bVar5 = uVar4 == 0;
  }
  if (0xf < local_8) {
    FUN_00402430(local_1c[0],local_8 + 1,1);
  }
  return bVar5;
}


