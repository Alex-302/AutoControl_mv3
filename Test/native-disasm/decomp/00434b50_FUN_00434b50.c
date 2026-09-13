// FUN_00434b50 @ 00434b50 size=221 callers=165

void * __thiscall FUN_00434b50(void *this,char *param_1,char *param_2,char param_3,char param_4)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  char *local_20;
  undefined4 local_1c;
  undefined **local_14;
  undefined8 local_10;
  
  *(undefined1 *)this = 0;
  *(undefined8 *)((int)this + 8) = 0;
  uVar1 = FUN_004476b0(param_1,param_2);
  if (param_3 == '\0') {
    if (param_4 == '\x02') goto LAB_00434bcf;
    if (param_4 == '\x01') {
      if ((char)uVar1 == '\0') {
        local_14 = std::exception::vftable;
        local_20 = "cannot create object from initializer list";
        local_1c = CONCAT31(local_1c._1_3_,1);
        local_10 = 0;
        ___std_exception_copy(&local_20,(undefined4 *)&local_10);
        local_14 = &PTR_FUN_0048eee8;
                    /* WARNING: Subroutine does not return */
        __CxxThrowException_8((int *)&local_14,&DAT_0049a03c);
      }
      goto LAB_00434b93;
    }
  }
  if ((char)uVar1 != '\0') {
LAB_00434b93:
    *(undefined1 *)this = 1;
    FUN_004381d0(&local_20,'\x01');
    *(char **)((int)this + 8) = local_20;
    *(undefined4 *)((int)this + 0xc) = local_1c;
    local_20 = this;
    FUN_00447920(param_1,param_2,(int *)&local_20);
    return this;
  }
LAB_00434bcf:
  *(undefined1 *)this = 2;
  puVar2 = FUN_004429e0((int *)&param_1);
  *(undefined4 **)((int)this + 8) = puVar2;
  return this;
}


