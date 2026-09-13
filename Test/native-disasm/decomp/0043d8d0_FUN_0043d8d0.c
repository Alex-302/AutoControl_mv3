// FUN_0043d8d0 @ 0043d8d0 size=137 callers=1

void __fastcall FUN_0043d8d0(undefined4 param_1,uint *param_2)

{
  uint uVar1;
  uint *puVar2;
  int unaff_EBP;
  uint *unaff_ESI;
  uint unaff_EDI;
  
  uVar1 = *(uint *)(unaff_EBP + 0xc);
  *(uint **)(unaff_EBP + -0x18) = param_2;
  if (uVar1 != 0) {
    puVar2 = unaff_ESI;
    if (7 < unaff_ESI[5]) {
      puVar2 = (uint *)*unaff_ESI;
    }
    if (uVar1 != 0) {
      FUN_0045c870(param_2,puVar2,uVar1 * 2);
    }
  }
  if (7 < unaff_ESI[5]) {
    FUN_00402430((void *)*unaff_ESI,unaff_ESI[5] + 1,2);
  }
  unaff_ESI[5] = 7;
  unaff_ESI[4] = 0;
  puVar2 = unaff_ESI;
  if (7 < unaff_ESI[5]) {
    puVar2 = (uint *)*unaff_ESI;
  }
  *(undefined2 *)puVar2 = 0;
  puVar2 = *(uint **)(unaff_EBP + -0x18);
  *unaff_ESI = (uint)puVar2;
  unaff_ESI[5] = unaff_EDI;
  unaff_ESI[4] = uVar1;
  if (7 < unaff_ESI[5]) {
    unaff_ESI = puVar2;
  }
  ExceptionList = *(void **)(unaff_EBP + -0xc);
  *(undefined2 *)((int)unaff_ESI + uVar1 * 2) = 0;
  return;
}


