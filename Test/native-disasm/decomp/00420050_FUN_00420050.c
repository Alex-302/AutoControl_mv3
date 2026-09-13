// FUN_00420050 @ 00420050 size=1219 callers=1

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

bool __thiscall FUN_00420050(void *this,int param_1,undefined4 param_2,int *param_3)

{
  LONG LVar1;
  LONG LVar2;
  byte bVar3;
  char cVar4;
  bool bVar5;
  byte *this_00;
  uint uVar6;
  undefined3 extraout_var;
  UINT UVar7;
  undefined *puVar8;
  int iVar9;
  char *pcVar10;
  int extraout_EDX;
  ushort uVar11;
  int iVar12;
  tagPOINT local_10;
  POINT local_8;
  
  pcVar10 = (char *)&DAT_004a2538;
  if (0xf < DAT_004a254c) {
    pcVar10 = DAT_004a2538;
  }
  switch(*(char *)((int)this + 7) + -1 + (uint)(byte)(pcVar10[4] - pcVar10[0x1e])) {
  case 0:
    uVar11 = *(ushort *)this & 0xfc00;
    uVar6 = FUN_00413170((uint)*(ushort *)this,*(char *)((int)this + 4));
    if (((char)uVar6 == '\0') &&
       ((*(ushort *)((int)this + 2) == 0 ||
        (uVar6 = FUN_00413170((uint)*(ushort *)((int)this + 2),*(char *)((int)this + 4)),
        (char)uVar6 == '\0')))) {
      return uVar11 != 0;
    }
    return uVar11 == 0;
  case 1:
    if ((bool)DAT_004a26c5 == (*(int *)this != 0)) {
      pcVar10 = (char *)&DAT_004a2538;
      if (0xf < DAT_004a254c) {
        pcVar10 = DAT_004a2538;
      }
      if ((uint)(byte)(pcVar10[6] - pcVar10[0x12]) < (uint)(DAT_004a2518 - DAT_004a2514 >> 2)) {
        return true;
      }
    }
    break;
  case 2:
    return (*(uint *)(DAT_004a25f8 + (uint)(*(ushort *)this >> 5) * 4) &
           1 << ((byte)*(ushort *)this & 0x1f)) != 0;
  case 3:
    this_00 = FUN_00433710(this);
    bVar5 = FUN_0041ff00(this_00,*(byte *)((int)this + 4),(uint)*(ushort *)((int)this + 2),
                         *(ushort *)((int)this + 2));
    return bVar5;
  case 4:
    cVar4 = FUN_00406370();
    return *(char *)((int)this + 2) == cVar4;
  case 5:
    if (((*(char *)(param_1 + 0x1e) == '\b') || (*(char *)(param_1 + 0x1e) == '\x03')) &&
       (uVar6 = FUN_00413350(), param_1 = extraout_EDX, (char)uVar6 != '\0')) {
      switch(*(undefined4 *)this) {
      case 1:
        return *(char *)(extraout_EDX + 0x15) == '\0';
      case 2:
      case 3:
        goto switchD_00420090_default;
      case 4:
        goto switchD_004201fb_caseD_4;
      }
    }
    pcVar10 = (char *)(param_1 + 0x14);
    iVar9 = (int)&DAT_004a26a4 - param_1;
    iVar12 = -0x14 - param_1;
    param_1._0_1_ = (char)iVar9;
    do {
      switch(*(undefined4 *)this) {
      case 1:
        bVar5 = *pcVar10 == '\0';
        break;
      case 2:
        param_1._0_1_ = '\x01';
        goto LAB_00420269;
      case 3:
        bVar5 = pcVar10 + iVar12 == (char *)0x0;
        break;
      case 4:
        bVar5 = pcVar10 + iVar12 == (char *)0x1;
        break;
      default:
        goto switchD_00420245_default;
      }
      param_1._0_1_ = !bVar5;
switchD_00420245_default:
      if ((char)param_1 != '\0') {
LAB_00420269:
        cVar4 = *pcVar10;
        if (cVar4 == -1) {
          cVar4 = '\0';
        }
        if (cVar4 != pcVar10[iVar9]) {
          return false;
        }
      }
      pcVar10 = pcVar10 + 1;
      if (9 < (int)(pcVar10 + iVar12)) {
        pcVar10 = (char *)&DAT_004a2538;
        if (0xf < DAT_004a254c) {
          pcVar10 = DAT_004a2538;
        }
        return pcVar10[6] == pcVar10[0x12];
      }
    } while( true );
  case 6:
    if ((uint)((param_3[1] - *param_3) / 0x24) <= (uint)*(ushort *)this) {
      return *(char *)(param_1 + 0x1f) == *(char *)((int)this + 2);
    }
    return *(char *)(*param_3 + (uint)*(ushort *)this * 0x24 + 0x1f) == *(char *)((int)this + 2);
  case 7:
    return (bool)*(char *)(*param_3 + 0x20 + (uint)*(ushort *)this * 0x24) ==
           (*(char *)((int)this + 2) != '\0');
  case 8:
    pcVar10 = (char *)&DAT_004a2538;
    if (0xf < DAT_004a254c) {
      pcVar10 = DAT_004a2538;
    }
    bVar5 = FUN_00413200(&DAT_004a26b0);
    return bVar5 == ((uint)(byte)(pcVar10[6] - pcVar10[0x12]) + *(int *)this != 0);
  case 9:
    pcVar10 = (char *)&DAT_004a2538;
    if (0xf < DAT_004a254c) {
      pcVar10 = DAT_004a2538;
    }
    return (uint)(byte)(*pcVar10 - pcVar10[0x18]) < (uint)(DAT_004a2518 - DAT_004a2514 >> 2) ==
           (*(int *)this != 0);
  case 10:
    return (int)DAT_004a264b == *(int *)this;
  case 0xb:
    bVar3 = FUN_00415e30(DAT_004a26b4);
    return (*(uint *)this & CONCAT31(extraout_var,bVar3)) != 0;
  case 0xc:
    if (((DAT_004a2998 != 0) || (DAT_004a299c != 0)) &&
       ((*(short *)this == 0 || (*(short *)this == DAT_004a29d0)))) {
      return true;
    }
    break;
  case 0xd:
    if ((DAT_004a26c2 & 0xfc00) == 0x1000) {
      local_10.x = DAT_004a23e0;
      local_10.y = DAT_004a23e4;
      LVar1 = local_10.x;
      LVar2 = local_10.y;
    }
    else {
      LVar1 = DAT_004a2a48;
      LVar2 = DAT_004a2a4c;
      if (200 < (uint)(DAT_004a26b4 - _DAT_004a32e8)) {
        GetCursorPos(&local_10);
        DAT_004a2a48 = local_10.x;
        DAT_004a2a4c = local_10.y;
        _DAT_004a32e8 = DAT_004a26b4;
        LVar1 = local_10.x;
        LVar2 = local_10.y;
      }
    }
    local_10.y = LVar2;
    local_10.x = LVar1;
    uVar6 = *(uint *)this;
    local_8.x = local_10.x;
    local_8.y = local_10.y;
    if ((uVar6 < 0x28) || (0x3b < uVar6)) {
      bVar5 = FUN_00415bf0(&local_8,uVar6);
      if ((bVar5) && (*(int *)this - 0x3cU < 0x15)) {
        _DAT_0049da44 = local_10.x;
        DAT_0049da48 = local_10.y;
      }
      return bVar5;
    }
    UVar7 = FUN_0041d3c0('\0',local_10.x,local_10.y);
    if (UVar7 == 0) {
      return false;
    }
    if (*(int *)this != 0x28) {
      puVar8 = FUN_00419890(UVar7);
      return *(uint *)this == ((byte)puVar8[0x24] & 0xffffff7f);
    }
switchD_004201fb_caseD_4:
    return true;
  case 0xe:
    iVar9 = DAT_004a26f0;
    if (DAT_004a26f0 == 0xd) {
      iVar9 = 1;
    }
    return *(int *)this == iVar9;
  default:
switchD_00420090_default:
    return false;
  }
  return false;
}


