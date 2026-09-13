// FUN_00442a70 @ 00442a70 size=206 callers=4

undefined4 * __thiscall FUN_00442a70(void *this,byte *param_1)

{
  char cVar1;
  uint uVar2;
  undefined4 *puVar3;
  byte *pbVar4;
  uint uVar5;
  uint uVar6;
  byte *pbVar7;
  undefined4 *puVar8;
  bool bVar9;
  undefined4 *local_4;
  
  local_4 = (undefined4 *)(*(undefined4 **)this)[1];
  cVar1 = *(char *)((int)local_4 + 0xd);
  puVar3 = *(undefined4 **)this;
  do {
    if (cVar1 != '\0') {
      return puVar3;
    }
    pbVar4 = (byte *)(local_4 + 4);
    pbVar7 = param_1;
    if (0xf < *(uint *)(param_1 + 0x14)) {
      pbVar7 = *(byte **)param_1;
    }
    if (0xf < (uint)local_4[9]) {
      pbVar4 = *(byte **)pbVar4;
    }
    uVar2 = local_4[8];
    uVar5 = *(uint *)(param_1 + 0x10);
    uVar6 = uVar5;
    if (uVar2 < uVar5) {
      uVar6 = uVar2;
    }
    if (uVar6 == 0) {
LAB_00442b30:
      if (uVar2 < uVar5) goto LAB_00442b12;
LAB_00442b34:
      puVar8 = (undefined4 *)*local_4;
    }
    else {
      while (uVar5 = uVar6 - 4, 3 < uVar6) {
        if (*(int *)pbVar4 != *(int *)pbVar7) goto LAB_00442ad6;
        pbVar4 = pbVar4 + 4;
        pbVar7 = pbVar7 + 4;
        uVar6 = uVar5;
      }
      if (uVar5 == 0xfffffffc) {
LAB_00442b0a:
        uVar5 = 0;
      }
      else {
LAB_00442ad6:
        bVar9 = *pbVar4 < *pbVar7;
        if ((*pbVar4 == *pbVar7) &&
           ((uVar5 == 0xfffffffd ||
            ((bVar9 = pbVar4[1] < pbVar7[1], pbVar4[1] == pbVar7[1] &&
             ((uVar5 == 0xfffffffe ||
              ((bVar9 = pbVar4[2] < pbVar7[2], pbVar4[2] == pbVar7[2] &&
               ((uVar5 == 0xffffffff || (bVar9 = pbVar4[3] < pbVar7[3], pbVar4[3] == pbVar7[3]))))))
             )))))) goto LAB_00442b0a;
        uVar5 = -(uint)bVar9 | 1;
      }
      if (uVar5 == 0) {
        uVar5 = *(uint *)(param_1 + 0x10);
        goto LAB_00442b30;
      }
      if (-1 < (int)uVar5) goto LAB_00442b34;
LAB_00442b12:
      puVar8 = (undefined4 *)local_4[2];
      local_4 = puVar3;
    }
    cVar1 = *(char *)((int)puVar8 + 0xd);
    puVar3 = local_4;
    local_4 = puVar8;
  } while( true );
}


