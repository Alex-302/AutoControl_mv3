// FUN_0043f200 @ 0043f200 size=50 callers=1

uint __thiscall FUN_0043f200(void *this,char *param_1,char *param_2,char *param_3,char *param_4)

{
  int iVar1;
  
  iVar1 = __Strcoll(param_1,param_2,param_3,param_4,(_Collvec *)((int)this + 8));
  if (iVar1 < 0) {
    return 0xffffffff;
  }
  return (uint)(iVar1 != 0);
}


