// FUN_00449880 @ 00449880 size=157 callers=1

void __thiscall FUN_00449880(void *this,undefined4 *param_1,byte *param_2)

{
  uint uVar1;
  byte *pbVar2;
  int *piVar3;
  uint uVar4;
  int *piVar5;
  undefined4 extraout_ECX;
  byte *pbVar6;
  undefined4 extraout_ECX_00;
  undefined4 uVar7;
  byte *pbVar8;
  
  pbVar2 = param_2;
  piVar3 = FUN_00442a70(this,param_2);
  uVar7 = extraout_ECX;
  if (piVar3 != *(int **)this) {
    pbVar8 = (byte *)(piVar3 + 4);
    if (0xf < (uint)piVar3[9]) {
      pbVar8 = *(byte **)pbVar8;
    }
    pbVar6 = pbVar2;
    if (0xf < *(uint *)(pbVar2 + 0x14)) {
      pbVar6 = *(byte **)pbVar2;
    }
    uVar1 = piVar3[8];
    uVar4 = uVar1;
    if (*(uint *)(pbVar2 + 0x10) < uVar1) {
      uVar4 = *(uint *)(pbVar2 + 0x10);
    }
    uVar4 = FUN_004023d0(pbVar6,pbVar8,uVar4);
    uVar7 = extraout_ECX_00;
    if (uVar4 == 0) {
      if (uVar1 <= *(uint *)(pbVar2 + 0x10)) {
LAB_0044990b:
        *param_1 = piVar3;
        *(undefined1 *)(param_1 + 1) = 0;
        return;
      }
    }
    else if (-1 < (int)uVar4) goto LAB_0044990b;
  }
  param_2 = pbVar2;
  piVar5 = FUN_004529d0(this,uVar7,&param_2);
  FUN_0044fd90(this,&param_2,piVar3,(byte *)(piVar5 + 4),piVar5);
  *param_1 = param_2;
  *(undefined1 *)(param_1 + 1) = 1;
  return;
}


