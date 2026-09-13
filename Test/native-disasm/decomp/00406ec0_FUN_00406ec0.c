// FUN_00406ec0 @ 00406ec0 size=420 callers=1

undefined4 * __fastcall FUN_00406ec0(undefined4 *param_1,DWORD param_2)

{
  char cVar1;
  undefined4 uVar2;
  HANDLE hProcess;
  BOOL BVar3;
  LONG LVar4;
  uint uVar5;
  char *pcVar6;
  int iVar7;
  code *pcVar8;
  undefined4 local_17c [6];
  DWORD local_164;
  undefined4 local_158;
  DWORD local_54;
  void *local_50 [4];
  undefined4 local_40;
  uint local_3c;
  FILETIME local_38;
  _FILETIME local_30;
  _FILETIME local_28;
  undefined4 local_20;
  undefined4 *local_1c;
  int local_18;
  DWORD local_14;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  puStack_c = &LAB_00479641;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  local_8 = 0;
  local_20 = 1;
  local_1c = param_1;
  local_14 = param_2;
  local_18 = CreateToolhelp32Snapshot(2,0);
  if (local_18 == -1) {
    ExceptionList = local_10;
    return param_1;
  }
  iVar7 = 0;
  pcVar8 = CloseHandle_exref;
  do {
    uVar2 = FUN_00406e30(local_18,param_2,local_17c);
    if ((char)uVar2 == '\0') break;
    hProcess = OpenProcess(0x400,0,param_2);
    BVar3 = GetProcessTimes(hProcess,&local_28,&local_30,&local_30,&local_30);
    pcVar8 = CloseHandle_exref;
    CloseHandle(hProcess);
    if (BVar3 == 0) {
LAB_00406f9c:
      if (iVar7 != 0) {
        local_54 = local_14;
        local_3c = 0xf;
        local_40 = 0;
        local_50[0] = (void *)((uint)local_50[0] & 0xffffff00);
        if ((char)local_158 == '\0') {
          uVar5 = 0;
        }
        else {
          pcVar6 = (char *)&local_158;
          do {
            cVar1 = *pcVar6;
            pcVar6 = pcVar6 + 1;
          } while (cVar1 != '\0');
          uVar5 = (int)pcVar6 - ((int)&local_158 + 1);
        }
        FUN_0043ace0(local_50,&local_158,uVar5);
        local_8 = 1;
        FUN_00433020(local_1c,&local_54);
        local_8 = local_8 & 0xffffff00;
        if (0xf < local_3c) {
          FUN_00402430(local_50[0],local_3c + 1,1);
        }
      }
    }
    else if (iVar7 != 0) {
      LVar4 = CompareFileTime(&local_28,&local_38);
      if (LVar4 == -1) goto LAB_00406f9c;
      break;
    }
    local_38.dwLowDateTime = local_28.dwLowDateTime;
    iVar7 = iVar7 + 1;
    local_14 = local_164;
    local_38.dwHighDateTime = local_28.dwHighDateTime;
    param_2 = local_164;
  } while (iVar7 < 0xb);
  (*pcVar8)(local_18);
  ExceptionList = local_10;
  return local_1c;
}


