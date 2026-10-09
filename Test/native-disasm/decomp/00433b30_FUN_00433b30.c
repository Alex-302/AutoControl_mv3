// FUN_00433b30 @ 00433b30 size=137 callers=11

undefined1 * __thiscall FUN_00433b30(void *this,undefined1 *param_1)

{
  int iVar1;
  char *local_14;
  undefined1 local_10;
  undefined **local_c;
  undefined8 local_8;
  
  if (**(char **)this == '\x01') {
    iVar1 = *(int *)((int)this + 4);
    *(undefined4 *)(param_1 + 0x14) = 0xf;
    *(undefined4 *)(param_1 + 0x10) = 0;
    *param_1 = 0;
    FUN_0043ade0(param_1,(undefined4 *)(iVar1 + 0x10),0,0xffffffff);
    return param_1;
  }
  local_c = std::exception::vftable;
  local_14 = "cannot use key() for non-object iterators";
  local_10 = 1;
  local_8 = 0;
  ___std_exception_copy(&local_14,(undefined4 *)&local_8);
  local_c = &PTR_FUN_0048eee8;
                    /* WARNING: Subroutine does not return */
  __CxxThrowException_8((int *)&local_c,&DAT_0049a03c);
}


