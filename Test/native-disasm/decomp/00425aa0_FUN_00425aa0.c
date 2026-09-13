// FUN_00425aa0 @ 00425aa0 size=2751 callers=1

/* WARNING: Removing unreachable block (ram,0x00425afe) */

undefined4 FUN_00425aa0(char *param_1,void *param_2)

{
  LONG LVar1;
  LONG LVar2;
  uint uVar3;
  void *this;
  char cVar4;
  uint uVar5;
  int *piVar6;
  LPSTR pCVar7;
  undefined1 *puVar8;
  undefined4 *puVar9;
  LPWSTR pWVar10;
  undefined1 uVar11;
  byte *in_stack_fffffcec;
  char *pcVar12;
  char local_2f4 [16];
  undefined1 local_2e4 [16];
  undefined1 local_2d4 [16];
  undefined1 local_2c4 [16];
  undefined1 local_2b4 [16];
  undefined1 local_2a4 [16];
  undefined1 local_294 [16];
  undefined1 local_284 [16];
  char local_274 [16];
  undefined1 local_264 [16];
  undefined1 local_254 [16];
  undefined1 local_244 [16];
  WCHAR local_234 [12];
  void *local_21c [5];
  uint local_208;
  char local_204 [8];
  undefined8 local_1fc;
  undefined1 local_1f4 [16];
  char local_1e4 [8];
  undefined8 local_1dc;
  undefined1 local_1d4 [16];
  char local_1c4 [8];
  undefined8 local_1bc;
  undefined1 local_1b4 [16];
  char local_1a4 [8];
  undefined8 local_19c;
  undefined1 local_194 [8];
  undefined8 local_18c;
  char local_184 [8];
  undefined8 local_17c;
  undefined1 local_174 [8];
  undefined8 local_16c;
  char local_164 [8];
  undefined8 local_15c;
  undefined1 local_154 [8];
  undefined8 local_14c;
  char local_144 [8];
  undefined8 local_13c;
  undefined1 local_134 [8];
  undefined8 local_12c;
  char local_124 [8];
  undefined8 local_11c;
  undefined1 local_114 [8];
  undefined8 local_10c;
  char local_104 [8];
  undefined8 local_fc;
  undefined1 local_f4 [8];
  undefined8 local_ec;
  char local_e4 [8];
  undefined8 local_dc;
  undefined1 local_d4 [8];
  undefined8 local_cc;
  char local_c4 [8];
  undefined8 local_bc;
  undefined1 local_b4 [8];
  undefined8 local_ac;
  byte local_a4 [24];
  char local_8c [8];
  undefined8 local_84;
  undefined1 local_7c;
  ulonglong local_74;
  void *local_6c [2];
  int local_64 [2];
  uint local_5c;
  uint local_58;
  int local_54;
  int local_50;
  int local_4c;
  DWORD local_48;
  uint local_44;
  int local_40;
  void *local_3c [4];
  undefined4 local_2c;
  uint local_28;
  DWORD local_24;
  tagRECT local_20;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  pcVar12 = param_1;
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047c4a8;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_00404670((int *)local_21c,(HWND)param_1);
  local_8._0_1_ = 0;
  local_8._1_3_ = 0;
                    /* WARNING: Ignoring partial resolution of indirect */
  uVar11 = 0;
  FUN_0043ade0(&stack0xfffffcec,local_21c,0,0xffffffff);
  cVar4 = FUN_004096c0(in_stack_fffffcec);
  if (cVar4 != '\0') {
    uVar5 = GetWindowLongA((HWND)pcVar12,-0x10);
    local_44 = CONCAT31((uint3)(uVar5 >> 0x1f),~(byte)(uVar5 >> 0x17)) & 0xffffff01;
    param_1 = (char *)(uVar5 >> 0x1d & 0xffffff01);
    if ((char)param_1 == '\0') {
      local_20.left = 0;
      local_20.top = 0;
      local_20.right = 0;
      local_20.bottom = 0;
      GetWindowRect((HWND)pcVar12,&local_20);
    }
    else {
      piVar6 = (int *)FUN_00404c40(pcVar12,local_64);
      local_20.left = *piVar6;
      local_20.top = piVar6[1];
      local_20.right = piVar6[2];
      local_20.bottom = piVar6[3];
    }
    local_50 = local_20.right - local_20.left;
    local_54 = local_20.bottom - local_20.top;
    local_4c = local_20.left;
    local_40 = local_20.top;
    FUN_00404790(local_234,(HWND)pcVar12,0x50,'\x01');
    local_8._0_1_ = 1;
    FUN_00403340(local_a4,(uint)pcVar12);
    local_8._0_1_ = 2;
    local_24 = 0;
    local_48 = GetWindowThreadProcessId((HWND)pcVar12,&local_24);
    local_8c[0] = '\0';
    local_84 = 0;
    FUN_00451110(local_8c,(uint *)"visible");
    local_7c = 4;
    uVar3 = CONCAT31(local_5c._1_3_,(byte)(uVar5 >> 0x1c));
    local_5c = uVar3 & 0xffffff01;
    local_74 = CONCAT44(local_58,uVar3) & 0xffffffffffffff01;
    local_8._0_1_ = 3;
    FUN_00434b50(local_2f4,local_8c,(char *)local_6c,'\x01','\x02');
    local_8._0_1_ = 5;
    _eh_vector_destructor_iterator_(local_8c,0x10,2,FUN_00434820);
    local_c4[0] = '\0';
    local_bc = 0;
    FUN_00451110(local_c4,(uint *)"state");
    local_8._0_1_ = 6;
    if ((char)param_1 == '\0') {
      if ((char)local_44 == '\0') {
        param_1 = "maximized";
        if ((uVar5 & 0x1000000) == 0) {
          param_1 = "normal";
        }
      }
      else {
        param_1 = "fullscreen";
      }
    }
    else {
      param_1 = "minimized";
    }
    local_b4[0] = 0;
    local_ac = 0;
    FUN_00451340(local_b4,&param_1);
    local_8._0_1_ = 7;
    FUN_00434b50(local_2e4,local_c4,(char *)local_a4,'\x01','\x02');
    local_8._0_1_ = 9;
    _eh_vector_destructor_iterator_(local_c4,0x10,2,FUN_00434820);
    local_1c4[0] = '\0';
    local_1bc = 0;
    FUN_00451110(local_1c4,(uint *)"title");
    local_8._0_1_ = 10;
    pCVar7 = FUN_00404580((LPSTR)local_3c,local_234,0x7fffffff);
    local_8 = CONCAT31(local_8._1_3_,0xb);
    FUN_00440c80(local_1b4,(undefined4 *)pCVar7);
    if (0xf < local_28) {
      FUN_00402430(local_3c[0],local_28 + 1,1);
    }
    local_28 = 0xf;
    local_2c = 0;
    local_3c[0] = (void *)((uint)local_3c[0] & 0xffffff00);
    local_8._0_1_ = 0xc;
    FUN_00434b50(local_2d4,local_1c4,local_1a4,'\x01','\x02');
    local_8._0_1_ = 0xe;
    _eh_vector_destructor_iterator_(local_1c4,0x10,2,FUN_00434820);
    local_1e4[0] = '\0';
    local_1dc = 0;
    FUN_00451110(local_1e4,(uint *)"clsname");
    local_8._0_1_ = 0xf;
    FUN_00440c80(local_1d4,local_21c);
    local_8._0_1_ = 0x10;
    FUN_00434b50(local_2c4,local_1e4,local_1c4,'\x01','\x02');
    local_8._0_1_ = 0x12;
    _eh_vector_destructor_iterator_(local_1e4,0x10,2,FUN_00434820);
    local_e4[0] = '\0';
    local_dc = 0;
    FUN_00451110(local_e4,(uint *)"thread");
    local_d4[0] = 0;
    local_cc = 0;
    FUN_00451040(local_d4,local_48);
    local_8._0_1_ = 0x13;
    FUN_00434b50(local_2b4,local_e4,local_c4,'\x01','\x02');
    local_8._0_1_ = 0x15;
    _eh_vector_destructor_iterator_(local_e4,0x10,2,FUN_00434820);
    local_104[0] = '\0';
    local_fc = 0;
    FUN_00451110(local_104,(uint *)"process");
    local_f4[0] = 0;
    local_ec = 0;
    FUN_00451040(local_f4,local_24);
    local_8._0_1_ = 0x16;
    FUN_00434b50(local_2a4,local_104,local_e4,'\x01','\x02');
    local_8._0_1_ = 0x18;
    _eh_vector_destructor_iterator_(local_104,0x10,2,FUN_00434820);
    local_124[0] = '\0';
    local_11c = 0;
    FUN_00451110(local_124,(uint *)"styles");
    local_114[0] = 0;
    local_10c = 0;
    FUN_00451040(local_114,uVar5);
    local_8._0_1_ = 0x19;
    FUN_00434b50(local_294,local_124,local_104,'\x01','\x02');
    local_8._0_1_ = 0x1b;
    _eh_vector_destructor_iterator_(local_124,0x10,2,FUN_00434820);
    local_204[0] = '\0';
    local_1fc = 0;
    FUN_00451110(local_204,(uint *)"coords");
    local_8._0_1_ = 0x1c;
    local_144[0] = '\0';
    local_13c = 0;
    FUN_00451110(local_144,(uint *)&DAT_0048d65c);
    local_134[0] = 0;
    local_12c = 0;
    FUN_00450f50(local_134,local_4c);
    local_8._0_1_ = 0x1d;
    FUN_00434b50(local_274,local_144,local_124,'\x01','\x02');
    local_8._0_1_ = 0x1f;
    _eh_vector_destructor_iterator_(local_144,0x10,2,FUN_00434820);
    local_164[0] = '\0';
    local_15c = 0;
    FUN_00451110(local_164,(uint *)&DAT_0048d660);
    local_154[0] = 0;
    local_14c = 0;
    FUN_00450f50(local_154,local_40);
    local_8._0_1_ = 0x20;
    FUN_00434b50(local_264,local_164,local_144,'\x01','\x02');
    local_8._0_1_ = 0x22;
    _eh_vector_destructor_iterator_(local_164,0x10,2,FUN_00434820);
    local_184[0] = '\0';
    local_17c = 0;
    FUN_00451110(local_184,(uint *)&DAT_0048d870);
    local_174[0] = 0;
    local_16c = 0;
    FUN_00450f50(local_174,local_50);
    local_8._0_1_ = 0x23;
    FUN_00434b50(local_254,local_184,local_164,'\x01','\x02');
    local_8._0_1_ = 0x25;
    _eh_vector_destructor_iterator_(local_184,0x10,2,FUN_00434820);
    local_1a4[0] = '\0';
    local_19c = 0;
    FUN_00451110(local_1a4,(uint *)&DAT_0048d874);
    local_194[0] = 0;
    local_18c = 0;
    FUN_00450f50(local_194,local_54);
    local_8._0_1_ = 0x26;
    FUN_00434b50(local_244,local_1a4,local_184,'\x01','\x02');
    local_8._0_1_ = 0x28;
    _eh_vector_destructor_iterator_(local_1a4,0x10,2,FUN_00434820);
    local_8._0_1_ = 0x29;
    FUN_00434b50(local_1f4,local_274,(char *)local_234,'\x01','\x02');
    local_8._0_1_ = 0x2b;
    _eh_vector_destructor_iterator_(local_274,0x10,4,FUN_00434820);
    local_8._0_1_ = 0x2c;
    FUN_00434b50(local_284,local_204,local_1e4,'\x01','\x02');
    local_8._0_1_ = 0x2e;
    _eh_vector_destructor_iterator_(local_204,0x10,2,FUN_00434820);
    local_8._0_1_ = 0x2f;
    FUN_00434b50(&local_20,local_2f4,local_274,'\x01','\x02');
    local_8._0_1_ = 0x30;
    puVar8 = FUN_00434440(param_2,local_a4);
    uVar11 = *puVar8;
    *puVar8 = (undefined1)local_20.left;
    local_20.left = CONCAT31(local_20.left._1_3_,uVar11);
    LVar1 = *(LONG *)(puVar8 + 8);
    LVar2 = *(LONG *)(puVar8 + 0xc);
    *(LONG *)(puVar8 + 8) = local_20.right;
    *(LONG *)(puVar8 + 0xc) = local_20.bottom;
    local_20.right = LVar1;
    local_20.bottom = LVar2;
    FUN_00434820((char *)&local_20);
    local_8._0_1_ = 2;
    _eh_vector_destructor_iterator_(local_2f4,0x10,8,FUN_00434820);
    param_1 = (char *)GetAncestor((HWND)pcVar12,1);
    if ((HWND)param_1 != DAT_004a2b60) {
      FUN_00442050(&local_20,(int *)&param_1);
      this = param_2;
      pcVar12 = "parentHwnd";
      local_8._0_1_ = 0x31;
      puVar8 = FUN_00434440(param_2,local_a4);
      puVar9 = FUN_00440e70(puVar8,(uint *)pcVar12);
      local_8._0_1_ = 2;
      uVar11 = *(undefined1 *)puVar9;
      *(undefined1 *)puVar9 = (undefined1)local_20.left;
      LVar1 = puVar9[2];
      LVar2 = puVar9[3];
      puVar9[2] = local_20.right;
      puVar9[3] = local_20.bottom;
      local_20.right = LVar1;
      local_20.bottom = LVar2;
      local_20.left._0_1_ = uVar11;
      FUN_00434820((char *)&local_20);
      piVar6 = FUN_00404670((int *)local_3c,(HWND)param_1);
      local_8._0_1_ = 0x32;
      FUN_00440c80(&local_20,piVar6);
      pcVar12 = "parentClass";
      local_8._0_1_ = 0x33;
      puVar8 = FUN_00434440(this,local_a4);
      puVar9 = FUN_00440e70(puVar8,(uint *)pcVar12);
      uVar11 = *(undefined1 *)puVar9;
      *(undefined1 *)puVar9 = (undefined1)local_20.left;
      local_20.left = CONCAT31(local_20.left._1_3_,uVar11);
      LVar1 = puVar9[2];
      LVar2 = puVar9[3];
      puVar9[2] = local_20.right;
      puVar9[3] = local_20.bottom;
      local_20.right = LVar1;
      local_20.bottom = LVar2;
      FUN_00434820((char *)&local_20);
      local_8._0_1_ = 2;
      if (0xf < local_28) {
        FUN_00402430(local_3c[0],local_28 + 1,1);
      }
      pWVar10 = FUN_00404790((LPWSTR)local_6c,(HWND)param_1,0x50,'\x01');
      local_8._0_1_ = 0x34;
      pCVar7 = FUN_00404580((LPSTR)local_3c,pWVar10,0x7fffffff);
      local_8._0_1_ = 0x35;
      FUN_00440c80(&local_20,(undefined4 *)pCVar7);
      pcVar12 = "parentTitle";
      local_8 = CONCAT31(local_8._1_3_,0x36);
      puVar8 = FUN_00434440(this,local_a4);
      puVar9 = FUN_00440e70(puVar8,(uint *)pcVar12);
      uVar11 = *(undefined1 *)puVar9;
      *(undefined1 *)puVar9 = (undefined1)local_20.left;
      local_20.left = CONCAT31(local_20.left._1_3_,uVar11);
      LVar1 = puVar9[2];
      LVar2 = puVar9[3];
      puVar9[2] = local_20.right;
      puVar9[3] = local_20.bottom;
      local_20.right = LVar1;
      local_20.bottom = LVar2;
      FUN_00434820((char *)&local_20);
      if (0xf < local_28) {
        FUN_00402430(local_3c[0],local_28 + 1,1);
      }
      local_8._0_1_ = 2;
      local_28 = 0xf;
      local_2c = 0;
      local_3c[0] = (void *)((uint)local_3c[0] & 0xffffff00);
      if (7 < local_58) {
        FUN_00402430(local_6c[0],local_58 + 1,2);
      }
      GetWindowThreadProcessId((HWND)param_1,&local_24);
      pWVar10 = FUN_00404a40((LPWSTR)local_6c,local_24);
      local_8._0_1_ = 0x37;
      pCVar7 = FUN_00404580((LPSTR)local_3c,pWVar10,0x7fffffff);
      local_8._0_1_ = 0x38;
      FUN_00440c80(&local_20,(undefined4 *)pCVar7);
      pcVar12 = "parentPath";
      local_8._0_1_ = 0x39;
      puVar8 = FUN_00434440(this,local_a4);
      puVar9 = FUN_00440e70(puVar8,(uint *)pcVar12);
      uVar11 = *(undefined1 *)puVar9;
      *(undefined1 *)puVar9 = (undefined1)local_20.left;
      local_20.left = CONCAT31(local_20.left._1_3_,uVar11);
      LVar1 = puVar9[2];
      LVar2 = puVar9[3];
      puVar9[2] = local_20.right;
      puVar9[3] = local_20.bottom;
      local_20.right = LVar1;
      local_20.bottom = LVar2;
      FUN_00434820((char *)&local_20);
      if (0xf < local_28) {
        FUN_00402430(local_3c[0],local_28 + 1,1);
      }
      local_28 = 0xf;
      local_2c = 0;
      local_3c[0] = (void *)((uint)local_3c[0] & 0xffffff00);
      if (7 < local_58) {
        FUN_00402430(local_6c[0],local_58 + 1,2);
      }
    }
    FUN_004061c0((undefined4 *)local_a4);
    FUN_00435170((undefined4 *)local_234);
  }
  if (0xf < local_208) {
    FUN_00402430(local_21c[0],local_208 + 1,1);
  }
  ExceptionList = local_10;
  return 1;
}


