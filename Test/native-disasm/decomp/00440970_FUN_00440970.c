// FUN_00440970 @ 00440970 size=85 callers=6

bool __fastcall FUN_00440970(byte *param_1,byte *param_2)

{
  uint *puVar1;
  byte bVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  byte *pbVar6;
  bool bVar7;
  
  if (*param_2 == 0) {
    uVar5 = 0;
  }
  else {
    pbVar6 = param_2;
    do {
      bVar2 = *pbVar6;
      pbVar6 = pbVar6 + 1;
    } while (bVar2 != 0);
    uVar5 = (int)pbVar6 - (int)(param_2 + 1);
  }
  puVar1 = (uint *)(param_1 + 0x10);
  if (0xf < *(uint *)(param_1 + 0x14)) {
    param_1 = *(byte **)param_1;
  }
  uVar3 = *puVar1;
  uVar4 = uVar5;
  if (uVar3 < uVar5) {
    uVar4 = uVar3;
  }
  uVar4 = FUN_004023d0(param_1,param_2,uVar4);
  bVar7 = false;
  if ((uVar4 == 0) && (bVar7 = uVar3 <= uVar5, uVar3 < uVar5)) {
    return false;
  }
  return bVar7;
}


