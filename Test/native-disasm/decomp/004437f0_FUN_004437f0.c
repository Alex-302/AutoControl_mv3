// FUN_004437f0 @ 004437f0 size=636 callers=20

void __thiscall FUN_004437f0(void *this,int *param_1,byte *param_2)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  int *piVar4;
  byte *pbVar5;
  int *piVar6;
  uint uVar7;
  byte *pbVar8;
  byte *pbVar9;
  int *piVar10;
  bool bVar11;
  int *local_14;
  int *local_c;
  
  local_14 = *(int **)this;
  piVar10 = local_14 + 1;
  local_c = local_14;
  if (*(char *)(local_14[1] + 0xd) == '\0') {
    uVar1 = *(uint *)(param_2 + 0x10);
    piVar4 = (int *)local_14[1];
    uVar7 = *(uint *)(param_2 + 0x14);
    do {
      pbVar5 = (byte *)(piVar4 + 4);
      pbVar9 = param_2;
      if (0xf < uVar7) {
        pbVar9 = *(byte **)param_2;
      }
      pbVar8 = pbVar5;
      if (0xf < (uint)piVar4[9]) {
        pbVar8 = *(byte **)pbVar5;
      }
      uVar7 = piVar4[8];
      uVar3 = uVar1;
      if (uVar7 < uVar1) {
        uVar3 = uVar7;
      }
      if (uVar3 == 0) {
LAB_00443913:
        if (uVar7 < uVar1) goto LAB_004438b3;
LAB_00443917:
        local_c = piVar4;
        if (*(char *)((int)local_14 + 0xd) == '\0') {
LAB_004439bc:
          piVar6 = (int *)*piVar4;
        }
        else {
          if (0xf < (uint)piVar4[9]) {
            pbVar5 = *(byte **)pbVar5;
          }
          pbVar9 = param_2;
          if (0xf < *(uint *)(param_2 + 0x14)) {
            pbVar9 = *(byte **)param_2;
          }
          uVar7 = piVar4[8];
          uVar3 = uVar7;
          if (uVar1 < uVar7) {
            uVar3 = uVar1;
          }
          if (uVar3 == 0) {
LAB_004439b4:
            if (uVar1 < uVar7) {
              local_14 = piVar4;
            }
            goto LAB_004439bc;
          }
          while (uVar2 = uVar3 - 4, 3 < uVar3) {
            if (*(int *)pbVar9 != *(int *)pbVar5) goto LAB_00443969;
            pbVar9 = pbVar9 + 4;
            pbVar5 = pbVar5 + 4;
            uVar3 = uVar2;
          }
          if (uVar2 == 0xfffffffc) {
LAB_0044399d:
            uVar3 = 0;
          }
          else {
LAB_00443969:
            bVar11 = *pbVar9 < *pbVar5;
            if ((*pbVar9 == *pbVar5) &&
               ((uVar2 == 0xfffffffd ||
                ((bVar11 = pbVar9[1] < pbVar5[1], pbVar9[1] == pbVar5[1] &&
                 ((uVar2 == 0xfffffffe ||
                  ((bVar11 = pbVar9[2] < pbVar5[2], pbVar9[2] == pbVar5[2] &&
                   ((uVar2 == 0xffffffff || (bVar11 = pbVar9[3] < pbVar5[3], pbVar9[3] == pbVar5[3])
                    ))))))))))) goto LAB_0044399d;
            uVar3 = -(uint)bVar11 | 1;
          }
          if (uVar3 == 0) goto LAB_004439b4;
          if (-1 < (int)uVar3) goto LAB_004439bc;
          piVar6 = (int *)*piVar4;
          local_14 = piVar4;
        }
      }
      else {
        while (uVar2 = uVar3 - 4, 3 < uVar3) {
          if (*(int *)pbVar8 != *(int *)pbVar9) goto LAB_00443877;
          pbVar8 = pbVar8 + 4;
          pbVar9 = pbVar9 + 4;
          uVar3 = uVar2;
        }
        if (uVar2 == 0xfffffffc) {
LAB_004438ab:
          uVar3 = 0;
        }
        else {
LAB_00443877:
          bVar11 = *pbVar8 < *pbVar9;
          if ((*pbVar8 == *pbVar9) &&
             ((uVar2 == 0xfffffffd ||
              ((bVar11 = pbVar8[1] < pbVar9[1], pbVar8[1] == pbVar9[1] &&
               ((uVar2 == 0xfffffffe ||
                ((bVar11 = pbVar8[2] < pbVar9[2], pbVar8[2] == pbVar9[2] &&
                 ((uVar2 == 0xffffffff || (bVar11 = pbVar8[3] < pbVar9[3], pbVar8[3] == pbVar9[3])))
                 ))))))))) goto LAB_004438ab;
          uVar3 = -(uint)bVar11 | 1;
        }
        if (uVar3 == 0) goto LAB_00443913;
        if (-1 < (int)uVar3) goto LAB_00443917;
LAB_004438b3:
        piVar6 = (int *)piVar4[2];
      }
      uVar7 = *(uint *)(param_2 + 0x14);
      piVar4 = piVar6;
    } while (*(char *)((int)piVar6 + 0xd) == '\0');
  }
  piVar4 = local_14;
  if (*(char *)((int)local_14 + 0xd) != '\0') {
    piVar4 = piVar10;
  }
  if (*(char *)(*piVar4 + 0xd) == '\0') {
    uVar1 = *(uint *)(param_2 + 0x10);
    piVar10 = (int *)*piVar4;
    do {
      pbVar5 = (byte *)(piVar10 + 4);
      if (0xf < (uint)piVar10[9]) {
        pbVar5 = *(byte **)pbVar5;
      }
      pbVar9 = param_2;
      if (0xf < *(uint *)(param_2 + 0x14)) {
        pbVar9 = *(byte **)param_2;
      }
      uVar7 = piVar10[8];
      uVar3 = uVar7;
      if (uVar1 < uVar7) {
        uVar3 = uVar1;
      }
      if (uVar3 == 0) {
LAB_00443a5f:
        if (uVar1 < uVar7) goto LAB_00443a32;
LAB_00443a63:
        piVar4 = (int *)piVar10[2];
      }
      else {
        while (uVar2 = uVar3 - 4, 3 < uVar3) {
          if (*(int *)pbVar9 != *(int *)pbVar5) goto LAB_004439f6;
          pbVar9 = pbVar9 + 4;
          pbVar5 = pbVar5 + 4;
          uVar3 = uVar2;
        }
        if (uVar2 == 0xfffffffc) {
LAB_00443a2a:
          uVar3 = 0;
        }
        else {
LAB_004439f6:
          bVar11 = *pbVar9 < *pbVar5;
          if ((*pbVar9 == *pbVar5) &&
             ((uVar2 == 0xfffffffd ||
              ((bVar11 = pbVar9[1] < pbVar5[1], pbVar9[1] == pbVar5[1] &&
               ((uVar2 == 0xfffffffe ||
                ((bVar11 = pbVar9[2] < pbVar5[2], pbVar9[2] == pbVar5[2] &&
                 ((uVar2 == 0xffffffff || (bVar11 = pbVar9[3] < pbVar5[3], pbVar9[3] == pbVar5[3])))
                 ))))))))) goto LAB_00443a2a;
          uVar3 = -(uint)bVar11 | 1;
        }
        if (uVar3 == 0) goto LAB_00443a5f;
        if (-1 < (int)uVar3) goto LAB_00443a63;
LAB_00443a32:
        piVar4 = (int *)*piVar10;
        local_14 = piVar10;
      }
      piVar10 = piVar4;
    } while (*(char *)((int)piVar4 + 0xd) == '\0');
  }
  param_1[1] = (int)local_14;
  *param_1 = (int)local_c;
  return;
}


