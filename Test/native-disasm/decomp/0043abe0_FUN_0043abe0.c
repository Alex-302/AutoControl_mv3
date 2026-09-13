// FUN_0043abe0 @ 0043abe0 size=40 callers=2

void __thiscall FUN_0043abe0(void *this,uint param_1,char param_2)

{
  if (param_1 <= *(uint *)((int)this + 0x10)) {
    *(uint *)((int)this + 0x10) = param_1;
    if (0xf < *(uint *)((int)this + 0x14)) {
      this = *(void **)this;
    }
    *(undefined1 *)((int)this + param_1) = 0;
    return;
  }
  FUN_0043aef0(this,param_1 - *(uint *)((int)this + 0x10),param_2);
  return;
}


