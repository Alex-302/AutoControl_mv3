// FUN_0041e6e0 @ 0041e6e0 size=159 callers=1

undefined4 __fastcall FUN_0041e6e0(undefined4 param_1,int *param_2)

{
  undefined *puVar1;
  undefined4 uVar2;
  int iVar3;
  int local_10;
  int local_c [2];
  
  if (*param_2 != 1) {
    return 0;
  }
  puVar1 = FUN_00419890(param_2[2]);
  if (param_2[2] < 0) {
    local_10 = param_2[5];
  }
  else {
    local_10 = *(int *)(puVar1 + 0x1c);
  }
  FUN_00436250(&DAT_004a28e0,local_c,(byte *)&local_10);
  if (local_c[0] != DAT_004a28e4) {
    uVar2 = FUN_0041a4e0((byte *)(local_c[0] + 0xc),puVar1,1,(int *)0x0);
    if ((puVar1[0x26] & 2) == 0) {
      iVar3 = DAT_004a29cc - 3;
    }
    else {
      iVar3 = 0;
    }
    param_2[4] = (int)(short)((uint)uVar2 >> 0x10);
    param_2[3] = (short)uVar2 - iVar3;
    return 1;
  }
                    /* WARNING: Subroutine does not return */
  FUN_00458ee4("invalid unordered_map<K, T> key");
}


