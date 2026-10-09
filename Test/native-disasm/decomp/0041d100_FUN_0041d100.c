// FUN_0041d100 @ 0041d100 size=434 callers=1

LRESULT FUN_0041d100(HWND param_1,uint param_2,uint param_3,int param_4)

{
  bool bVar1;
  bool bVar2;
  void *this;
  char cVar3;
  ushort uVar4;
  uint uVar5;
  LRESULT LVar6;
  
  this = DAT_004a299c;
  if (param_2 < 0x201) {
    if (param_2 != 0x200) {
      if (param_2 == 0x100) {
        switch(param_3) {
        case 0xd:
          goto switchD_0041d145_caseD_d;
        default:
          return 0;
        case 0x1b:
          FUN_0041d0d0();
          return 0;
        case 0x25:
          FUN_0041cbf0(DAT_004a299c,-1,'\0');
          return 0;
        case 0x26:
          FUN_0041cbf0(DAT_004a299c,'\0',-1);
          return 0;
        case 0x27:
          FUN_0041cbf0(DAT_004a299c,'\x01','\0');
          return 0;
        case 0x28:
          FUN_0041cbf0(DAT_004a299c,'\0','\x01');
          return 0;
        }
      }
switchD_0041d225_caseD_203:
      LVar6 = DefWindowProcA(param_1,param_2,param_3,param_4);
      return LVar6;
    }
  }
  else {
    switch(param_2) {
    case 0x201:
    case 0x207:
      *(undefined4 *)((int)DAT_004a299c + 0x38) = 0xffffffff;
      break;
    case 0x202:
    case 0x208:
      uVar5 = FUN_00419fb0(param_2 == 0x208,param_3);
      FUN_0041ca10(this,(char)uVar5);
      return 0;
    default:
      goto switchD_0041d225_caseD_203;
    }
  }
  if (*(int *)((int)this + 0x38) != 0) {
    if (param_4 != *(int *)((int)this + 0x38)) {
      uVar4 = FUN_0041c900(this,(int)(short)param_4,(int)(short)((uint)param_4 >> 0x10));
      FUN_0041c9b0(this,uVar4);
    }
    return 0;
  }
  *(int *)((int)this + 0x38) = param_4;
  return 0;
switchD_0041d145_caseD_d:
  if (((*(byte *)(DAT_004a28b0 + 0x14) & 4) == 0) && ((*(byte *)(DAT_004a28b0 + 0x14) & 8) == 0)) {
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
  if (((*(byte *)(DAT_004a28b0 + 0x14) & 1) == 0) && ((*(byte *)(DAT_004a28b0 + 0x14) & 2) == 0)) {
    bVar2 = false;
  }
  else {
    bVar2 = true;
  }
  if (bVar1) {
    cVar3 = '\x02';
    if (bVar2) goto LAB_0041d1b2;
  }
  else if (!bVar2) {
    FUN_0041ca10(DAT_004a299c,'\0');
    return 0;
  }
  cVar3 = '\x01';
LAB_0041d1b2:
  FUN_0041ca10(DAT_004a299c,cVar3);
  return 0;
}


