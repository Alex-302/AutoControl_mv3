// FUN_00422240 @ 00422240 size=203 callers=1

uint __fastcall FUN_00422240(char param_1)

{
  undefined4 in_EAX;
  uint uVar1;
  undefined4 uVar2;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c [7];
  
  if (param_1 == '\0') {
    if (DAT_004a2398 != '\0') {
      FUN_00411ed0(&DAT_004a28e0);
      FUN_00432210();
      in_EAX = GdiplusShutdown(DAT_004a330c);
      DAT_004a2398 = '\0';
    }
  }
  else if (DAT_004a2398 == '\0') {
    local_2c = 1;
    local_28 = 0;
    local_24 = 0;
    local_20 = 0;
    uVar1 = GdiplusStartup(&DAT_004a330c,&local_2c,0);
    if (uVar1 != 0) {
      return uVar1 & 0xffffff00;
    }
    DAT_004a2398 = '\x01';
    in_EAX = FUN_00411bb0(0x4a28e0);
    if (DAT_004a284d == '\0') {
      FUN_00435260(local_1c,(uint *)&DAT_0048d7dc);
      FUN_0040b4b0(local_1c,DAT_004a29a0);
      uVar2 = FUN_00435170(local_1c);
      return CONCAT31((int3)((uint)uVar2 >> 8),1);
    }
  }
  return CONCAT31((int3)((uint)in_EAX >> 8),1);
}


