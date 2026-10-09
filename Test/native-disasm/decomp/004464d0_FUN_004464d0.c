// FUN_004464d0 @ 004464d0 size=397 callers=2

undefined4 * __fastcall FUN_004464d0(undefined4 *param_1,uint param_2,int param_3)

{
  byte bVar1;
  undefined4 *puVar2;
  undefined **local_2c;
  undefined8 local_28;
  char *local_20;
  undefined1 local_1c;
  undefined4 *local_18;
  undefined4 local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_004792d9;
  local_10 = ExceptionList;
  local_8 = 0;
  local_14 = 0;
  local_18 = param_1;
  if (param_2 - 0xd800 < 0x400) {
    if (0x3ff < param_3 - 0xdc00U) {
      local_2c = std::exception::vftable;
      local_20 = "missing or wrong low surrogate";
      local_1c = 1;
      local_28 = 0;
      ExceptionList = &local_10;
      ___std_exception_copy(&local_20,(undefined4 *)&local_28);
      local_2c = std::invalid_argument::vftable;
                    /* WARNING: Subroutine does not return */
      __CxxThrowException_8((int *)&local_2c,&DAT_00499edc);
    }
    param_2 = param_2 * 0x400 + -0x35fdc00 + param_3;
  }
  ExceptionList = &local_10;
  param_1[4] = 0;
  param_1[5] = 0;
  param_1[5] = 0xf;
  param_1[4] = 0;
  puVar2 = param_1;
  if (0xf < (uint)param_1[5]) {
    puVar2 = (undefined4 *)*param_1;
  }
  *(undefined1 *)puVar2 = 0;
  local_8 = 0;
  local_14 = 1;
  if (0x7f < param_2) {
    if (param_2 < 0x800) {
      bVar1 = (byte)(param_2 >> 6) & 0x1f | 0xc0;
    }
    else {
      if (param_2 < 0x10000) {
        bVar1 = (byte)(param_2 >> 0xc) & 0xf | 0xe0;
      }
      else {
        if (0x10ffff < param_2) {
          FUN_00402590(&local_2c,"code points above 0x10FFFF are invalid");
                    /* WARNING: Subroutine does not return */
          __CxxThrowException_8((int *)&local_2c,&DAT_00499ebc);
        }
        FUN_0043aef0(param_1,1,(byte)(param_2 >> 0x12) & 7 | 0xf0);
        bVar1 = (byte)(param_2 >> 0xc) & 0x3f | 0x80;
      }
      FUN_0043aef0(param_1,1,bVar1);
      bVar1 = (byte)(param_2 >> 6) & 0x3f | 0x80;
    }
    FUN_0043aef0(param_1,1,bVar1);
    param_2 = (uint)((byte)param_2 & 0x3f | 0x80);
  }
  FUN_0043aef0(param_1,1,(char)param_2);
  ExceptionList = local_10;
  return param_1;
}


