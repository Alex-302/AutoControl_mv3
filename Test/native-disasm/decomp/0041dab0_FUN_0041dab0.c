// FUN_0041dab0 @ 0041dab0 size=135 callers=3

HMENU __thiscall FUN_0041dab0(void *this,uint param_1)

{
  HMENU pHVar1;
  MENUINFO local_1c;
  
  pHVar1 = CreatePopupMenu();
  local_1c.cbSize = 0x1c;
  local_1c._20_8_ = ZEXT48(this) << 0x20;
  local_1c.cyMax = 0;
  local_1c.hbrBack = (HBRUSH)0x0;
  local_1c.fMask = 0x80000018;
  local_1c.dwStyle = 0x24000000;
  if (param_1 != 0xf0000000) {
    local_1c.fMask = 0x8000001a;
    local_1c.hbrBack =
         CreateSolidBrush((param_1 >> 8 & 0xff | (param_1 & 0xff) << 8) << 8 |
                          param_1 >> 0x10 & 0xff);
  }
  SetMenuInfo(pHVar1,&local_1c);
  return pHVar1;
}


