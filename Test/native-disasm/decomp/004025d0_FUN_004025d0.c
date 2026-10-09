// FUN_004025d0 @ 004025d0 size=204 callers=2

void * __thiscall FUN_004025d0(void *this,char *param_1)

{
  undefined **local_28;
  undefined8 local_24;
  char *local_1c;
  undefined1 local_18;
  void *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_004790da;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_14 = this;
  std::_Lockit::_Lockit(this,0);
  *(undefined4 *)((int)this + 4) = 0;
  *(undefined1 *)((int)this + 8) = 0;
  *(undefined4 *)((int)this + 0xc) = 0;
  *(undefined1 *)((int)this + 0x10) = 0;
  *(undefined4 *)((int)this + 0x14) = 0;
  *(undefined2 *)((int)this + 0x18) = 0;
  *(undefined4 *)((int)this + 0x1c) = 0;
  *(undefined2 *)((int)this + 0x20) = 0;
  *(undefined4 *)((int)this + 0x24) = 0;
  *(undefined1 *)((int)this + 0x28) = 0;
  *(undefined4 *)((int)this + 0x2c) = 0;
  *(undefined1 *)((int)this + 0x30) = 0;
  local_8 = 6;
  if (param_1 == (char *)0x0) {
    local_28 = std::exception::vftable;
    local_1c = "bad locale name";
    local_18 = 1;
    local_24 = 0;
    ___std_exception_copy(&local_1c,(undefined4 *)&local_24);
    local_28 = std::runtime_error::vftable;
                    /* WARNING: Subroutine does not return */
    __CxxThrowException_8((int *)&local_28,&DAT_00499efc);
  }
  std::_Locinfo::_Locinfo_ctor(this,param_1);
  ExceptionList = local_10;
  return this;
}


