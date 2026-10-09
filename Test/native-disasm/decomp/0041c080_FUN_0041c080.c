// FUN_0041c080 @ 0041c080 size=176 callers=10

void __thiscall FUN_0041c080(void *this,ushort param_1)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  int local_10;
  undefined4 *local_c;
  
  if ((uint)param_1 < (uint)((*(int *)((int)this + 0x10) - *(int *)((int)this + 0xc)) / 0x14)) {
    iVar3 = (uint)param_1 * 0x14;
    uVar1 = *(uint *)(iVar3 + *(int *)((int)this + 0xc));
    uVar2 = CONCAT11(uVar1 == DAT_004a29c0,(uVar1 != DAT_004a29bc) + -1) & 0xffffff02;
    local_c = (undefined4 *)FUN_00419890(uVar1);
    FUN_00436250(&DAT_004a28e0,&local_10,(byte *)(local_c + 7));
    if (local_10 == DAT_004a28e4) {
                    /* WARNING: Subroutine does not return */
      FUN_00458ee4("invalid unordered_map<K, T> key");
    }
    FUN_0041a7b0(*(undefined4 *)((int)this + 0x2c),(int *)(*(int *)((int)this + 0xc) + 4 + iVar3),
                 (byte *)(local_10 + 0xc),local_c,(byte)uVar2 | (byte)(uVar2 >> 8),'\0','\0');
  }
  return;
}


