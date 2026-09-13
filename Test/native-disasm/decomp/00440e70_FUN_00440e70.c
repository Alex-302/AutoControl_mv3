// FUN_00440e70 @ 00440e70 size=296 callers=112

undefined4 * __thiscall FUN_00440e70(void *this,uint *param_1)

{
  uint uVar1;
  uint *puVar2;
  undefined1 local_7c [24];
  undefined1 local_64 [24];
  void *local_4c [4];
  undefined4 local_3c;
  uint local_38;
  undefined **local_34;
  undefined8 local_30;
  undefined4 *local_28;
  undefined1 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047e018;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  if (*(char *)this == '\0') {
    ExceptionList = &local_10;
    *(undefined1 *)this = 1;
    FUN_004381d0(&local_20,'\x01');
    *(undefined4 *)((int)this + 8) = local_20;
    *(undefined4 *)((int)this + 0xc) = local_1c;
  }
  if (*(char *)this == '\x01') {
    local_38 = 0xf;
    local_3c = 0;
    local_4c[0] = (void *)((uint)local_4c[0] & 0xffffff00);
    if ((char)*param_1 == '\0') {
      uVar1 = 0;
    }
    else {
      puVar2 = param_1;
      do {
        uVar1 = *puVar2;
        puVar2 = (uint *)((int)puVar2 + 1);
      } while ((char)uVar1 != '\0');
      uVar1 = (int)puVar2 - ((int)param_1 + 1);
    }
    FUN_0043ace0(local_4c,param_1,uVar1);
    local_8 = 0;
    FUN_00449880(*(void **)((int)this + 8),&local_28,(byte *)local_4c);
    if (0xf < local_38) {
      FUN_00402430(local_4c[0],local_38 + 1,1);
    }
    ExceptionList = local_10;
    return local_28 + 10;
  }
  puVar2 = (uint *)FUN_00438430(this,local_64);
  local_8 = 1;
  local_28 = (undefined4 *)FUN_00442600(local_7c,(uint *)"cannot use operator[] with ",puVar2);
  local_8 = CONCAT31(local_8._1_3_,2);
  if (0xf < (uint)local_28[5]) {
    local_28 = (undefined4 *)*local_28;
  }
  local_34 = std::exception::vftable;
  local_30 = 0;
  local_24 = 1;
  ___std_exception_copy(&local_28,(undefined4 *)&local_30);
  local_34 = &PTR_FUN_0048eee8;
                    /* WARNING: Subroutine does not return */
  __CxxThrowException_8((int *)&local_34,&DAT_0049a03c);
}


