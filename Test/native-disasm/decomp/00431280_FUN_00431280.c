// FUN_00431280 @ 00431280 size=2431 callers=1

/* WARNING: Type propagation algorithm not settling */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __cdecl FUN_00431280(RAWINPUTDEVICE *param_1,int param_2)

{
  uint *puVar1;
  HANDLE pvVar2;
  undefined1 *this;
  undefined4 *******pppppppuVar3;
  RAWINPUTDEVICE *pRVar4;
  int *piVar5;
  ulong uVar6;
  char *pcVar7;
  char *pcVar8;
  HWND hwnd;
  uint *puVar9;
  char *pcVar10;
  uint uVar11;
  bool bVar12;
  void *in_stack_fffffe50;
  DWORD DVar13;
  int iVar14;
  _MEMORYSTATUSEX local_18c;
  tagMSG local_14c;
  char local_130 [16];
  undefined1 local_120 [16];
  DWORD local_110;
  byte local_10c [16];
  int local_fc;
  undefined4 *******local_f4 [4];
  uint local_e4;
  uint local_e0;
  char local_dc [8];
  int local_d4;
  char *local_d0;
  char local_cc [4];
  DWORD *local_c8 [3];
  char *local_bc;
  char *local_b8;
  char *local_b4;
  char *local_b0;
  char *local_ac;
  char *local_a8;
  char *local_a4;
  char *local_a0;
  char *local_9c;
  char *local_98;
  char *local_94;
  char *local_90;
  char *local_8c;
  char *local_88;
  char *local_84;
  void *local_80;
  undefined1 *puStack_7c;
  undefined4 local_78;
  char local_74 [8];
  undefined8 local_6c;
  undefined1 local_64 [8];
  undefined8 local_5c;
  char local_54 [8];
  undefined8 local_4c;
  char local_44 [8];
  undefined8 local_3c;
  char local_34 [8];
  undefined8 local_2c;
  char *local_24;
  char *local_20;
  RAWINPUTDEVICE local_1c;
  undefined4 local_10;
  undefined4 local_c;
  HWND local_8;
  
  local_78 = 0xffffffff;
  puStack_7c = &LAB_0047d8b2;
  local_80 = ExceptionList;
  if (1 < (int)param_1) {
    LOCK();
    UNLOCK();
    DAT_004a2458 = DAT_004a2464;
    iVar14 = DAT_004a2464 + 1;
    ExceptionList = &local_80;
    *(int *)(*(int *)ThreadLocalStoragePointer + 4) = DAT_004a2464;
    DAT_004a2464 = iVar14;
    DAT_004a245c = GetCurrentThreadId();
    DVar13 = 0x80;
    pvVar2 = GetCurrentProcess();
    SetPriorityClass(pvVar2,DVar13);
    iVar14 = 0xf;
    pvVar2 = GetCurrentThread();
    SetThreadPriority(pvVar2,iVar14);
    FUN_004099d0();
    local_54[0] = '\0';
    local_4c = 0;
    FUN_00451110(local_54,(uint *)"verNum");
    local_44[0] = '\0';
    local_2c = ((double)DAT_004a2758 + (double)(&DAT_0048f2d0)[-(DAT_004a2758 >> 0x1f)]) /
               _DAT_0048f270;
    local_3c = 0;
    FUN_0044deb0(local_44);
    local_78 = 0;
    FUN_00434b50(local_cc,local_54,local_34,'\x01','\x02');
    local_78 = CONCAT31(local_78._1_3_,2);
    _eh_vector_destructor_iterator_(local_54,0x10,2,FUN_00434820);
    local_78 = 3;
    FUN_00434b50(local_dc,local_cc,(char *)&local_bc,'\x01','\x02');
    local_78 = CONCAT31(local_78._1_3_,4);
    FUN_00408600(0x2c0,local_dc);
    FUN_00434820(local_dc);
    local_78 = 0xffffffff;
    _eh_vector_destructor_iterator_(local_cc,0x10,1,FUN_00434820);
    local_18c.dwLength = 0x40;
    _memset(&local_18c.dwMemoryLoad,0,0x3c);
    GlobalMemoryStatusEx(&local_18c);
    DAT_004a23a8 = local_18c.ullTotalPhys._0_4_;
    DAT_004a23ac = local_18c.ullTotalPhys._4_4_;
    DVar13 = GetCurrentProcessId();
    FUN_00406ec0(local_c8,DVar13);
    local_78 = 5;
    local_20 = OpenProcess(0x100000,0,*local_c8[0]);
    FUN_0040d400(&local_110,(DWORD *)local_c8);
    local_78._0_1_ = 6;
    if (local_fc != 0) {
      FUN_0040d060(&local_110);
    }
    this = FUN_00435340(local_f4,(undefined1 *)&local_1c,2,3);
    local_78._0_1_ = 7;
    _DAT_004a23f0 = FUN_004032e0(this,0x24);
    local_78._0_1_ = 6;
    if (0xf < local_8) {
      FUN_00402430((void *)local_1c._0_4_,(int)local_8 + 1,1);
    }
    uVar11 = 0;
    if (local_e4 != 0) {
      do {
        pppppppuVar3 = local_f4;
        if (0xf < local_e0) {
          pppppppuVar3 = local_f4[0];
        }
        pcVar7 = (char *)&DAT_004a2538;
        if (0xf < DAT_004a254c) {
          pcVar7 = DAT_004a2538;
        }
        pcVar7[uVar11 * 2] = *(char *)((int)pppppppuVar3 + uVar11);
        uVar11 = uVar11 + 1;
      } while (uVar11 < local_e4);
    }
    pRVar4 = (RAWINPUTDEVICE *)FUN_00435340(local_f4,(undefined1 *)&local_1c,0x16,2);
    local_78._0_1_ = 8;
    if ((HWND)&DAT_0000000f < pRVar4[1].hwndTarget) {
      pRVar4 = *(RAWINPUTDEVICE **)pRVar4;
    }
    piVar5 = __errno();
    *piVar5 = 0;
    uVar6 = _strtoul((char *)pRVar4,(char **)&param_1,0x24);
    if (pRVar4 == param_1) {
                    /* WARNING: Subroutine does not return */
      FUN_00458ea4("invalid stoul argument");
    }
    piVar5 = __errno();
    if (*piVar5 == 0x22) {
                    /* WARNING: Subroutine does not return */
      FUN_00458ee4("stoul argument out of range");
    }
    local_78._0_1_ = 6;
    _DAT_004a23c0 = uVar6;
    if (0xf < local_8) {
      FUN_00402430((void *)local_1c._0_4_,(int)local_8 + 1,1);
    }
    pRVar4 = (RAWINPUTDEVICE *)FUN_00435340(local_f4,(undefined1 *)&local_1c,0xd,2);
    local_78._0_1_ = 9;
    if ((HWND)&DAT_0000000f < pRVar4[1].hwndTarget) {
      pRVar4 = *(RAWINPUTDEVICE **)pRVar4;
    }
    piVar5 = __errno();
    *piVar5 = 0;
    uVar6 = _strtoul((char *)pRVar4,(char **)&param_1,0x24);
    if (pRVar4 == param_1) {
                    /* WARNING: Subroutine does not return */
      FUN_00458ea4("invalid stoul argument");
    }
    piVar5 = __errno();
    if (*piVar5 == 0x22) {
                    /* WARNING: Subroutine does not return */
      FUN_00458ee4("stoul argument out of range");
    }
    local_78._0_1_ = 6;
    _DAT_004a23bc = uVar6;
    if (0xf < local_8) {
      FUN_00402430((void *)local_1c._0_4_,(int)local_8 + 1,1);
    }
    local_8 = (HWND)0xf;
    local_c = 0;
    local_1c._0_4_ = local_1c._0_4_ & 0xffffff00;
    puVar1 = *(uint **)(param_2 + 4);
    if ((char)*puVar1 == '\0') {
      uVar11 = 0;
    }
    else {
      puVar9 = puVar1;
      do {
        uVar11 = *puVar9;
        puVar9 = (uint *)((int)puVar9 + 1);
      } while ((char)uVar11 != '\0');
      uVar11 = (int)puVar9 - ((int)puVar1 + 1);
    }
    FUN_0043ace0(&local_1c,puVar1,uVar11);
    local_78._0_1_ = 10;
    pRVar4 = &local_1c;
    if (0xf < local_8) {
      pRVar4 = (RAWINPUTDEVICE *)local_1c._0_4_;
    }
    piVar5 = __errno();
    *piVar5 = 0;
    pvVar2 = (HANDLE)_strtoul((char *)pRVar4,(char **)&param_1,10);
    if (pRVar4 == param_1) {
                    /* WARNING: Subroutine does not return */
      FUN_00458ea4("invalid stoul argument");
    }
    piVar5 = __errno();
    if (*piVar5 == 0x22) {
                    /* WARNING: Subroutine does not return */
      FUN_00458ee4("stoul argument out of range");
    }
    SetEvent(pvVar2);
    local_78._0_1_ = 6;
    if (0xf < local_8) {
      FUN_00402430((void *)local_1c._0_4_,(int)local_8 + 1,1);
    }
    pcVar7 = local_20;
    WaitForSingleObject(local_20,3000);
    CloseHandle(pcVar7);
    bVar12 = 0xf < DAT_004a254c;
    local_98 = (char *)&DAT_004a2538;
    if (bVar12) {
      local_98 = DAT_004a2538;
    }
    pcVar7 = (char *)&DAT_004a2538;
    if (bVar12) {
      pcVar7 = DAT_004a2538;
    }
    local_d0 = (char *)&DAT_004a2538;
    if (bVar12) {
      local_d0 = DAT_004a2538;
    }
    pcVar8 = (char *)&DAT_004a2538;
    if (bVar12) {
      pcVar8 = DAT_004a2538;
    }
    local_8c = (char *)&DAT_004a2538;
    if (0xf < DAT_004a254c) {
      local_8c = DAT_004a2538;
    }
    pcVar10 = (char *)&DAT_004a2538;
    if (0xf < DAT_004a254c) {
      pcVar10 = DAT_004a2538;
    }
    param_1 = (RAWINPUTDEVICE *)
              ((uint)(byte)(local_d0[6] - local_d0[0x12]) +
              (uint)(byte)(local_d0[4] - local_d0[0x1e]));
    local_bc = local_d0;
    local_b8 = local_d0;
    local_b4 = local_d0;
    local_b0 = local_d0;
    local_ac = local_d0;
    local_a8 = local_d0;
    local_a4 = local_d0;
    local_a0 = local_d0;
    local_9c = local_d0;
    local_94 = local_d0;
    local_90 = local_d0;
    local_88 = local_d0;
    local_84 = local_d0;
    local_24 = local_98;
    local_20 = local_d0;
    local_2c._4_4_ = pcVar7;
    if ((int)param_1 +
        (char)(DAT_004a255c / 0x5609) + -7 +
        (uint)(byte)(*local_98 - pcVar7[0x18]) +
        (uint)(byte)(local_d0[10] - local_d0[0x3e]) +
        (uint)(byte)(local_d0[0xc] - local_d0[0x20]) +
        (uint)(byte)(local_d0[0xe] - local_d0[0x3c]) +
        (uint)(byte)(local_d0[0x14] - local_d0[0x24]) +
        (uint)(byte)(local_d0[0x16] - local_d0[0x3a]) +
        (uint)(byte)(local_98[0x2a] - local_d0[0x34]) +
        (uint)(byte)(pcVar8[0x2c] - local_8c[0x30]) +
        (uint)(byte)(local_d0[2] - local_d0[0x30]) + (uint)(byte)(pcVar10[0x20] - local_8c[0x38]) !=
        0) {
      local_54[0] = '\0';
      local_4c = 0;
      FUN_00451110(local_54,(uint *)"extId");
      local_78._0_1_ = 0xb;
      local_3c = 0;
      local_44[0] = '\x03';
      pcVar7 = operator_new(0x18);
      local_d4 = (int)&param_1 + 3;
      local_78._0_1_ = 0xd;
      local_d0 = pcVar7;
      local_24 = pcVar7;
      local_2c._4_4_ = pcVar7;
      if (pcVar7 != (char *)0x0) {
        pcVar7[0x14] = '\x0f';
        pcVar7[0x15] = '\0';
        pcVar7[0x16] = '\0';
        pcVar7[0x17] = '\0';
        pcVar7[0x10] = '\0';
        pcVar7[0x11] = '\0';
        pcVar7[0x12] = '\0';
        pcVar7[0x13] = '\0';
        pcVar8 = pcVar7;
        if (0xf < *(uint *)(pcVar7 + 0x14)) {
          pcVar8 = *(char **)pcVar7;
        }
        *pcVar8 = '\0';
        FUN_0043ade0(pcVar7,local_f4,0,0xffffffff);
      }
      local_3c = CONCAT44(local_2c._4_4_,pcVar7);
      local_78._0_1_ = 0xe;
      FUN_00434b50(local_130,local_54,local_34,'\x01','\x02');
      local_78._0_1_ = 0x10;
      _eh_vector_destructor_iterator_(local_54,0x10,2,FUN_00434820);
      local_74[0] = '\0';
      local_6c = 0;
      FUN_00451110(local_74,(uint *)"ancestors");
      local_78._0_1_ = 0x11;
      local_64[0] = 0;
      local_5c = 0;
      FUN_0044ded0(local_64,(undefined4 *)&DAT_004a2550);
      local_78._0_1_ = 0x12;
      FUN_00434b50(local_120,local_74,local_54,'\x01','\x02');
      local_78._0_1_ = 0x14;
      _eh_vector_destructor_iterator_(local_74,0x10,2,FUN_00434820);
      local_78._0_1_ = 0x15;
      FUN_00434b50(&local_1c.hwndTarget,local_130,(char *)&local_110,'\x01','\x02');
      local_78._0_1_ = 0x16;
      FUN_004355e0(&stack0xfffffe50,(uint *)"invalidExtId");
      FUN_00408c90(&local_1c.hwndTarget,in_stack_fffffe50);
      FUN_00434820((char *)&local_1c.hwndTarget);
      local_78._0_1_ = 6;
      _eh_vector_destructor_iterator_(local_130,0x10,2,FUN_00434820);
    }
    bVar12 = FUN_00440970(local_10c,(byte *)"AutoControlZero.exe");
    if (bVar12) {
      local_74[0] = '\0';
      local_6c = 0;
      FUN_00451110(local_74,(uint *)"ancestors");
      local_78._0_1_ = 0x17;
      local_64[0] = 0;
      local_5c = 0;
      FUN_0044ded0(local_64,(undefined4 *)&DAT_004a2550);
      local_78._0_1_ = 0x18;
      FUN_00434b50(local_34,local_74,local_54,'\x01','\x02');
      local_78._0_1_ = 0x1a;
      _eh_vector_destructor_iterator_(local_74,0x10,2,FUN_00434820);
      local_78._0_1_ = 0x1b;
      FUN_00434b50(&local_1c.hwndTarget,local_34,(char *)&local_24,'\x01','\x02');
      local_78._0_1_ = 0x1c;
      FUN_004355e0(&stack0xfffffe50,(uint *)"badBrwrName");
      FUN_00408c90(&local_1c.hwndTarget,in_stack_fffffe50);
      FUN_00434820((char *)&local_1c.hwndTarget);
      local_78._0_1_ = 6;
      _eh_vector_destructor_iterator_(local_34,0x10,1,FUN_00434820);
    }
    FUN_00447d20(_DAT_004a2550,DAT_004a2554);
    DAT_004a2554 = _DAT_004a2550;
    FUN_0040da40((int)&local_110);
    FUN_00432fc0((int *)local_c8);
    hwnd = FUN_00431110();
    RegisterShellHookWindow(hwnd);
    DAT_004a23cc = SetWinEventHook(0x20,0x20,(HMODULE)0x0,FUN_004238e0,0,0,0);
    DAT_004a244c = SetWinEventHook(3,3,(HMODULE)0x0,FUN_004238e0,0,0,0);
    DAT_004a23f8 = CreateThread((LPSECURITY_ATTRIBUTES)0x0,1,FUN_00430a70,(LPVOID)0x0,0,
                                &DAT_004a2450);
    CreateThread((LPSECURITY_ATTRIBUTES)0x0,1,FUN_00430a30,(LPVOID)0x0,0,&DAT_004a23c8);
    pRVar4 = (RAWINPUTDEVICE *)CoInitializeEx((LPVOID)0x0,0);
    local_78 = 0x1d;
    local_1c._0_4_ = (RAWINPUTDEVICE *)0x60001;
    local_1c.dwFlags = 0x300;
    local_10 = 0x20001;
    local_c = 0x100;
    param_1 = pRVar4;
    local_1c.hwndTarget = hwnd;
    local_8 = hwnd;
    RegisterRawInputDevices(&local_1c,2,0xc);
    iVar14 = GetMessageA(&local_14c,(HWND)0x0,0,0);
    while (iVar14 != 0) {
      DispatchMessageA(&local_14c);
      iVar14 = GetMessageA(&local_14c,(HWND)0x0,0,0);
    }
    FUN_0040f310();
    if (-1 < (int)pRVar4) {
      CoUninitialize();
    }
  }
  ExceptionList = local_80;
  return 0;
}


