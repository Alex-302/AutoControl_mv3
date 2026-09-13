// FUN_00402f00 @ 00402f00 size=412 callers=11

void __thiscall FUN_00402f00(void *this,uint param_1,char param_2)

{
  void *pvVar1;
  undefined *puVar2;
  undefined ***pppuVar3;
  uint uVar4;
  void *local_68 [4];
  undefined4 local_58;
  uint local_54;
  void *local_50 [4];
  undefined4 local_40;
  uint local_3c;
  undefined **local_38 [5];
  undefined **local_24 [5];
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  pvVar1 = ExceptionList;
  local_8 = 0xffffffff;
  puStack_c = &LAB_00479188;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  *(uint *)((int)this + 0xc) = param_1 & 0x17;
  uVar4 = *(uint *)((int)this + 0x10) & param_1 & 0x17;
  if (uVar4 == 0) {
    ExceptionList = pvVar1;
    return;
  }
  if (param_2 != '\0') {
                    /* WARNING: Subroutine does not return */
    __CxxThrowException_8((int *)0x0,(byte *)0x0);
  }
  if ((uVar4 & 4) == 0) {
    if ((uVar4 & 2) == 0) {
      puVar2 = FUN_00440790();
      local_3c = 0xf;
      local_40 = 0;
      local_50[0] = (void *)((uint)local_50[0] & 0xffffff00);
      FUN_0043ace0(local_50,(uint *)"ios_base::eofbit set",0x14);
      local_8 = 2;
      FUN_00402d50(local_38,local_50,1,puVar2);
      local_8 = 0xffffffff;
      if (0xf < local_3c) {
        FUN_00402430(local_50[0],local_3c + 1,1);
      }
      local_3c = 0xf;
      pppuVar3 = local_38;
      local_40 = 0;
      local_50[0] = (void *)((uint)local_50[0] & 0xffffff00);
      local_38[0] = &PTR_FUN_0048f208;
      goto LAB_00402faf;
    }
    puVar2 = FUN_00440790();
    local_54 = 0xf;
    local_58 = 0;
    local_68[0] = (void *)((uint)local_68[0] & 0xffffff00);
    FUN_0043ace0(local_68,(uint *)"ios_base::failbit set",0x15);
    local_8 = 1;
    FUN_00402d50(local_24,local_68,1,puVar2);
  }
  else {
    puVar2 = FUN_00440790();
    local_54 = 0xf;
    local_58 = 0;
    local_68[0] = (void *)((uint)local_68[0] & 0xffffff00);
    FUN_0043ace0(local_68,(uint *)"ios_base::badbit set",0x14);
    local_8 = 0;
    FUN_00402d50(local_24,local_68,1,puVar2);
  }
  local_8 = 0xffffffff;
  if (0xf < local_54) {
    local_8 = 0xffffffff;
    FUN_00402430(local_68[0],local_54 + 1,1);
  }
  local_24[0] = &PTR_FUN_0048f208;
  pppuVar3 = local_24;
LAB_00402faf:
                    /* WARNING: Subroutine does not return */
  __CxxThrowException_8((int *)pppuVar3,&DAT_0049a04c);
}


