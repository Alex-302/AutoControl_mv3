// FUN_00405040 @ 00405040 size=562 callers=1

undefined4 * __fastcall
FUN_00405040(undefined4 *param_1,LPWSTR param_2,LPCWSTR param_3,WORD param_4,DWORD param_5,
            byte param_6)

{
  BOOL BVar1;
  uint *puVar2;
  byte bVar3;
  _STARTUPINFOW local_d0;
  undefined4 local_84;
  void *local_80 [3];
  _SECURITY_ATTRIBUTES local_74;
  HANDLE local_68;
  DWORD DStack_64;
  DWORD DStack_60;
  DWORD DStack_5c;
  void *local_58 [4];
  undefined4 local_48;
  uint local_44;
  _PROCESS_INFORMATION local_40;
  undefined4 *local_30;
  HANDLE local_2c;
  HANDLE local_28;
  byte local_21;
  undefined1 *puStack_20;
  void *local_1c;
  undefined1 *puStack_18;
  undefined4 local_14;
  
  puStack_20 = &stack0xfffffffc;
  local_14 = 0xffffffff;
  puStack_18 = &LAB_00479388;
  local_1c = ExceptionList;
  local_84 = 0;
  local_d0.cb = 0x44;
  ExceptionList = &local_1c;
  local_30 = param_1;
  _memset(&local_d0.lpReserved,0,0x40);
  local_d0.wShowWindow = param_4;
  local_30 = (undefined4 *)((uint)(int)(char)param_6 >> 2 & 0xffffff01);
  local_d0.dwFlags = 1;
  local_28 = (HANDLE)0x0;
  local_2c = (HANDLE)0x0;
  bVar3 = param_6 & 1;
  if ((char)local_30 != '\0') {
    local_74.nLength = 0xc;
    local_74.lpSecurityDescriptor = (LPVOID)0x0;
    local_74.bInheritHandle = 1;
    CreatePipe(&local_2c,&local_28,&local_74,0);
    local_21 = 1;
    SetHandleInformation(local_2c,1,0);
    local_d0.dwFlags = local_d0.dwFlags | 0x100;
    local_d0.hStdOutput = local_28;
    bVar3 = local_21;
  }
  local_44 = 0xf;
  local_68 = (HANDLE)0x0;
  DStack_64 = 0;
  DStack_60 = 0;
  DStack_5c = 0;
  local_48 = 0;
  local_58[0] = (void *)((uint)local_58[0] & 0xffffff00);
  local_14 = 0;
  local_40.hProcess = (HANDLE)0x0;
  local_40.hThread = (HANDLE)0x0;
  local_40.dwProcessId = 0;
  local_40.dwThreadId = 0;
  BVar1 = CreateProcessW((LPCWSTR)0x0,param_2,(LPSECURITY_ATTRIBUTES)0x0,(LPSECURITY_ATTRIBUTES)0x0,
                         (uint)bVar3,0,(LPVOID)0x0,param_3,&local_d0,&local_40);
  if (BVar1 == 0) {
    DStack_5c = GetLastError();
  }
  else {
    CloseHandle(local_40.hThread);
    if ((char)local_30 != '\0') {
      CloseHandle(local_28);
      puVar2 = (uint *)FUN_00404f10((int *)local_80,local_2c);
      FUN_00435570(local_58,puVar2);
      if (0xf < (uint)local_74.bInheritHandle) {
        FUN_00402430(local_80[0],local_74.bInheritHandle + 1,1);
      }
    }
    if (param_5 != 0) {
      WaitForSingleObject(local_40.hProcess,param_5);
    }
    GetExitCodeProcess(local_40.hProcess,&DStack_60);
    if ((param_6 & 2) == 0) {
      CloseHandle(local_40.hProcess);
      DStack_64 = local_40.dwProcessId;
    }
    else {
      local_68 = local_40.hProcess;
      DStack_64 = local_40.dwProcessId;
    }
  }
  if ((char)local_30 != '\0') {
    CloseHandle(local_28);
    CloseHandle(local_2c);
  }
  *param_1 = local_68;
  param_1[1] = DStack_64;
  param_1[2] = DStack_60;
  param_1[3] = DStack_5c;
  param_1[9] = 0xf;
  param_1[8] = 0;
  *(undefined1 *)(param_1 + 4) = 0;
  FUN_0043b1c0(param_1 + 4,(uint *)local_58);
  if (0xf < local_44) {
    FUN_00402430(local_58[0],local_44 + 1,1);
  }
  ExceptionList = local_1c;
  return param_1;
}


