// FUN_004229b0 @ 004229b0 size=787 callers=2

void __fastcall FUN_004229b0(int param_1,undefined4 *param_2)

{
  int *piVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  byte *pbVar4;
  char *pcVar5;
  void *pvVar6;
  BOOL BVar7;
  int *piVar8;
  undefined4 *in_stack_fffffec0;
  undefined4 local_114 [24];
  void *local_b4 [5];
  uint local_a0;
  undefined4 local_9c;
  undefined4 uStack_98;
  undefined4 uStack_94;
  undefined4 uStack_90;
  char local_8c [20];
  undefined4 *local_78;
  void *local_74 [4];
  undefined4 local_64;
  uint local_60;
  undefined4 *local_5c;
  int *local_58;
  void *local_54 [4];
  undefined4 local_44;
  uint local_40;
  char local_3c [8];
  ulonglong local_34;
  void *local_2c;
  int local_28;
  int local_24;
  undefined4 *local_20;
  undefined1 *local_1c;
  undefined4 *local_18;
  undefined1 local_11;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047bd82;
  local_10 = ExceptionList;
  if (*(int *)(param_1 + 8) != 0) {
    local_40 = 7;
    local_44 = 0;
    local_54[0] = (void *)((uint)local_54[0] & 0xffff0000);
    ExceptionList = &local_10;
    local_5c = param_2;
    FUN_0043a650(local_54,(uint *)&DAT_0048d62c,3);
    local_8 = 0;
    puVar2 = (undefined4 *)FUN_0040abb0(local_54,(undefined4 *)local_3c);
    local_9c = *puVar2;
    uStack_98 = puVar2[1];
    uStack_94 = puVar2[2];
    uStack_90 = puVar2[3];
    local_8 = 0xffffffff;
    if (7 < local_40) {
      FUN_00402430(local_54[0],local_40 + 1,2);
    }
    FUN_00434a40(local_8c,(char *)0x0,(char *)0x0);
    local_8 = 1;
    piVar1 = *(int **)(param_1 + 4);
    piVar8 = (int *)**(int **)(param_1 + 4);
    if (piVar8 != piVar1) {
      local_1c = &local_11;
      do {
        local_58 = FUN_0040aa70((int *)local_b4,piVar8[3],&local_9c);
        local_8._0_1_ = 2;
        local_34 = 0;
        local_3c[0] = '\x03';
        puVar2 = operator_new(0x18);
        local_8._0_1_ = 4;
        local_78 = puVar2;
        local_20 = puVar2;
        if (puVar2 != (undefined4 *)0x0) {
          puVar2[5] = 0xf;
          puVar2[4] = 0;
          puVar3 = puVar2;
          if (0xf < (uint)puVar2[5]) {
            puVar3 = (undefined4 *)*puVar2;
          }
          *(undefined1 *)puVar3 = 0;
          local_18 = puVar2;
          FUN_0043ade0(puVar2,local_58,0,0xffffffff);
        }
        local_18 = (undefined4 *)0x0;
        local_34 = ZEXT48(puVar2);
        local_8._0_1_ = 5;
        pbVar4 = FUN_00403340((undefined1 *)local_54,piVar8[2]);
        local_8 = CONCAT31(local_8._1_3_,6);
        pcVar5 = FUN_00434440(local_8c,pbVar4);
        local_3c[0] = *pcVar5;
        *pcVar5 = '\x03';
        local_34 = *(ulonglong *)(pcVar5 + 8);
        *(undefined4 **)(pcVar5 + 8) = puVar2;
        *(undefined4 **)(pcVar5 + 0xc) = local_18;
        FUN_00434820(local_3c);
        if (0xf < local_40) {
          FUN_00402430(local_54[0],local_40 + 1,1);
        }
        local_8 = CONCAT31(local_8._1_3_,1);
        local_40 = 0xf;
        local_44 = 0;
        local_54[0] = (void *)((uint)local_54[0] & 0xffffff00);
        if (0xf < local_a0) {
          FUN_00402430(local_b4[0],local_a0 + 1,1);
        }
        piVar8 = (int *)*piVar8;
      } while (piVar8 != piVar1);
    }
    puVar2 = local_5c;
    FUN_00404910((int *)&stack0xfffffec0);
    pvVar6 = FUN_00403a70(local_114,in_stack_fffffec0);
    local_8._0_1_ = 8;
    FUN_00441f50((undefined2 *)local_74,pvVar6,puVar2);
    local_8._0_1_ = 10;
    FUN_00403c20(local_114);
    FUN_00433cb0((uint *)&local_2c,local_8c);
    local_8 = CONCAT31(local_8._1_3_,0xb);
    puVar2 = FUN_00405440(&local_1c,(LPCWSTR)local_74,'W',0);
    if (((HANDLE)*puVar2 != (HANDLE)0x0) &&
       (BVar7 = WriteFile((HANDLE)*puVar2,local_2c,local_28 - (int)local_2c,(LPDWORD)&local_20,
                          (LPOVERLAPPED)0x0), BVar7 == 0)) {
      GetLastError();
    }
    if (local_1c != (undefined1 *)0x0) {
      CloseHandle(local_1c);
    }
    if (local_2c != (void *)0x0) {
      pvVar6 = local_2c;
      if (0xfff < (uint)(local_24 - (int)local_2c)) {
        if (((uint)local_2c & 0x1f) != 0) {
                    /* WARNING: Subroutine does not return */
          FUN_00465fb2();
        }
        pvVar6 = *(void **)((int)local_2c + -4);
        if (local_2c <= pvVar6) {
                    /* WARNING: Subroutine does not return */
          FUN_00465fb2();
        }
        if ((uint)((int)local_2c - (int)pvVar6) < 4) {
                    /* WARNING: Subroutine does not return */
          FUN_00465fb2();
        }
        if (0x23 < (uint)((int)local_2c - (int)pvVar6)) {
                    /* WARNING: Subroutine does not return */
          FUN_00465fb2();
        }
      }
      FID_conflict__free(pvVar6);
      local_2c = (void *)0x0;
      local_28 = 0;
      local_24 = 0;
    }
    if (7 < local_60) {
      FUN_00402430(local_74[0],local_60 + 1,2);
    }
    local_60 = 7;
    local_64 = 0;
    local_74[0] = (void *)((uint)local_74[0] & 0xffff0000);
    FUN_00434820(local_8c);
  }
  ExceptionList = local_10;
  return;
}


