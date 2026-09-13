// exit_or_terminate_process @ 00467b07 size=64 callers=1

/* Library Function - Single Match
    void __cdecl exit_or_terminate_process(unsigned int)
   
   Library: Visual Studio 2015 Release */

void __cdecl exit_or_terminate_process(uint param_1)

{
  uint uVar1;
  HANDLE hProcess;
  
  uVar1 = ___acrt_is_packaged_app();
  if (((char)uVar1 != '\0') && ((*(uint *)((int)ProcessEnvironmentBlock + 0x68) >> 8 & 1) == 0)) {
    uVar1 = param_1;
    hProcess = GetCurrentProcess();
    TerminateProcess(hProcess,uVar1);
  }
  try_cor_exit_process(param_1);
                    /* WARNING: Subroutine does not return */
  ExitProcess(param_1);
}


