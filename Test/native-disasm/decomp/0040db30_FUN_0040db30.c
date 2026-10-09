// FUN_0040db30 @ 0040db30 size=140 callers=2

char __fastcall FUN_0040db30(char param_1)

{
  char cVar1;
  undefined4 uVar2;
  BOOL BVar3;
  
  if (param_1 == '\0') {
    DAT_004a2a38 = '\0';
    if (DAT_0049fc58 != (HWINEVENTHOOK)0x0) {
      BVar3 = UnhookWinEvent(DAT_0049fc58);
      if (BVar3 == 0) {
        return '\0';
      }
    }
    cVar1 = '\x01';
  }
  else {
    cVar1 = DAT_004a2a38;
    if (DAT_004a2a38 == '\0') {
      if (DAT_0049fc58 == (HWINEVENTHOOK)0x0) {
        DAT_0049fc58 = SetWinEventHook(2,2,(HMODULE)0x0,FUN_0040dac0,0,0,0);
      }
      if ((DAT_004a2518 - (int)DAT_004a2514 & 0xfffffffcU) != 0) {
        uVar2 = FUN_0040daf0((HWND)*DAT_004a2514);
        if (((char)uVar2 != '\0') && (DAT_0049fc58 != (HWINEVENTHOOK)0x0)) {
          DAT_004a2a38 = 1;
          return '\x01';
        }
      }
      DAT_004a2a38 = 0;
      return '\0';
    }
  }
  return cVar1;
}


