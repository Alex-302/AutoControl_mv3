// FUN_00402b70 @ 00402b70 size=80 callers=1

void * __thiscall FUN_00402b70(void *this,byte param_1)

{
  *(undefined ***)this = std::ctype<char>::vftable;
  if (*(int *)((int)this + 0x10) < 1) {
    if (*(int *)((int)this + 0x10) < 0) {
      FID_conflict__free(*(void **)((int)this + 0xc));
    }
  }
  else {
    FID_conflict__free(*(void **)((int)this + 0xc));
  }
  FID_conflict__free(*(void **)((int)this + 0x14));
  *(undefined ***)this = std::_Facet_base::vftable;
  if ((param_1 & 1) != 0) {
    FUN_0045a6a4(this);
  }
  return this;
}


