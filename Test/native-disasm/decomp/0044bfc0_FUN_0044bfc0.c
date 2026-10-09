// FUN_0044bfc0 @ 0044bfc0 size=85 callers=1

void __fastcall FUN_0044bfc0(int param_1)

{
  byte *pbVar1;
  byte *pbVar2;
  void *this;
  byte *local_c;
  byte *local_8 [2];
  
  pbVar1 = (byte *)(param_1 + 8);
  FUN_00437190(&local_c,pbVar1);
  pbVar2 = local_c;
  if (local_c == DAT_004a27d4) {
    local_c = pbVar1;
    FUN_0044a880(this,(int *)local_8,this,&local_c);
    pbVar2 = local_8[0];
  }
  *(undefined4 *)(pbVar2 + 0xc) = *(undefined4 *)(param_1 + 0xc);
  FUN_004228a0(*(undefined4 *)(param_1 + 0xc),*(undefined4 *)pbVar1,*(uint *)(param_1 + 0x10),
               *(int *)(param_1 + 0x14));
  return;
}


