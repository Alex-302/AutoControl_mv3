// FUN_004582a0 @ 004582a0 size=80 callers=1

undefined1 * __fastcall FUN_004582a0(undefined2 *param_1,undefined2 *param_2,undefined1 *param_3)

{
  int extraout_ECX;
  int iVar1;
  undefined2 *extraout_EDX;
  uint uVar2;
  uint uVar3;
  
  uVar3 = 0;
  uVar2 = (uint)((int)param_2 + (1 - (int)param_1)) >> 1;
  if (param_2 < param_1) {
    uVar2 = 0;
  }
  if (uVar2 == 0) {
    return param_3;
  }
  do {
    iVar1 = 0;
    if (param_3 != (undefined1 *)0x0) {
      *param_3 = 0;
      *(undefined8 *)(param_3 + 8) = 0;
      FUN_004512e0(param_3,CONCAT22((short)((uint)param_2 >> 0x10),*param_1));
      iVar1 = extraout_ECX;
      param_2 = extraout_EDX;
    }
    uVar3 = uVar3 + 1;
    param_3 = (undefined1 *)(iVar1 + 0x10);
    param_1 = param_1 + 1;
  } while (uVar3 != uVar2);
  return param_3;
}


