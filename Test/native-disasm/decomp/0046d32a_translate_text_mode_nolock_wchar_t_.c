// translate_text_mode_nolock<wchar_t> @ 0046d32a size=448 callers=1

/* Library Function - Single Match
    int __cdecl translate_text_mode_nolock<wchar_t>(int,wchar_t * const,unsigned int)
   
   Library: Visual Studio 2015 Release */

int __cdecl translate_text_mode_nolock<wchar_t>(int param_1,wchar_t *param_2,uint param_3)

{
  byte *pbVar1;
  byte bVar2;
  wchar_t wVar3;
  int iVar4;
  BOOL BVar5;
  wchar_t *pwVar6;
  wchar_t *pwVar7;
  wchar_t *pwVar8;
  int unaff_EDI;
  int iVar9;
  DWORD local_1c;
  HANDLE local_18;
  wchar_t *local_14;
  wchar_t *local_10;
  int local_c;
  short local_8 [2];
  
  local_c = param_1 >> 6;
  iVar9 = (param_1 & 0x3fU) * 0x30;
  iVar4 = (&DAT_0049f8f8)[local_c];
  local_18 = *(HANDLE *)(iVar4 + 0x18 + iVar9);
  if ((param_3 == 0) || (*param_2 != L'\n')) {
    pbVar1 = (byte *)(iVar4 + 0x28 + iVar9);
    *pbVar1 = *pbVar1 & 0xfb;
  }
  else {
    pbVar1 = (byte *)(iVar4 + 0x28 + iVar9);
    *pbVar1 = *pbVar1 | 4;
  }
  local_14 = param_2 + param_3;
  pwVar8 = param_2;
  if (param_2 < local_14) {
    local_10 = param_2 + 1;
    pwVar6 = param_2;
    do {
      wVar3 = *pwVar6;
      if (wVar3 == L'\x1a') {
        bVar2 = *(byte *)((&DAT_0049f8f8)[local_c] + 0x28 + iVar9);
        if ((bVar2 & 0x40) == 0) {
          *(byte *)((&DAT_0049f8f8)[local_c] + 0x28 + iVar9) = bVar2 | 2;
        }
        else {
          *pwVar8 = *pwVar6;
          pwVar8 = pwVar8 + 1;
        }
        break;
      }
      if (wVar3 == L'\r') {
        if (local_10 < local_14) {
          if (*local_10 == L'\n') {
            pwVar7 = pwVar6 + 2;
            *pwVar8 = L'\n';
            local_10 = local_10 + 2;
            pwVar8 = pwVar8 + 1;
            goto LAB_0046d4b1;
          }
          *pwVar8 = L'\r';
          pwVar8 = pwVar8 + 1;
          local_10 = local_10 + 1;
        }
        else {
          local_10 = local_10 + 1;
          pwVar7 = pwVar6 + 1;
          BVar5 = ReadFile(local_18,local_8,2,&local_1c,(LPOVERLAPPED)0x0);
          if ((BVar5 == 0) || (local_1c == 0)) {
LAB_0046d4a2:
            *pwVar8 = L'\r';
            pwVar8 = pwVar8 + 1;
          }
          else if ((*(byte *)((&DAT_0049f8f8)[local_c] + 0x28 + iVar9) & 0x48) == 0) {
            if ((local_8[0] == 10) && (pwVar8 == param_2)) {
              *pwVar8 = L'\n';
              pwVar8 = pwVar8 + 1;
              goto LAB_0046d4b1;
            }
            __lseeki64_nolock(param_1,0x1ffffffff,unaff_EDI);
            if (local_8[0] != 10) goto LAB_0046d4a2;
          }
          else if (local_8[0] == 10) {
            *pwVar8 = L'\n';
          }
          else {
            *pwVar8 = L'\r';
            *(char *)((&DAT_0049f8f8)[local_c] + 0x2a + iVar9) = (char)local_8[0];
            *(char *)((&DAT_0049f8f8)[local_c] + 0x2b + iVar9) = (char)((ushort)local_8[0] >> 8);
            *(undefined1 *)((&DAT_0049f8f8)[local_c] + 0x2c + iVar9) = 10;
          }
        }
        pwVar7 = pwVar6 + 1;
      }
      else {
        pwVar7 = pwVar6 + 1;
        *pwVar8 = wVar3;
        pwVar8 = pwVar8 + 1;
        local_10 = local_10 + 1;
      }
LAB_0046d4b1:
      pwVar6 = pwVar7;
    } while (pwVar7 < local_14);
  }
  return (int)pwVar8 - (int)param_2 & 0xfffffffe;
}


