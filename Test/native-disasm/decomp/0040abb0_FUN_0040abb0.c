// FUN_0040abb0 @ 0040abb0 size=454 callers=2

/* WARNING: Removing unreachable block (ram,0x0040ac24) */

void __thiscall FUN_0040abb0(void *this,undefined4 *param_1)

{
  undefined4 *puVar1;
  undefined4 *_Memory;
  int iVar2;
  void *this_00;
  undefined1 (*pauVar3) [16];
  uint uVar4;
  undefined8 uVar5;
  undefined2 uVar6;
  wint_t *in_stack_ffffff80;
  undefined4 local_60;
  undefined4 local_50;
  uint local_4c;
  void *local_48 [2];
  undefined4 local_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  uint uStack_34;
  undefined4 *local_2c;
  uint local_28;
  uint local_24;
  undefined1 *puStack_20;
  void *local_1c;
  undefined1 *puStack_18;
  undefined4 local_14;
  
  puStack_20 = &stack0xfffffffc;
  local_14 = 0xffffffff;
  puStack_18 = &LAB_00479dd0;
  local_1c = ExceptionList;
  ExceptionList = &local_1c;
  iVar2 = GdipGetImageEncodersSize();
  if (iVar2 == 0) {
    FUN_004413d0(&local_2c,local_28);
    local_14 = 0;
                    /* WARNING: Ignoring partial resolution of indirect */
    uVar6 = 0;
    FUN_0043a750(&stack0xffffff80,this,0,0xffffffff);
    this_00 = FUN_004038f0(local_48,in_stack_ffffff80);
    local_14 = CONCAT31(local_14._1_3_,1);
    uVar5 = FUN_0043a420(this_00,(void *)0x0,(uint *)&DAT_0048d0c4,(void *)0x1);
    local_4c = 7;
    local_60 = (undefined1 (*) [16])((uint)local_60._2_2_ << 0x10);
    local_50 = 0;
    FUN_0043a750(&local_60,(undefined4 *)uVar5,0,0xffffffff);
    if (7 < uStack_34) {
      FUN_00402430(local_48[0],uStack_34 + 1,2);
    }
    _Memory = local_2c;
    iVar2 = GdipGetImageEncoders();
    if ((iVar2 == 0) && (uVar4 = 0, local_24 != 0)) {
      local_2c = _Memory + 0xb;
      do {
        pauVar3 = (undefined1 (*) [16])&local_60;
        if (7 < local_4c) {
          pauVar3 = local_60;
        }
        pauVar3 = FUN_0045b68e((undefined1 (*) [16])*local_2c,pauVar3);
        if (pauVar3 != (undefined1 (*) [16])0x0) {
          puVar1 = _Memory + uVar4 * 0x13;
          local_40 = *puVar1;
          uStack_3c = puVar1[1];
          uStack_38 = puVar1[2];
          uStack_34 = puVar1[3];
          if (7 < local_4c) {
            FUN_00402430(local_60,local_4c + 1,2);
          }
          local_4c = 7;
          local_50 = 0;
          local_60 = (undefined1 (*) [16])((uint)local_60 & 0xffff0000);
          if (_Memory != (undefined4 *)0x0) {
            FID_conflict__free(_Memory);
          }
          goto LAB_0040ad14;
        }
        uVar4 = uVar4 + 1;
        local_2c = local_2c + 0x13;
      } while (uVar4 < local_24);
    }
    if (7 < local_4c) {
      FUN_00402430(local_60,local_4c + 1,2);
    }
    local_4c = 7;
    local_50 = 0;
    local_60 = (undefined1 (*) [16])((uint)local_60 & 0xffff0000);
    if (_Memory != (undefined4 *)0x0) {
      FID_conflict__free(_Memory);
    }
  }
  local_40 = 0;
  uStack_3c = 0;
  uStack_38 = 0;
  uStack_34 = 0;
LAB_0040ad14:
  *param_1 = local_40;
  param_1[1] = uStack_3c;
  param_1[2] = uStack_38;
  param_1[3] = uStack_34;
  ExceptionList = local_1c;
  return;
}


