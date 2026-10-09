// FUN_00445600 @ 00445600 size=852 callers=2

/* WARNING: Removing unreachable block (ram,0x004457fa) */
/* WARNING: Removing unreachable block (ram,0x00445813) */

undefined4 * __thiscall FUN_00445600(void *this,undefined4 *param_1)

{
  bool bVar1;
  uint uVar2;
  undefined1 *puVar3;
  uint uVar4;
  ulong uVar5;
  char *pcVar6;
  undefined4 *puVar7;
  int iVar8;
  undefined1 *_Buf;
  undefined1 *puVar9;
  undefined4 local_38;
  undefined1 local_34;
  int local_2c;
  undefined4 local_28;
  undefined4 local_24;
  ulong local_20;
  undefined4 local_1c;
  void *local_18;
  undefined1 local_11;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  puStack_c = &LAB_0047e429;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  param_1[4] = 0;
  param_1[5] = 0;
  param_1[5] = 0xf;
  param_1[4] = 0;
  puVar7 = param_1;
  if (0xf < (uint)param_1[5]) {
    puVar7 = (undefined4 *)*param_1;
  }
  *(undefined1 *)puVar7 = 0;
  local_8 = 0;
  uVar2 = (*(int *)((int)this + 0x40) - *(int *)((int)this + 0x38)) - 2;
  local_1c = 1;
  local_18 = this;
  if (((uint)param_1[4] <= uVar2) && (param_1[5] != uVar2)) {
    iVar8 = param_1[4];
    bVar1 = FUN_0043de20(param_1,uVar2,'\x01');
    if (bVar1) {
      param_1[4] = iVar8;
      puVar7 = param_1;
      if (0xf < (uint)param_1[5]) {
        puVar7 = (undefined4 *)*param_1;
      }
      *(undefined1 *)((int)puVar7 + iVar8) = 0;
    }
  }
  iVar8 = *(int *)((int)this + 0x40);
  _Buf = (undefined1 *)(*(int *)((int)this + 0x38) + 1);
  if (_Buf < (undefined1 *)(iVar8 - 1U)) {
    do {
      puVar3 = _memchr(_Buf,0x5c,(iVar8 + -1) - (int)_Buf);
      puVar9 = (undefined1 *)(iVar8 + -1);
      if (puVar3 != (undefined1 *)0x0) {
        puVar9 = puVar3;
      }
      if (puVar9 == _Buf) {
        puVar9 = _Buf + 1;
        switch(_Buf[1]) {
        case 0x22:
          FUN_00444450(param_1,(uint *)&DAT_0048e078);
          break;
        case 0x2f:
          FUN_00444450(param_1,(uint *)&DAT_0048df9c);
          break;
        case 0x5c:
          FUN_00444450(param_1,(uint *)&DAT_0048e074);
          break;
        case 0x62:
          FUN_00444450(param_1,(uint *)&DAT_0048e064);
          break;
        case 0x66:
          FUN_00444450(param_1,(uint *)&DAT_0048e068);
          break;
        case 0x6e:
          FUN_00444450(param_1,(uint *)&DAT_0048e06c);
          break;
        case 0x72:
          FUN_00444450(param_1,(uint *)&DAT_0048e070);
          break;
        case 0x74:
          FUN_00444450(param_1,(uint *)&DAT_0048e060);
          break;
        case 0x75:
          local_38 = *(undefined4 *)(_Buf + 2);
          local_24 = 0xf;
          local_28 = 4;
          local_34 = 0;
          uVar5 = _strtoul((char *)&local_38,(char **)0x0,0x10);
          local_20 = uVar5;
          FUN_004061c0(&local_38);
          if (uVar5 - 0xd800 < 0x400) {
            if (((*(char **)((int)local_18 + 0x44) <= _Buf + 7) || (_Buf[6] != '\\')) ||
               (_Buf[7] != 'u')) {
              pcVar6 = "missing low surrogate";
LAB_00445937:
              FUN_00402500(&local_2c,pcVar6);
                    /* WARNING: Subroutine does not return */
              __CxxThrowException_8(&local_2c,&DAT_00499edc);
            }
            pcVar6 = FUN_00435630(&local_38,(uint *)(_Buf + 8),4);
            if (0xf < *(uint *)(pcVar6 + 0x14)) {
              pcVar6 = *(char **)pcVar6;
            }
            uVar5 = _strtoul(pcVar6,(char **)0x0,0x10);
            FUN_004061c0(&local_38);
            puVar7 = FUN_004464d0(&local_38,local_20,uVar5);
            local_8 = 1;
            FUN_0043b0c0(param_1,puVar7,0,0xffffffff);
            local_8 = local_8 & 0xffffff00;
            FUN_004061c0(&local_38);
            puVar9 = _Buf + 0xb;
          }
          else {
            if ((0xdbff < uVar5) && (uVar5 < 0xe000)) {
              pcVar6 = "missing high surrogate";
              goto LAB_00445937;
            }
            puVar7 = FUN_004464d0(&local_38,uVar5,0);
            local_8 = 2;
            FUN_0043b0c0(param_1,puVar7,0,0xffffffff);
            local_8 = local_8 & 0xffffff00;
            FUN_004061c0(&local_38);
            puVar9 = _Buf + 5;
          }
        }
      }
      else {
        for (; _Buf < puVar9; _Buf = _Buf + 1) {
          local_11 = *_Buf;
          uVar2 = param_1[5];
          if (param_1[4] == uVar2) {
            uVar4 = param_1[4] + 1;
            if (uVar4 == 0xffffffff) {
                    /* WARNING: Subroutine does not return */
              FUN_00458ec4("string too long");
            }
            if (uVar2 < uVar4) {
              FUN_0043f5f0(param_1,uVar4);
            }
            else if (uVar4 == 0) {
              param_1[4] = 0;
              puVar7 = param_1;
              if (0xf < uVar2) {
                puVar7 = (undefined4 *)*param_1;
              }
              *(undefined1 *)puVar7 = 0;
            }
          }
          puVar7 = param_1;
          if (0xf < (uint)param_1[5]) {
            puVar7 = (undefined4 *)*param_1;
          }
          *(undefined1 *)((int)puVar7 + param_1[4]) = local_11;
          param_1[4] = param_1[4] + 1;
          *(undefined1 *)(param_1[4] + (int)puVar7) = 0;
        }
        puVar9 = puVar9 + -1;
      }
      _Buf = puVar9 + 1;
      iVar8 = *(int *)((int)local_18 + 0x40);
    } while (_Buf < (undefined1 *)(iVar8 - 1U));
  }
  ExceptionList = local_10;
  return param_1;
}


