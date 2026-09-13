// FUN_004495b0 @ 004495b0 size=458 callers=1

int * __fastcall FUN_004495b0(int *param_1,undefined4 *param_2)

{
  code *pcVar1;
  uint uVar2;
  undefined4 *puVar3;
  int *piVar4;
  int iVar5;
  byte *pbVar6;
  void *this;
  uint uVar7;
  void *pvStack_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047e5c6;
  pvStack_10 = ExceptionList;
  uVar7 = 0;
  piVar4 = *(int **)(*(int *)(*param_1 + 4) + 0x38 + (int)param_1);
  ExceptionList = &pvStack_10;
  if ((piVar4 != (int *)0x0) &&
     (pcVar1 = *(code **)(*piVar4 + 4), ExceptionList = &pvStack_10, pcVar1 != guard_check_icall)) {
    ExceptionList = &pvStack_10;
    (*pcVar1)();
  }
  local_8 = 0;
  uVar2 = FUN_0044db40(param_1);
  if ((char)uVar2 == '\0') {
    uVar7 = 2;
  }
  else {
    local_8 = 2;
    param_2[4] = 0;
    puVar3 = param_2;
    if (0xf < (uint)param_2[5]) {
      puVar3 = (undefined4 *)*param_2;
    }
    *(undefined1 *)puVar3 = 0;
    piVar4 = *(int **)(*(int *)(*param_1 + 4) + 0x38 + (int)param_1);
    if ((*(byte **)piVar4[7] == (byte *)0x0) || (*(int *)piVar4[0xb] < 1)) {
      uVar2 = (**(code **)(*piVar4 + 0x18))();
    }
    else {
      uVar2 = (uint)**(byte **)piVar4[7];
    }
    while( true ) {
      if (uVar2 == 0xffffffff) {
        piVar4 = (int *)FUN_004497aa();
        return piVar4;
      }
      if (uVar2 == 10) break;
      if (0xfffffffd < (uint)param_2[4]) {
        piVar4 = (int *)FUN_004497aa();
        return piVar4;
      }
      FUN_0043aef0(param_2,1,(char)uVar2);
      piVar4 = *(int **)(*(int *)(*param_1 + 4) + 0x38 + (int)param_1);
      if (*(int *)piVar4[7] == 0) {
LAB_00449731:
        uVar2 = FUN_0044d910(piVar4);
        if (uVar2 == 0xffffffff) {
          uVar2 = 0xffffffff;
        }
        else if ((*(byte **)piVar4[7] == (byte *)0x0) || (*(int *)piVar4[0xb] < 1)) {
          uVar2 = (**(code **)(*piVar4 + 0x18))();
        }
        else {
          uVar2 = (uint)**(byte **)piVar4[7];
        }
      }
      else {
        iVar5 = *(int *)piVar4[0xb];
        if (iVar5 < 2) goto LAB_00449731;
        *(int *)piVar4[0xb] = iVar5 + -1;
        pbVar6 = (byte *)(*(int *)piVar4[7] + 1);
        *(int *)piVar4[7] = (int)pbVar6;
        uVar2 = (uint)*pbVar6;
      }
    }
    piVar4 = *(int **)(*(int *)(*param_1 + 4) + 0x38 + (int)param_1);
    if (*(int *)piVar4[7] != 0) {
      iVar5 = *(int *)piVar4[0xb];
      if (0 < iVar5) {
        *(int *)piVar4[0xb] = iVar5 + -1;
        *(int *)piVar4[7] = *(int *)piVar4[7] + 1;
        piVar4 = (int *)FUN_004497aa();
        return piVar4;
      }
    }
    pcVar1 = *(code **)(*piVar4 + 0x1c);
    if (pcVar1 != std::basic_streambuf<char,std::char_traits<char>_>::uflow) {
      (*pcVar1)();
      piVar4 = (int *)FUN_004497aa();
      return piVar4;
    }
    iVar5 = (**(code **)(*piVar4 + 0x18))();
    if (iVar5 != -1) {
      *(int *)piVar4[0xb] = *(int *)piVar4[0xb] + -1;
      *(int *)piVar4[7] = *(int *)piVar4[7] + 1;
      piVar4 = (int *)FUN_004497aa();
      return piVar4;
    }
  }
  local_8 = 1;
  this = (void *)(*(int *)(*param_1 + 4) + (int)param_1);
  if (uVar7 != 0) {
    uVar7 = *(uint *)((int)this + 0xc) | uVar7;
    uVar2 = uVar7 | 4;
    if (*(int *)((int)this + 0x38) != 0) {
      uVar2 = uVar7;
    }
    FUN_00402f00(this,uVar2,'\0');
  }
  local_8 = 4;
  piVar4 = *(int **)(*(int *)(*param_1 + 4) + 0x38 + (int)param_1);
  if ((piVar4 != (int *)0x0) && (pcVar1 = *(code **)(*piVar4 + 8), pcVar1 != guard_check_icall)) {
    (*pcVar1)();
  }
  ExceptionList = pvStack_10;
  return param_1;
}


