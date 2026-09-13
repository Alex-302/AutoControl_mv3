// FUN_00447780 @ 00447780 size=399 callers=2

void __thiscall
FUN_00447780(void *this,undefined4 *param_1,undefined4 param_2,byte *param_3,int *param_4)

{
  uint uVar1;
  uint uVar2;
  undefined1 *puVar3;
  byte bVar4;
  uint uVar5;
  undefined4 *puVar6;
  uint uVar7;
  byte *pbVar8;
  int *extraout_ECX;
  int *piVar9;
  byte *pbVar10;
  int *piVar11;
  bool bVar12;
  int *piVar13;
  byte local_1c;
  int *local_18;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0047e500;
  local_10 = ExceptionList;
  local_8 = 0;
  local_14 = &stack0xffffffcc;
  piVar13 = *(int **)this;
  bVar4 = 1;
  local_1c = 1;
  piVar9 = piVar13;
  if (*(char *)(piVar13[1] + 0xd) == '\0') {
    uVar7 = *(uint *)(param_3 + 0x10);
    piVar11 = (int *)piVar13[1];
    do {
      piVar9 = piVar11;
      pbVar8 = (byte *)(piVar9 + 4);
      if (0xf < (uint)piVar9[9]) {
        pbVar8 = *(byte **)pbVar8;
      }
      pbVar10 = param_3;
      if (0xf < *(uint *)(param_3 + 0x14)) {
        pbVar10 = *(byte **)param_3;
      }
      uVar1 = piVar9[8];
      uVar5 = uVar1;
      if (uVar7 < uVar1) {
        uVar5 = uVar7;
      }
      if (uVar5 == 0) {
LAB_00447855:
        if (uVar7 < uVar1) {
          uVar5 = 0xffffffff;
        }
        else {
          uVar5 = (uint)(uVar1 < uVar7);
        }
      }
      else {
        while (uVar2 = uVar5 - 4, 3 < uVar5) {
          if (*(int *)pbVar10 != *(int *)pbVar8) goto LAB_00447818;
          pbVar10 = pbVar10 + 4;
          pbVar8 = pbVar8 + 4;
          uVar5 = uVar2;
        }
        if (uVar2 == 0xfffffffc) {
LAB_0044784c:
          uVar5 = 0;
        }
        else {
LAB_00447818:
          bVar12 = *pbVar10 < *pbVar8;
          if ((*pbVar10 == *pbVar8) &&
             ((uVar2 == 0xfffffffd ||
              ((bVar12 = pbVar10[1] < pbVar8[1], pbVar10[1] == pbVar8[1] &&
               ((uVar2 == 0xfffffffe ||
                ((bVar12 = pbVar10[2] < pbVar8[2], pbVar10[2] == pbVar8[2] &&
                 ((uVar2 == 0xffffffff || (bVar12 = pbVar10[3] < pbVar8[3], pbVar10[3] == pbVar8[3])
                  ))))))))))) goto LAB_0044784c;
          uVar5 = -(uint)bVar12 | 1;
        }
        if (uVar5 == 0) goto LAB_00447855;
      }
      local_1c = (byte)(uVar5 >> 0x18);
      bVar4 = local_1c >> 7;
      local_1c = local_1c >> 7;
      if ((int)uVar5 < 0) {
        piVar11 = (int *)*piVar9;
      }
      else {
        piVar11 = (int *)piVar9[2];
      }
    } while (*(char *)((int)piVar11 + 0xd) == '\0');
  }
  ExceptionList = &local_10;
  local_18 = piVar9;
  puVar3 = &stack0xffffffcc;
  if (bVar4 != 0) {
    if (piVar9 == (int *)*piVar13) {
      local_1c = 1;
      ExceptionList = &local_10;
      local_14 = &stack0xffffffcc;
      goto LAB_0044789f;
    }
    ExceptionList = &local_10;
    FUN_00448e20((int *)&local_18);
    puVar3 = local_14;
  }
  local_14 = puVar3;
  piVar11 = local_18;
  uVar7 = FUN_00438340((byte *)(local_18 + 4),param_3);
  piVar13 = extraout_ECX;
  if ((char)uVar7 == '\0') {
    FUN_00448930(param_4);
    *param_1 = piVar11;
    *(undefined1 *)(param_1 + 1) = 0;
    ExceptionList = local_10;
    return;
  }
LAB_0044789f:
  puVar6 = (undefined4 *)FUN_0044a8f0(this,&param_3,local_1c,piVar9,piVar13,param_4);
  *param_1 = *puVar6;
  *(undefined1 *)(param_1 + 1) = 1;
  ExceptionList = local_10;
  return;
}


