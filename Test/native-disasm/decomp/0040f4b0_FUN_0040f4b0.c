// FUN_0040f4b0 @ 0040f4b0 size=61 callers=1

undefined4 * __fastcall FUN_0040f4b0(undefined4 *param_1)

{
  undefined4 *local_8;
  undefined4 *local_4;
  
  local_8 = &DAT_004a2514;
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  local_4 = param_1;
  EnumWindows(thunk_FUN_0040f4f0,(LPARAM)&local_8);
  return param_1;
}


