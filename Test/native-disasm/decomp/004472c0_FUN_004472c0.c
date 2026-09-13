// FUN_004472c0 @ 004472c0 size=91 callers=1

void __thiscall FUN_004472c0(void *this,undefined4 *param_1)

{
  if (this != (void *)0x0) {
    *(undefined ***)this = &PTR_FUN_0048e7d0;
    *(undefined4 *)((int)this + 4) = *param_1;
    *(undefined4 *)((int)this + 8) = param_1[1];
    *(undefined4 *)((int)this + 0xc) = 0;
    *(undefined4 *)((int)this + 0x10) = 0;
    *(undefined4 *)((int)this + 0x14) = 0;
    *(undefined4 *)((int)this + 0xc) = param_1[2];
    *(undefined4 *)((int)this + 0x10) = param_1[3];
    *(undefined4 *)((int)this + 0x14) = param_1[4];
    param_1[2] = 0;
    param_1[3] = 0;
    param_1[4] = 0;
  }
  *(void **)((int)this + 0x24) = this;
  return;
}


