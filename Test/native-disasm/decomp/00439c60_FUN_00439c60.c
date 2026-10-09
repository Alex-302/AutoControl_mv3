// FUN_00439c60 @ 00439c60 size=185 callers=6

void __thiscall FUN_00439c60(void *this,byte *param_1)

{
  uint *puVar1;
  undefined1 local_98 [24];
  undefined1 local_80 [84];
  undefined **local_2c;
  undefined8 local_28;
  undefined4 *local_20;
  undefined1 local_1c;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047ddc3;
  local_10 = ExceptionList;
  local_14 = &stack0xffffff58;
  if (*(char *)this == '\x01') {
    local_8 = 0;
    ExceptionList = &local_10;
    local_14 = &stack0xffffff58;
    FUN_0043d520(*(void **)((int)this + 8),param_1);
    ExceptionList = local_10;
    return;
  }
  ExceptionList = &local_10;
  puVar1 = (uint *)FUN_00438430(this,local_80);
  local_8 = 4;
  local_20 = (undefined4 *)FUN_00442600(local_98,(uint *)"cannot use at() with ",puVar1);
  local_8 = CONCAT31(local_8._1_3_,5);
  if (0xf < (uint)local_20[5]) {
    local_20 = (undefined4 *)*local_20;
  }
  local_2c = std::exception::vftable;
  local_28 = 0;
  local_1c = 1;
  ___std_exception_copy(&local_20,(undefined4 *)&local_28);
  local_2c = &PTR_FUN_0048eee8;
                    /* WARNING: Subroutine does not return */
  __CxxThrowException_8((int *)&local_2c,&DAT_0049a03c);
}


