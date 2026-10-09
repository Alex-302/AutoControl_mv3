// translate_ansi_or_utf8_nolock @ 0046d4ea size=336 callers=1

/* Library Function - Single Match
    int __cdecl translate_ansi_or_utf8_nolock(int,char * const,unsigned int,wchar_t * const,unsigned
   int)
   
   Library: Visual Studio 2015 Release */

int __cdecl
translate_ansi_or_utf8_nolock(int param_1,char *param_2,uint param_3,wchar_t *param_4,uint param_5)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  DWORD DVar5;
  int iVar6;
  uint uVar7;
  int unaff_ESI;
  byte *pbVar8;
  byte *pbVar9;
  int iVar10;
  
  iVar3 = translate_text_mode_nolock<char>(param_1,param_2,param_3);
  if (iVar3 == 0) {
    return 0;
  }
  iVar6 = param_1 >> 6;
  iVar10 = (param_1 & 0x3fU) * 0x30;
  iVar2 = (&DAT_0049f8f8)[iVar6];
  if (*(char *)(iVar2 + 0x29 + iVar10) != '\0') {
    pbVar8 = (byte *)(param_2 + iVar3 + -1);
    bVar1 = *pbVar8;
    if ((char)bVar1 < '\0') {
      uVar7 = 1;
      while ((((&DAT_0049d2f8)[bVar1] == '\0' && (uVar7 < 5)) && (param_2 <= pbVar8))) {
        pbVar8 = pbVar8 + -1;
        uVar7 = uVar7 + 1;
        bVar1 = *pbVar8;
      }
      if ((char)(&DAT_0049d2f8)[*pbVar8] == 0) {
        piVar4 = __errno();
        *piVar4 = 0x2a;
        return -1;
      }
      if ((int)(char)(&DAT_0049d2f8)[*pbVar8] + 1U == uVar7) {
        pbVar8 = pbVar8 + uVar7;
      }
      else if ((*(byte *)(iVar2 + 0x28 + iVar10) & 0x48) == 0) {
        __lseeki64_nolock(param_1,CONCAT44(1,(int)-uVar7 >> 0x1f),unaff_ESI);
      }
      else {
        pbVar9 = pbVar8 + 1;
        *(byte *)(iVar2 + 0x2a + iVar10) = *pbVar8;
        if (1 < uVar7) {
          bVar1 = *pbVar9;
          pbVar9 = pbVar8 + 2;
          *(byte *)((&DAT_0049f8f8)[iVar6] + 0x2b + iVar10) = bVar1;
        }
        if (uVar7 == 3) {
          bVar1 = *pbVar9;
          pbVar9 = pbVar9 + 1;
          *(byte *)((&DAT_0049f8f8)[iVar6] + 0x2c + iVar10) = bVar1;
        }
        pbVar8 = pbVar9 + -uVar7;
      }
    }
    else {
      pbVar8 = pbVar8 + 1;
    }
    iVar3 = MultiByteToWideChar(0xfde9,0,param_2,(int)pbVar8 - (int)param_2,param_4,param_5);
    if (iVar3 == 0) {
      DVar5 = GetLastError();
      ___acrt_errno_map_os_error(DVar5);
      return -1;
    }
    pbVar9 = (byte *)((&DAT_0049f8f8)[iVar6] + 0x2d + iVar10);
    *pbVar9 = *pbVar9 ^ ((iVar3 != (int)pbVar8 - (int)param_2) * '\x02' ^
                        *(byte *)((&DAT_0049f8f8)[iVar6] + 0x2d + iVar10)) & 2;
    return iVar3 * 2;
  }
  return iVar3;
}


