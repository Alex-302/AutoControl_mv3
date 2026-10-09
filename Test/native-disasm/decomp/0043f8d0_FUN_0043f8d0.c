// FUN_0043f8d0 @ 0043f8d0 size=50 callers=1

void * __thiscall FUN_0043f8d0(void *this,byte param_1)

{
  *(undefined ***)this = std::collate<char>::vftable;
  FID_conflict__free(*(void **)((int)this + 0xc));
  *(undefined ***)this = std::_Facet_base::vftable;
  if ((param_1 & 1) != 0) {
    FUN_0045a6a4(this);
  }
  return this;
}


