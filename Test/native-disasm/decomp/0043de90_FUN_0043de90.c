// FUN_0043de90 @ 0043de90 size=66 callers=1

void __thiscall FUN_0043de90(void *this,int param_1,size_t param_2,char param_3)

{
  if (param_2 == 1) {
    if (0xf < *(uint *)((int)this + 0x14)) {
      this = *(void **)this;
    }
    *(char *)((int)this + param_1) = param_3;
    return;
  }
  if (0xf < *(uint *)((int)this + 0x14)) {
    this = *(void **)this;
  }
  _memset((void *)(param_1 + (int)this),(int)param_3,param_2);
  return;
}


