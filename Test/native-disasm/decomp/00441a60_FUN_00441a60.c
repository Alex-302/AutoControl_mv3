// FUN_00441a60 @ 00441a60 size=197 callers=7

ushort __thiscall FUN_00441a60(void *this,undefined4 *param_1,ushort param_2)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  char *pcVar3;
  ushort local_34 [2];
  undefined4 local_30;
  undefined4 local_2c;
  void *local_20 [4];
  undefined4 local_10;
  uint local_c;
  
  if (*(char *)this == '\x01') {
    local_c = 0xf;
    local_10 = 0;
    local_20[0] = (void *)((uint)local_20[0] & 0xffffff00);
    FUN_0043ade0(local_20,param_1,0,0xffffffff);
    FUN_004340a0(this,&local_30);
    if (*(char *)this == '\x01') {
      puVar1 = (undefined4 *)
               FUN_00432d50(*(void **)((int)this + 8),(int *)local_34,(byte *)local_20);
      local_2c = *puVar1;
    }
    if (0xf < local_c) {
      FUN_00402430(local_20[0],local_c + 1,1);
    }
    FUN_004340a0(this,local_20);
    uVar2 = FUN_004383a0(&local_30,(int *)local_20);
    if ((char)uVar2 == '\0') {
      pcVar3 = FUN_00433bc0(&local_30);
      FUN_00453970(pcVar3,local_34);
      return local_34[0];
    }
  }
  return param_2;
}


