// FUN_0043ac10 @ 0043ac10 size=193 callers=9

void * __thiscall FUN_0043ac10(void *this,uint param_1,char param_2)

{
  void *_Dst;
  
  if (param_1 == 0xffffffff) {
                    /* WARNING: Subroutine does not return */
    FUN_00458ec4("string too long");
  }
  if (param_1 == 0xffffffff) {
                    /* WARNING: Subroutine does not return */
    FUN_00458ec4("string too long");
  }
  if (*(uint *)((int)this + 0x14) < param_1) {
    FUN_0043f5f0(this,param_1);
    if (param_1 == 0) {
      return this;
    }
  }
  else if (param_1 == 0) {
    *(undefined4 *)((int)this + 0x10) = 0;
    if (0xf < *(uint *)((int)this + 0x14)) {
      **(undefined1 **)this = 0;
      return this;
    }
    *(undefined1 *)this = 0;
    return this;
  }
  if (param_1 == 1) {
    if (*(uint *)((int)this + 0x14) < 0x10) {
      *(char *)this = param_2;
    }
    else {
      **(char **)this = param_2;
    }
  }
  else {
    _Dst = this;
    if (0xf < *(uint *)((int)this + 0x14)) {
      _Dst = *(void **)this;
    }
    _memset(_Dst,(int)param_2,param_1);
  }
  *(uint *)((int)this + 0x10) = param_1;
  if (*(uint *)((int)this + 0x14) < 0x10) {
    *(undefined1 *)((int)this + param_1) = 0;
    return this;
  }
  *(undefined1 *)(*(int *)this + param_1) = 0;
  return this;
}


