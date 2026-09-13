// FUN_0040a470 @ 0040a470 size=60 callers=1

void * __thiscall FUN_0040a470(void *this,uint param_1)

{
  *(undefined ***)this = &PTR_FUN_0048ed48;
  GdipDisposeImage(*(undefined4 *)((int)this + 4));
  if ((param_1 & 1) != 0) {
    if ((param_1 & 4) == 0) {
      GdipFree(this);
      return this;
    }
    guard_check_icall();
  }
  return this;
}


