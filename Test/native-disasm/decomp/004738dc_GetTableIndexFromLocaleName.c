// GetTableIndexFromLocaleName @ 004738dc size=188 callers=1

/* Library Function - Single Match
    int __cdecl GetTableIndexFromLocaleName(wchar_t const *)
   
   Library: Visual Studio 2015 Release */

int __cdecl GetTableIndexFromLocaleName(wchar_t *param_1)

{
  ushort uVar1;
  int iVar2;
  int iVar3;
  ushort uVar4;
  ushort *puVar5;
  int local_10;
  int local_c;
  int local_8;
  
  local_10 = 0;
  local_c = 0xe3;
  while( true ) {
    local_8 = 0x55;
    iVar2 = (local_c + local_10) / 2;
    puVar5 = (ushort *)(&PTR_DAT_00488148)[iVar2 * 2];
    iVar3 = (int)param_1 - (int)puVar5;
    do {
      uVar4 = *(ushort *)(iVar3 + (int)puVar5);
      if ((0x40 < uVar4) && (uVar4 < 0x5b)) {
        uVar4 = uVar4 + 0x20;
      }
      uVar1 = *puVar5;
      if ((0x40 < uVar1) && (uVar1 < 0x5b)) {
        uVar1 = uVar1 + 0x20;
      }
      puVar5 = puVar5 + 1;
      local_8 = local_8 + -1;
    } while (((local_8 != 0) && (uVar4 != 0)) && (uVar4 == uVar1));
    if ((uint)uVar4 == (uint)uVar1) break;
    if ((int)((uint)uVar4 - (uint)uVar1) < 0) {
      local_c = iVar2 + -1;
    }
    else {
      local_10 = iVar2 + 1;
    }
    if (local_c < local_10) {
      return -1;
    }
  }
  return *(int *)(&DAT_0048814c + iVar2 * 8);
}


