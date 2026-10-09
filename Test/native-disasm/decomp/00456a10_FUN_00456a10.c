// FUN_00456a10 @ 00456a10 size=386 callers=1

undefined4 __cdecl FUN_00456a10(int *param_1,int *param_2,int *param_3)

{
  char cVar1;
  uint uVar2;
  int *piVar3;
  int *piVar4;
  uint uVar5;
  byte *pbVar6;
  uint uVar7;
  byte *pbVar8;
  bool bVar9;
  
  do {
    if (param_1 == param_2) {
      return CONCAT31((int3)((uint)param_1 >> 8),1);
    }
    pbVar6 = (byte *)(param_3 + 4);
    pbVar8 = (byte *)(param_1 + 4);
    if (0xf < (uint)param_3[9]) {
      pbVar6 = *(byte **)pbVar6;
    }
    if (0xf < (uint)param_1[9]) {
      pbVar8 = *(byte **)pbVar8;
    }
    uVar2 = param_3[8];
    uVar5 = param_1[8];
    uVar7 = uVar2;
    if (uVar5 < uVar2) {
      uVar7 = uVar5;
    }
    if (uVar7 != 0) {
      while (uVar5 = uVar7 - 4, 3 < uVar7) {
        if (*(int *)pbVar8 != *(int *)pbVar6) goto LAB_00456a76;
        pbVar8 = pbVar8 + 4;
        pbVar6 = pbVar6 + 4;
        uVar7 = uVar5;
      }
      if (uVar5 == 0xfffffffc) {
LAB_00456aaa:
        uVar5 = 0;
      }
      else {
LAB_00456a76:
        bVar9 = *pbVar8 < *pbVar6;
        if ((*pbVar8 == *pbVar6) &&
           ((uVar5 == 0xfffffffd ||
            ((bVar9 = pbVar8[1] < pbVar6[1], pbVar8[1] == pbVar6[1] &&
             ((uVar5 == 0xfffffffe ||
              ((bVar9 = pbVar8[2] < pbVar6[2], pbVar8[2] == pbVar6[2] &&
               ((uVar5 == 0xffffffff || (bVar9 = pbVar8[3] < pbVar6[3], pbVar8[3] == pbVar6[3]))))))
             )))))) goto LAB_00456aaa;
        uVar5 = -(uint)bVar9 | 1;
      }
      if (uVar5 != 0) goto LAB_00456b8b;
      uVar5 = param_1[8];
    }
    if (((uVar5 < uVar2) || (uVar2 < uVar5)) ||
       (uVar5 = FUN_004441e0((char *)(param_1 + 10),(char *)(param_3 + 10)), (char)uVar5 == '\0')) {
LAB_00456b8b:
      return uVar5 & 0xffffff00;
    }
    if (*(char *)((int)param_1 + 0xd) == '\0') {
      piVar3 = (int *)param_1[2];
      if (*(char *)((int)piVar3 + 0xd) == '\0') {
        cVar1 = *(char *)(*piVar3 + 0xd);
        param_1 = piVar3;
        piVar3 = (int *)*piVar3;
        while (cVar1 == '\0') {
          cVar1 = *(char *)(*piVar3 + 0xd);
          param_1 = piVar3;
          piVar3 = (int *)*piVar3;
        }
      }
      else {
        cVar1 = *(char *)(param_1[1] + 0xd);
        piVar4 = (int *)param_1[1];
        piVar3 = param_1;
        while ((param_1 = piVar4, cVar1 == '\0' && (piVar3 == (int *)param_1[2]))) {
          cVar1 = *(char *)(param_1[1] + 0xd);
          piVar4 = (int *)param_1[1];
          piVar3 = param_1;
        }
      }
    }
    if (*(char *)((int)param_3 + 0xd) == '\0') {
      piVar3 = (int *)param_3[2];
      if (*(char *)((int)piVar3 + 0xd) == '\0') {
        cVar1 = *(char *)(*piVar3 + 0xd);
        param_3 = piVar3;
        piVar3 = (int *)*piVar3;
        while (cVar1 == '\0') {
          cVar1 = *(char *)(*piVar3 + 0xd);
          param_3 = piVar3;
          piVar3 = (int *)*piVar3;
        }
      }
      else {
        cVar1 = *(char *)(param_3[1] + 0xd);
        piVar4 = (int *)param_3[1];
        piVar3 = param_3;
        while ((param_3 = piVar4, cVar1 == '\0' && (piVar3 == (int *)param_3[2]))) {
          cVar1 = *(char *)(param_3[1] + 0xd);
          piVar4 = (int *)param_3[1];
          piVar3 = param_3;
        }
      }
    }
  } while( true );
}


