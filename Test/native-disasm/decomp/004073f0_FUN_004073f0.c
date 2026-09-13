// FUN_004073f0 @ 004073f0 size=130 callers=2

bool __fastcall FUN_004073f0(char param_1)

{
  BOOL BVar1;
  RAWINPUTDEVICE local_18;
  undefined4 local_c;
  DWORD local_8;
  HWND local_4;
  
  if ((param_1 != DAT_004a2a30) && ((DAT_004a23c7 == '\0' || (param_1 != '\0')))) {
    local_18.dwFlags = 1;
    if (param_1 == '\0') {
      local_18.hwndTarget = (HWND)0x0;
    }
    else {
      local_18.dwFlags = 0x100;
      local_18.hwndTarget = *(HWND *)(&DAT_004a2470 + DAT_004a2458 * 4);
    }
    local_18.usUsagePage = 1;
    local_18.usUsage = 4;
    local_c = 0x50001;
    DAT_004a2a30 = param_1;
    local_8 = local_18.dwFlags;
    local_4 = local_18.hwndTarget;
    BVar1 = RegisterRawInputDevices(&local_18,2,0xc);
    return BVar1 != 0;
  }
  return true;
}


