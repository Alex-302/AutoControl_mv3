// FUN_00453250 @ 00453250 size=58 callers=1

void * __fastcall FUN_00453250(undefined4 *param_1,undefined4 *param_2,void *param_3)

{
  if (param_1 == param_2) {
    return param_3;
  }
  do {
    if (param_3 != (void *)0x0) {
      FUN_00456ce0(param_3,param_1);
      *(undefined1 *)((int)param_3 + 0x14) = *(undefined1 *)(param_1 + 5);
    }
    param_1 = param_1 + 6;
    param_3 = (void *)((int)param_3 + 0x18);
  } while (param_1 != param_2);
  return param_3;
}


