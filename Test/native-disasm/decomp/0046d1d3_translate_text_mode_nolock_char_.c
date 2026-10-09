// translate_text_mode_nolock<char> @ 0046d1d3 size=343 callers=1

/* Library Function - Single Match
    int __cdecl translate_text_mode_nolock<char>(int,char * const,unsigned int)
   
   Library: Visual Studio 2015 Release */

int __cdecl translate_text_mode_nolock<char>(int param_1,char *param_2,uint param_3)

{
  byte *pbVar1;
  char cVar2;
  byte bVar3;
  int iVar4;
  BOOL BVar5;
  char *pcVar6;
  char *pcVar7;
  int unaff_EDI;
  int iVar8;
  DWORD local_1c;
  HANDLE local_18;
  int local_14;
  char *local_10;
  char *local_c;
  char local_5;
  
  local_14 = param_1 >> 6;
  iVar8 = (param_1 & 0x3fU) * 0x30;
  iVar4 = (&DAT_0049f8f8)[local_14];
  local_18 = *(HANDLE *)(iVar4 + 0x18 + iVar8);
  if ((param_3 == 0) || (*param_2 != '\n')) {
    pbVar1 = (byte *)(iVar4 + 0x28 + iVar8);
    *pbVar1 = *pbVar1 & 0xfb;
  }
  else {
    pbVar1 = (byte *)(iVar4 + 0x28 + iVar8);
    *pbVar1 = *pbVar1 | 4;
  }
  local_c = param_2 + param_3;
  pcVar7 = param_2;
  if (param_2 < local_c) {
    local_10 = param_2 + 1;
    pcVar6 = param_2;
    do {
      cVar2 = *pcVar6;
      if (cVar2 == '\x1a') {
        bVar3 = *(byte *)((&DAT_0049f8f8)[local_14] + 0x28 + iVar8);
        if ((bVar3 & 0x40) == 0) {
          *(byte *)((&DAT_0049f8f8)[local_14] + 0x28 + iVar8) = bVar3 | 2;
        }
        else {
          *pcVar7 = *pcVar6;
          pcVar7 = pcVar7 + 1;
        }
        break;
      }
      if (cVar2 == '\r') {
        if (local_c <= local_10) {
          local_10 = local_10 + 1;
          BVar5 = ReadFile(local_18,&local_5,1,&local_1c,(LPOVERLAPPED)0x0);
          if ((BVar5 == 0) || (local_1c == 0)) {
LAB_0046d2e9:
            *pcVar7 = '\r';
            pcVar7 = pcVar7 + 1;
          }
          else if ((*(byte *)((&DAT_0049f8f8)[local_14] + 0x28 + iVar8) & 0x48) == 0) {
            if ((local_5 == '\n') && (pcVar7 == param_2)) {
              *pcVar7 = '\n';
              pcVar7 = pcVar7 + 1;
            }
            else {
              __lseeki64_nolock(param_1,0x1ffffffff,unaff_EDI);
              if (local_5 != '\n') goto LAB_0046d2e9;
            }
          }
          else if (local_5 == '\n') {
            *pcVar7 = '\n';
          }
          else {
            *pcVar7 = '\r';
            *(char *)((&DAT_0049f8f8)[local_14] + 0x2a + iVar8) = local_5;
          }
          goto LAB_0046d2f3;
        }
        if (*local_10 == '\n') {
          pcVar6 = pcVar6 + 2;
          *pcVar7 = '\n';
          local_10 = local_10 + 2;
          pcVar7 = pcVar7 + 1;
        }
        else {
          *pcVar7 = '\r';
          pcVar7 = pcVar7 + 1;
          pcVar6 = pcVar6 + 1;
          local_10 = local_10 + 1;
        }
      }
      else {
        *pcVar7 = cVar2;
        pcVar7 = pcVar7 + 1;
        local_10 = local_10 + 1;
LAB_0046d2f3:
        pcVar6 = pcVar6 + 1;
      }
    } while (pcVar6 < local_c);
  }
  return (int)pcVar7 - (int)param_2;
}


