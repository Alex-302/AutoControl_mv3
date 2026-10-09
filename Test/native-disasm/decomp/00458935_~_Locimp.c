// ~_Locimp @ 00458935 size=91 callers=1

/* Library Function - Single Match
    protected: virtual __thiscall std::locale::_Locimp::~_Locimp(void)
   
   Library: Visual Studio 2015 Release */

void __thiscall std::locale::_Locimp::~_Locimp(_Locimp *this)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 uStack_8;
  
  uStack_8 = 0xffffffff;
  puStack_c = &LAB_0047ed78;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  *(undefined ***)this = vftable;
  _Locimp_dtor(this);
  if (*(int *)(this + 0x18) != 0) {
    FID_conflict__free(*(void **)(this + 0x18));
  }
  *(undefined4 *)(this + 0x18) = 0;
  *(undefined ***)this = _Facet_base::vftable;
  ExceptionList = local_10;
  return;
}


