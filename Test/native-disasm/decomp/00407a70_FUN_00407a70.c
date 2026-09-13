// FUN_00407a70 @ 00407a70 size=330 callers=1

undefined4 * __fastcall FUN_00407a70(undefined4 *param_1)

{
  uint uVar1;
  PRAWINPUTDEVICELIST ptVar2;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined8 local_34;
  undefined4 local_2c;
  PRAWINPUTDEVICELIST local_28;
  PRAWINPUTDEVICELIST local_24;
  int local_20;
  undefined4 *local_1c;
  undefined4 local_18;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00479711;
  local_10 = ExceptionList;
  local_8 = 0;
  local_18 = 0;
  ExceptionList = &local_10;
  local_1c = param_1;
  GetRawInputDeviceList((PRAWINPUTDEVICELIST)0x0,&local_14,8);
  FUN_00432e10(&local_28,local_14);
  local_8 = 1;
  GetRawInputDeviceList(local_28,&local_14,8);
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  local_18 = 1;
  ptVar2 = local_28;
  if (local_28 != local_24) {
    do {
      if (ptVar2->dwType == 2) {
        local_14 = 0x20;
        local_48 = 0x20;
        local_2c = 0;
        local_44 = 0;
        uStack_40 = 0;
        uStack_3c = 0;
        uStack_38 = 0;
        local_34 = 0;
        GetRawInputDeviceInfoA(ptVar2->hDevice,0x2000000b,&local_48,&local_14);
        if (((short)local_34 == 1) && (local_34._2_2_ == 4)) {
          FUN_00432e80(param_1,&ptVar2->hDevice);
        }
      }
      ptVar2 = ptVar2 + 1;
    } while (ptVar2 != local_24);
  }
  if (local_28 != (PRAWINPUTDEVICELIST)0x0) {
    uVar1 = local_20 - (int)local_28 >> 3;
    if (0x1fffffff < uVar1) {
                    /* WARNING: Subroutine does not return */
      FUN_00465fb2();
    }
    ptVar2 = local_28;
    if (0xfff < uVar1 << 3) {
      if (((uint)local_28 & 0x1f) != 0) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
      ptVar2 = (PRAWINPUTDEVICELIST)local_28[-1].dwType;
      if (local_28 <= ptVar2) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
      if ((uint)((int)local_28 - (int)ptVar2) < 4) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
      if (0x23 < (uint)((int)local_28 - (int)ptVar2)) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
    }
    FID_conflict__free(ptVar2);
  }
  ExceptionList = local_10;
  return param_1;
}


