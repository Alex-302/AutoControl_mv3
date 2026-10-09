// FUN_0041e3b0 @ 0041e3b0 size=490 callers=1

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

bool __fastcall FUN_0041e3b0(uint param_1,char param_2)

{
  int iVar1;
  int iVar2;
  HWND pHVar3;
  DWORD DVar4;
  short sVar5;
  undefined4 *puVar6;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  char local_38 [20];
  char local_24 [8];
  tagPOINT local_1c;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  iVar1 = DAT_004a299c;
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047b8fe;
  local_10 = ExceptionList;
  if ((DAT_004a2998 != 0) || (DAT_004a299c != 0)) {
    sVar5 = (short)param_1;
    local_14 = param_1;
    if ((sVar5 == 1) || ((sVar5 == 4 || (sVar5 == 2)))) {
      ExceptionList = &local_10;
      if (200 < (uint)(DAT_004a26b4 - _DAT_004a32e8)) {
        ExceptionList = &local_10;
        GetCursorPos(&local_1c);
        DAT_004a2a48 = local_1c.x;
        DAT_004a2a4c = local_1c.y;
        _DAT_004a32e8 = DAT_004a26b4;
      }
      local_1c.x = DAT_004a2a48;
      local_1c.y = DAT_004a2a4c;
      pHVar3 = FUN_00404e30(&local_1c,'\0');
      DVar4 = GetWindowThreadProcessId(pHVar3,(LPDWORD)0x0);
      local_24[0] = DVar4 == DAT_004a2450;
      if (!(bool)local_24[0]) {
        DAT_004a2445 = 1;
        local_8 = 0;
        FUN_004381d0(&local_1c,'\0');
        local_8 = 1;
        FUN_00426e50(local_38);
        FUN_00434820(local_38);
        FUN_00434820(local_24);
      }
    }
    else if (param_2 == '\0') {
      local_44 = 0x25001b;
      builtin_strncpy(local_38 + 0xc,"]\x01]\x04]\x05",6);
      local_1c.x = (LONG)&local_44;
      local_40 = 0x260125;
      local_1c.y = (LONG)(local_38 + 0x12);
      local_3c = 0x270126;
      builtin_strncpy(local_38,"\'\x01(",4);
      builtin_strncpy(local_38 + 4,"(\x01\r",4);
      builtin_strncpy(local_38 + 8,"\r\x01]",4);
      ExceptionList = &local_10;
      iVar2 = FUN_00442000(&local_1c.x,(short *)&local_14);
      if (-1 < iVar2) {
        if (iVar1 == 0) {
          pHVar3 = *(HWND *)(&DAT_004a2470 + DAT_004a23dc * 4);
        }
        else {
          pHVar3 = *(HWND *)(iVar1 + 0x28);
        }
        PostMessageA(pHVar3,0x101 - ((param_1 & 0xfc00) != 0x400),param_1 & 0x2ff,0);
        ExceptionList = local_10;
        return true;
      }
    }
  }
  puVar6 = &DAT_004a2538;
  if (0xf < DAT_004a254c) {
    puVar6 = DAT_004a2538;
  }
  ExceptionList = local_10;
  return *(char *)(puVar6 + 1) != *(char *)((int)puVar6 + 0x1e);
}


