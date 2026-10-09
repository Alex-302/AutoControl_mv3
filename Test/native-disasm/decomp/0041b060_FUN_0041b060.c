// FUN_0041b060 @ 0041b060 size=353 callers=1

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

bool __fastcall FUN_0041b060(undefined4 *param_1,ushort param_2)

{
  float fVar1;
  int iVar2;
  float local_28;
  float local_24;
  tagRECT local_20;
  
  local_28 = (float)param_1[7];
  FUN_00436250(&DAT_004a28e0,(int *)&local_24,(byte *)&local_28);
  if (local_24 == DAT_004a28e4) {
                    /* WARNING: Subroutine does not return */
    FUN_00458ee4("invalid unordered_map<K, T> key");
  }
  FUN_00436020(&DAT_004a296c,(int *)&local_24,(byte *)((int)local_24 + 0xc));
  fVar1 = local_24;
  if (local_24 != DAT_004a2970) {
    local_24 = (float)DAT_004a29c8 * _DAT_0048f218;
    iVar2 = FUN_0040b4b0(param_1,DAT_004a29a0);
    local_28 = (float)(int)*(short *)((int)fVar1 + 0x34) * local_24 + (float)iVar2 +
               (float)DAT_004a29c8;
    if ((*(byte *)((int)param_1 + 0x26) & 2) != 0) {
      local_28 = (float)DAT_004a29ce + local_28;
    }
    local_24 = (float)((int)*(short *)((int)fVar1 + 0x30) + (int)*(short *)((int)fVar1 + 0x2e) +
                      (int)*(short *)((int)fVar1 + 0x2c)) * (float)DAT_004a29c8 * _DAT_0048f218;
    local_20.left = 0;
    local_20.top = 0;
    local_20.right = 0;
    local_20.bottom = 0;
    GetMenuItemRect((HWND)0x0,(HMENU)param_1[7],(uint)param_2,&local_20);
    return (float)(local_20.right - local_20.left) < local_24 + local_24 + local_28;
  }
                    /* WARNING: Subroutine does not return */
  FUN_00458ee4("invalid unordered_map<K, T> key");
}


