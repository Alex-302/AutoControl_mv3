// FUN_00433e10 @ 00433e10 size=607 callers=12

void __thiscall FUN_00433e10(void *this,char *param_1)

{
  char cVar1;
  undefined4 uVar2;
  uint *puVar3;
  undefined4 *puVar4;
  undefined4 uVar5;
  char *pcVar6;
  byte *pbVar7;
  void *this_00;
  undefined1 local_bc [24];
  undefined1 local_a4 [24];
  void *local_8c [5];
  uint local_78;
  undefined1 local_74 [8];
  int local_6c [4];
  undefined1 local_5c [8];
  char *local_54;
  int local_50;
  int local_4c;
  int local_48;
  void *local_44;
  int local_40;
  undefined4 local_3c;
  uint local_38;
  char local_30 [4];
  undefined **local_2c;
  undefined8 local_28;
  undefined8 local_20;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047da74;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_44 = this;
  if (*(char *)this == '\0') {
    ExceptionList = &local_10;
    *(undefined1 *)this = 2;
    FUN_004381d0(&local_40,'\x02');
    *(int *)((int)this + 8) = local_40;
    *(undefined4 *)((int)this + 0xc) = local_3c;
  }
  if (*(char *)this == '\x02') {
    FUN_004382c0(*(void **)((int)this + 8),param_1);
    *param_1 = '\0';
  }
  else {
    if (*(char *)this != '\x01') {
      puVar3 = (uint *)FUN_00438430(this,local_a4);
      local_8 = 6;
      puVar4 = (undefined4 *)FUN_00442600(local_bc,(uint *)"cannot use push_back() with ",puVar3);
      local_8 = CONCAT31(local_8._1_3_,7);
      if (0xf < (uint)puVar4[5]) {
        puVar4 = (undefined4 *)*puVar4;
      }
      local_2c = std::exception::vftable;
      local_28 = 0;
      local_20._0_5_ = CONCAT14(1,puVar4);
      ___std_exception_copy((undefined4 *)&local_20,(undefined4 *)&local_28);
      local_2c = &PTR_FUN_0048eee8;
                    /* WARNING: Subroutine does not return */
      __CxxThrowException_8((int *)&local_2c,&DAT_0049a03c);
    }
    if (*param_1 != '\x01') {
      puVar3 = (uint *)FUN_00438430(this,(undefined1 *)local_8c);
      local_8 = 0;
      puVar3 = (uint *)FUN_00442600(local_74,(uint *)"cannot append ",puVar3);
      local_8._0_1_ = 1;
      puVar4 = (undefined4 *)FUN_004412a0(local_5c,puVar3,(uint *)" to object");
      local_8 = CONCAT31(local_8._1_3_,2);
      FUN_00402490(&local_40,puVar4);
                    /* WARNING: Subroutine does not return */
      __CxxThrowException_8(&local_40,&DAT_0049a03c);
    }
    FUN_00434120(param_1,&local_54);
    FUN_004340a0(this_00,local_6c);
    uVar5 = FUN_004383a0(&local_54,local_6c);
    if ((char)uVar5 == '\0') {
      do {
        pcVar6 = FUN_00433bc0(&local_54);
        local_20 = 0;
        cVar1 = *pcVar6;
        uVar5 = *(undefined4 *)(pcVar6 + 8);
        uVar2 = *(undefined4 *)(pcVar6 + 0xc);
        local_28 = *(undefined8 *)(pcVar6 + 8);
        *pcVar6 = '\0';
        pcVar6[8] = '\0';
        pcVar6[9] = '\0';
        pcVar6[10] = '\0';
        pcVar6[0xb] = '\0';
        pcVar6[0xc] = '\0';
        pcVar6[0xd] = '\0';
        pcVar6[0xe] = '\0';
        pcVar6[0xf] = '\0';
        local_8 = 3;
        local_30[0] = cVar1;
        pbVar7 = FUN_00433b30(&local_54,(undefined1 *)local_8c);
        local_8 = CONCAT31(local_8._1_3_,4);
        pcVar6 = FUN_00434440(local_44,pbVar7);
        local_30[0] = *pcVar6;
        *pcVar6 = cVar1;
        local_28 = *(undefined8 *)(pcVar6 + 8);
        *(undefined4 *)(pcVar6 + 8) = uVar5;
        *(undefined4 *)(pcVar6 + 0xc) = uVar2;
        FUN_00434820(local_30);
        local_8 = 0xffffffff;
        if (0xf < local_78) {
          FUN_00402430(local_8c[0],local_78 + 1,1);
        }
        if (*local_54 == '\x01') {
          local_38 = local_38 & 0xffffff00;
          FUN_00447660(&local_50);
        }
        else if (*local_54 == '\x02') {
          local_4c = local_4c + 0x10;
        }
        else {
          local_48 = local_48 + 1;
        }
        FUN_004340a0(param_1,local_6c);
        uVar5 = FUN_004383a0(&local_54,local_6c);
      } while ((char)uVar5 == '\0');
      ExceptionList = local_10;
      return;
    }
  }
  ExceptionList = local_10;
  return;
}


