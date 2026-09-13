// FUN_0044d7d0 @ 0044d7d0 size=89 callers=9

undefined1 __thiscall FUN_0044d7d0(void *this,undefined1 param_1)

{
  undefined4 ****ppppuVar1;
  undefined1 uVar2;
  undefined4 ***local_20 [4];
  int local_10;
  uint local_c;
  
  FUN_0044da90(*(void **)this,local_20,&param_1,&stack0x00000005);
  uVar2 = param_1;
  if (local_10 == 1) {
    ppppuVar1 = local_20;
    if (0xf < local_c) {
      ppppuVar1 = (undefined4 ****)local_20[0];
    }
    uVar2 = *(undefined1 *)ppppuVar1;
  }
  if (0xf < local_c) {
    FUN_00402430(local_20[0],local_c + 1,1);
  }
  return uVar2;
}


