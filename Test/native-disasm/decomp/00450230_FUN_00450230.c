// FUN_00450230 @ 00450230 size=89 callers=5

undefined1 * __fastcall FUN_00450230(undefined1 *param_1,undefined1 *param_2,undefined1 *param_3)

{
  if (param_1 == param_2) {
    return param_3;
  }
  do {
    if (param_3 != (undefined1 *)0x0) {
      *param_3 = *param_1;
      *(undefined4 *)(param_3 + 8) = *(undefined4 *)(param_1 + 8);
      *(undefined4 *)(param_3 + 0xc) = *(undefined4 *)(param_1 + 0xc);
      *param_1 = 0;
      *(undefined4 *)(param_1 + 8) = 0;
      *(undefined4 *)(param_1 + 0xc) = 0;
    }
    param_1 = param_1 + 0x10;
    param_3 = param_3 + 0x10;
  } while (param_1 != param_2);
  return param_3;
}


