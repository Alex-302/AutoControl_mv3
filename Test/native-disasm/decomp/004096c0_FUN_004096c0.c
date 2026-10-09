// FUN_004096c0 @ 004096c0 size=138 callers=6

undefined1 __cdecl FUN_004096c0(byte *param_1)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  char *pcVar4;
  byte **ppbVar5;
  undefined1 uVar6;
  uint in_stack_00000014;
  uint in_stack_00000018;
  
  if (*PTR_s_Chrome_WidgetWin__0049d9f8 == '\0') {
    iVar3 = 0;
  }
  else {
    pcVar4 = PTR_s_Chrome_WidgetWin__0049d9f8;
    do {
      cVar1 = *pcVar4;
      pcVar4 = pcVar4 + 1;
    } while (cVar1 != '\0');
    iVar3 = (int)pcVar4 - (int)(PTR_s_Chrome_WidgetWin__0049d9f8 + 1);
  }
  iVar3 = FUN_0043aad0(&param_1,PTR_s_Chrome_WidgetWin__0049d9f8,iVar3,iVar3);
  if (iVar3 == 0) {
    ppbVar5 = &param_1;
    if (0xf < in_stack_00000018) {
      ppbVar5 = (byte **)param_1;
    }
    uVar2 = 0x12;
    if (in_stack_00000014 < 0x12) {
      uVar2 = in_stack_00000014;
    }
    uVar2 = FUN_004023d0((byte *)ppbVar5,(byte *)"Chrome_WidgetWin_0",uVar2);
    if (((uVar2 != 0) || (in_stack_00000014 < 0x12)) || (0x12 < in_stack_00000014)) {
      uVar6 = 1;
      goto LAB_0040972d;
    }
  }
  uVar6 = 0;
LAB_0040972d:
  if (0xf < in_stack_00000018) {
    FUN_00402430(param_1,in_stack_00000018 + 1,1);
  }
  return uVar6;
}


