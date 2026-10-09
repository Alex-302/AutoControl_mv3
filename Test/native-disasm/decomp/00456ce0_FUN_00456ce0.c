// FUN_00456ce0 @ 00456ce0 size=156 callers=1

void * __thiscall FUN_00456ce0(void *this,undefined4 *param_1)

{
  int *piVar1;
  int iVar2;
  _Locimp *p_Var3;
  _Facet_base *p_Var4;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_004791b6;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  *(undefined4 *)this = 0;
  local_8 = 0;
  p_Var3 = std::locale::_Init(true);
  *(_Locimp **)((int)this + 0x10) = p_Var3;
  local_8 = 0xffffffff;
  p_Var4 = FUN_004436c0((void *)((int)this + 0xc));
  *(_Facet_base **)((int)this + 4) = p_Var4;
  p_Var4 = FUN_00440660((int)this + 0xc);
  *(_Facet_base **)((int)this + 8) = p_Var4;
  if (this != param_1) {
    if (*(int *)this != 0) {
      LOCK();
      piVar1 = (int *)(*(int *)this + 0x20);
      iVar2 = *piVar1 + -1;
      *piVar1 = iVar2;
      UNLOCK();
      if (iVar2 == 0) {
        FUN_004033e0(*(undefined4 **)this,(undefined4 *)0x0);
      }
    }
    *(undefined4 *)this = 0;
    *(undefined4 *)this = *param_1;
    *param_1 = 0;
  }
  ExceptionList = local_10;
  return this;
}


