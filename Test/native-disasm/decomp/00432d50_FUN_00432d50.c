// FUN_00432d50 @ 00432d50 size=116 callers=12

void __thiscall FUN_00432d50(void *this,int *param_1,byte *param_2)

{
  uint *puVar1;
  undefined4 *puVar2;
  uint uVar3;
  undefined4 *puVar4;
  uint uVar5;
  uint uVar6;
  byte *pbVar7;
  
  puVar4 = FUN_00442a70(this,param_2);
  puVar2 = *(undefined4 **)this;
  if (puVar4 != puVar2) {
    pbVar7 = (byte *)(puVar4 + 4);
    if (0xf < (uint)puVar4[9]) {
      pbVar7 = *(byte **)pbVar7;
    }
    puVar1 = (uint *)(param_2 + 0x10);
    if (0xf < *(uint *)(param_2 + 0x14)) {
      param_2 = *(byte **)param_2;
    }
    uVar6 = *puVar1;
    uVar3 = puVar4[8];
    uVar5 = uVar3;
    if (uVar6 < uVar3) {
      uVar5 = uVar6;
    }
    uVar6 = FUN_004023d0(param_2,pbVar7,uVar5);
    if (uVar6 == 0) {
      if (uVar3 <= *puVar1) {
LAB_00432db7:
        *param_1 = (int)puVar4;
        return;
      }
    }
    else if (-1 < (int)uVar6) goto LAB_00432db7;
  }
  *param_1 = (int)puVar2;
  return;
}


