// FUN_004383a0 @ 004383a0 size=142 callers=72

undefined4 __thiscall FUN_004383a0(void *this,int *param_1)

{
  char cVar1;
  char *local_14;
  undefined1 local_10;
  undefined **local_c;
  undefined8 local_8;
  
  if (*(char **)this != (char *)*param_1) {
    local_c = std::exception::vftable;
    local_14 = "cannot compare iterators of different containers";
    local_10 = 1;
    local_8 = 0;
    ___std_exception_copy(&local_14,(undefined4 *)&local_8);
    local_c = &PTR_FUN_0048eee8;
                    /* WARNING: Subroutine does not return */
    __CxxThrowException_8((int *)&local_c,&DAT_0049a03c);
  }
  cVar1 = **(char **)this;
  if (cVar1 != '\x01') {
    if (cVar1 != '\x02') {
      return CONCAT31((int3)((uint)*(int *)((int)this + 0xc) >> 8),
                      *(int *)((int)this + 0xc) == param_1[3]);
    }
    return CONCAT31((int3)((uint)*(int *)((int)this + 8) >> 8),*(int *)((int)this + 8) == param_1[2]
                   );
  }
  return CONCAT31((int3)((uint)*(int *)((int)this + 4) >> 8),*(int *)((int)this + 4) == param_1[1]);
}


