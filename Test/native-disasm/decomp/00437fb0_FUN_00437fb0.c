// FUN_00437fb0 @ 00437fb0 size=189 callers=1

void * __thiscall FUN_00437fb0(void *this,undefined4 param_1)

{
  lconv *plVar1;
  void *_Dst;
  char cVar2;
  
  *(undefined4 *)this = param_1;
  _memset((void *)((int)this + 4),0,0x40);
  plVar1 = _localeconv();
  *(lconv **)((int)this + 0x44) = plVar1;
  if (plVar1->thousands_sep == (char *)0x0) {
    cVar2 = '\0';
  }
  else {
    cVar2 = *plVar1->thousands_sep;
  }
  *(char *)((int)this + 0x48) = cVar2;
  if (plVar1->decimal_point == (char *)0x0) {
    cVar2 = '\0';
  }
  else {
    cVar2 = *plVar1->decimal_point;
  }
  *(char *)((int)this + 0x49) = cVar2;
  *(undefined4 *)((int)this + 0x60) = 0xf;
  *(undefined4 *)((int)this + 0x5c) = 0;
  *(undefined1 *)((int)this + 0x4c) = 0;
  if (*(uint *)((int)this + 0x60) < 0x200) {
    FUN_0043f5f0((void *)((int)this + 0x4c),0x200);
  }
  if (*(uint *)((int)this + 0x60) < 0x10) {
    _Dst = (void *)((int)this + 0x4c);
  }
  else {
    _Dst = *(void **)((int)this + 0x4c);
  }
  _memset(_Dst,0x20,0x200);
  *(undefined4 *)((int)this + 0x5c) = 0x200;
  if (0xf < *(uint *)((int)this + 0x60)) {
    *(undefined1 *)(*(int *)((int)this + 0x4c) + 0x200) = 0;
    return this;
  }
  *(undefined1 *)((int)this + 0x24c) = 0;
  return this;
}


