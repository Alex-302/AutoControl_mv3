// FUN_00439500 @ 00439500 size=1622 callers=4

void __fastcall FUN_00439500(undefined1 *param_1,uint *param_2)

{
  uint uVar1;
  int *piVar2;
  int *piVar3;
  uint uVar4;
  undefined4 *puVar5;
  undefined1 *puVar6;
  undefined4 *puVar7;
  undefined1 *puVar8;
  int iVar9;
  char local_2c [16];
  int local_1c;
  int *local_18;
  char local_11;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047a018;
  local_10 = ExceptionList;
  switch(*param_1) {
  case 0:
    local_11 = -10;
    ExceptionList = &local_10;
    FUN_00434cd0(param_2,&local_11);
    ExceptionList = local_10;
    return;
  case 1:
    local_18 = *(int **)(*(int *)(param_1 + 8) + 4);
    if (local_18 < (int *)0x18) {
      local_11 = (char)local_18 + -0x60;
      ExceptionList = &local_10;
      FUN_00434cd0(param_2,&local_11);
    }
    else {
      if (local_18 < (int *)0x100) {
        local_11 = -0x48;
        ExceptionList = &local_10;
        FUN_00434cd0(param_2,&local_11);
        iVar9 = 0;
      }
      else if (local_18 < (int *)0x10000) {
        local_11 = -0x47;
        ExceptionList = &local_10;
        FUN_00434cd0(param_2,&local_11);
        iVar9 = 1;
      }
      else {
        local_11 = -0x46;
        ExceptionList = &local_10;
        FUN_00434cd0(param_2,&local_11);
        iVar9 = 3;
      }
      FUN_00443390(iVar9);
    }
    piVar2 = (int *)**(int **)(param_1 + 8);
    piVar3 = (int *)*piVar2;
    while (piVar3 != piVar2) {
      local_18 = piVar3;
      FUN_00440c80(local_2c,piVar3 + 4);
      local_8 = 0;
      FUN_00439500(local_2c,param_2);
      local_8 = 0xffffffff;
      FUN_00434820(local_2c);
      FUN_00439500((undefined1 *)(piVar3 + 10),param_2);
      FUN_0043ed80((int *)&local_18);
      piVar3 = local_18;
    }
    break;
  case 2:
    local_18 = (int *)((*(int **)(param_1 + 8))[1] - **(int **)(param_1 + 8) >> 4);
    if (local_18 < (int *)0x18) {
      local_11 = (char)local_18 + -0x80;
      ExceptionList = &local_10;
      FUN_00434cd0(param_2,&local_11);
    }
    else {
      if (local_18 < (int *)0x100) {
        local_11 = -0x68;
        ExceptionList = &local_10;
        FUN_00434cd0(param_2,&local_11);
        iVar9 = 0;
      }
      else if (local_18 < (int *)0x10000) {
        local_11 = -0x67;
        ExceptionList = &local_10;
        FUN_00434cd0(param_2,&local_11);
        iVar9 = 1;
      }
      else {
        local_11 = -0x66;
        ExceptionList = &local_10;
        FUN_00434cd0(param_2,&local_11);
        iVar9 = 3;
      }
      FUN_00443390(iVar9);
    }
    puVar6 = (undefined1 *)(*(int **)(param_1 + 8))[1];
    puVar8 = (undefined1 *)**(int **)(param_1 + 8);
    if (puVar8 != puVar6) {
      do {
        FUN_00439500(puVar8,param_2);
        puVar8 = puVar8 + 0x10;
      } while (puVar8 != puVar6);
      ExceptionList = local_10;
      return;
    }
    break;
  case 3:
    local_18 = *(int **)(*(int *)(param_1 + 8) + 0x10);
    if (local_18 < (int *)0x18) {
      local_11 = (char)local_18 + '`';
      ExceptionList = &local_10;
      FUN_00434cd0(param_2,&local_11);
    }
    else {
      if (local_18 < (int *)0x100) {
        local_11 = 'x';
        ExceptionList = &local_10;
        FUN_00434cd0(param_2,&local_11);
        iVar9 = 0;
      }
      else if (local_18 < (int *)0x10000) {
        local_11 = 'y';
        ExceptionList = &local_10;
        FUN_00434cd0(param_2,&local_11);
        iVar9 = 1;
      }
      else {
        local_11 = 'z';
        ExceptionList = &local_10;
        FUN_00434cd0(param_2,&local_11);
        iVar9 = 3;
      }
      FUN_00443390(iVar9);
    }
    puVar5 = *(undefined4 **)(param_1 + 8);
    puVar7 = puVar5;
    if (0xf < (uint)puVar5[5]) {
      puVar7 = (undefined4 *)*puVar5;
    }
    puVar5 = (undefined4 *)FUN_004354a0(puVar5,&local_1c);
    local_18 = (int *)((uint)local_18 & 0xffffff00);
    FUN_00453020(&local_18,(undefined1 *)puVar7,(undefined1 *)*puVar5,param_2);
    ExceptionList = local_10;
    return;
  case 4:
    uVar4 = (uint)(byte)((param_1[8] != '\0') - 0xc);
    goto LAB_0043955e;
  case 5:
    uVar4 = *(uint *)(param_1 + 0xc);
    uVar1 = *(uint *)(param_1 + 8);
    if (-1 < (int)uVar4) {
      if (((int)uVar4 < 1) && ((int)uVar4 < 1)) {
        if (((int)uVar4 < 0) || (uVar1 < 0x18)) {
          ExceptionList = &local_10;
          FUN_00443150(param_2,0);
          ExceptionList = local_10;
          return;
        }
        if ((int)uVar4 < 1) {
          if (((int)uVar4 < 0) || (uVar1 < 0x100)) {
            local_11 = '\x18';
            ExceptionList = &local_10;
            FUN_00434cd0(param_2,&local_11);
            FUN_00443150(param_2,0);
            ExceptionList = local_10;
            return;
          }
          if ((int)uVar4 < 1) {
            if (((int)uVar4 < 0) || (uVar1 < 0x10000)) {
              local_11 = '\x19';
              ExceptionList = &local_10;
              FUN_00434cd0(param_2,&local_11);
              FUN_00443150(param_2,1);
              ExceptionList = local_10;
              return;
            }
            if ((int)uVar4 < 1) {
              local_11 = '\x1a';
              ExceptionList = &local_10;
              FUN_00434cd0(param_2,&local_11);
              FUN_00443150(param_2,3);
              ExceptionList = local_10;
              return;
            }
          }
        }
      }
      local_11 = '\x1b';
      ExceptionList = &local_10;
      FUN_00434cd0(param_2,&local_11);
      FUN_00443150(param_2,7);
      ExceptionList = local_10;
      return;
    }
    local_18 = (int *)~uVar1;
    if ((-2 < (int)uVar4) && ((uVar4 < 0x80000000 || (0xffffffe7 < uVar1)))) {
      local_11 = (char)local_18 + ' ';
      ExceptionList = &local_10;
      FUN_00434cd0(param_2,&local_11);
      ExceptionList = local_10;
      return;
    }
    if (-2 < (int)uVar4) {
      if ((-1 < (int)uVar4) || (local_18 < (int *)0x100)) {
        local_11 = '8';
        ExceptionList = &local_10;
        FUN_00434cd0(param_2,&local_11);
        FUN_00443150(param_2,0);
        ExceptionList = local_10;
        return;
      }
      if (-2 < (int)uVar4) {
        if ((-1 < (int)uVar4) || (local_18 < (int *)0x10000)) {
          local_11 = '9';
          ExceptionList = &local_10;
          FUN_00434cd0(param_2,&local_11);
          FUN_00443150(param_2,1);
          ExceptionList = local_10;
          return;
        }
        if (-2 < (int)uVar4) {
          local_11 = ':';
          ExceptionList = &local_10;
          FUN_00434cd0(param_2,&local_11);
          FUN_00443150(param_2,3);
          ExceptionList = local_10;
          return;
        }
      }
    }
    local_11 = ';';
    ExceptionList = &local_10;
    FUN_00434cd0(param_2,&local_11);
    FUN_00443150(param_2,7);
    ExceptionList = local_10;
    return;
  case 6:
    uVar4 = *(uint *)(param_1 + 8);
    if (*(int *)(param_1 + 0xc) != 0) {
      local_11 = '\x1b';
      ExceptionList = &local_10;
      FUN_00434cd0(param_2,&local_11);
      FUN_00443270(param_2,7);
      ExceptionList = local_10;
      return;
    }
    if (0x17 < uVar4) {
      if (uVar4 < 0x100) {
        local_11 = '\x18';
        ExceptionList = &local_10;
        FUN_00434cd0(param_2,&local_11);
        FUN_00443270(param_2,0);
        ExceptionList = local_10;
        return;
      }
      if (0xffff < uVar4) {
        local_11 = '\x1a';
        ExceptionList = &local_10;
        FUN_00434cd0(param_2,&local_11);
        FUN_00443270(param_2,3);
        ExceptionList = local_10;
        return;
      }
      local_11 = '\x19';
      ExceptionList = &local_10;
      FUN_00434cd0(param_2,&local_11);
      FUN_00443270(param_2,1);
      ExceptionList = local_10;
      return;
    }
LAB_0043955e:
    local_11 = (char)uVar4;
    ExceptionList = &local_10;
    FUN_00434cd0(param_2,&local_11);
    ExceptionList = local_10;
    return;
  case 7:
    local_11 = -5;
    ExceptionList = &local_10;
    FUN_00434cd0(param_2,&local_11);
    puVar6 = param_1 + 0xf;
    iVar9 = 8;
    do {
      FUN_00434cd0(param_2,puVar6);
      puVar6 = puVar6 + -1;
      iVar9 = iVar9 + -1;
    } while (iVar9 != 0);
    ExceptionList = local_10;
    return;
  }
  ExceptionList = local_10;
  return;
}


