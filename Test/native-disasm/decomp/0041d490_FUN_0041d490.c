// FUN_0041d490 @ 0041d490 size=113 callers=1

undefined1 __fastcall FUN_0041d490(HWND param_1)

{
  bool bVar1;
  bool bVar2;
  DWORD DVar3;
  byte *pbVar4;
  undefined1 uVar5;
  void *local_1c [5];
  uint local_8;
  
  bVar1 = false;
  DVar3 = GetWindowThreadProcessId(param_1,(LPDWORD)0x0);
  if (DVar3 == DAT_004a2450) {
    pbVar4 = (byte *)FUN_00404670((int *)local_1c,param_1);
    bVar1 = true;
    bVar2 = FUN_00440970(pbVar4,(byte *)"#32768");
    if (bVar2) {
      uVar5 = 1;
      goto LAB_0041d4d9;
    }
  }
  uVar5 = 0;
LAB_0041d4d9:
  if ((bVar1) && (0xf < local_8)) {
    FUN_00402430(local_1c[0],local_8 + 1,1);
  }
  return uVar5;
}


