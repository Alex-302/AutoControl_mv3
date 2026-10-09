// FUN_00425250 @ 00425250 size=2032 callers=1

undefined4 FUN_00425250(char *param_1,undefined1 *param_2)

{
  undefined1 uVar1;
  char cVar2;
  LONG LVar3;
  LONG LVar4;
  HWND hWnd;
  char cVar5;
  DWORD DVar6;
  uint uVar7;
  int *piVar8;
  undefined1 *puVar9;
  char *pcVar10;
  uint uVar11;
  undefined4 *puVar12;
  LPWSTR pWVar13;
  LPSTR pCVar14;
  undefined1 *puVar15;
  char extraout_CL;
  uint uVar16;
  undefined4 uVar17;
  undefined *puVar18;
  undefined4 uVar19;
  undefined4 uVar20;
  char local_1f4 [16];
  undefined1 local_1e4 [16];
  undefined1 local_1d4 [16];
  undefined1 local_1c4 [16];
  char local_1b4 [16];
  undefined1 local_1a4 [16];
  undefined1 local_194 [16];
  void *local_184 [4];
  int local_174;
  uint local_170;
  char local_16c [8];
  undefined8 local_164;
  undefined1 local_15c [16];
  char local_14c [8];
  undefined8 local_144;
  undefined1 local_13c [8];
  undefined8 local_134;
  char local_12c [8];
  undefined8 local_124;
  undefined1 local_11c [8];
  undefined8 local_114;
  char local_10c [8];
  undefined8 local_104;
  undefined1 local_fc [8];
  undefined8 local_f4;
  char local_ec [8];
  undefined8 local_e4;
  undefined1 local_dc [8];
  undefined8 local_d4;
  char local_cc [8];
  undefined8 local_c4;
  undefined1 local_bc [8];
  undefined8 local_b4;
  char local_ac [8];
  undefined8 local_a4;
  undefined1 local_9c;
  undefined4 local_94;
  undefined4 uStack_90;
  WCHAR local_8c [4];
  int local_84 [2];
  undefined4 local_7c;
  undefined4 local_78;
  void *local_74 [5];
  uint local_60;
  void *local_5c [4];
  uint local_4c;
  uint local_48;
  int local_44;
  int local_40;
  int local_3c;
  uint local_38;
  uint local_34;
  int local_30;
  int local_2c [2];
  tagRECT local_24;
  HWND local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  pcVar10 = param_1;
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047c22d;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  cVar5 = FUN_00409750((HWND)param_1);
  if (((cVar5 != '\0') &&
      (((DAT_004a2a88 == '\0' || (DAT_004a2460 == 0)) ||
       (DVar6 = GetWindowThreadProcessId((HWND)pcVar10,(LPDWORD)0x0), DAT_004a2460 == DVar6)))) &&
     ((local_14 = (HWND)0x0, DAT_004a2a88 == '\0' ||
      (local_14 = GetAncestor((HWND)pcVar10,1), local_14 != DAT_004a3344)))) {
    FUN_00404790((LPWSTR)local_184,(HWND)pcVar10,200,'\x01');
    local_8._0_1_ = 0;
    local_8._1_3_ = 0;
    uVar7 = GetWindowLongA((HWND)pcVar10,-0x10);
    param_1 = (char *)(uVar7 >> 0x1c & 0xffffff01);
    if ((local_174 != 0) || ((char)param_1 != '\0')) {
      local_38 = uVar7 & 0xc40000;
      local_34 = uVar7 >> 0x1d & 0xffffff01;
      if ((char)local_34 == '\0') {
        local_24.left = 0;
        local_24.top = 0;
        local_24.right = 0;
        local_24.bottom = 0;
        GetWindowRect((HWND)pcVar10,&local_24);
      }
      else {
        piVar8 = (int *)FUN_00404c40(pcVar10,local_84);
        local_24.left = *piVar8;
        local_24.top = piVar8[1];
        local_24.right = piVar8[2];
        local_24.bottom = piVar8[3];
      }
      local_40 = local_24.right - local_24.left;
      local_44 = local_24.bottom - local_24.top;
      local_3c = local_24.left;
      local_30 = local_24.top;
      FUN_00403340((undefined1 *)local_74,(uint)pcVar10);
      local_8._0_1_ = 1;
      local_ac[0] = '\0';
      local_a4 = 0;
      FUN_00451110(local_ac,(uint *)"visible");
      local_7c = CONCAT31(local_7c._1_3_,(char)param_1);
      local_9c = 4;
      _local_94 = CONCAT44(local_78,local_7c);
      local_8._0_1_ = 2;
      FUN_00434b50(local_1b4,local_ac,(char *)local_8c,'\x01','\x02');
      local_8._0_1_ = 4;
      _eh_vector_destructor_iterator_(local_ac,0x10,2,FUN_00434820);
      local_cc[0] = '\0';
      local_c4 = 0;
      FUN_00451110(local_cc,(uint *)"state");
      local_8._0_1_ = 5;
      if ((char)local_34 == '\0') {
        if (local_38 == 0) {
          param_1 = "fullscreen";
        }
        else {
          param_1 = "maximized";
          if ((uVar7 & 0x1000000) == 0) {
            param_1 = "normal";
          }
        }
      }
      else {
        param_1 = "minimized";
      }
      local_bc[0] = 0;
      local_b4 = 0;
      FUN_00451340(local_bc,&param_1);
      local_8._0_1_ = 6;
      FUN_00434b50(local_1a4,local_cc,local_ac,'\x01','\x02');
      local_8._0_1_ = 8;
      _eh_vector_destructor_iterator_(local_cc,0x10,2,FUN_00434820);
      local_16c[0] = '\0';
      local_164 = 0;
      FUN_00451110(local_16c,(uint *)"coords");
      local_8._0_1_ = 9;
      local_ec[0] = '\0';
      local_e4 = 0;
      FUN_00451110(local_ec,(uint *)&DAT_0048d65c);
      local_dc[0] = 0;
      local_d4 = 0;
      FUN_00450f50(local_dc,local_3c);
      local_8._0_1_ = 10;
      FUN_00434b50(local_1f4,local_ec,local_cc,'\x01','\x02');
      local_8._0_1_ = 0xc;
      _eh_vector_destructor_iterator_(local_ec,0x10,2,FUN_00434820);
      local_10c[0] = '\0';
      local_104 = 0;
      FUN_00451110(local_10c,(uint *)&DAT_0048d660);
      local_fc[0] = 0;
      local_f4 = 0;
      FUN_00450f50(local_fc,local_30);
      local_8._0_1_ = 0xd;
      FUN_00434b50(local_1e4,local_10c,local_ec,'\x01','\x02');
      local_8._0_1_ = 0xf;
      _eh_vector_destructor_iterator_(local_10c,0x10,2,FUN_00434820);
      local_12c[0] = '\0';
      local_124 = 0;
      FUN_00451110(local_12c,(uint *)&DAT_0048d870);
      local_11c[0] = 0;
      local_114 = 0;
      FUN_00450f50(local_11c,local_40);
      local_8._0_1_ = 0x10;
      FUN_00434b50(local_1d4,local_12c,local_10c,'\x01','\x02');
      local_8._0_1_ = 0x12;
      _eh_vector_destructor_iterator_(local_12c,0x10,2,FUN_00434820);
      local_14c[0] = '\0';
      local_144 = 0;
      FUN_00451110(local_14c,(uint *)&DAT_0048d874);
      local_13c[0] = 0;
      local_134 = 0;
      FUN_00450f50(local_13c,local_44);
      local_8._0_1_ = 0x13;
      FUN_00434b50(local_1c4,local_14c,local_12c,'\x01','\x02');
      local_8._0_1_ = 0x15;
      _eh_vector_destructor_iterator_(local_14c,0x10,2,FUN_00434820);
      local_8._0_1_ = 0x16;
      FUN_00434b50(local_15c,local_1f4,local_1b4,'\x01','\x02');
      local_8._0_1_ = 0x18;
      _eh_vector_destructor_iterator_(local_1f4,0x10,4,FUN_00434820);
      local_8._0_1_ = 0x19;
      FUN_00434b50(local_194,local_16c,local_14c,'\x01','\x02');
      local_8._0_1_ = 0x1b;
      _eh_vector_destructor_iterator_(local_16c,0x10,2,FUN_00434820);
      local_8._0_1_ = 0x1c;
      FUN_00434b50(&local_24,local_1b4,(char *)local_184,'\x01','\x02');
      puVar15 = param_2;
      local_8._0_1_ = 0x1d;
      puVar9 = FUN_00434440(param_2,(byte *)local_74);
      uVar1 = *puVar9;
      *puVar9 = (undefined1)local_24.left;
      local_24.left = CONCAT31(local_24.left._1_3_,uVar1);
      LVar3 = *(LONG *)(puVar9 + 8);
      LVar4 = *(LONG *)(puVar9 + 0xc);
      *(LONG *)(puVar9 + 8) = local_24.right;
      *(LONG *)(puVar9 + 0xc) = local_24.bottom;
      local_24.right = LVar3;
      local_24.bottom = LVar4;
      FUN_00434820((char *)&local_24);
      uVar16 = 0x10;
      pcVar10 = local_1b4;
      local_8._0_1_ = 1;
      _eh_vector_destructor_iterator_(pcVar10,0x10,3,FUN_00434820);
      cVar5 = (char)pcVar10;
      puVar18 = (undefined *)0x7fffffff;
      uVar7 = 0x4257d8;
      FUN_00404580((LPSTR)local_5c,(LPCWSTR)local_184,0x7fffffff);
      local_8._0_1_ = 0x1e;
      uVar1 = (undefined1)local_8;
      local_8._0_1_ = 0x1e;
      pcVar10 = PTR_s___Google_Chrome_0049da04;
      do {
        cVar2 = *pcVar10;
        pcVar10 = pcVar10 + 1;
      } while (cVar2 != '\0');
      if ((uint)((int)pcVar10 - (int)(PTR_s___Google_Chrome_0049da04 + 1)) <= local_4c) {
        uVar16 = local_4c - ((int)pcVar10 - (int)(PTR_s___Google_Chrome_0049da04 + 1));
        cVar5 = '\r';
        puVar18 = PTR_s___Google_Chrome_0049da04;
        uVar11 = FUN_004352c0(local_5c,uVar16,local_4c,PTR_s___Google_Chrome_0049da04);
        uVar7 = local_4c;
        uVar1 = (undefined1)local_8;
        if (uVar11 == 0) {
          param_1 = &stack0xfffffdf4;
          FUN_00440c80(&stack0xfffffdf4,local_5c);
          pcVar10 = "title";
          local_8._0_1_ = 0x1f;
          puVar9 = FUN_00434440(puVar15,(byte *)local_74);
          puVar12 = FUN_00440e70(puVar9,(uint *)pcVar10);
          local_8._0_1_ = 0x1e;
          FUN_004348c0(puVar12,cVar5,uVar16,local_4c,puVar18);
          uVar7 = local_4c;
          uVar1 = (undefined1)local_8;
        }
      }
      local_8._0_1_ = uVar1;
      if (DAT_004a2a88 != '\0') {
        param_2 = &stack0xfffffdf4;
        FUN_00442050(&stack0xfffffdf4,(int *)&local_14);
        pcVar10 = "parentHwnd";
        local_8._0_1_ = 0x20;
        puVar9 = FUN_00434440(puVar15,(byte *)local_74);
        puVar12 = FUN_00440e70(puVar9,(uint *)pcVar10);
        local_8._0_1_ = 0x1e;
        FUN_004348c0(puVar12,cVar5,uVar16,uVar7,puVar18);
        hWnd = local_14;
        uVar19 = 0x425899;
        piVar8 = FUN_00404670(local_2c,local_14);
        param_2 = &stack0xfffffdf4;
        local_8._0_1_ = 0x21;
        FUN_00440c80(&stack0xfffffdf4,piVar8);
        pcVar10 = "parentClass";
        local_8._0_1_ = 0x22;
        puVar9 = FUN_00434440(puVar15,(byte *)local_74);
        puVar12 = FUN_00440e70(puVar9,(uint *)pcVar10);
        local_8._0_1_ = 0x21;
        FUN_004348c0(puVar12,cVar5,uVar16,uVar7,uVar19);
        local_8._0_1_ = 0x1e;
        FUN_004061c0(local_2c);
        uVar20 = 1;
        uVar17 = 0x50;
        pWVar13 = FUN_00404790(local_8c,hWnd,0x50,'\x01');
        uVar19 = 0x7fffffff;
        local_8._0_1_ = 0x23;
        pCVar14 = FUN_00404580((LPSTR)local_2c,pWVar13,0x7fffffff);
        param_2 = &stack0xfffffdf4;
        local_8._0_1_ = 0x24;
        cVar5 = extraout_CL;
        FUN_00440c80(&stack0xfffffdf4,(undefined4 *)pCVar14);
        pcVar10 = "parentTitle";
        local_8._0_1_ = 0x25;
        puVar9 = FUN_00434440(puVar15,(byte *)local_74);
        puVar12 = FUN_00440e70(puVar9,(uint *)pcVar10);
        local_8._0_1_ = 0x24;
        FUN_004348c0(puVar12,cVar5,uVar19,uVar17,uVar20);
        FUN_004061c0(local_2c);
        local_8._0_1_ = 0x1e;
        FUN_00435170((undefined4 *)local_8c);
        param_1 = (char *)0x0;
        uVar19 = 0x425960;
        GetWindowThreadProcessId(hWnd,(LPDWORD)&param_1);
        pWVar13 = FUN_00404a40(local_8c,(DWORD)param_1);
        uVar20 = 0x7fffffff;
        local_8._0_1_ = 0x26;
        uVar17 = 0x425981;
        pCVar14 = FUN_00404580((LPSTR)local_2c,pWVar13,0x7fffffff);
        param_2 = &stack0xfffffdf4;
        local_8._0_1_ = 0x27;
        FUN_00440c80(&stack0xfffffdf4,(undefined4 *)pCVar14);
        pcVar10 = "parentPath";
        local_8._0_1_ = 0x28;
        puVar15 = FUN_00434440(puVar15,(byte *)local_74);
        puVar12 = FUN_00440e70(puVar15,(uint *)pcVar10);
        local_8._0_1_ = 0x27;
        FUN_004348c0(puVar12,cVar5,uVar19,uVar17,uVar20);
        FUN_004061c0(local_2c);
        FUN_00435170((undefined4 *)local_8c);
      }
      if (0xf < local_48) {
        FUN_00402430(local_5c[0],local_48 + 1,1);
      }
      local_48 = 0xf;
      local_4c = 0;
      local_5c[0] = (void *)((uint)local_5c[0] & 0xffffff00);
      if (0xf < local_60) {
        FUN_00402430(local_74[0],local_60 + 1,1);
      }
    }
    if (7 < local_170) {
      FUN_00402430(local_184[0],local_170 + 1,2);
    }
  }
  ExceptionList = local_10;
  return 1;
}


