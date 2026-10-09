// FUN_0040a510 @ 0040a510 size=60 callers=1

void * __thiscall FUN_0040a510(void *this,uint param_1)

{
  *(undefined ***)this = &PTR_FUN_0048e4a4;
  GdipDeleteBrush(*(undefined4 *)((int)this + 4));
  if ((param_1 & 1) != 0) {
    if ((param_1 & 4) == 0) {
      GdipFree(this);
      return this;
    }
    guard_check_icall();
  }
  return this;
}


