// write_text_utf8_nolock @ 0046b356 size=301 callers=1

/* WARNING: Function: __alloca_probe replaced with injection: alloca_probe */
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* Library Function - Single Match
    struct `anonymous namespace'::write_result __cdecl write_text_utf8_nolock(int,char const *
   const,unsigned int)
   
   Library: Visual Studio 2015 Release */

int __cdecl write_text_utf8_nolock(int param_1,char *param_2,uint param_3)

{
  WCHAR WVar1;
  HANDLE hFile;
  WCHAR *pWVar2;
  uint uVar3;
  BOOL BVar4;
  DWORD DVar5;
  uint uVar6;
  WCHAR *pWVar7;
  int in_stack_00000010;
  DWORD local_1414;
  WCHAR *local_1410;
  CHAR local_140c [3416];
  WCHAR local_6b4 [854];
  uint local_8;
  
  local_8 = DAT_0049d070 ^ (uint)&stack0xfffffffc;
  hFile = *(HANDLE *)((&DAT_0049f8f8)[(int)param_2 >> 6] + 0x18 + ((uint)param_2 & 0x3f) * 0x30);
  local_1410 = (WCHAR *)(in_stack_00000010 + param_3);
  *(undefined4 *)param_1 = 0;
  *(undefined4 *)(param_1 + 4) = 0;
  *(undefined4 *)(param_1 + 8) = 0;
  pWVar7 = (WCHAR *)param_3;
  if (param_3 < local_1410) {
    do {
      uVar6 = 0;
      pWVar2 = local_6b4;
      do {
        if (local_1410 <= pWVar7) break;
        WVar1 = *pWVar7;
        pWVar7 = pWVar7 + 1;
        if (WVar1 == L'\n') {
          *pWVar2 = L'\r';
          pWVar2 = pWVar2 + 1;
        }
        *pWVar2 = WVar1;
        pWVar2 = pWVar2 + 1;
      } while (pWVar2 < local_6b4 + 0x354);
      uVar3 = WideCharToMultiByte(0xfde9,0,local_6b4,(int)pWVar2 - (int)local_6b4 >> 1,local_140c,
                                  0xd55,(LPCSTR)0x0,(LPBOOL)0x0);
      if (uVar3 == 0) {
LAB_0046b468:
        DVar5 = GetLastError();
        *(DWORD *)param_1 = DVar5;
        return param_1;
      }
      do {
        BVar4 = WriteFile(hFile,local_140c + uVar6,uVar3 - uVar6,&local_1414,(LPOVERLAPPED)0x0);
        if (BVar4 == 0) goto LAB_0046b468;
        uVar6 = uVar6 + local_1414;
      } while (uVar6 < uVar3);
      *(uint *)(param_1 + 4) = (int)pWVar7 - param_3;
    } while (pWVar7 < local_1410);
  }
  return param_1;
}


