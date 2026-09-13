// FUN_00410a10 @ 00410a10 size=1430 callers=1

/* WARNING: Removing unreachable block (ram,0x00410f46) */

void FUN_00410a10(void)

{
  undefined8 uVar1;
  char cVar2;
  undefined4 uVar3;
  char *pcVar4;
  undefined1 *puVar5;
  LPCWSTR pWVar6;
  undefined4 *puVar7;
  DWORD DVar8;
  undefined4 *this;
  undefined4 *puVar9;
  byte *pbVar10;
  void *this_00;
  uint uVar11;
  undefined1 uVar12;
  void *in_stack_fffffec4;
  void *local_118 [5];
  uint local_104;
  void *local_100 [4];
  undefined4 local_f0;
  uint local_ec;
  void *local_e8 [4];
  undefined4 local_d8;
  uint local_d4;
  char local_d0 [16];
  char local_c0 [16];
  HANDLE local_b0;
  undefined4 local_ac;
  char local_a8 [16];
  char local_98 [16];
  void *local_88;
  undefined1 *puStack_84;
  undefined4 local_80;
  int local_7c [4];
  undefined4 *local_6c;
  uint local_68;
  DWORD local_64;
  DWORD local_60;
  uint local_5c;
  char local_58 [8];
  undefined8 local_50;
  char local_48;
  undefined8 local_40;
  undefined8 local_38;
  undefined4 *local_30;
  char *local_2c;
  int local_28;
  int local_24;
  int local_20;
  char local_1c [8];
  undefined8 local_14;
  undefined1 local_9;
  uint local_8;
  
  local_80 = 0xffffffff;
  puStack_84 = &LAB_0047a8c4;
  local_88 = ExceptionList;
  uVar11 = 0;
  local_8 = 0;
  ExceptionList = &local_88;
  FUN_00434a40(local_c0,(char *)0x0,(char *)0x0);
  local_80 = 0;
  FUN_004108c0(local_98);
  local_80._0_1_ = 1;
  if (local_98[0] == '\x01') {
    FUN_00434120(local_98,&local_2c);
    FUN_004340a0(this_00,local_7c);
    uVar3 = FUN_004383a0(&local_2c,local_7c);
    cVar2 = (char)uVar3;
    while (cVar2 == '\0') {
      pcVar4 = FUN_00433bc0(&local_2c);
      FUN_004536b0(pcVar4,&local_64);
      puVar5 = FUN_00433b30(&local_2c,(undefined1 *)local_118);
      local_80._0_1_ = 2;
      if (*(int *)(puVar5 + 0x10) == 0) {
        pWVar6 = (LPCWSTR)FUN_00404910((int *)local_100);
        local_80 = CONCAT31(local_80._1_3_,3);
        local_8 = uVar11 | 1;
        puVar7 = FUN_00405440(&local_b0,pWVar6,'P',0);
        uVar11 = uVar11 | 3;
        local_8 = uVar11;
        DVar8 = GetFileSize((HANDLE)*puVar7,(LPDWORD)0x0);
      }
      else {
        local_58[0] = '\0';
        local_50 = 0;
        FUN_00451110(local_58,(uint *)&DAT_0048d074);
        local_80 = 5;
        local_5c = uVar11 | 4;
        local_8 = local_5c;
        puVar7 = (undefined4 *)FUN_00433b30(&local_2c,(undefined1 *)local_e8);
        local_80 = 6;
        local_8 = uVar11 | 0xc;
        local_40 = 0;
        local_48 = '\x03';
        this = operator_new(0x18);
        local_38 = CONCAT44(this,&local_9);
        local_80 = 8;
        local_6c = this;
        local_30 = this;
        if (this != (undefined4 *)0x0) {
          this[5] = 0xf;
          this[4] = 0;
          puVar9 = this;
          if (0xf < (uint)this[5]) {
            puVar9 = (undefined4 *)*this;
          }
          *(undefined1 *)puVar9 = 0;
          FUN_0043ade0(this,puVar7,0,0xffffffff);
        }
        uVar11 = (local_5c | 0x18) & 0xfffffff7;
        local_38 = local_38 & 0xffffffff;
        local_40 = CONCAT44(local_ac,this);
        if (0xf < local_d4) {
          FUN_00402430(local_e8[0],local_d4 + 1,1);
        }
        local_d4 = 0xf;
        local_d8 = 0;
        local_e8[0] = (void *)((uint)local_e8[0] & 0xffffff00);
        local_80 = 9;
        local_8 = uVar11 | 0x20;
        FUN_00434b50(local_a8,local_58,(char *)&local_38,'\x01','\x02');
        local_80 = 0xb;
        uVar11 = (uVar11 | 0x60) & 0xffffffdf;
        local_8 = uVar11;
        _eh_vector_destructor_iterator_(local_58,0x10,2,FUN_00434820);
        local_30 = (undefined4 *)&stack0xfffffecc;
        local_8 = uVar11 | 0x80;
        FUN_00451040(&stack0xfffffecc,0xffffffff);
        local_80 = 0xd;
        FUN_00434b50(&stack0xfffffebc,local_a8,local_98,'\x01','\x02');
        local_80 = CONCAT31(local_80._1_3_,0xc);
        pcVar4 = FUN_00408a00(local_d0,0x2fd);
        uVar11 = uVar11 | 0x180;
        local_80 = 0xe;
        local_8 = uVar11;
        FUN_00453810(pcVar4,&local_60);
        DVar8 = local_60;
      }
      if ((uVar11 & 0x100) != 0) {
        uVar11 = uVar11 & 0xfffffeff;
        local_8 = uVar11;
        FUN_00434820(local_d0);
      }
      local_80 = 4;
      if ((char)uVar11 < '\0') {
        uVar11 = uVar11 & 0xffffff7f;
        local_8 = uVar11;
        _eh_vector_destructor_iterator_(local_a8,0x10,1,FUN_00434820);
      }
      if (((uVar11 & 2) != 0) &&
         (uVar11 = uVar11 & 0xfffffffd, local_8 = uVar11, local_b0 != (HANDLE)0x0)) {
        CloseHandle(local_b0);
      }
      local_80 = 2;
      if ((uVar11 & 1) != 0) {
        uVar11 = uVar11 & 0xfffffffe;
        local_8 = uVar11;
        if (7 < local_ec) {
          FUN_00402430(local_100[0],local_ec + 1,2);
        }
        local_ec = 7;
        local_f0 = 0;
        local_100[0] = (void *)((uint)local_100[0] & 0xffff0000);
      }
      local_80._0_1_ = 1;
      if (0xf < local_104) {
        FUN_00402430(local_118[0],local_104 + 1,1);
      }
      if (DVar8 == 0xffffffff) goto LAB_00410f84;
      if (DVar8 != local_64) {
        local_1c[0] = '\0';
        local_14 = 0;
        FUN_00450f50(local_1c,DVar8 - local_64);
        local_80._0_1_ = 0xf;
        pbVar10 = FUN_00433b30(&local_2c,(undefined1 *)local_118);
        local_80._0_1_ = 0x10;
        pcVar4 = FUN_00434440(local_c0,pbVar10);
        cVar2 = *pcVar4;
        *pcVar4 = local_1c[0];
        uVar1 = *(undefined8 *)(pcVar4 + 8);
        *(undefined4 *)(pcVar4 + 8) = (undefined4)local_14;
        *(undefined4 *)(pcVar4 + 0xc) = local_14._4_4_;
        local_1c[0] = cVar2;
        local_14 = uVar1;
        FUN_00434820(local_1c);
        local_80._0_1_ = 1;
        if (0xf < local_104) {
          FUN_00402430(local_118[0],local_104 + 1,1);
        }
      }
      if (*local_2c == '\x01') {
        local_68 = local_68 & 0xffffff00;
        FUN_00447660(&local_28);
      }
      else if (*local_2c == '\x02') {
        local_24 = local_24 + 0x10;
      }
      else {
        local_20 = local_20 + 1;
      }
      FUN_004340a0(local_98,local_7c);
      uVar3 = FUN_004383a0(&local_2c,local_7c);
      cVar2 = (char)uVar3;
    }
  }
  local_58[0] = '\0';
  local_50 = 0;
  FUN_00451110(local_58,(uint *)"result");
  local_80 = CONCAT31(local_80._1_3_,0x12);
  if (local_98[0] == '\x01') {
    pcVar4 = FUN_00434940(local_d0,local_c0);
    uVar11 = uVar11 | 0x200;
  }
  else {
    local_1c[0] = '\0';
    local_14 = 0;
    FUN_00450f70(local_1c,(uint *)"NO INTEGRITY MAP");
    pcVar4 = local_1c;
    uVar11 = uVar11 | 0x400;
  }
  local_48 = *pcVar4;
  local_40 = *(undefined8 *)(pcVar4 + 8);
  local_38 = 0;
  pcVar4[8] = '\0';
  pcVar4[9] = '\0';
  pcVar4[10] = '\0';
  pcVar4[0xb] = '\0';
  *pcVar4 = '\0';
  pcVar4[0xc] = '\0';
  pcVar4[0xd] = '\0';
  pcVar4[0xe] = '\0';
  pcVar4[0xf] = '\0';
  if ((uVar11 & 0x400) != 0) {
    uVar11 = uVar11 & 0xfffffbff;
    FUN_00434820(local_1c);
  }
  local_80 = 0x12;
  if ((uVar11 & 0x200) != 0) {
    FUN_00434820(local_d0);
  }
  local_80._0_1_ = 0x14;
  FUN_00434b50(local_7c,local_58,(char *)&local_38,'\x01','\x02');
  local_80._0_1_ = 0x16;
  _eh_vector_destructor_iterator_(local_58,0x10,2,FUN_00434820);
  local_80._0_1_ = 0x17;
  FUN_00434b50(local_a8,(char *)local_7c,(char *)&local_6c,'\x01','\x02');
  local_80._0_1_ = 0x18;
                    /* WARNING: Ignoring partial resolution of indirect */
  uVar12 = 0;
  FUN_0043ace0(&stack0xfffffec4,(uint *)&DAT_0048d418,4);
  FUN_00408c90(local_a8,in_stack_fffffec4);
  FUN_00434820(local_a8);
  local_80._0_1_ = 1;
  _eh_vector_destructor_iterator_(local_7c,0x10,1,FUN_00434820);
LAB_00410f84:
  FUN_00434820(local_98);
  FUN_00434820(local_c0);
  ExceptionList = local_88;
  return;
}


