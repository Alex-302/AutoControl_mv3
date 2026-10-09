// FUN_00434a40 @ 00434a40 size=189 callers=13

void * __thiscall FUN_00434a40(void *this,char *param_1,char *param_2)

{
  undefined4 uVar1;
  void *local_28;
  undefined4 local_24;
  undefined4 local_20;
  char *local_1c;
  undefined1 local_18;
  undefined **local_14;
  undefined8 local_10;
  
  local_20 = 0;
  *(undefined1 *)this = 0;
  *(undefined8 *)((int)this + 8) = 0;
  local_28 = this;
  uVar1 = FUN_004476b0(param_1,param_2);
  if ((char)uVar1 != '\0') {
    *(undefined1 *)this = 1;
    FUN_004381d0(&local_28,'\x01');
    *(void **)((int)this + 8) = local_28;
    *(undefined4 *)((int)this + 0xc) = local_24;
    local_28 = this;
    FUN_00447920(param_1,param_2,(int *)&local_28);
    return this;
  }
  local_14 = std::exception::vftable;
  local_1c = "cannot create object from initializer list";
  local_18 = 1;
  local_10 = 0;
  ___std_exception_copy(&local_1c,(undefined4 *)&local_10);
  local_14 = &PTR_FUN_0048eee8;
                    /* WARNING: Subroutine does not return */
  __CxxThrowException_8((int *)&local_14,&DAT_0049a03c);
}


