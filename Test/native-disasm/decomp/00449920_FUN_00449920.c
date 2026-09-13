// FUN_00449920 @ 00449920 size=466 callers=3

void __thiscall FUN_00449920(void *this,undefined4 *param_1,byte *param_2,byte *param_3,int param_4)

{
  byte *pbVar1;
  char cVar2;
  int *piVar3;
  uint uVar4;
  byte bVar5;
  byte local_10 [4];
  undefined4 local_c [2];
  
  if (param_4 == 0) {
    param_4 = *(int *)((int)this + 0x58);
  }
  if (param_2 != param_3) {
    while (param_4 != 0) {
      switch(*(undefined4 *)(param_4 + 4)) {
      case 1:
      case 8:
      case 9:
      case 0xd:
      case 0xe:
      case 0x14:
        param_4 = *(int *)(param_4 + 0xc);
        break;
      case 2:
        if ((*(byte *)((int)this + 0x60) & 1) == 0) goto LAB_00449972;
        goto LAB_00449ae6;
      case 3:
        if ((*(byte *)((int)this + 0x60) & 2) == 0) goto LAB_00449998;
        goto LAB_00449ae6;
      default:
        goto switchD_00449958_caseD_4;
      case 6:
        goto switchD_00449958_caseD_6;
      case 7:
        goto switchD_00449958_caseD_7;
      case 0xc:
      case 0x15:
        param_4 = 0;
        break;
      case 0x10:
        goto switchD_00449958_caseD_10;
      }
    }
  }
  goto switchD_00449958_caseD_4;
switchD_00449958_caseD_7:
  local_10[0] = *param_2;
  bVar5 = *param_2;
  if (*(int *)(param_4 + 0x14) == 0) {
LAB_00449a27:
    if (*(int *)(param_4 + 0x20) != 0) {
      if ((*(uint *)((int)this + 0x5c) & 0x800) == 0) {
        uVar4 = (uint)bVar5;
      }
      else {
        cVar2 = FUN_0044d7d0(*(void **)((int)this + 0x70),local_10[0]);
        uVar4 = (uint)cVar2;
      }
      uVar4 = FUN_0044ef90(uVar4 & 0xff,*(int *)(param_4 + 0x20));
      if ((char)uVar4 != '\0') {
        uVar4 = 1;
        goto LAB_00449a92;
      }
    }
    if ((*(int *)(param_4 + 0x18) == 0) ||
       ((*(byte *)((uint)(local_10[0] >> 3) + *(int *)(param_4 + 0x18)) &
        (byte)(1 << (local_10[0] & 7))) == 0)) {
      uVar4 = 0;
    }
    else {
      uVar4 = 1;
    }
  }
  else {
    piVar3 = FUN_0044ef00(local_c,*(uint **)(param_4 + 0x14),(char *)param_2,(char *)(param_2 + 1));
    if ((byte *)*piVar3 == param_2) {
      bVar5 = local_10[0];
      goto LAB_00449a27;
    }
    uVar4 = 1;
  }
LAB_00449a92:
  if (uVar4 != (*(uint *)(param_4 + 8) & 1)) goto switchD_00449958_caseD_4;
  param_2 = param_2 + 1;
  if (param_2 == param_3) {
    *param_1 = param_2;
    return;
  }
  goto switchD_00449958_caseD_7;
switchD_00449958_caseD_6:
  while( true ) {
    pbVar1 = param_2 + 1;
    piVar3 = FUN_0044ee50((undefined4 *)local_10,*(byte **)(param_4 + 0x1c),param_2,pbVar1,
                          *(byte **)(param_4 + 0x1c) + 1,*(int *)((int)this + 0x70),
                          *(uint *)((int)this + 0x5c));
    if ((byte *)*piVar3 != param_2) break;
    param_2 = pbVar1;
    if (pbVar1 == param_3) {
      *param_1 = pbVar1;
      return;
    }
  }
  goto switchD_00449958_caseD_4;
LAB_00449998:
  while (*param_2 != 10) {
    param_2 = param_2 + 1;
    if (param_2 == param_3) {
      *param_1 = param_2;
      return;
    }
  }
  goto switchD_00449958_caseD_4;
  while( true ) {
    piVar3 = (int *)FUN_00449920(this,local_c,param_2,param_3,*(int *)(param_4 + 0xc));
    param_3 = (byte *)*piVar3;
    param_4 = *(int *)(param_4 + 0x18);
    if (param_2 == param_3) break;
switchD_00449958_caseD_10:
    if (param_4 == 0) break;
  }
LAB_00449ae6:
  *param_1 = param_3;
  return;
  while (param_2 = param_2 + 1, param_2 != param_3) {
LAB_00449972:
    if (param_2[-1] == 10) break;
  }
switchD_00449958_caseD_4:
  *param_1 = param_2;
  return;
}


