// FUN_0043d670 @ 0043d670 size=187 callers=1

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0043d670(uint param_1)

{
  uint *puVar1;
  int iVar2;
  
  puVar1 = FUN_0043ffd0(param_1);
  FUN_00450290(_DAT_004a2550,DAT_004a2554,puVar1);
  iVar2 = (int)DAT_004a2554 - (int)_DAT_004a2550;
  if (_DAT_004a2550 != (uint *)0x0) {
    FUN_00447d20(_DAT_004a2550,DAT_004a2554);
    FUN_00402430(_DAT_004a2550,((int)_DAT_004a2558 - (int)_DAT_004a2550) / 0x18,0x18);
  }
  _DAT_004a2550 = puVar1;
  _DAT_004a2558 = puVar1 + param_1 * 6;
  DAT_004a2554 = puVar1 + (iVar2 / 0x18) * 6;
  return;
}


