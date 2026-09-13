// FUN_00412d40 @ 00412d40 size=198 callers=2

void __fastcall FUN_00412d40(uint param_1,char param_2,undefined4 param_3)

{
  uint *puVar1;
  int iVar2;
  uint uVar3;
  short extraout_CX;
  uint uVar4;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 uStack_8;
  
  uStack_8 = 0xffffffff;
  puStack_c = &LAB_0047ab50;
  local_10 = ExceptionList;
  uVar4 = param_1 & 0x1f;
  puVar1 = (uint *)(DAT_004a28b0 + ((param_1 & 0xffff) >> 5) * 4);
  DAT_004a23a2 = (*puVar1 & 1 << (sbyte)uVar4) != 0;
  ExceptionList = &local_10;
  if (DAT_004a23a2 != param_2) {
    DAT_004a26b8 = DAT_004a26b8 + (param_2 != '\0') * '\x02' + -1;
    if (param_2 == '\0') {
      uVar4 = *puVar1 & ~(1 << uVar4);
    }
    else {
      uVar4 = *puVar1 | 1 << uVar4;
    }
    ExceptionList = &local_10;
    *puVar1 = uVar4;
  }
  iVar2 = DAT_004a28b0;
  uVar4 = FUN_00412bd0((ushort)param_1);
  uVar3 = uVar4 & 0xffff;
  if (((short)uVar4 != extraout_CX) &&
     ((*(uint *)(iVar2 + (uVar3 >> 5) * 4) & 1 << ((byte)uVar3 & 0x1f)) != 0)) {
    puVar1 = (uint *)(iVar2 + (uVar3 >> 5) * 4);
    *puVar1 = *puVar1 & ~(1 << (uVar4 & 0x1f));
    DAT_004a26b8 = DAT_004a26b8 + -1;
  }
  DAT_004a26b4 = param_3;
  ExceptionList = local_10;
  return;
}


