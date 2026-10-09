// FUN_00434210 @ 00434210 size=218 callers=1

int __thiscall FUN_00434210(void *this,byte *param_1)

{
  int iVar1;
  uint *puVar2;
  undefined1 local_5c [24];
  undefined1 local_44 [24];
  undefined **local_2c;
  undefined8 local_28;
  int *local_20;
  int *local_1c;
  void *local_18;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047da90;
  local_10 = ExceptionList;
  local_18 = this;
  if (*(char *)this == '\x01') {
    ExceptionList = &local_10;
    FUN_004437f0(*(void **)((int)this + 8),(int *)&local_20,param_1);
    iVar1 = FUN_00447a70(local_20,local_1c);
    FUN_0043d0d0(*(void **)((int)local_18 + 8),&param_1,local_20,local_1c);
    ExceptionList = local_10;
    return iVar1;
  }
  ExceptionList = &local_10;
  puVar2 = (uint *)FUN_00438430(this,local_44);
  local_8 = 0;
  local_20 = (int *)FUN_00442600(local_5c,(uint *)"cannot use erase() with ",puVar2);
  local_8 = CONCAT31(local_8._1_3_,1);
  if (0xf < (uint)local_20[5]) {
    local_20 = (int *)*local_20;
  }
  local_2c = std::exception::vftable;
  local_28 = 0;
  local_1c = (int *)CONCAT31(local_1c._1_3_,1);
  ___std_exception_copy(&local_20,(undefined4 *)&local_28);
  local_2c = &PTR_FUN_0048eee8;
                    /* WARNING: Subroutine does not return */
  __CxxThrowException_8((int *)&local_2c,&DAT_0049a03c);
}


