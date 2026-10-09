// FUN_00408230 @ 00408230 size=132 callers=1

uint __fastcall FUN_00408230(ushort param_1)

{
  ulonglong uVar1;
  undefined1 uVar2;
  uint uVar3;
  byte bVar4;
  undefined4 local_4;
  
  local_4 = 0;
  if ((((param_1 & 0xfc00) == 0) || ((param_1 & 0xfc00) == 0x400)) && (0x21f < (param_1 & 0x3ff))) {
    uVar1 = (ulonglong)(ushort)((param_1 & 0x3ff) - 0x220);
    uVar2 = (undefined1)(uVar1 / 0x3c);
    bVar4 = (byte)(uVar1 % 0x3c);
    if (bVar4 < 0x20) {
      local_4._0_2_ = CONCAT11(0x42,uVar2);
      local_4 = (uint)CONCAT12(bVar4,(undefined2)local_4);
      return local_4;
    }
    local_4._0_2_ = CONCAT11(0x56,uVar2);
    uVar3 = (int)(char)(bVar4 - 0x20) & 0x80000001;
    if ((int)uVar3 < 0) {
      uVar3 = (uVar3 - 1 | 0xfffffffe) + 1;
    }
    local_4 = CONCAT13((char)uVar3 * '\x02' + -1,
                       CONCAT12((char)(bVar4 - 0x20) / '\x02',(undefined2)local_4));
  }
  return local_4;
}


