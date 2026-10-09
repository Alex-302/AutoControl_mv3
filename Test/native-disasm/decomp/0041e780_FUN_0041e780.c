// FUN_0041e780 @ 0041e780 size=139 callers=1

byte __fastcall
FUN_0041e780(uint param_1,uint param_2,undefined4 param_3,undefined4 param_4,int *param_5,
            char param_6)

{
  undefined4 *puVar1;
  bool bVar2;
  undefined4 local_10;
  int local_c [2];
  
  bVar2 = param_1 != DAT_004a29bc;
  puVar1 = (undefined4 *)FUN_00419890(param_1);
  local_10 = param_3;
  FUN_00436250(&DAT_004a28e0,local_c,(byte *)&local_10);
  if (local_c[0] != DAT_004a28e4) {
    FUN_0041a7b0(param_4,param_5,(byte *)(local_c[0] + 0xc),puVar1,
                 (byte)(param_2 >> 7) & 1 | bVar2 - 1U & 2,param_6,'\x01');
    return *(byte *)((int)puVar1 + 0x26) >> 1 & 1;
  }
                    /* WARNING: Subroutine does not return */
  FUN_00458ee4("invalid unordered_map<K, T> key");
}


