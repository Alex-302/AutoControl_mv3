// FUN_00406470 @ 00406470 size=212 callers=1

void __fastcall FUN_00406470(HWND param_1,char param_2)

{
  uint uVar1;
  int *piVar2;
  int local_20;
  int iStack_1c;
  int iStack_18;
  int iStack_14;
  
  uVar1 = GetWindowLongA(param_1,-0x10);
  if (uVar1 != 0) {
    if (param_2 == '\0') {
      piVar2 = (int *)FUN_00404c40(param_1,&local_20);
      local_20 = *piVar2;
      iStack_1c = piVar2[1];
      iStack_18 = piVar2[2] - local_20;
      iStack_14 = piVar2[3] - iStack_1c;
      uVar1 = uVar1 & 0xfeffffff;
    }
    else {
      local_20 = 0;
      iStack_1c = 0;
      iStack_18 = 0;
      iStack_14 = 0;
      uVar1 = uVar1 & 0xdfffffff | 0x1000000;
    }
    SetWindowLongA(param_1,-0x10,uVar1);
    SetWindowPos(param_1,(HWND)0x0,local_20,iStack_1c,iStack_18,iStack_14,0x4034);
  }
  return;
}


