// FUN_00429c50 @ 00429c50 size=125 callers=1

void __fastcall FUN_00429c50(int *param_1)

{
  byte *pbVar1;
  void *this;
  byte *local_10;
  byte *local_c;
  byte *local_8 [2];
  
  if (*param_1 == 0) {
    FUN_00437090(&local_10,(byte *)(param_1 + 1));
    for (pbVar1 = local_10; pbVar1 != local_c; pbVar1 = *(byte **)pbVar1) {
    }
    FUN_00437230((int *)&local_10,(int *)local_10,(int *)local_c);
    return;
  }
  FUN_00437190(&local_10,(byte *)(param_1 + 1));
  if (local_10 == DAT_004a27d4) {
    local_10 = (byte *)(param_1 + 1);
    FUN_0044a880(this,(int *)local_8,this,&local_10);
    local_10 = local_8[0];
  }
  *(int *)(local_10 + 0xc) = *param_1;
  return;
}


