// FUN_00439b80 @ 00439b80 size=209 callers=1

void __thiscall FUN_00439b80(void *this,byte *param_1)

{
  uint *puVar1;
  void *extraout_ECX;
  void *pvVar2;
  undefined1 local_5c [24];
  undefined1 local_44 [24];
  undefined **local_2c;
  undefined8 local_28;
  undefined4 *local_20;
  undefined4 local_1c;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047da90;
  local_10 = ExceptionList;
  if (*(char *)this == '\0') {
    ExceptionList = &local_10;
    *(undefined1 *)this = 1;
    FUN_004381d0(&local_20,'\x01');
    *(undefined4 **)((int)this + 8) = local_20;
    *(undefined4 *)((int)this + 0xc) = local_1c;
    pvVar2 = extraout_ECX;
  }
  else {
    pvVar2 = this;
    ExceptionList = &local_10;
    if (*(char *)this != '\x01') {
      ExceptionList = &local_10;
      puVar1 = (uint *)FUN_00438430(this,local_44);
      local_8 = 0;
      local_20 = (undefined4 *)FUN_00442600(local_5c,(uint *)"cannot use push_back() with ",puVar1);
      local_8 = CONCAT31(local_8._1_3_,1);
      if (0xf < (uint)local_20[5]) {
        local_20 = (undefined4 *)*local_20;
      }
      local_2c = std::exception::vftable;
      local_28 = 0;
      local_1c = CONCAT31(local_1c._1_3_,1);
      ___std_exception_copy(&local_20,(undefined4 *)&local_28);
      local_2c = &PTR_FUN_0048eee8;
                    /* WARNING: Subroutine does not return */
      __CxxThrowException_8((int *)&local_2c,&DAT_0049a03c);
    }
  }
  FUN_00447b80(*(void **)((int)this + 8),&local_20,pvVar2,param_1,param_1);
  ExceptionList = local_10;
  return;
}


