// FUN_00413a50 @ 00413a50 size=192 callers=2

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_00413a50(char param_1)

{
  undefined4 uVar1;
  uint uVar2;
  int iVar3;
  undefined **local_38;
  char local_34;
  undefined ***local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047aba8;
  local_10 = ExceptionList;
  iVar3 = (int)param_1;
  uVar2 = *(int *)(&DAT_004a2428 + iVar3 * 4) - *(int *)(&DAT_004a23b0 + iVar3 * 4) >> 0x1f;
  if ((800 < (int)((*(int *)(&DAT_004a2428 + iVar3 * 4) - *(int *)(&DAT_004a23b0 + iVar3 * 4) ^
                   uVar2) - uVar2)) &&
     (ExceptionList = &local_10,
     *(int *)(&DAT_004a2468 + iVar3 * 4) = *(int *)(&DAT_004a2468 + iVar3 * 4) + 1,
     *(int *)(&DAT_004a2468 + iVar3 * 4) == 2)) {
    if (param_1 == '\x01') {
      uVar1 = FUN_00413a10();
      if ((char)uVar1 == '\0') {
        _DAT_004a246c = 0;
        ExceptionList = local_10;
        return;
      }
    }
    local_14 = &local_38;
    local_38 = &PTR_LAB_0048e424;
    local_8 = 0;
    local_34 = param_1;
    FUN_0040fd50(100,(int *)local_14);
    if (local_14 != (undefined ***)0x0) {
      (*(code *)(*local_14)[4])(local_14 != &local_38);
    }
  }
  ExceptionList = local_10;
  return;
}


