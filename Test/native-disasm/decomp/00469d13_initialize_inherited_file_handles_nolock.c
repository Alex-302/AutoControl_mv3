// initialize_inherited_file_handles_nolock @ 00469d13 size=182 callers=1

/* Library Function - Single Match
    void __cdecl initialize_inherited_file_handles_nolock(void)
   
   Library: Visual Studio 2015 Release */

void __cdecl initialize_inherited_file_handles_nolock(void)

{
  HANDLE hFile;
  DWORD DVar1;
  int iVar2;
  uint *puVar3;
  uint uVar4;
  uint uVar5;
  _STARTUPINFOW local_4c;
  byte *local_8;
  
  GetStartupInfoW(&local_4c);
  if ((local_4c.cbReserved2 != 0) && ((uint *)local_4c.lpReserved2 != (uint *)0x0)) {
    uVar4 = *(uint *)local_4c.lpReserved2;
    puVar3 = (uint *)((int)local_4c.lpReserved2 + 4);
    local_8 = (byte *)((int)puVar3 + uVar4);
    if (0x1fff < (int)uVar4) {
      uVar4 = 0x2000;
    }
    ___acrt_lowio_ensure_fh_exists(uVar4);
    if ((int)DAT_0049faf8 < (int)uVar4) {
      uVar4 = DAT_0049faf8;
    }
    uVar5 = 0;
    if (uVar4 != 0) {
      do {
        hFile = *(HANDLE *)local_8;
        if ((((hFile != (HANDLE)0xffffffff) && (hFile != (HANDLE)0xfffffffe)) &&
            ((*puVar3 & 1) != 0)) &&
           (((*puVar3 & 8) != 0 || (DVar1 = GetFileType(hFile), DVar1 != 0)))) {
          iVar2 = (uVar5 & 0x3f) * 0x30 + (&DAT_0049f8f8)[(int)uVar5 >> 6];
          *(undefined4 *)(iVar2 + 0x18) = *(undefined4 *)local_8;
          *(byte *)(iVar2 + 0x28) = (byte)*puVar3;
        }
        uVar5 = uVar5 + 1;
        local_8 = local_8 + 4;
        puVar3 = (uint *)((int)puVar3 + 1);
      } while (uVar5 != uVar4);
    }
  }
  return;
}


