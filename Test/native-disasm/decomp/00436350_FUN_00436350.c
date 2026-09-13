// FUN_00436350 @ 00436350 size=182 callers=14

int * __thiscall FUN_00436350(void *this,int *param_1,byte *param_2)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  uint uVar7;
  undefined4 *puVar8;
  
  iVar2 = *(int *)((int)this + 0xc);
  uVar7 = *(uint *)((int)this + 0x18) &
          ((((*param_2 ^ 0x811c9dc5) * 0x1000193 ^ (uint)param_2[1]) * 0x1000193 ^ (uint)param_2[2])
           * 0x1000193 ^ (uint)param_2[3]) * 0x1000193;
  puVar5 = *(undefined4 **)(iVar2 + uVar7 * 8);
  puVar3 = *(undefined4 **)((int)this + 4);
  iVar1 = iVar2 + uVar7 * 8;
  puVar4 = *(undefined4 **)(iVar2 + uVar7 * 8);
  while( true ) {
    puVar6 = puVar3;
    if (puVar4 != puVar3) {
      puVar6 = (undefined4 *)**(undefined4 **)(iVar1 + 4);
    }
    if (puVar5 == puVar6) goto LAB_004363f6;
    if (puVar5[2] == *(int *)param_2) break;
    puVar5 = (undefined4 *)*puVar5;
  }
  puVar6 = puVar5;
  while( true ) {
    puVar8 = puVar3;
    if (puVar4 != puVar3) {
      puVar8 = (undefined4 *)**(undefined4 **)(iVar1 + 4);
    }
    if ((puVar6 == puVar8) || (*(int *)param_2 != puVar6[2])) break;
    puVar6 = (undefined4 *)*puVar6;
  }
  if (puVar5 != puVar6) {
    param_1[1] = (int)puVar6;
    *param_1 = (int)puVar5;
    return param_1;
  }
LAB_004363f6:
  *param_1 = (int)puVar3;
  param_1[1] = (int)puVar3;
  return param_1;
}


