// FUN_00456c20 @ 00456c20 size=177 callers=2

void * __thiscall FUN_00456c20(void *this,undefined4 *param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0047c863;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  *(undefined4 *)this = 0;
  *(undefined4 *)((int)this + 4) = 0;
  *(undefined4 *)((int)this + 8) = 0;
  *(undefined4 *)this = *param_1;
  *(undefined4 *)((int)this + 4) = param_1[1];
  *(undefined4 *)((int)this + 8) = param_1[2];
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  *(undefined4 *)((int)this + 0xc) = param_1[3];
  param_1[3] = 0;
  local_8 = 0;
  FUN_00437780((void *)((int)this + 0x10),param_1 + 4);
  local_8 = CONCAT31(local_8._1_3_,1);
  FUN_00437600((void *)((int)this + 0x30),param_1 + 0xc);
  *(undefined4 *)((int)this + 0x50) = param_1[0x14];
  *(undefined4 *)((int)this + 0x54) = param_1[0x15];
  ExceptionList = local_10;
  return this;
}


