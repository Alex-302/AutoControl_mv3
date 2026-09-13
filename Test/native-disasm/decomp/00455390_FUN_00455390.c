// FUN_00455390 @ 00455390 size=44 callers=1

void * __thiscall FUN_00455390(void *this,byte param_1)

{
  FID_conflict__free(*(void **)((int)this + 0x1c));
  *(undefined ***)this = &PTR_LAB_0048ecb0;
  if ((param_1 & 1) != 0) {
    FUN_0045a6a4(this);
  }
  return this;
}


