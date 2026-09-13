// FUN_00434440 @ 00434440 size=261 callers=24

undefined1 * __thiscall FUN_00434440(void *this,byte *param_1)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  uint *puVar3;
  undefined1 local_68 [24];
  undefined1 local_50 [24];
  undefined **local_38;
  undefined8 local_34;
  undefined1 *local_2c;
  undefined4 *local_28;
  undefined4 *local_24;
  undefined4 *local_20;
  undefined4 *local_1c;
  undefined1 local_15 [5];
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047dae9;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  if (*(char *)this == '\0') {
    ExceptionList = &local_10;
    *(undefined1 *)this = 1;
    puVar1 = operator_new(8);
    local_2c = local_15;
    local_8 = 1;
    local_28 = puVar1;
    local_20 = puVar1;
    local_1c = puVar1;
    if (puVar1 != (undefined4 *)0x0) {
      *puVar1 = 0;
      puVar1[1] = 0;
      uVar2 = FUN_00449130();
      *puVar1 = uVar2;
    }
    *(undefined4 **)((int)this + 8) = puVar1;
  }
  local_8 = 0xffffffff;
  if (*(char *)this == '\x01') {
    FUN_00447ae0(*(void **)((int)this + 8),&local_2c,param_1);
    ExceptionList = local_10;
    return local_2c + 0x28;
  }
  puVar3 = (uint *)FUN_00438430(this,local_50);
  local_8 = 2;
  local_24 = (undefined4 *)FUN_00442600(local_68,(uint *)"cannot use operator[] with ",puVar3);
  local_8 = CONCAT31(local_8._1_3_,3);
  if (0xf < (uint)local_24[5]) {
    local_24 = (undefined4 *)*local_24;
  }
  local_38 = std::exception::vftable;
  local_34 = 0;
  local_20 = (undefined4 *)CONCAT31(local_20._1_3_,1);
  ___std_exception_copy(&local_24,(undefined4 *)&local_34);
  local_38 = &PTR_FUN_0048eee8;
                    /* WARNING: Subroutine does not return */
  __CxxThrowException_8((int *)&local_38,&DAT_0049a03c);
}


