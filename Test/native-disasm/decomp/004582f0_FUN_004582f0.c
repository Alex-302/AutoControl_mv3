// FUN_004582f0 @ 004582f0 size=77 callers=1

undefined1 * __fastcall FUN_004582f0(char *param_1,char *param_2,undefined1 *param_3)

{
  int extraout_ECX;
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = (int)param_2 - (int)param_1;
  iVar3 = 0;
  if (param_2 < param_1) {
    iVar2 = 0;
  }
  if (iVar2 == 0) {
    return param_3;
  }
  do {
    iVar1 = 0;
    if (param_3 != (undefined1 *)0x0) {
      *param_3 = 0;
      *(undefined8 *)(param_3 + 8) = 0;
      FUN_004511e0(param_3,*param_1);
      iVar1 = extraout_ECX;
    }
    iVar3 = iVar3 + 1;
    param_3 = (undefined1 *)(iVar1 + 0x10);
    param_1 = param_1 + 1;
  } while (iVar3 != iVar2);
  return param_3;
}


