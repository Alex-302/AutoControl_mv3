// FUN_0043ce20 @ 0043ce20 size=541 callers=5

void FUN_0043ce20(char *param_1)

{
  int *piVar1;
  undefined1 uVar2;
  int iVar3;
  char *pcVar4;
  undefined4 ****ppppuVar5;
  char *pcVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  undefined2 *puVar10;
  undefined4 ***local_38 [4];
  int local_28;
  uint local_24;
  undefined2 local_20;
  undefined1 local_1e;
  undefined1 local_1d;
  undefined1 local_1c;
  undefined4 *local_18;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_004792a8;
  local_10 = ExceptionList;
  uVar9 = *(uint *)(param_1 + 0x14);
  pcVar4 = param_1;
  if (0xf < uVar9) {
    pcVar4 = *(char **)param_1;
  }
  iVar8 = *(int *)(param_1 + 0x10);
  piVar1 = (int *)(param_1 + 0x10);
  pcVar6 = param_1;
  if (0xf < uVar9) {
    pcVar6 = *(char **)param_1;
  }
  ExceptionList = &local_10;
  iVar3 = FUN_004480d0(pcVar6,pcVar4 + iVar8);
  if (iVar3 == 0) {
    if (0xf < uVar9) {
      param_1 = *(char **)param_1;
    }
    FUN_0043e0b0((void *)*local_18,param_1,iVar8,0);
    ExceptionList = local_10;
    return;
  }
  local_24 = 0xf;
  local_28 = 0;
  local_38[0] = (undefined4 ***)((uint)local_38[0] & 0xffffff00);
  FUN_0043ac10(local_38,iVar3 + iVar8,'\\');
  local_8 = 0;
  iVar8 = 0;
  pcVar4 = param_1;
  if (0xf < *(uint *)(param_1 + 0x14)) {
    pcVar4 = *(char **)param_1;
    param_1 = *(char **)param_1;
  }
  iVar3 = *piVar1;
  do {
    if (pcVar4 == param_1 + iVar3) {
      ppppuVar5 = local_38;
      if (0xf < local_24) {
        ppppuVar5 = (undefined4 ****)local_38[0];
      }
      FUN_0043e0b0((void *)*local_18,ppppuVar5,local_28,0);
      if (0xf < local_24) {
        FUN_00402430(local_38[0],local_24 + 1,1);
      }
      ExceptionList = local_10;
      return;
    }
    uVar9 = (uint)*pcVar4;
    switch(uVar9) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 0xb:
    case 0xe:
    case 0xf:
    case 0x10:
    case 0x11:
    case 0x12:
    case 0x13:
    case 0x14:
    case 0x15:
    case 0x16:
    case 0x17:
    case 0x18:
    case 0x19:
    case 0x1a:
    case 0x1b:
    case 0x1c:
    case 0x1d:
    case 0x1e:
    case 0x1f:
      local_20 = 0x3075;
      local_1e = 0x30;
      iVar7 = 0;
      local_1d = (&DAT_0048e4b0)[(int)uVar9 >> 4];
      puVar10 = &local_20;
      local_1c = (&DAT_0048e4b0)[uVar9 & 0xf];
      do {
        uVar2 = *(undefined1 *)puVar10;
        iVar8 = iVar8 + 1;
        puVar10 = (undefined2 *)((int)puVar10 + 1);
        ppppuVar5 = local_38;
        if (0xf < local_24) {
          ppppuVar5 = (undefined4 ****)local_38[0];
        }
        iVar7 = iVar7 + 1;
        *(undefined1 *)((int)ppppuVar5 + iVar8) = uVar2;
      } while (iVar7 != 5);
      goto LAB_0043cfee;
    case 8:
      ppppuVar5 = local_38;
      if (0xf < local_24) {
        ppppuVar5 = (undefined4 ****)local_38[0];
      }
      *(undefined1 *)((int)ppppuVar5 + iVar8 + 1) = 0x62;
      iVar8 = iVar8 + 2;
      break;
    case 9:
      ppppuVar5 = local_38;
      if (0xf < local_24) {
        ppppuVar5 = (undefined4 ****)local_38[0];
      }
      *(undefined1 *)((int)ppppuVar5 + iVar8 + 1) = 0x74;
      iVar8 = iVar8 + 2;
      break;
    case 10:
      ppppuVar5 = local_38;
      if (0xf < local_24) {
        ppppuVar5 = (undefined4 ****)local_38[0];
      }
      *(undefined1 *)((int)ppppuVar5 + iVar8 + 1) = 0x6e;
      iVar8 = iVar8 + 2;
      break;
    case 0xc:
      ppppuVar5 = local_38;
      if (0xf < local_24) {
        ppppuVar5 = (undefined4 ****)local_38[0];
      }
      *(undefined1 *)((int)ppppuVar5 + iVar8 + 1) = 0x66;
      iVar8 = iVar8 + 2;
      break;
    case 0xd:
      ppppuVar5 = local_38;
      if (0xf < local_24) {
        ppppuVar5 = (undefined4 ****)local_38[0];
      }
      *(undefined1 *)((int)ppppuVar5 + iVar8 + 1) = 0x72;
      iVar8 = iVar8 + 2;
      break;
    default:
      ppppuVar5 = local_38;
      if (0xf < local_24) {
        ppppuVar5 = (undefined4 ****)local_38[0];
      }
      *(char *)((int)ppppuVar5 + iVar8) = *pcVar4;
LAB_0043cfee:
      iVar8 = iVar8 + 1;
      break;
    case 0x22:
      ppppuVar5 = local_38;
      if (0xf < local_24) {
        ppppuVar5 = (undefined4 ****)local_38[0];
      }
      *(undefined1 *)((int)ppppuVar5 + iVar8 + 1) = 0x22;
    case 0x5c:
      iVar8 = iVar8 + 2;
    }
    pcVar4 = pcVar4 + 1;
  } while( true );
}


