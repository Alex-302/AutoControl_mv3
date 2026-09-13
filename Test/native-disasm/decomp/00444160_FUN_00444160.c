// FUN_00444160 @ 00444160 size=124 callers=1

int __thiscall FUN_00444160(void *this,int param_1)

{
  char *local_14;
  undefined1 local_10;
  undefined **local_c;
  undefined8 local_8;
  
  if (**(char **)this == '\x01') {
    local_c = std::exception::vftable;
    local_14 = "cannot use offsets with object iterators";
    local_10 = 1;
    local_8 = 0;
    ___std_exception_copy(&local_14,(undefined4 *)&local_8);
    local_c = &PTR_FUN_0048eee8;
                    /* WARNING: Subroutine does not return */
    __CxxThrowException_8((int *)&local_c,&DAT_0049a03c);
  }
  if (**(char **)this != '\x02') {
    return *(int *)((int)this + 0xc) - *(int *)(param_1 + 0xc);
  }
  return *(int *)((int)this + 8) - *(int *)(param_1 + 8) >> 4;
}


