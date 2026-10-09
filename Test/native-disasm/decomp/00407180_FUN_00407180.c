// FUN_00407180 @ 00407180 size=529 callers=1

undefined4 * __fastcall FUN_00407180(undefined4 *param_1,DWORD param_2)

{
  undefined4 *puVar1;
  HANDLE hObject;
  uint uVar2;
  int iVar3;
  FARPROC pFVar4;
  char *lpProcName;
  undefined4 *****pppppuVar5;
  uint uVar6;
  undefined2 uVar7;
  undefined1 local_7c [4];
  uint auStack_78 [11];
  undefined4 ****local_4c [5];
  uint local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 *local_2c;
  int local_28;
  uint local_24;
  FARPROC local_20;
  undefined4 local_1c;
  HMODULE local_18;
  char local_11;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00479671;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  param_1[4] = 0;
  param_1[5] = 0;
  param_1[5] = 7;
  param_1[4] = 0;
  puVar1 = param_1;
  if (7 < (uint)param_1[5]) {
    puVar1 = (undefined4 *)*param_1;
  }
  *(undefined2 *)puVar1 = 0;
  local_8 = 0;
  local_1c = 1;
  local_2c = param_1;
  hObject = OpenProcess(0x410,0,param_2);
  if (hObject != (HANDLE)0x0) {
    local_18 = GetModuleHandleA("ntdll.dll");
    if (local_18 != (HMODULE)0x0) {
      uVar2 = FUN_004070b0(hObject);
      if ((byte)uVar2 == 0) {
        uVar7 = 0;
        lpProcName = "NtQueryInformationProcess";
      }
      else {
        uVar7 = (undefined2)CONCAT31((uint3)(byte)uVar2,1);
        lpProcName = "NtWow64QueryInformationProcess64";
      }
      local_11 = (char)uVar7;
      local_20 = GetProcAddress(local_18,lpProcName);
      if ((local_20 != (FARPROC)0x0) &&
         (iVar3 = (*local_20)(hObject,0,local_7c,
                              (int)(0x30 / (ulonglong)(((char)uVar7 == '\0') + 1)),0), iVar3 == 0))
      {
        if ((char)((ushort)uVar7 >> 8) == '\0') {
          pFVar4 = (FARPROC)&LAB_00407150;
        }
        else {
          pFVar4 = GetProcAddress(local_18,"NtWow64ReadVirtualMemory64");
        }
        if (pFVar4 != (FARPROC)0x0) {
          local_20 = (FARPROC)0x20;
          uVar6 = (uint)(local_11 != '\0');
          local_28 = uVar6 * 4 + 4;
          uVar2 = 0x10;
          if (local_11 != '\0') {
            uVar2 = 0x20;
          }
          iVar3 = (*pFVar4)(hObject,uVar2 + auStack_78[uVar6],
                            auStack_78[uVar6 + 1] + (uint)CARRY4(uVar2,auStack_78[uVar6]),&local_24,
                            local_28,0,0);
          if (iVar3 == 0) {
            uVar2 = 0x40;
            if (local_11 != '\0') {
              uVar2 = 0x70;
            }
            iVar3 = (*pFVar4)(hObject,uVar2 + local_24,local_20 + CARRY4(uVar2,local_24),&local_18,2
                              ,0,0);
            if (iVar3 == 0) {
              uVar2 = 0x44;
              if (local_11 != '\0') {
                uVar2 = 0x78;
              }
              iVar3 = (*pFVar4)(hObject,uVar2 + local_24,local_20 + CARRY4(uVar2,local_24),&local_34
                                ,local_28,0,0);
              if (iVar3 == 0) {
                FUN_00435230(local_4c,(uint)local_18 & 0xffff,0);
                local_8 = 1;
                pppppuVar5 = local_4c;
                if (7 < local_38) {
                  pppppuVar5 = (undefined4 *****)local_4c[0];
                }
                iVar3 = (*pFVar4)(hObject,local_34,local_30,pppppuVar5,((uint)local_18 & 0xffff) * 2
                                  ,0,0);
                if (iVar3 == 0) {
                  FUN_004351b0(param_1,(uint *)local_4c);
                }
                FUN_00435170(local_4c);
              }
            }
          }
        }
      }
    }
    CloseHandle(hObject);
  }
  ExceptionList = local_10;
  return param_1;
}


