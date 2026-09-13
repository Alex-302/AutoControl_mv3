// __write_nolock @ 0046b56e size=524 callers=1

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* Library Function - Single Match
    __write_nolock
   
   Library: Visual Studio 2015 Release */

int __cdecl __write_nolock(int _FileHandle,void *_Buf,uint _MaxCharCount)

{
  ulong uVar1;
  char cVar2;
  bool bVar3;
  ulong *puVar4;
  int *piVar5;
  BOOL BVar6;
  int iVar7;
  int unaff_EBX;
  int iVar8;
  ulong local_18;
  DWORD local_14 [2];
  uint local_c;
  uint local_8;
  
  local_8 = DAT_0049d070 ^ (uint)&stack0xfffffffc;
  local_c = _MaxCharCount;
  if (_MaxCharCount == 0) {
    return 0;
  }
  if (_Buf == (void *)0x0) {
    puVar4 = ___doserrno();
    *puVar4 = 0;
    piVar5 = __errno();
    *piVar5 = 0x16;
    FUN_00465fa2();
    return -1;
  }
  iVar8 = _FileHandle >> 6;
  iVar7 = (_FileHandle & 0x3fU) * 0x30;
  cVar2 = *(char *)((&DAT_0049f8f8)[iVar8] + 0x29 + iVar7);
  if (((cVar2 == '\x02') || (cVar2 == '\x01')) && ((~_MaxCharCount & 1) == 0)) {
    puVar4 = ___doserrno();
    *puVar4 = 0;
    piVar5 = __errno();
    *piVar5 = 0x16;
    FUN_00465fa2();
    return -1;
  }
  if ((*(byte *)((&DAT_0049f8f8)[iVar8] + 0x28 + iVar7) & 0x20) != 0) {
    __lseeki64_nolock(_FileHandle,0x200000000,unaff_EBX);
  }
  bVar3 = write_requires_double_translation_nolock(_FileHandle);
  if (bVar3) {
    if (cVar2 == '\0') {
      puVar4 = (ulong *)write_double_translated_ansi_nolock
                                  ((int)&local_18,(char *)_FileHandle,(uint)_Buf);
    }
    else {
      if (1 < (byte)(cVar2 - 1U)) goto LAB_0046b731;
      puVar4 = (ulong *)write_double_translated_unicode_nolock((char *)&local_18,(uint)_Buf);
    }
  }
  else if ((*(byte *)((&DAT_0049f8f8)[iVar8] + 0x28 + iVar7) & 0x80) == 0) {
    local_18 = 0;
    local_14[0] = 0;
    local_14[1] = 0;
    BVar6 = WriteFile(*(HANDLE *)((&DAT_0049f8f8)[iVar8] + 0x18 + iVar7),_Buf,local_c,local_14,
                      (LPOVERLAPPED)0x0);
    if (BVar6 == 0) {
      local_18 = GetLastError();
    }
    puVar4 = &local_18;
  }
  else if (cVar2 == '\0') {
    puVar4 = (ulong *)write_text_ansi_nolock((int)&local_18,(char *)_FileHandle,(uint)_Buf);
  }
  else if (cVar2 == '\x01') {
    puVar4 = (ulong *)write_text_utf8_nolock((int)&local_18,(char *)_FileHandle,(uint)_Buf);
  }
  else {
    if (cVar2 != '\x02') goto LAB_0046b731;
    puVar4 = (ulong *)write_text_utf16le_nolock((int)&local_18,(char *)_FileHandle,(uint)_Buf);
  }
  uVar1 = *puVar4;
  if (puVar4[1] != 0) {
    return puVar4[1] - puVar4[2];
  }
  if (uVar1 != 0) {
    if (uVar1 == 5) {
      piVar5 = __errno();
      *piVar5 = 9;
      puVar4 = ___doserrno();
      *puVar4 = 5;
      return -1;
    }
    ___acrt_errno_map_os_error(uVar1);
    return -1;
  }
LAB_0046b731:
  if (((*(byte *)((&DAT_0049f8f8)[iVar8] + 0x28 + iVar7) & 0x40) != 0) && (*(char *)_Buf == '\x1a'))
  {
    return 0;
  }
  piVar5 = __errno();
  *piVar5 = 0x1c;
  puVar4 = ___doserrno();
  *puVar4 = 0;
  return -1;
}


