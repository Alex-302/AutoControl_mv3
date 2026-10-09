// operator() @ 004657c9 size=154 callers=1

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Library Function - Single Match
    public: int __thiscall <lambda_b721fa326cdb32351d23dfa67958c160>::operator()(void)const 
   
   Library: Visual Studio 2015 Release */

int __thiscall
<lambda_b721fa326cdb32351d23dfa67958c160>::operator()
          (<lambda_b721fa326cdb32351d23dfa67958c160> *this)

{
  LPVOID pvVar1;
  int iVar2;
  uint uVar3;
  undefined4 uVar4;
  
  uVar3 = **(uint **)this & 0xfffffffe;
  ___acrt_stdio_flush_nolock((FILE *)**(undefined4 **)(this + 4));
  ___acrt_stdio_free_buffer_nolock((undefined4 *)**(undefined4 **)(this + 4));
  LOCK();
  *(uint *)(**(int **)(this + 4) + 0xc) = *(uint *)(**(int **)(this + 4) + 0xc) & 0xfffff81f;
  UNLOCK();
  if ((**(byte **)(this + 8) & 4) == 0) {
    pvVar1 = (LPVOID)**(int **)(this + 0xc);
    if (pvVar1 == (LPVOID)0x0) {
      pvVar1 = __malloc_base(uVar3);
      FID_conflict__free((void *)0x0);
      if (pvVar1 == (LPVOID)0x0) {
        _DAT_0049f560 = _DAT_0049f560 + 1;
        return -1;
      }
      uVar4 = 0x140;
    }
    else {
      uVar4 = 0x180;
    }
    iVar2 = **(int **)(this + 4);
  }
  else {
    uVar4 = 0x400;
    uVar3 = 2;
    pvVar1 = (LPVOID)(**(int **)(this + 4) + 0x14);
    iVar2 = **(int **)(this + 4);
  }
  iVar2 = set_buffer(iVar2,pvVar1,uVar3,uVar4);
  return iVar2;
}


