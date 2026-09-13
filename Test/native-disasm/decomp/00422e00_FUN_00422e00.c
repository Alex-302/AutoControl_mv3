// FUN_00422e00 @ 00422e00 size=481 callers=1

void FUN_00422e00(void)

{
  int *piVar1;
  undefined4 *puVar2;
  void *pvVar3;
  char cVar4;
  undefined4 uVar5;
  char *pcVar6;
  long lVar7;
  int *piVar8;
  int iVar9;
  void *this;
  undefined4 extraout_ECX;
  HANDLE unaff_EBX;
  int unaff_EBP;
  void *unaff_EDI;
  
  if (*(char *)(unaff_EBP + -0x30) == '\x01') {
    FUN_00434120((void *)(unaff_EBP + -0x30),(undefined4 *)(unaff_EBP + -0x20));
    FUN_004340a0(this,(undefined4 *)(unaff_EBP + -0x78));
    uVar5 = FUN_004383a0((void *)(unaff_EBP + -0x20),(int *)(unaff_EBP + -0x78));
    cVar4 = (char)uVar5;
    while (cVar4 == '\0') {
      pcVar6 = FUN_00433bc0((undefined4 *)(unaff_EBP + -0x20));
      FUN_00440d90(pcVar6,(undefined4 *)(unaff_EBP + -0xa8));
      *(undefined1 *)(unaff_EBP + -4) = 9;
      pcVar6 = FUN_00433b30((void *)(unaff_EBP + -0x20),(undefined1 *)(unaff_EBP + -0x90));
      *(undefined1 *)(unaff_EBP + -4) = 10;
      lVar7 = FUN_00403280(pcVar6);
      *(long *)(unaff_EBP + -0x38) = lVar7;
      piVar8 = FUN_0040a960((int *)(unaff_EBP + -0x54),(undefined4 *)(unaff_EBP + -0xa8));
      *(undefined1 *)(unaff_EBP + -4) = 0xb;
      FUN_00436250(unaff_EDI,(int *)(unaff_EBP + -0x4c),(byte *)(unaff_EBP + -0x38));
      iVar9 = *(int *)(unaff_EBP + -0x4c);
      if (iVar9 == *(int *)((int)unaff_EDI + 4)) {
        *(int *)(unaff_EBP + -0x50) = unaff_EBP + -0x38;
        FUN_0044a600(unaff_EDI,(int *)(unaff_EBP + -0x5c),extraout_ECX,
                     (undefined4 *)(unaff_EBP + -0x50));
        iVar9 = *(int *)(unaff_EBP + -0x5c);
      }
      else {
        *(int *)(unaff_EBP + -0x5c) = iVar9;
        *(undefined1 *)(unaff_EBP + -0x58) = 0;
      }
      piVar1 = (int *)(iVar9 + 0xc);
      if (piVar1 != piVar8) {
        iVar9 = *piVar8;
        *piVar8 = 0;
        puVar2 = (undefined4 *)*piVar1;
        *piVar1 = iVar9;
        if (puVar2 != (undefined4 *)0x0) {
          (**(code **)*puVar2)(1);
        }
      }
      if (*(undefined4 **)(unaff_EBP + -0x54) != (undefined4 *)0x0) {
        (**(code **)**(undefined4 **)(unaff_EBP + -0x54))(1);
      }
      if (0xf < *(uint *)(unaff_EBP + -0x7c)) {
        FUN_00402430(*(void **)(unaff_EBP + -0x90),*(uint *)(unaff_EBP + -0x7c) + 1,1);
      }
      *(undefined1 *)(unaff_EBP + -4) = 6;
      *(undefined4 *)(unaff_EBP + -0x7c) = 0xf;
      *(undefined4 *)(unaff_EBP + -0x80) = 0;
      *(undefined1 *)(unaff_EBP + -0x90) = 0;
      if (0xf < *(uint *)(unaff_EBP + -0x94)) {
        FUN_00402430(*(void **)(unaff_EBP + -0xa8),*(uint *)(unaff_EBP + -0x94) + 1,1);
      }
      if (**(char **)(unaff_EBP + -0x20) == '\x01') {
        *(undefined1 *)(unaff_EBP + -0x3c) = 0;
        FUN_00447660((int *)(unaff_EBP + -0x1c));
      }
      else if (**(char **)(unaff_EBP + -0x20) == '\x02') {
        *(int *)(unaff_EBP + -0x18) = *(int *)(unaff_EBP + -0x18) + 0x10;
      }
      else {
        *(int *)(unaff_EBP + -0x14) = *(int *)(unaff_EBP + -0x14) + 1;
      }
      FUN_004340a0((void *)(unaff_EBP + -0x30),(undefined4 *)(unaff_EBP + -0x78));
      uVar5 = FUN_004383a0((void *)(unaff_EBP + -0x20),(int *)(unaff_EBP + -0x78));
      cVar4 = (char)uVar5;
    }
  }
  FUN_00434820((char *)(unaff_EBP + -0x30));
  pvVar3 = *(void **)(unaff_EBP + -0x68);
  if (pvVar3 != (void *)0x0) {
    FUN_00402430(pvVar3,*(int *)(unaff_EBP + -0x60) - (int)pvVar3,1);
  }
  if (unaff_EBX != (HANDLE)0x0) {
    CloseHandle(unaff_EBX);
  }
  if (7 < *(uint *)(unaff_EBP + -0xac)) {
    FUN_00402430(*(void **)(unaff_EBP + -0xc0),*(uint *)(unaff_EBP + -0xac) + 1,2);
  }
  ExceptionList = *(void **)(unaff_EBP + -0xc);
  return;
}


