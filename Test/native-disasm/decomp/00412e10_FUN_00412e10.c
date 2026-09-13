// FUN_00412e10 @ 00412e10 size=805 callers=1

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __fastcall FUN_00412e10(int param_1,uint *param_2,byte param_3)

{
  byte bVar1;
  bool bVar2;
  ushort uVar3;
  uint3 uVar4;
  char cVar5;
  bool bVar6;
  ushort uVar7;
  undefined4 *puVar8;
  uint uVar9;
  undefined2 uStack00000006;
  uint *local_24;
  uint local_20;
  uint local_1c;
  int local_15;
  undefined1 local_11;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 uStack_8;
  
  uStack_8 = 0xffffffff;
  puStack_c = &LAB_0047ab50;
  local_10 = ExceptionList;
  if (param_3 == 0) {
    if ((param_1 == 0x100) || (uStack00000006._1_1_ = '\0', param_1 == 0x104)) {
      uStack00000006._1_1_ = '\x01';
    }
    if (((param_2[2] & 1) == 0) ||
       ((((bVar1 = (byte)*param_2, bVar1 < 0x21 || (0x28 < bVar1)) && (bVar1 != 0x2d)) &&
        ((bVar1 != 0x2e && (bVar1 != 0xd)))))) {
      uVar3 = 0;
    }
    else {
      uVar3 = 0x100;
    }
    uVar3 = (ushort)*param_2 | uVar3;
    uVar9 = *param_2;
    if ((((uVar9 < 7) || ((uVar9 - 0x15 < 0xb && (uVar9 != 0x1b)))) || (0xe2 < uVar9)) ||
       ((((0x39 < uVar9 && (uVar9 < 0x41)) || ((0xc0 < uVar9 && (uVar9 < 0xdb)))) ||
        (((uVar9 == 0x11 || (uVar9 == 0x10)) || (uVar9 == 0x12)))))) {
      cVar5 = -1;
    }
    else if ((param_2[2] & 0x10) == 0) {
      cVar5 = '\0';
    }
    else {
      cVar5 = (param_2[4] != 0xd6c18935) * '\x02' + -1;
    }
    if ((cVar5 < (char)(DAT_004a255c / 0x5609)) || (('\0' < cVar5 && (DAT_004a2425 != '\0')))) {
      local_11 = 1;
      DAT_004a2448 = 0;
    }
    else {
      local_11 = 0;
      ExceptionList = &local_10;
      FUN_00412d40((uint)uVar3,uStack00000006._1_1_,param_2[3]);
    }
    if (uStack00000006._1_1_ == '\0') {
      puVar8 = &DAT_004a2538;
      if (0xf < DAT_004a254c) {
        puVar8 = DAT_004a2538;
      }
      _param_3 = CONCAT13(local_11,CONCAT12(cVar5,(byte)(*(char *)(puVar8 + 3) -
                                                        *(char *)(puVar8 + 8)) + 0x400 | uVar3));
      ExceptionList = local_10;
      return _param_3;
    }
    _param_3 = CONCAT13(local_11,CONCAT12(cVar5,uVar3));
    ExceptionList = local_10;
    return _param_3;
  }
  uVar3 = (ushort)CONCAT31((uint3)param_3,1);
  uVar9 = 0;
  local_15 = CONCAT31(local_15._1_3_,1);
  bVar2 = true;
  uVar4 = (uint3)((uint)param_1 >> 8);
  switch(param_1) {
  case 0x202:
    uVar3 = (ushort)param_3 << 8;
    local_15 = (uint)local_15._1_3_ << 8;
  case 0x201:
    uVar9 = 1;
    break;
  default:
    goto switchD_00412fbd_caseD_203;
  case 0x205:
    uVar3 = (ushort)param_3 << 8;
    local_15 = (uint)local_15._1_3_ << 8;
  case 0x204:
    uVar9 = 2;
    break;
  case 0x208:
    uVar3 = (ushort)param_3 << 8;
    local_15 = (uint)local_15._1_3_ << 8;
  case 0x207:
    uVar9 = 4;
    break;
  case 0x20a:
  case 0x20e:
    bVar2 = false;
    uVar7 = (param_1 != 0x20a) + 0x200;
    bVar6 = 0x7fff0000 < (param_2[2] & 0xffff0000);
    uVar3 = CONCAT11(param_3,bVar6);
    local_15 = CONCAT31(local_15._1_3_,bVar6);
    goto LAB_0041302b;
  case 0x20c:
    uVar3 = (ushort)param_3 << 8;
    local_15 = (uint)local_15._1_3_ << 8;
  case 0x20b:
    uVar7 = 6 - ((param_2[2] & 0x50000) != 0);
LAB_0041302b:
    uVar9 = (uint)uVar7;
    if (uVar7 != 0) break;
    goto switchD_00412fbd_caseD_203;
  }
  if ((param_2[3] & 1) == 0) {
    local_1c = (uint)uVar4 << 8;
  }
  else if (param_2[5] == 0xd6c18935) {
switchD_00412fbd_caseD_203:
    local_1c = CONCAT31(uVar4,0xff);
  }
  else {
    local_1c = 1;
    if (param_2[5] == 0xd6c18936) {
      local_1c = 0xfffffffe;
    }
  }
  bVar6 = SUB21(uVar3,0);
  if (((char)local_1c < (char)(DAT_004a255c / 0x5609)) ||
     (('\0' < (char)local_1c && (DAT_004a2424 != '\0')))) {
    uVar7 = CONCAT11(1,bVar6);
    (&DAT_004a2448)[(char)(uVar3 >> 8)] = 0;
  }
  else {
    uVar7 = uVar3 & 0xff;
    local_20 = uVar9 & 0x1f;
    local_24 = (uint *)(DAT_004a28b0 + (uVar9 >> 5) * 4);
    DAT_004a23a2 = (*local_24 & 1 << (sbyte)local_20) != 0;
    if (((bool)DAT_004a23a2 != bVar6) && (bVar2)) {
      DAT_004a26b9 = DAT_004a26b9 + (bVar6 != false) * '\x02' + -1;
      ExceptionList = &local_10;
      FUN_004338f0(&local_24,(char)local_15);
    }
    DAT_004a26b4 = param_2[4];
    DAT_004a2a48 = *param_2;
    DAT_004a2a4c = param_2[1];
    _DAT_004a32e8 = DAT_004a26b4;
  }
  _param_3 = (local_1c & 0xff) << 0x10;
  uVar3 = 0x400;
  _param_3 = CONCAT13((char)(uVar7 >> 8),_param_3);
  if ((char)uVar7 != '\0') {
    uVar3 = 0;
  }
  ExceptionList = local_10;
  _param_3 = CONCAT22(uStack00000006,uVar3 | (ushort)uVar9);
  return _param_3;
}


