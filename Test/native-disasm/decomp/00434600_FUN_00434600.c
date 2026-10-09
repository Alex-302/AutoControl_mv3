// FUN_00434600 @ 00434600 size=305 callers=10

int __thiscall FUN_00434600(void *this,uint param_1)

{
  int *piVar1;
  char *pcVar2;
  uint uVar3;
  undefined4 *puVar4;
  uint *puVar5;
  undefined1 local_60 [24];
  undefined1 local_48 [24];
  char local_30 [4];
  undefined **local_2c;
  undefined8 local_28;
  undefined4 *local_1c;
  undefined1 local_18;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047db3e;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  if (*(char *)this == '\0') {
    ExceptionList = &local_10;
    *(undefined1 *)this = 2;
    puVar4 = operator_new(0xc);
    if (puVar4 != (undefined4 *)0x0) {
      *puVar4 = 0;
      puVar4[1] = 0;
      puVar4[2] = 0;
    }
    *(undefined4 **)((int)this + 8) = puVar4;
  }
  uVar3 = param_1;
  if (*(char *)this == '\x02') {
    piVar1 = *(int **)((int)this + 8);
    if ((uint)(piVar1[1] - *piVar1 >> 4) <= param_1) {
      pcVar2 = (char *)piVar1[1];
      local_8 = 0;
      local_30[0] = '\0';
      FUN_004381d0(&local_28,'\0');
      local_8 = 1;
      piVar1 = *(int **)((int)this + 8);
      FUN_0043d1c0(piVar1,(int *)&param_1,pcVar2,(uVar3 - (piVar1[1] - *piVar1 >> 4)) + 1,local_30);
      FUN_00434820(local_30);
    }
    ExceptionList = local_10;
    return uVar3 * 0x10 + **(int **)((int)this + 8);
  }
  puVar5 = (uint *)FUN_00438430(this,local_48);
  local_8 = 2;
  local_1c = (undefined4 *)FUN_00442600(local_60,(uint *)"cannot use operator[] with ",puVar5);
  local_8 = CONCAT31(local_8._1_3_,3);
  if (0xf < (uint)local_1c[5]) {
    local_1c = (undefined4 *)*local_1c;
  }
  local_2c = std::exception::vftable;
  local_28 = 0;
  local_18 = 1;
  ___std_exception_copy(&local_1c,(undefined4 *)&local_28);
  local_2c = &PTR_FUN_0048eee8;
                    /* WARNING: Subroutine does not return */
  __CxxThrowException_8((int *)&local_2c,&DAT_0049a03c);
}


