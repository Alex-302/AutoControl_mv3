// FUN_00413a10 @ 00413a10 size=51 callers=1

int FUN_00413a10(void)

{
  BOOL BVar1;
  uint3 uVar2;
  tagCURSORINFO local_14;
  
  local_14.cbSize = 0x14;
  local_14.flags = 0;
  local_14.hCursor = (HCURSOR)0x0;
  local_14.ptScreenPos.x = 0;
  local_14.ptScreenPos.y = 0;
  BVar1 = GetCursorInfo(&local_14);
  uVar2 = (uint3)((uint)BVar1 >> 8);
  if ((BVar1 != 0) && (local_14.flags == 0)) {
    return (uint)uVar2 << 8;
  }
  return CONCAT31(uVar2,1);
}


