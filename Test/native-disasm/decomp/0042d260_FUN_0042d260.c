// FUN_0042d260 @ 0042d260 size=2443 callers=1

/* WARNING: Removing unreachable block (ram,0x0042d3bc) */
/* WARNING: Removing unreachable block (ram,0x0042d68c) */

char * __cdecl FUN_0042d260(char *param_1,void *param_2)

{
  ulonglong uVar1;
  HANDLE hFile;
  undefined1 uVar2;
  char cVar3;
  undefined4 *puVar4;
  BOOL BVar5;
  uint uVar6;
  undefined4 *******pppppppuVar7;
  uint *puVar8;
  char *pcVar9;
  int *piVar10;
  DWORD DVar11;
  uint uVar12;
  int iVar13;
  undefined8 uVar14;
  undefined2 uVar15;
  char cVar16;
  undefined4 uVar17;
  void **ppvVar18;
  undefined4 uVar19;
  undefined4 local_1ec [6];
  WCHAR local_1d4 [24];
  undefined1 local_1a4 [24];
  char local_18c [16];
  undefined1 local_17c [8];
  undefined4 local_174 [2];
  undefined1 local_16c [16];
  char local_15c [16];
  undefined1 local_14c [16];
  undefined4 local_13c;
  undefined4 local_138;
  char local_134 [8];
  undefined8 local_12c;
  undefined1 local_124 [16];
  void *local_114 [5];
  uint local_100;
  void *local_fc [5];
  uint local_e8;
  char local_e4 [8];
  undefined8 local_dc;
  undefined1 local_d4 [8];
  undefined8 local_cc;
  _FILETIME local_c4;
  void *local_bc [4];
  undefined4 local_ac;
  uint local_a8;
  char local_a4 [8];
  undefined8 local_9c;
  undefined1 local_94 [8];
  undefined8 local_8c;
  int local_84;
  undefined1 *local_80;
  char local_7c [8];
  undefined4 local_74;
  undefined4 local_70;
  char local_6c [8];
  undefined4 local_64;
  undefined4 local_60;
  undefined4 ******local_5c [4];
  DWORD local_4c;
  uint local_48;
  void *local_44 [4];
  undefined4 local_34;
  uint local_30;
  undefined8 local_2c;
  undefined8 local_24;
  undefined1 *local_1c;
  uint local_18;
  char local_11;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047d144;
  local_10 = ExceptionList;
  ppvVar18 = local_44;
  uVar12 = 0;
  local_18 = 0;
  ExceptionList = &local_10;
  puVar4 = FUN_00440e70(param_2,(uint *)&DAT_0048d05c);
  FUN_00440d90(puVar4,ppvVar18);
  local_8 = 1;
  FUN_00404640((LPWSTR)local_fc,(LPCSTR)local_44);
  local_8._0_1_ = 3;
  if (0xf < local_30) {
    FUN_00402430(local_44[0],local_30 + 1,1);
  }
  local_30 = 0xf;
  local_34 = 0;
  local_44[0] = (void *)((uint)local_44[0] & 0xffffff00);
  FUN_00405440(&local_2c,(LPCWSTR)local_fc,'R',0);
  local_8._0_1_ = 4;
  uVar2 = (undefined1)local_8;
  local_8._0_1_ = 4;
  hFile = (HANDLE)local_2c;
  DVar11 = local_2c._4_4_;
  if (local_2c._4_4_ == 0) {
    BVar5 = GetFileTime((HANDLE)local_2c,(LPFILETIME)0x0,(LPFILETIME)0x0,&local_c4);
    if (BVar5 != 0) {
      uVar14 = __alldiv(local_c4.dwLowDateTime,local_c4.dwHighDateTime,10000,0);
      iVar13 = (uint)uVar14 + 0xcf499800;
      local_80 = (undefined1 *)
                 (((int)((ulonglong)uVar14 >> 0x20) + -0xa97) - (uint)((uint)uVar14 < 0x30b66800));
      local_84 = iVar13;
      local_1c = local_80;
      FUN_004355e0(local_bc,(uint *)"minModTime");
      local_8._0_1_ = 5;
      local_24 = FUN_004411d0(param_2,local_bc);
      local_8._0_1_ = 4;
      if (0xf < local_a8) {
        FUN_00402430(local_bc[0],local_a8 + 1,1);
      }
      if ((local_24 != 0) && (CONCAT44(local_1c,iVar13) <= (longlong)local_24)) {
        uVar1 = local_2c >> 0x20;
        local_2c = local_2c & 0xffffffffffffff00;
        param_1[8] = '\0';
        param_1[9] = '\0';
        param_1[10] = '\0';
        param_1[0xb] = '\0';
        param_1[0xc] = '\0';
        param_1[0xd] = '\0';
        param_1[0xe] = '\0';
        param_1[0xf] = '\0';
        *(HANDLE *)(param_1 + 8) = (HANDLE)local_2c;
        *param_1 = '\x04';
        *(int *)(param_1 + 0xc) = (int)uVar1;
        if (hFile != (HANDLE)0x0) {
          CloseHandle(hFile);
        }
        FUN_00435170(local_fc);
        ExceptionList = local_10;
        return param_1;
      }
      local_1c = (undefined1 *)GetFileSize(hFile,(LPDWORD)0x0);
      if (local_1c != (undefined1 *)0xffffffff) {
        FUN_004355e0(local_bc,(uint *)"chunk");
        local_8._0_1_ = 6;
        uVar6 = FUN_004409d0(param_2,local_bc,200000);
        local_8._0_1_ = 4;
        FUN_004061c0(local_bc);
        local_a4[0] = '\0';
        local_9c = 0;
        FUN_00451110(local_a4,(uint *)&DAT_0048d638);
        local_94[0] = 0;
        local_8c = 0;
        FUN_00451040(local_94,local_1c);
        local_8._0_1_ = 7;
        FUN_00434b50(local_18c,local_a4,(char *)&local_84,'\x01','\x02');
        local_8._0_1_ = 9;
        _eh_vector_destructor_iterator_(local_a4,0x10,2,FUN_00434820);
        local_e4[0] = '\0';
        local_dc = 0;
        FUN_00451110(local_e4,(uint *)"modTime");
        local_d4[0] = 0;
        local_cc = 0;
        FUN_0044de90(local_d4,&local_84);
        local_8._0_1_ = 10;
        FUN_00434b50(local_17c,local_e4,(char *)&local_c4,'\x01','\x02');
        local_8._0_1_ = 0xc;
        _eh_vector_destructor_iterator_(local_e4,0x10,2,FUN_00434820);
        local_134[0] = '\0';
        local_12c = 0;
        FUN_00451110(local_134,(uint *)"content");
        local_8._0_1_ = 0xd;
        FUN_00410550(local_124,(int *)&local_1c);
        local_8._0_1_ = 0xe;
        FUN_00434b50(local_16c,local_134,(char *)local_114,'\x01','\x02');
        local_8._0_1_ = 0x10;
        _eh_vector_destructor_iterator_(local_134,0x10,2,FUN_00434820);
        local_8._0_1_ = 0x11;
        FUN_00434b50(local_7c,local_18c,local_15c,'\x01','\x02');
        local_8._0_1_ = 0x13;
        _eh_vector_destructor_iterator_(local_18c,0x10,3,FUN_00434820);
        local_48 = 0xf;
        local_4c = 0;
        local_5c[0] = (undefined4 ******)((uint)local_5c[0] & 0xffffff00);
        FUN_0043ac10(local_5c,uVar6,'\0');
        local_8._0_1_ = 0x14;
        iVar13 = 0;
        do {
          local_24 = CONCAT44(local_24._4_4_,iVar13);
          pppppppuVar7 = local_5c;
          if (0xf < local_48) {
            pppppppuVar7 = (undefined4 *******)local_5c[0];
          }
          puVar4 = (undefined4 *)0x42d636;
          BVar5 = ReadFile(hFile,pppppppuVar7,local_4c,(LPDWORD)((int)&local_24 + 4),
                           (LPOVERLAPPED)0x0);
          if (BVar5 == 0) {
            FUN_004061c0(local_5c);
            local_8._0_1_ = 4;
            FUN_00434820(local_7c);
            break;
          }
          if (local_4c < local_24._4_4_) {
            FUN_0043aef0(local_5c,local_24._4_4_ - local_4c,'\0');
          }
          else {
            local_4c = local_24._4_4_;
            pppppppuVar7 = local_5c;
            if (0xf < local_48) {
              pppppppuVar7 = (undefined4 *******)local_5c[0];
            }
            *(undefined1 *)((int)pppppppuVar7 + local_24._4_4_) = 0;
          }
          if (iVar13 == 0) {
                    /* WARNING: Ignoring partial resolution of indirect */
            uVar15 = 0;
            FUN_0043a750(&stack0xfffffdec,local_fc,0,0xffffffff);
            FUN_00403a70(local_1ec,puVar4);
            local_8._0_1_ = 0x15;
            uVar6 = FUN_00444360(local_1a4,(ushort *)&DAT_0048dabc);
            if (uVar6 == 0) {
              puVar4 = FUN_004355e0(&local_9c,(uint *)"text/javascript");
              local_8 = CONCAT31(local_8._1_3_,0x16);
              uVar12 = uVar12 | 2;
            }
            else {
              uVar6 = FUN_00444360(local_1a4,(ushort *)&DAT_0048dad4);
              if (uVar6 == 0) {
                ppvVar18 = FUN_004355e0(&local_dc,(uint *)"text/javascript");
                uVar12 = uVar12 | 4;
              }
              else {
                uVar6 = FUN_00444360(local_1a4,(ushort *)L"json");
                if (uVar6 == 0) {
                  puVar8 = FUN_004355e0(&local_12c,(uint *)"application/json");
                  uVar12 = uVar12 | 8;
                }
                else {
                  puVar8 = (uint *)FUN_0042ce50((undefined1 *)local_174,local_1d4,local_5c);
                  uVar12 = uVar12 | 0x10;
                }
                local_a8 = 0xf;
                local_ac = 0;
                local_bc[0] = (void *)((uint)local_bc[0] & 0xffffff00);
                FUN_0043b1c0(local_bc,puVar8);
                ppvVar18 = local_bc;
                uVar12 = uVar12 | 0x20;
              }
              local_138 = 0xf;
              local_13c = 0;
              local_14c[0] = 0;
              FUN_0043b1c0(local_14c,(uint *)ppvVar18);
              puVar4 = (undefined4 *)local_14c;
              local_8 = 0x1b;
              uVar12 = uVar12 | 0x40;
            }
            local_30 = 0xf;
            local_34 = 0;
            local_44[0] = (void *)((uint)local_44[0] & 0xffffff00);
            cVar16 = -0x22;
            local_18 = uVar12;
            FUN_0043ade0(local_44,puVar4,0,0xffffffff);
            local_8 = 0x1c;
            if ((uVar12 & 0x40) != 0) {
              uVar12 = uVar12 & 0xffffffbf;
              local_18 = uVar12;
              FUN_004061c0((undefined4 *)local_14c);
            }
            if ((uVar12 & 0x20) != 0) {
              uVar12 = uVar12 & 0xffffffdf;
              local_18 = uVar12;
              FUN_004061c0(local_bc);
            }
            if ((uVar12 & 0x10) != 0) {
              uVar12 = uVar12 & 0xffffffef;
              local_18 = uVar12;
              FUN_004061c0(local_174);
            }
            if ((uVar12 & 8) != 0) {
              uVar12 = uVar12 & 0xfffffff7;
              local_18 = uVar12;
              FUN_004061c0((undefined4 *)&local_12c);
            }
            if ((uVar12 & 4) != 0) {
              uVar12 = uVar12 & 0xfffffffb;
              local_18 = uVar12;
              FUN_004061c0((undefined4 *)&local_dc);
            }
            local_8._0_1_ = 0x22;
            if ((uVar12 & 2) != 0) {
              uVar12 = uVar12 & 0xfffffffd;
              local_18 = uVar12;
              FUN_004061c0((undefined4 *)&local_9c);
            }
            FUN_00440c80(local_6c,local_44);
            local_8._0_1_ = 0x23;
            pcVar9 = (char *)FUN_00440e70(local_7c,(uint *)&DAT_0048dafc);
            local_8._0_1_ = 0x22;
            cVar3 = *pcVar9;
            *pcVar9 = local_6c[0];
            uVar17 = *(undefined4 *)(pcVar9 + 8);
            uVar19 = *(undefined4 *)(pcVar9 + 0xc);
            *(undefined4 *)(pcVar9 + 8) = local_64;
            *(undefined4 *)(pcVar9 + 0xc) = local_60;
            local_6c[0] = cVar3;
            local_64 = uVar17;
            local_60 = uVar19;
            FUN_00434820(local_6c);
            FUN_004355e0(local_114,(uint *)"charEnc");
            ppvVar18 = local_114;
            local_8 = CONCAT31(local_8._1_3_,0x24);
            local_18 = uVar12 | 0x80;
            uVar17 = 0x42d8e7;
            cVar3 = FUN_00441100(param_2,ppvVar18);
            if (cVar3 == '\0') {
              ppvVar18 = (void **)&DAT_0048d624;
              uVar17 = 0x42d8f9;
              iVar13 = FUN_004353c0(local_44,&DAT_0048d624);
              if (iVar13 == 0) goto LAB_0042d915;
              ppvVar18 = (void **)0x42d90d;
              uVar6 = FUN_00444360(local_1a4,(ushort *)L"json");
              local_11 = '\0';
              if (uVar6 == 0) goto LAB_0042d915;
            }
            else {
LAB_0042d915:
              local_11 = '\x01';
            }
            local_8 = 0x22;
            local_18 = uVar12;
            FUN_004061c0(local_114);
            if (local_11 != '\0') {
              uVar19 = 0x42d948;
              puVar4 = (undefined4 *)FUN_00410410((undefined1 *)local_114,(uint *)local_5c);
              local_80 = &stack0xfffffdf4;
              local_8._0_1_ = 0x25;
              FUN_00440c80(&stack0xfffffdf4,puVar4);
              local_8._0_1_ = 0x26;
              puVar4 = FUN_00440e70(local_7c,(uint *)"charEnc");
              local_8 = CONCAT31(local_8._1_3_,0x25);
              FUN_004348c0(puVar4,cVar16,uVar17,ppvVar18,uVar19);
              FUN_004061c0(local_114);
            }
            if (0xf < local_30) {
              FUN_00402430(local_44[0],local_30 + 1,1);
            }
            local_30 = 0xf;
            local_34 = 0;
            local_44[0] = (void *)((uint)local_44[0] & 0xffffff00);
            local_8._0_1_ = 0x14;
            FUN_00403c20(local_1ec);
            iVar13 = (int)local_24;
          }
          cVar16 = local_7c[0];
          if (local_24._4_4_ == 0) goto LAB_0042da69;
          piVar10 = FUN_004043e0((int *)local_114,local_5c);
          local_8._0_1_ = 0x27;
          FUN_00440c80(local_15c,piVar10);
          local_8._0_1_ = 0x28;
          FUN_004355e0(local_44,(uint *)&DAT_0048d634);
          local_8 = CONCAT31(local_8._1_3_,0x29);
          FUN_00410660(local_1c,local_44,local_15c);
          if (0xf < local_30) {
            FUN_00402430(local_44[0],local_30 + 1,1);
          }
          local_30 = 0xf;
          local_34 = 0;
          local_44[0] = (void *)((uint)local_44[0] & 0xffffff00);
          FUN_00434820(local_15c);
          local_8._0_1_ = 0x14;
          if (0xf < local_100) {
            FUN_00402430(local_114[0],local_100 + 1,1);
          }
          iVar13 = iVar13 + 1;
        } while( true );
      }
    }
    DVar11 = GetLastError();
    uVar2 = (undefined1)local_8;
  }
  local_8._0_1_ = uVar2;
  local_a4[0] = '\0';
  local_9c = 0;
  FUN_00451110(local_a4,(uint *)"error");
  local_94[0] = 0;
  local_8c = 0;
  FUN_00451040(local_94,DVar11);
  local_8._0_1_ = 0x2a;
  FUN_00434b50(local_6c,local_a4,(char *)&local_84,'\x01','\x02');
  local_8._0_1_ = 0x2c;
  _eh_vector_destructor_iterator_(local_a4,0x10,2,FUN_00434820);
  local_8._0_1_ = 0x2d;
  FUN_00434b50(param_1,local_6c,(char *)local_5c,'\x01','\x02');
  local_8._0_1_ = 4;
  local_18 = uVar12 | 1;
  _eh_vector_destructor_iterator_(local_6c,0x10,1,FUN_00434820);
  if (hFile != (HANDLE)0x0) {
    CloseHandle(hFile);
  }
joined_r0x0042dada:
  if (7 < local_e8) {
    FUN_00402430(local_fc[0],local_e8 + 1,2);
  }
  ExceptionList = local_10;
  return param_1;
LAB_0042da69:
  local_2c = 0;
  local_7c[0] = '\0';
  *param_1 = cVar16;
  *(undefined4 *)(param_1 + 8) = local_74;
  *(undefined4 *)(param_1 + 0xc) = local_70;
  local_74 = 0;
  local_70 = 0;
  if (0xf < local_48) {
    FUN_00402430(local_5c[0],local_48 + 1,1);
  }
  local_48 = 0xf;
  local_4c = 0;
  local_5c[0] = (undefined4 ******)((uint)local_5c[0] & 0xffffff00);
  FUN_00434820(local_7c);
  if (hFile != (HANDLE)0x0) {
    CloseHandle(hFile);
  }
  goto joined_r0x0042dada;
}


