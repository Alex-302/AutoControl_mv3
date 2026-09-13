// write_text_ansi_nolock @ 0046b189 size=223 callers=1

/* WARNING: Function: __alloca_probe replaced with injection: alloca_probe */
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* Library Function - Single Match
    struct `anonymous namespace'::write_result __cdecl write_text_ansi_nolock(int,char const *
   const,unsigned int)
   
   Library: Visual Studio 2015 Release */

int __cdecl write_text_ansi_nolock(int param_1,char *param_2,uint param_3)

{
  char cVar1;
  HANDLE hFile;
  BOOL BVar2;
  DWORD DVar3;
  char *pcVar4;
  int in_stack_00000010;
  uint local_1410;
  char *local_140c;
  char local_1408 [5120];
  uint local_8;
  
  local_8 = DAT_0049d070 ^ (uint)&stack0xfffffffc;
  hFile = *(HANDLE *)((&DAT_0049f8f8)[(int)param_2 >> 6] + 0x18 + ((uint)param_2 & 0x3f) * 0x30);
  *(undefined4 *)param_1 = 0;
  local_140c = (char *)(in_stack_00000010 + param_3);
  *(undefined4 *)(param_1 + 4) = 0;
  *(undefined4 *)(param_1 + 8) = 0;
  do {
    if (local_140c <= param_3) {
      return param_1;
    }
    pcVar4 = local_1408;
    do {
      if (local_140c <= param_3) break;
      cVar1 = *(char *)param_3;
      param_3 = param_3 + 1;
      if (cVar1 == '\n') {
        *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 1;
        *pcVar4 = '\r';
        pcVar4 = pcVar4 + 1;
      }
      *pcVar4 = cVar1;
      pcVar4 = pcVar4 + 1;
    } while (pcVar4 < local_1408 + 0x13ff);
    BVar2 = WriteFile(hFile,local_1408,(int)pcVar4 - (int)local_1408,&local_1410,(LPOVERLAPPED)0x0);
    if (BVar2 == 0) {
      DVar3 = GetLastError();
      *(DWORD *)param_1 = DVar3;
      return param_1;
    }
    *(int *)(param_1 + 4) = *(int *)(param_1 + 4) + local_1410;
    if (local_1410 < (uint)((int)pcVar4 - (int)local_1408)) {
      return param_1;
    }
  } while( true );
}


