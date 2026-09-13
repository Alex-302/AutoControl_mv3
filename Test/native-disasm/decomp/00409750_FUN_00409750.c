// FUN_00409750 @ 00409750 size=162 callers=7

undefined1 __fastcall FUN_00409750(HWND param_1)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined1 uVar5;
  byte *in_stack_ffffffb8;
  CHAR local_28 [4];
  uint local_24;
  void *local_20 [5];
  uint local_c;
  
  local_24 = 0;
  FUN_00404670((int *)&stack0xffffffb8,param_1);
  cVar1 = FUN_004096c0(in_stack_ffffffb8);
  uVar2 = local_24;
  if (cVar1 != '\0') {
    uVar2 = GetWindowLongA(param_1,-0x10);
    if ((uVar2 & 0x30000) == 0x30000) {
      uVar5 = 1;
      uVar2 = local_24;
      goto LAB_004097cc;
    }
    iVar3 = GetWindowTextA(param_1,local_28,2);
    uVar2 = local_24;
    if (iVar3 != 0) {
      puVar4 = FUN_004057a0(local_20,param_1);
      uVar2 = 1;
      if (puVar4[4] != 0) {
        uVar5 = 1;
        goto LAB_004097cc;
      }
    }
  }
  uVar5 = 0;
LAB_004097cc:
  if (((uVar2 & 1) != 0) && (0xf < local_c)) {
    FUN_00402430(local_20[0],local_c + 1,1);
  }
  return uVar5;
}


