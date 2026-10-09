// FUN_00416a50 @ 00416a50 size=48 callers=1

void * __thiscall FUN_00416a50(void *this,SIZE_T param_1)

{
  HGLOBAL hMem;
  LPVOID pvVar1;
  
  hMem = GlobalAlloc(2,param_1);
  *(undefined4 *)((int)this + 4) = 0;
  *(HGLOBAL *)this = hMem;
  if (hMem != (HGLOBAL)0x0) {
    pvVar1 = GlobalLock(hMem);
    *(LPVOID *)((int)this + 4) = pvVar1;
  }
  *(undefined1 *)((int)this + 8) = 0;
  return this;
}


