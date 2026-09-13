// FUN_00439d60 @ 00439d60 size=216 callers=1

int __thiscall FUN_00439d60(void *this,uint param_1)

{
  int iVar1;
  uint *puVar2;
  undefined1 local_b0 [24];
  undefined1 local_98 [108];
  undefined4 *local_2c;
  undefined1 local_28;
  undefined **local_24;
  undefined8 local_20;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047ddfe;
  local_10 = ExceptionList;
  local_14 = &stack0xffffff40;
  if (*(char *)this != '\x02') {
    ExceptionList = &local_10;
    puVar2 = (uint *)FUN_00438430(this,local_98);
    local_8 = 5;
    local_2c = (undefined4 *)FUN_00442600(local_b0,(uint *)"cannot use at() with ",puVar2);
    local_8 = CONCAT31(local_8._1_3_,6);
    if (0xf < (uint)local_2c[5]) {
      local_2c = (undefined4 *)*local_2c;
    }
    local_24 = std::exception::vftable;
    local_20 = 0;
    local_28 = 1;
    ___std_exception_copy(&local_2c,(undefined4 *)&local_20);
    local_24 = &PTR_FUN_0048eee8;
                    /* WARNING: Subroutine does not return */
    __CxxThrowException_8((int *)&local_24,&DAT_0049a03c);
  }
  local_8 = 0;
  iVar1 = **(int **)((int)this + 8);
  if ((uint)((*(int **)((int)this + 8))[1] - iVar1 >> 4) <= param_1) {
    ExceptionList = &local_10;
    local_14 = &stack0xffffff40;
                    /* WARNING: Subroutine does not return */
    FUN_00458ee4("invalid vector<T> subscript");
  }
  return iVar1 + param_1 * 0x10;
}


