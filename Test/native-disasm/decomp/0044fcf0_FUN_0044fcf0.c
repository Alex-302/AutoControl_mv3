// FUN_0044fcf0 @ 0044fcf0 size=48 callers=1

void * __fastcall FUN_0044fcf0(undefined4 *param_1,undefined4 *param_2,void *param_3)

{
  int extraout_ECX;
  int iVar1;
  
  if (param_1 == param_2) {
    return param_3;
  }
  do {
    iVar1 = 0;
    if (param_3 != (void *)0x0) {
      FUN_004561d0(param_3,param_1);
      iVar1 = extraout_ECX;
    }
    param_1 = param_1 + 9;
    param_3 = (void *)(iVar1 + 0x24);
  } while (param_1 != param_2);
  return param_3;
}


