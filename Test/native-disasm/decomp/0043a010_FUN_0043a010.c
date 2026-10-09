// FUN_0043a010 @ 0043a010 size=99 callers=1

void __thiscall FUN_0043a010(void *this,char param_1,int param_2)

{
  uint *puVar1;
  
  if ((param_1 != '\0') && (7 < *(uint *)((int)this + 0x14))) {
    puVar1 = *(uint **)this;
    if (param_2 != 0) {
      FUN_0045c870(this,puVar1,param_2 * 2);
    }
    FUN_00402430(puVar1,*(int *)((int)this + 0x14) + 1,2);
  }
  *(undefined4 *)((int)this + 0x14) = 7;
  *(int *)((int)this + 0x10) = param_2;
  if (7 < *(uint *)((int)this + 0x14)) {
    *(undefined2 *)(*(int *)this + param_2 * 2) = 0;
    return;
  }
  *(undefined2 *)((int)this + param_2 * 2) = 0;
  return;
}


