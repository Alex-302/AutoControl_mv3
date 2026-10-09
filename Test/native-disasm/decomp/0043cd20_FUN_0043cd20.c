// FUN_0043cd20 @ 0043cd20 size=243 callers=1

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_0043cd20(undefined4 *param_1)

{
  char cVar1;
  ushort uVar2;
  undefined2 extraout_var;
  int iVar3;
  void *_Dst;
  char *pcVar4;
  char *pcVar5;
  undefined4 in_XMM1_Da;
  undefined4 in_XMM1_Db;
  
  if ((double)CONCAT44(in_XMM1_Db,in_XMM1_Da) == _DAT_0048f210) {
    uVar2 = FUN_0045fde0(in_XMM1_Da,in_XMM1_Db);
    if (CONCAT22(extraout_var,uVar2) == 0) {
      FUN_0043e0b0((void *)*param_1,&DAT_0048df74,3,0);
      return;
    }
    FUN_0043e0b0((void *)*param_1,&DAT_0048df6c,4,0);
    return;
  }
  pcVar5 = (char *)(param_1 + 1);
  iVar3 = FUN_004023b0(pcVar5,0x40,"%.*g");
  if (*(char *)(param_1 + 0x12) != '\0') {
    _Dst = (void *)FUN_00447fd0(pcVar5,(byte *)(pcVar5 + iVar3),(byte *)(param_1 + 0x12));
    _memset(_Dst,0,(int)param_1 + (0x44 - (int)_Dst));
    iVar3 = (int)_Dst - (int)pcVar5;
  }
  cVar1 = *(char *)((int)param_1 + 0x49);
  if ((cVar1 != '\0') && (cVar1 != '.')) {
    for (pcVar4 = pcVar5; pcVar4 != (char *)(param_1 + 0x11); pcVar4 = pcVar4 + 1) {
      if (*pcVar4 == cVar1) {
        *pcVar4 = '.';
        break;
      }
    }
  }
  FUN_0043e0b0((void *)*param_1,pcVar5,iVar3,iVar3 >> 0x1f);
  while( true ) {
    if (pcVar5 == (char *)((int)param_1 + iVar3 + 5)) {
      FUN_0043e0b0((void *)*param_1,&DAT_0048df80,2,0);
      return;
    }
    if (*pcVar5 == '.') break;
    if (*pcVar5 == 'e') {
      return;
    }
    pcVar5 = pcVar5 + 1;
  }
  return;
}


