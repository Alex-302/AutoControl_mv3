// __read_nolock @ 0046d7ce size=949 callers=2

/* Library Function - Single Match
    __read_nolock
   
   Library: Visual Studio 2015 Release */

int __cdecl __read_nolock(int _FileHandle,void *_DstBuf,uint _MaxCharCount)

{
  uint uVar1;
  ulong *puVar2;
  int *piVar3;
  wchar_t *pwVar4;
  int iVar5;
  BOOL BVar6;
  ulong uVar7;
  size_t sVar8;
  int unaff_ESI;
  wchar_t *_Memory;
  int iVar9;
  uint uVar10;
  longlong lVar11;
  DWORD local_2c;
  wchar_t *local_28;
  uint local_24;
  HANDLE local_20;
  int local_1c;
  uint local_18;
  int local_14;
  size_t local_10;
  wchar_t *local_c;
  char local_6;
  byte local_5;
  
  if (_FileHandle == -2) {
    puVar2 = ___doserrno();
    *puVar2 = 0;
    piVar3 = __errno();
    *piVar3 = 9;
    return -1;
  }
  if ((-1 < _FileHandle) && ((uint)_FileHandle < DAT_0049faf8)) {
    local_18 = 1;
    iVar9 = _FileHandle >> 6;
    local_1c = (_FileHandle & 0x3fU) * 0x30;
    iVar5 = (&DAT_0049f8f8)[iVar9];
    local_5 = *(byte *)(local_1c + 0x28 + iVar5);
    local_14 = iVar9;
    if ((local_5 & 1) != 0) {
      if (_MaxCharCount < 0x80000000) {
        if ((_MaxCharCount == 0) || ((local_5 & 2) != 0)) {
          return 0;
        }
        if (_DstBuf != (void *)0x0) {
          local_20 = *(HANDLE *)(local_1c + 0x18 + iVar5);
          local_5 = *(char *)(local_1c + 0x29 + iVar5);
          if (local_5 == '\x01') {
            if ((~(byte)_MaxCharCount & 1) == 0) goto LAB_0046d8b7;
            local_10 = 4;
            if (3 < _MaxCharCount >> 1) {
              local_10 = _MaxCharCount >> 1;
            }
            pwVar4 = __malloc_base(local_10);
            FID_conflict__free((void *)0x0);
            FID_conflict__free((void *)0x0);
            local_c = pwVar4;
            if (pwVar4 != (wchar_t *)0x0) {
              lVar11 = __lseeki64_nolock(_FileHandle,(ulonglong)local_18 << 0x20,unaff_ESI);
              iVar5 = (&DAT_0049f8f8)[iVar9];
              *(int *)(local_1c + 0x20 + iVar5) = (int)lVar11;
              *(int *)(local_1c + 0x24 + iVar5) = (int)((ulonglong)lVar11 >> 0x20);
              _Memory = pwVar4;
              goto LAB_0046d948;
            }
            piVar3 = __errno();
            *piVar3 = 0xc;
            puVar2 = ___doserrno();
            *puVar2 = 8;
          }
          else if ((local_5 == '\x02') && ((~_MaxCharCount & 1) == 0)) {
LAB_0046d8b7:
            puVar2 = ___doserrno();
            *puVar2 = 0;
            piVar3 = __errno();
            *piVar3 = 0x16;
            FUN_00465fa2();
            pwVar4 = (wchar_t *)0x0;
          }
          else {
            local_10 = _MaxCharCount;
            local_c = _DstBuf;
            pwVar4 = _DstBuf;
            _Memory = (wchar_t *)0x0;
LAB_0046d948:
            uVar10 = 0;
            local_24 = (&DAT_0049f8f8)[local_14];
            sVar8 = local_10;
            if ((((*(byte *)(local_1c + 0x28 + local_24) & 0x48) != 0) &&
                (local_6 = *(char *)(local_1c + 0x2a + local_24), local_6 != '\n')) &&
               (local_10 != 0)) {
              *(char *)pwVar4 = local_6;
              local_c = (wchar_t *)((int)pwVar4 + 1);
              sVar8 = local_10 - 1;
              *(undefined1 *)(local_1c + 0x2a + (&DAT_0049f8f8)[local_14]) = 10;
              uVar10 = local_18;
              if (((local_5 != '\0') &&
                  (local_6 = *(char *)(local_1c + 0x2b + (&DAT_0049f8f8)[local_14]), local_6 != '\n'
                  )) && (sVar8 != 0)) {
                uVar10 = 2;
                *(char *)local_c = local_6;
                local_c = pwVar4 + 1;
                sVar8 = local_10 - 2;
                *(undefined1 *)(local_1c + 0x2b + (&DAT_0049f8f8)[local_14]) = 10;
                if (((local_5 == (char)local_18) &&
                    (local_6 = *(char *)(local_1c + 0x2c + (&DAT_0049f8f8)[local_14]),
                    local_6 != '\n')) && (sVar8 != 0)) {
                  uVar10 = 3;
                  *(char *)local_c = local_6;
                  local_c = (wchar_t *)((int)pwVar4 + 3);
                  *(undefined1 *)(local_1c + 0x2c + (&DAT_0049f8f8)[local_14]) = 10;
                  sVar8 = local_10 - 3;
                }
              }
            }
            local_10 = sVar8;
            local_28 = pwVar4;
            iVar5 = __isatty(_FileHandle);
            pwVar4 = _Memory;
            if (((iVar5 == 0) ||
                ((*(byte *)(local_1c + 0x28 + (&DAT_0049f8f8)[local_14]) & 0x80) == 0)) ||
               (BVar6 = GetConsoleMode(local_20,&local_2c), BVar6 == 0)) {
              local_18 = local_18 & 0xffffff00;
LAB_0046dab6:
              BVar6 = ReadFile(local_20,local_c,local_10,&local_24,(LPOVERLAPPED)0x0);
              if ((BVar6 != 0) && (uVar1 = local_24, local_24 <= _MaxCharCount)) {
LAB_0046dadb:
                uVar10 = uVar10 + uVar1;
                if ((*(byte *)(local_1c + 0x28 + (&DAT_0049f8f8)[local_14]) & 0x80) != 0) {
                  if (local_5 == '\x02') {
                    if ((char)local_18 == '\0') {
                      uVar10 = translate_text_mode_nolock<wchar_t>(_FileHandle,local_28,uVar10 >> 1)
                      ;
                    }
                    else {
                      uVar10 = translate_utf16_from_console_nolock(_FileHandle,local_28,uVar10 >> 1)
                      ;
                    }
                  }
                  else {
                    uVar10 = translate_ansi_or_utf8_nolock
                                       (_FileHandle,(char *)local_c,uVar10,_DstBuf,
                                        _MaxCharCount >> 1);
                  }
                }
                goto LAB_0046da98;
              }
              uVar7 = GetLastError();
              if (uVar7 != 5) {
                if (uVar7 == 0x6d) {
                  uVar10 = 0;
                  goto LAB_0046da98;
                }
                goto LAB_0046da8e;
              }
              piVar3 = __errno();
              *piVar3 = 9;
              puVar2 = ___doserrno();
              *puVar2 = 5;
            }
            else {
              if (local_5 != '\x02') goto LAB_0046dab6;
              BVar6 = ReadConsoleW(local_20,local_c,local_10 >> 1,&local_24,
                                   (PCONSOLE_READCONSOLE_CONTROL)0x0);
              if (BVar6 != 0) {
                uVar1 = local_24 * 2;
                goto LAB_0046dadb;
              }
              uVar7 = GetLastError();
LAB_0046da8e:
              ___acrt_errno_map_os_error(uVar7);
            }
          }
          uVar10 = 0xffffffff;
          _Memory = pwVar4;
LAB_0046da98:
          FID_conflict__free(_Memory);
          return uVar10;
        }
      }
      puVar2 = ___doserrno();
      *puVar2 = 0;
      piVar3 = __errno();
      *piVar3 = 0x16;
      goto LAB_0046db75;
    }
  }
  puVar2 = ___doserrno();
  *puVar2 = 0;
  piVar3 = __errno();
  *piVar3 = 9;
LAB_0046db75:
  FUN_00465fa2();
  return -1;
}


