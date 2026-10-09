// FUN_0043a990 @ 0043a990 size=92 callers=1

void __thiscall FUN_0043a990(void *this,char param_1,uint param_2)

{
  uint *puVar1;
  
  if ((param_1 != '\0') && (0xf < *(uint *)((int)this + 0x14))) {
    puVar1 = *(uint **)this;
    if (param_2 != 0) {
      FUN_0045c870(this,puVar1,param_2);
    }
    FUN_00402430(puVar1,*(int *)((int)this + 0x14) + 1,1);
  }
  *(undefined4 *)((int)this + 0x14) = 0xf;
  *(uint *)((int)this + 0x10) = param_2;
  if (0xf < *(uint *)((int)this + 0x14)) {
    *(undefined1 *)(*(int *)this + param_2) = 0;
    return;
  }
  *(undefined1 *)((int)this + param_2) = 0;
  return;
}


