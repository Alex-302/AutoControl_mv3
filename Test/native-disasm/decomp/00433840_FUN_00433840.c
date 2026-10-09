// FUN_00433840 @ 00433840 size=176 callers=5

void * __thiscall FUN_00433840(void *this,char *param_1,uint param_2)

{
  char cVar1;
  _Locimp *p_Var2;
  _Facet_base *p_Var3;
  int iVar4;
  char *pcVar5;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0047d9bc;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  *(undefined4 *)this = 0;
  local_8 = 0;
  p_Var2 = std::locale::_Init(true);
  *(_Locimp **)((int)this + 0x10) = p_Var2;
  local_8 = 1;
  p_Var3 = FUN_004436c0((void *)((int)this + 0xc));
  *(_Facet_base **)((int)this + 4) = p_Var3;
  p_Var3 = FUN_00440660((int)this + 0xc);
  *(_Facet_base **)((int)this + 8) = p_Var3;
  local_8 = 2;
  if (*param_1 == '\0') {
    iVar4 = 0;
  }
  else {
    pcVar5 = param_1;
    do {
      cVar1 = *pcVar5;
      pcVar5 = pcVar5 + 1;
    } while (cVar1 != '\0');
    iVar4 = (int)pcVar5 - (int)(param_1 + 1);
  }
  FUN_00442790(this,param_1,param_1 + iVar4,param_2);
  ExceptionList = local_10;
  return this;
}


