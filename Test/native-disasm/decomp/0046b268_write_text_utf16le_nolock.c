// write_text_utf16le_nolock @ 0046b268 size=238 callers=1

/* WARNING: Function: __alloca_probe replaced with injection: alloca_probe */
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* Library Function - Single Match
    struct `anonymous namespace'::write_result __cdecl write_text_utf16le_nolock(int,char const *
   const,unsigned int)
   
   Library: Visual Studio 2015 Release */

int __cdecl write_text_utf16le_nolock(int param_1,char *param_2,uint param_3)

{
  short sVar1;
  HANDLE hFile;
  BOOL BVar2;
  DWORD DVar3;
  short *psVar4;
  int in_stack_00000010;
  uint local_1410;
  short *local_140c;
  short local_1408 [2560];
  uint local_8;
  
  local_8 = DAT_0049d070 ^ (uint)&stack0xfffffffc;
  hFile = *(HANDLE *)((&DAT_0049f8f8)[(int)param_2 >> 6] + 0x18 + ((uint)param_2 & 0x3f) * 0x30);
  local_140c = (short *)(in_stack_00000010 + param_3);
  *(undefined4 *)param_1 = 0;
  *(undefined4 *)(param_1 + 4) = 0;
  *(undefined4 *)(param_1 + 8) = 0;
  do {
    if (local_140c <= param_3) {
      return param_1;
    }
    psVar4 = local_1408;
    do {
      if (local_140c <= param_3) break;
      sVar1 = *(short *)param_3;
      param_3 = param_3 + 2;
      if (sVar1 == 10) {
        *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 2;
        *psVar4 = 0xd;
        psVar4 = psVar4 + 1;
      }
      *psVar4 = sVar1;
      psVar4 = psVar4 + 1;
    } while (psVar4 < local_1408 + 0x9ff);
    BVar2 = WriteFile(hFile,local_1408,(int)psVar4 - (int)local_1408,&local_1410,(LPOVERLAPPED)0x0);
    if (BVar2 == 0) {
      DVar3 = GetLastError();
      *(DWORD *)param_1 = DVar3;
      return param_1;
    }
    *(int *)(param_1 + 4) = *(int *)(param_1 + 4) + local_1410;
    if (local_1410 < (uint)((int)psVar4 - (int)local_1408)) {
      return param_1;
    }
  } while( true );
}


