// FUN_00430200 @ 00430200 size=399 callers=1

undefined4 FUN_00430200(HWND param_1,char *param_2)

{
  undefined4 uVar1;
  uint uVar2;
  bool bVar3;
  char cVar4;
  LPWSTR pWVar5;
  int iVar6;
  undefined4 *puVar7;
  char *pcVar8;
  bool bVar9;
  void *local_78 [5];
  uint local_64;
  void *local_60 [5];
  uint local_4c;
  void *local_48 [5];
  uint local_34;
  void *local_30 [2];
  char local_28 [8];
  undefined4 local_20;
  uint local_1c;
  int *local_18;
  int *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047d5b8;
  local_10 = ExceptionList;
  bVar9 = false;
  local_14 = (int *)0x0;
  ExceptionList = &local_10;
  cVar4 = FUN_00409750(param_1);
  if (cVar4 != '\0') {
    pWVar5 = FUN_00404790((LPWSTR)local_60,param_1,1,'\0');
    bVar9 = true;
    bVar3 = true;
    if (*(int *)(pWVar5 + 8) != 0) goto LAB_00430253;
  }
  bVar3 = false;
LAB_00430253:
  if ((bVar9) && (7 < local_4c)) {
    FUN_00402430(local_60[0],local_4c + 1,2);
  }
  if (bVar3) {
    FUN_004057a0(local_48,param_1);
    local_8 = 0;
    local_1c = 0xf;
    local_20 = 0;
    local_30[0] = (void *)((uint)local_30[0] & 0xffffff00);
    FUN_0043ade0(local_30,local_48,0,0xffffffff);
    if (*param_2 == '\x01') {
      FUN_004437f0(*(void **)(param_2 + 8),(int *)&local_18,(byte *)local_30);
      iVar6 = FUN_00447a70(local_18,local_14);
    }
    else {
      iVar6 = 0;
    }
    if (0xf < local_1c) {
      FUN_00402430(local_30[0],local_1c + 1,1);
    }
    if (iVar6 == 0) {
      puVar7 = (undefined4 *)FUN_0040d260((undefined1 *)local_78,(byte *)local_48);
      local_8._0_1_ = 1;
      FUN_00440c80(local_28,puVar7);
      local_8 = CONCAT31(local_8._1_3_,2);
      pcVar8 = FUN_00434440(param_2,(byte *)local_48);
      cVar4 = *pcVar8;
      *pcVar8 = local_28[0];
      uVar1 = *(undefined4 *)(pcVar8 + 8);
      uVar2 = *(uint *)(pcVar8 + 0xc);
      *(undefined4 *)(pcVar8 + 8) = local_20;
      *(uint *)(pcVar8 + 0xc) = local_1c;
      local_28[0] = cVar4;
      local_20 = uVar1;
      local_1c = uVar2;
      FUN_00434820(local_28);
      if (0xf < local_64) {
        FUN_00402430(local_78[0],local_64 + 1,1);
      }
    }
    if (0xf < local_34) {
      FUN_00402430(local_48[0],local_34 + 1,1);
    }
  }
  ExceptionList = local_10;
  return 1;
}


