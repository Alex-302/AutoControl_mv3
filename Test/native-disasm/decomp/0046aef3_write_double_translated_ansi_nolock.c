// write_double_translated_ansi_nolock @ 0046aef3 size=435 callers=1

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* Library Function - Single Match
    struct `anonymous namespace'::write_result __cdecl write_double_translated_ansi_nolock(int,char
   const * const,unsigned int)
   
   Library: Visual Studio 2015 Release */

int __cdecl write_double_translated_ansi_nolock(int param_1,char *param_2,uint param_3)

{
  byte bVar1;
  HANDLE hFile;
  UINT CodePage;
  ushort *puVar2;
  int iVar3;
  uint uVar4;
  BOOL BVar5;
  DWORD DVar6;
  int iVar7;
  int iVar8;
  byte *pbVar9;
  int in_stack_00000010;
  byte *_SrcCh;
  size_t _SrcSizeInBytes;
  uint local_24;
  undefined2 local_20;
  wchar_t local_1c [2];
  CHAR local_18 [8];
  byte local_10;
  undefined1 local_f;
  uint local_8;
  
  local_8 = DAT_0049d070 ^ (uint)&stack0xfffffffc;
  iVar7 = (int)param_2 >> 6;
  iVar8 = ((uint)param_2 & 0x3f) * 0x30;
  hFile = *(HANDLE *)((&DAT_0049f8f8)[iVar7] + 0x18 + iVar8);
  CodePage = GetConsoleCP();
  *(undefined4 *)param_1 = 0;
  *(undefined4 *)(param_1 + 4) = 0;
  *(undefined4 *)(param_1 + 8) = 0;
  pbVar9 = (byte *)param_3;
  do {
    do {
      if ((byte *)(in_stack_00000010 + param_3) <= pbVar9) {
        return param_1;
      }
      local_1c[0] = L'\0';
      local_20 = CONCAT11(*pbVar9,(undefined1)local_20);
      iVar3 = (&DAT_0049f8f8)[iVar7];
      bVar1 = *(byte *)(iVar3 + 0x2d + iVar8);
      if ((bVar1 & 4) == 0) {
        puVar2 = ___pctype_func();
        if ((puVar2[*pbVar9] & 0x8000) == 0) {
          _SrcSizeInBytes = 1;
          _SrcCh = pbVar9;
          goto LAB_0046afc7;
        }
        if ((byte *)(in_stack_00000010 + param_3) <= pbVar9) {
          *(byte *)((&DAT_0049f8f8)[iVar7] + 0x2e + iVar8) = *pbVar9;
          pbVar9 = (byte *)((&DAT_0049f8f8)[iVar7] + 0x2d + iVar8);
          *pbVar9 = *pbVar9 | 4;
          *(int *)(param_1 + 4) = *(int *)(param_1 + 4) + 1;
          return param_1;
        }
        iVar3 = _mbtowc(local_1c,(char *)pbVar9,2);
        if (iVar3 == -1) {
          return param_1;
        }
        pbVar9 = pbVar9 + 1;
      }
      else {
        local_10 = *(byte *)(iVar3 + 0x2e + iVar8);
        uVar4 = CONCAT11(*pbVar9,bVar1) & 0xfffffffb;
        _SrcSizeInBytes = 2;
        local_f = (undefined1)(uVar4 >> 8);
        *(char *)(iVar3 + 0x2d + iVar8) = (char)uVar4;
        _SrcCh = &local_10;
LAB_0046afc7:
        iVar3 = _mbtowc(local_1c,(char *)_SrcCh,_SrcSizeInBytes);
        if (iVar3 == -1) {
          return param_1;
        }
      }
      pbVar9 = pbVar9 + 1;
      uVar4 = WideCharToMultiByte(CodePage,0,local_1c,1,local_18,5,(LPCSTR)0x0,(LPBOOL)0x0);
      if (uVar4 == 0) {
        return param_1;
      }
      BVar5 = WriteFile(hFile,local_18,uVar4,&local_24,(LPOVERLAPPED)0x0);
      if (BVar5 == 0) goto LAB_0046b08b;
      *(byte **)(param_1 + 4) = pbVar9 + (*(int *)(param_1 + 8) - param_3);
      if (local_24 < uVar4) {
        return param_1;
      }
    } while (local_20._1_1_ != '\n');
    local_20 = 0xd;
    BVar5 = WriteFile(hFile,&local_20,1,&local_24,(LPOVERLAPPED)0x0);
    if (BVar5 == 0) {
LAB_0046b08b:
      DVar6 = GetLastError();
      *(DWORD *)param_1 = DVar6;
      return param_1;
    }
    if (local_24 == 0) {
      return param_1;
    }
    *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 1;
    *(int *)(param_1 + 4) = *(int *)(param_1 + 4) + 1;
  } while( true );
}


