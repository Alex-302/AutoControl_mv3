// FUN_00427f50 @ 00427f50 size=847 callers=2

void __cdecl FUN_00427f50(void *param_1)

{
  HRESULT HVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  undefined2 *this;
  int in_stack_00000014;
  uint in_stack_00000018;
  undefined4 local_70 [6];
  WCHAR local_58 [8];
  int local_48;
  HRESULT local_40;
  DWORD local_3c;
  int local_38;
  DWORD local_34;
  int local_30;
  int *local_2c;
  int *local_28;
  int *local_24;
  int *local_20;
  int *local_1c;
  int *local_18;
  int *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined1 local_8;
  undefined3 uStack_7;
  
  puStack_c = &LAB_0047c77e;
  local_10 = ExceptionList;
  local_8 = 0;
  uStack_7 = 0;
  ExceptionList = &local_10;
  HVar1 = CoInitializeEx((LPVOID)0x0,2);
  local_2c = (int *)0x0;
  local_40 = HVar1;
  piVar2 = (int *)CoCreateInstance((IID *)&DAT_0049da4c,(LPUNKNOWN)0x0,1,(IID *)&DAT_0049da14,
                                   &local_2c);
  if (piVar2 == (int *)0x0) {
    local_8 = 4;
    local_28 = piVar2;
    piVar2 = (int *)(**(code **)(*local_2c + 0x10))(local_2c,0,0,&local_28);
    if (piVar2 == (int *)0x0) {
      local_8 = 7;
      local_24 = piVar2;
      piVar2 = (int *)(**(code **)(*local_28 + 0xc))(local_28,&DAT_0049da60,1,0,&local_24);
      if (piVar2 == (int *)0x0) {
        local_8 = 0xb;
        local_1c = piVar2;
        iVar3 = (**(code **)(*local_24 + 0x14))(local_24,&local_1c);
        if (iVar3 == 0) {
          FUN_00435020(&param_1,0,1,0x5c);
          local_30 = 0;
          (**(code **)(*local_1c + 0xc))(local_1c,&local_30);
          iVar3 = 0;
          if (0 < local_30) {
            do {
              local_18 = (int *)0x0;
              local_8 = 0x10;
              iVar4 = (**(code **)(*local_1c + 0x10))(local_1c,iVar3,&local_18);
              if (iVar4 == 0) {
                local_14 = (int *)0x0;
                local_8 = 0x12;
                iVar4 = (**(code **)*local_18)(local_18,&DAT_0049da70,&local_14);
                if (iVar4 == 0) {
                  iVar4 = (**(code **)(*local_14 + 0x38))(local_14,&local_34);
                  if ((iVar4 == 0) || (iVar4 == 0x889000d)) {
                    FUN_00404a40(local_58,local_34);
                    local_8 = 0x17;
                    uVar5 = local_48 - in_stack_00000014;
                    if ((int)uVar5 < 0) {
                      uVar5 = 0;
                    }
                    this = FUN_00434e10(local_58,(undefined2 *)local_70,uVar5,0xffffffff);
                    uVar5 = FUN_004443e0(this,(ushort *)&param_1);
                    FUN_00435170(local_70);
                    if (uVar5 == 0) {
                      local_20 = (int *)0x0;
                      local_8 = 0x1a;
                      iVar4 = (**(code **)*local_14)(local_14,&DAT_0049da24,&local_20);
                      if (iVar4 == 0) {
                        local_3c = local_34;
                        if (*(int **)(local_38 + 0x24) == (int *)0x0) {
                    /* WARNING: Subroutine does not return */
                          FUN_00458e87();
                        }
                        (**(code **)(**(int **)(local_38 + 0x24) + 8))(&local_3c,local_20);
                        local_8 = 0x1e;
                        if (local_20 != (int *)0x0) {
                          (**(code **)(*local_20 + 8))(local_20);
                        }
                        FUN_00435170((undefined4 *)local_58);
                        local_8 = 0x1f;
                        if (local_14 != (int *)0x0) {
                          (**(code **)(*local_14 + 8))(local_14);
                        }
                        local_8 = 0x20;
                      }
                      else {
                        local_8 = 0x1b;
                        if (local_20 != (int *)0x0) {
                          (**(code **)(*local_20 + 8))(local_20);
                        }
                        FUN_00435170((undefined4 *)local_58);
                        local_8 = 0x1c;
                        if (local_14 != (int *)0x0) {
                          (**(code **)(*local_14 + 8))(local_14);
                        }
                        local_8 = 0x1d;
                      }
                    }
                    else {
                      FUN_00435170((undefined4 *)local_58);
                      local_8 = 0x18;
                      if (local_14 != (int *)0x0) {
                        (**(code **)(*local_14 + 8))(local_14);
                      }
                      local_8 = 0x19;
                    }
                  }
                  else {
                    local_8 = 0x15;
                    if (local_14 != (int *)0x0) {
                      (**(code **)(*local_14 + 8))(local_14);
                    }
                    local_8 = 0x16;
                  }
                }
                else {
                  local_8 = 0x13;
                  if (local_14 != (int *)0x0) {
                    (**(code **)(*local_14 + 8))(local_14);
                  }
                  local_8 = 0x14;
                }
              }
              else {
                local_8 = 0x11;
              }
              if (local_18 != (int *)0x0) {
                (**(code **)(*local_18 + 8))(local_18);
              }
              iVar3 = iVar3 + 1;
            } while (iVar3 < local_30);
          }
          local_8 = 0x21;
          if (local_1c != (int *)0x0) {
            (**(code **)(*local_1c + 8))(local_1c);
          }
          local_8 = 0x22;
          if (local_24 != (int *)0x0) {
            (**(code **)(*local_24 + 8))(local_24);
          }
          local_8 = 0x23;
          if (local_28 != (int *)0x0) {
            (**(code **)(*local_28 + 8))(local_28);
          }
          _local_8 = CONCAT31(uStack_7,0x24);
          goto LAB_0042803a;
        }
        local_8 = 0xc;
        if (local_1c != (int *)0x0) {
          (**(code **)(*local_1c + 8))(local_1c);
        }
      }
      local_8 = 0xd;
      if (local_24 != (int *)0x0) {
        (**(code **)(*local_24 + 8))(local_24);
      }
    }
    local_8 = 0xe;
    if (local_28 != (int *)0x0) {
      (**(code **)(*local_28 + 8))(local_28);
    }
  }
  _local_8 = CONCAT31(uStack_7,0xf);
LAB_0042803a:
  if (local_2c != (int *)0x0) {
    (**(code **)(*local_2c + 8))(local_2c);
  }
  if (-1 < HVar1) {
    CoUninitialize();
  }
  if (7 < in_stack_00000018) {
    FUN_00402430(param_1,in_stack_00000018 + 1,2);
  }
  ExceptionList = local_10;
  return;
}


