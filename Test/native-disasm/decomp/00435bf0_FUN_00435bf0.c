// FUN_00435bf0 @ 00435bf0 size=72 callers=1

void __thiscall FUN_00435bf0(void *this,undefined4 param_1,undefined4 *param_2)

{
  void *pvVar1;
  int extraout_ECX;
  
  *(undefined4 *)this = 0;
  *(undefined4 *)((int)this + 4) = 0;
  *(undefined4 *)((int)this + 8) = 0;
  pvVar1 = FUN_0043f960(1);
  *(void **)this = pvVar1;
  *(void **)((int)this + 4) = pvVar1;
  *(int *)((int)this + 8) = *(int *)this + 4;
  FUN_00447da0(*(void **)this,param_2);
  *(int *)((int)this + 4) = extraout_ECX + 4;
  return;
}


