// FUN_00423920 @ 00423920 size=241 callers=1

uint FUN_00423920(HWND param_1,uint param_2,HWND param_3,HMENU param_4)

{
  HMENU pHVar1;
  bool bVar2;
  char *pcVar3;
  undefined4 *this;
  int iVar4;
  uint uVar5;
  undefined8 uVar6;
  void *in_stack_ffffff74;
  undefined4 uVar7;
  undefined **ppuStack_64;
  undefined8 uStack_60;
  HWND *ppHStack_58;
  undefined ***pppuStack_40;
  char local_3c [16];
  byte abStack_2c [12];
  char *pcStack_20;
  int iStack_1c;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  pHVar1 = param_4;
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047bf28;
  local_10 = ExceptionList;
  local_14 = &stack0xffffff8c;
  if (0x123 < param_2) {
    if (param_2 < 0x30e) {
      if (param_2 == 0x30d) {
        if (DAT_004a23ec == (HWND)0x0) {
          return 0;
        }
        if (param_3 == DAT_004a23ec) {
          DAT_004a23ec = (HWND)param_4;
          return 0;
        }
        ExceptionList = &local_10;
        local_14 = &stack0xffffff8c;
        SendMessageA(DAT_004a23ec,0x30d,(WPARAM)param_3,(LPARAM)param_4);
        ExceptionList = local_10;
        return 0;
      }
      if (param_2 == 0x124) {
        if (DAT_004a2444 == '\0') {
          return 0;
        }
        ExceptionList = &local_10;
        local_14 = &stack0xffffff8c;
        uVar5 = FUN_0041f390((int)param_4);
        ExceptionList = local_10;
        return uVar5;
      }
      if (param_2 == 0x125) {
        ExceptionList = &local_10;
        local_14 = &stack0xffffff8c;
        uVar5 = FUN_0041eea0();
        ExceptionList = local_10;
        return uVar5;
      }
      if (param_2 == 0x308) {
        ExceptionList = &local_10;
        local_14 = &stack0xffffff8c;
        FUN_00417f10(0);
        if (DAT_004a23ec == (HWND)0x0) {
          ExceptionList = local_10;
          return 0;
        }
        SendMessageA(DAT_004a23ec,0x308,(WPARAM)param_3,(LPARAM)param_4);
        ExceptionList = local_10;
        return 0;
      }
    }
    else {
      if (param_2 == 0x31d) {
        ExceptionList = &local_10;
        FUN_00417f10(0);
        ExceptionList = local_10;
        return 0;
      }
      if (param_2 == 0x9e41) {
        ExceptionList = &local_10;
        local_14 = &stack0xffffff8c;
        FUN_0040f950(&param_4->unused,param_3);
        ExceptionList = local_10;
        return 0;
      }
    }
switchD_0042396b_caseD_2d:
LAB_00423d59:
    ExceptionList = &local_10;
    local_14 = &stack0xffffff8c;
    uVar5 = DefWindowProcA(param_1,param_2,(WPARAM)param_3,(LPARAM)param_4);
    ExceptionList = local_10;
    return uVar5;
  }
  if (param_2 == 0x123) {
    ExceptionList = &local_10;
    local_14 = &stack0xffffff8c;
    uVar5 = FUN_0041ef90((ushort)param_3,param_4);
    ExceptionList = local_10;
    return uVar5;
  }
  switch(param_2) {
  case 0x2b:
    if (param_4->unused == 1) {
      ExceptionList = &local_10;
      local_14 = &stack0xffffff8c;
      uVar5 = FUN_0041e910((int)param_4);
      ExceptionList = local_10;
      return uVar5;
    }
    break;
  case 0x2c:
    local_8 = 0xffffffff;
    ExceptionList = &local_10;
    local_14 = &stack0xffffff8c;
    uVar5 = FUN_0041e6e0(param_2,&param_4->unused);
    ExceptionList = local_10;
    return uVar5;
  default:
    goto switchD_0042396b_caseD_2d;
  case 0x4a:
    if (param_4->unused != 0) {
      ExceptionList = &local_10;
      local_14 = &stack0xffffff8c;
      pcVar3 = FUN_00440fd0(local_3c,(char *)param_4[2].unused);
      local_8 = 0;
      FUN_00408600(pHVar1->unused,pcVar3);
      FUN_00434820(local_3c);
      ExceptionList = local_10;
      return 1;
    }
    local_8 = 1;
    if ((uint)param_4[1].unused < 0xf4241) {
      ExceptionList = &local_10;
      local_14 = &stack0xffffff8c;
      FUN_004420c0(local_3c,param_4[2].unused,param_4[1].unused + param_4[2].unused);
      local_8._0_1_ = 2;
      if (local_3c[0] == '\x01') {
        FUN_004355e0(&stack0xffffff74,(uint *)&DAT_0048d80c);
        pcVar3 = (char *)0x423a31;
        iVar4 = FUN_004341b0(local_3c,in_stack_ffffff74);
        if (iVar4 != 0) {
          uVar7 = 0;
          this = FUN_00440e70(local_3c,(uint *)&DAT_0048d80c);
          FUN_00440bb0(this,(undefined4 *)&stack0xffffff70);
          pcVar3 = FUN_00403840(abStack_2c,pcVar3);
          local_8._0_1_ = 3;
          uVar6 = FUN_004037c0(pcVar3," \t\n\r\f\v");
          uVar5 = FUN_004409d0(&DAT_004a28d0,(undefined4 *)uVar6,uVar7);
          param_3 = (HWND)(uVar5 & 0xffff);
          local_8._0_1_ = 2;
          FUN_004061c0((undefined4 *)abStack_2c);
          if ((short)param_3 != 0) {
            FUN_004355e0(abStack_2c,(uint *)&DAT_0048d80c);
            local_8._0_1_ = 4;
            FUN_00434210(local_3c,abStack_2c);
            FUN_004061c0((undefined4 *)abStack_2c);
            pcStack_20 = local_3c;
            param_4 = (HMENU)((uint)param_4 & 0xffffff);
            iStack_1c = (int)&param_4 + 3;
            ppHStack_58 = &param_3;
            uStack_60 = CONCAT44(iStack_1c,pcStack_20);
            pppuStack_40 = &ppuStack_64;
            ppuStack_64 = &PTR_LAB_0048ef20;
            local_8 = CONCAT31(local_8._1_3_,5);
            FUN_0040f7a0(DAT_004a2458,(int *)pppuStack_40);
            FUN_0040fe40((int *)&ppuStack_64);
            bVar2 = param_4._3_1_ != '\0';
            FUN_00434820(local_3c);
            ExceptionList = local_10;
            return bVar2 + 1;
          }
          FUN_00434820(local_3c);
          ExceptionList = local_10;
          return 0xfffffffb;
        }
      }
      FUN_00434820(local_3c);
      ExceptionList = local_10;
      return 0xfffffffc;
    }
    return 0xfffffffe;
  case 0x4e:
    if (param_4[2].unused == -0x209) {
      ExceptionList = &local_10;
      local_14 = &stack0xffffff8c;
      bVar2 = FUN_004063a0((HWND)param_4->unused);
      ExceptionList = local_10;
      return (uint)bVar2;
    }
    goto LAB_00423d59;
  case 0x117:
    param_4 = (HMENU)param_3;
    ExceptionList = &local_10;
    local_14 = &stack0xffffff8c;
    FUN_00431ea0(&param_4);
    pHVar1 = param_4;
    iVar4 = GetMenuItemCount(param_4);
    if (iVar4 == 0) {
      FUN_0041dfe0(pHVar1);
    }
    break;
  case 0x11f:
    ExceptionList = &local_10;
    local_14 = &stack0xffffff8c;
    uVar5 = FUN_0041eb10((uint)param_3,param_4);
    ExceptionList = local_10;
    return uVar5;
  }
  ExceptionList = local_10;
  return 0;
}


