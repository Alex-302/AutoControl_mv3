// FUN_00448230 @ 00448230 size=68 callers=1

undefined4 __fastcall FUN_00448230(int *param_1,int *param_2)

{
  char *pcVar1;
  uint uVar2;
  char *pcVar3;
  int iVar4;
  
  pcVar3 = (char *)*param_1;
  pcVar1 = (char *)param_1[1];
  uVar2 = (int)pcVar1 - (int)pcVar3;
  if (((param_2[1] - *param_2 ^ uVar2) & 0xfffffff0) == 0) {
    if (pcVar3 != pcVar1) {
      iVar4 = *param_2 - (int)pcVar3;
      do {
        uVar2 = FUN_004441e0(pcVar3,pcVar3 + iVar4);
        if ((char)uVar2 == '\0') goto LAB_0044826e;
        pcVar3 = pcVar3 + 0x10;
      } while (pcVar3 != pcVar1);
    }
    return CONCAT31((int3)(uVar2 >> 8),1);
  }
LAB_0044826e:
  return uVar2 & 0xffffff00;
}


