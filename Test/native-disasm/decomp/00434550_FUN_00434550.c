// FUN_00434550 @ 00434550 size=163 callers=12

int __thiscall FUN_00434550(void *this,int param_1)

{
  uint *puVar1;
  undefined1 local_58 [24];
  undefined1 local_40 [24];
  undefined **local_28;
  undefined8 local_24;
  undefined4 *local_1c;
  undefined1 local_18;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047db10;
  local_10 = ExceptionList;
  if (*(char *)this == '\x02') {
    return param_1 * 0x10 + **(int **)((int)this + 8);
  }
  ExceptionList = &local_10;
  puVar1 = (uint *)FUN_00438430(this,local_40);
  local_8 = 0;
  local_1c = (undefined4 *)FUN_00442600(local_58,(uint *)"cannot use operator[] with ",puVar1);
  local_8 = CONCAT31(local_8._1_3_,1);
  if (0xf < (uint)local_1c[5]) {
    local_1c = (undefined4 *)*local_1c;
  }
  local_28 = std::exception::vftable;
  local_24 = 0;
  local_18 = 1;
  ___std_exception_copy(&local_1c,(undefined4 *)&local_24);
  local_28 = &PTR_FUN_0048eee8;
                    /* WARNING: Subroutine does not return */
  __CxxThrowException_8((int *)&local_28,&DAT_0049a03c);
}


