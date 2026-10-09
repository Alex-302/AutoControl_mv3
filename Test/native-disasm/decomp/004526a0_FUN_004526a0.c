// FUN_004526a0 @ 004526a0 size=164 callers=1

uint __fastcall FUN_004526a0(int param_1)

{
  int *piVar1;
  int *piVar2;
  uint *in_EAX;
  int iVar3;
  uint uVar4;
  uint uVar5;
  
  uVar5 = 0;
  if (*(uint *)(param_1 + 0x68) != 0) {
    do {
      iVar3 = (uVar5 >> 5) * 4;
      in_EAX = (uint *)(*(int *)(param_1 + 0x24) + iVar3);
      uVar4 = 1 << ((byte)uVar5 & 0x1f);
      if (((*in_EAX & uVar4) != 0) &&
         (in_EAX = (uint *)(*(int *)(param_1 + 4) + iVar3), (*in_EAX & uVar4) != 0)) {
        piVar1 = (int *)(*(int *)(param_1 + 0x14) + uVar5 * 8);
        piVar2 = (int *)(*(int *)(param_1 + 0x34) + uVar5 * 8);
        if (*piVar2 != *piVar1) {
          iVar3 = *(int *)(*(int *)(param_1 + 0x14) + uVar5 * 8) - *(int *)(param_1 + 0x4c);
          return CONCAT31((int3)((uint)iVar3 >> 8),
                          *(int *)(*(int *)(param_1 + 0x34) + uVar5 * 8) - *(int *)(param_1 + 0x4c)
                          < iVar3);
        }
        in_EAX = (uint *)piVar2[1];
        if (in_EAX != (uint *)piVar1[1]) {
          iVar3 = *(int *)(*(int *)(param_1 + 0x14) + 4 + uVar5 * 8) - *(int *)(param_1 + 0x4c);
          return CONCAT31((int3)((uint)iVar3 >> 8),
                          *(int *)(*(int *)(param_1 + 0x34) + 4 + uVar5 * 8) -
                          *(int *)(param_1 + 0x4c) < iVar3);
        }
      }
      uVar5 = uVar5 + 1;
    } while (uVar5 < *(uint *)(param_1 + 0x68));
  }
  return (uint)in_EAX & 0xffffff00;
}


