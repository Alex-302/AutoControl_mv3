// FUN_00447b80 @ 00447b80 size=398 callers=1

void __thiscall
FUN_00447b80(void *this,undefined4 *param_1,undefined4 param_2,byte *param_3,undefined4 param_4)

{
  int *piVar1;
  uint uVar2;
  uint uVar3;
  undefined1 *puVar4;
  byte bVar5;
  uint uVar6;
  undefined4 *puVar7;
  uint uVar8;
  byte *pbVar9;
  int *piVar10;
  byte *pbVar11;
  int *piVar12;
  bool bVar13;
  byte local_1c;
  int *local_18;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0047e510;
  local_10 = ExceptionList;
  local_8 = 0;
  local_14 = &stack0xffffffcc;
  piVar1 = *(int **)this;
  bVar5 = 1;
  local_1c = 1;
  piVar10 = piVar1;
  if (*(char *)(piVar1[1] + 0xd) == '\0') {
    uVar8 = *(uint *)(param_3 + 0x10);
    piVar12 = (int *)piVar1[1];
    do {
      piVar10 = piVar12;
      pbVar9 = (byte *)(piVar10 + 4);
      if (0xf < (uint)piVar10[9]) {
        pbVar9 = *(byte **)pbVar9;
      }
      pbVar11 = param_3;
      if (0xf < *(uint *)(param_3 + 0x14)) {
        pbVar11 = *(byte **)param_3;
      }
      uVar2 = piVar10[8];
      uVar6 = uVar2;
      if (uVar8 < uVar2) {
        uVar6 = uVar8;
      }
      if (uVar6 == 0) {
LAB_00447c55:
        if (uVar8 < uVar2) {
          uVar6 = 0xffffffff;
        }
        else {
          uVar6 = (uint)(uVar2 < uVar8);
        }
      }
      else {
        while (uVar3 = uVar6 - 4, 3 < uVar6) {
          if (*(int *)pbVar11 != *(int *)pbVar9) goto LAB_00447c18;
          pbVar11 = pbVar11 + 4;
          pbVar9 = pbVar9 + 4;
          uVar6 = uVar3;
        }
        if (uVar3 == 0xfffffffc) {
LAB_00447c4c:
          uVar6 = 0;
        }
        else {
LAB_00447c18:
          bVar13 = *pbVar11 < *pbVar9;
          if ((*pbVar11 == *pbVar9) &&
             ((uVar3 == 0xfffffffd ||
              ((bVar13 = pbVar11[1] < pbVar9[1], pbVar11[1] == pbVar9[1] &&
               ((uVar3 == 0xfffffffe ||
                ((bVar13 = pbVar11[2] < pbVar9[2], pbVar11[2] == pbVar9[2] &&
                 ((uVar3 == 0xffffffff || (bVar13 = pbVar11[3] < pbVar9[3], pbVar11[3] == pbVar9[3])
                  ))))))))))) goto LAB_00447c4c;
          uVar6 = -(uint)bVar13 | 1;
        }
        if (uVar6 == 0) goto LAB_00447c55;
      }
      local_1c = (byte)(uVar6 >> 0x18);
      bVar5 = local_1c >> 7;
      local_1c = local_1c >> 7;
      if ((int)uVar6 < 0) {
        piVar12 = (int *)*piVar10;
      }
      else {
        piVar12 = (int *)piVar10[2];
      }
    } while (*(char *)((int)piVar12 + 0xd) == '\0');
  }
  ExceptionList = &local_10;
  local_18 = piVar10;
  puVar4 = &stack0xffffffcc;
  if (bVar5 != 0) {
    if (piVar10 == (int *)*piVar1) {
      local_1c = 1;
      ExceptionList = &local_10;
      pbVar9 = param_3;
      local_14 = &stack0xffffffcc;
      goto LAB_00447ca2;
    }
    ExceptionList = &local_10;
    FUN_00448e20((int *)&local_18);
    puVar4 = local_14;
  }
  local_14 = puVar4;
  piVar1 = local_18;
  pbVar9 = param_3;
  uVar8 = FUN_00438340((byte *)(local_18 + 4),param_3);
  if ((char)uVar8 == '\0') {
    *param_1 = piVar1;
    *(undefined1 *)(param_1 + 1) = 0;
    ExceptionList = local_10;
    return;
  }
LAB_00447ca2:
  puVar7 = (undefined4 *)FUN_0044ac60(this,&param_3,local_1c,piVar10,(undefined4 *)pbVar9);
  *param_1 = *puVar7;
  *(undefined1 *)(param_1 + 1) = 1;
  ExceptionList = local_10;
  return;
}


