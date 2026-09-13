// FUN_0043f6bd @ 0043f6bd size=127 callers=3

void FUN_0043f6bd(void)

{
  uint uVar1;
  uint *puVar2;
  uint *unaff_EBX;
  int unaff_EBP;
  uint *unaff_ESI;
  uint unaff_EDI;
  
  uVar1 = *(uint *)(unaff_EBP + 0xc);
  if (uVar1 != 0) {
    puVar2 = unaff_ESI;
    if (0xf < unaff_ESI[5]) {
      puVar2 = (uint *)*unaff_ESI;
    }
    if (uVar1 != 0) {
      FUN_0045c870(unaff_EBX,puVar2,uVar1);
    }
  }
  if (0xf < unaff_ESI[5]) {
    FUN_00402430((void *)*unaff_ESI,unaff_ESI[5] + 1,1);
  }
  unaff_ESI[5] = 0xf;
  unaff_ESI[4] = 0;
  puVar2 = unaff_ESI;
  if (0xf < unaff_ESI[5]) {
    puVar2 = (uint *)*unaff_ESI;
  }
  *(undefined1 *)puVar2 = 0;
  uVar1 = *(uint *)(unaff_EBP + 0xc);
  *unaff_ESI = (uint)unaff_EBX;
  unaff_ESI[5] = unaff_EDI;
  unaff_ESI[4] = uVar1;
  if (0xf < unaff_ESI[5]) {
    unaff_ESI = unaff_EBX;
  }
  ExceptionList = *(void **)(unaff_EBP + -0xc);
  *(undefined1 *)((int)unaff_ESI + uVar1) = 0;
  return;
}


