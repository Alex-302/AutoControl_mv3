// FUN_00439e90 @ 00439e90 size=104 callers=1

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00439e90(void)

{
  if (_DAT_004a2550 != (uint *)0x0) {
    FUN_00447d20(_DAT_004a2550,DAT_004a2554);
    FUN_00402430(_DAT_004a2550,(_DAT_004a2558 - (int)_DAT_004a2550) / 0x18,0x18);
    _DAT_004a2550 = (uint *)0x0;
    DAT_004a2554 = (uint *)0x0;
    _DAT_004a2558 = 0;
  }
  return;
}


