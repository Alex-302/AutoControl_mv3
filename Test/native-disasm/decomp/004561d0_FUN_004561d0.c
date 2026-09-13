// FUN_004561d0 @ 004561d0 size=184 callers=1

void * __thiscall FUN_004561d0(void *this,undefined4 *param_1)

{
  *(undefined4 *)this = 0;
  *(undefined4 *)((int)this + 4) = 0;
  *(undefined4 *)((int)this + 8) = 0;
  *(undefined4 *)this = *param_1;
  *(undefined4 *)((int)this + 4) = param_1[1];
  *(undefined4 *)((int)this + 8) = param_1[2];
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  *(undefined4 *)((int)this + 0xc) = param_1[3];
  *(undefined2 *)((int)this + 0xc) = *(undefined2 *)(param_1 + 3);
  *(undefined2 *)((int)this + 0xc) = *(undefined2 *)(param_1 + 3);
  *(undefined1 *)((int)this + 0xe) = *(undefined1 *)((int)param_1 + 0xe);
  *(undefined2 *)((int)this + 0xc) = *(undefined2 *)(param_1 + 3);
  *(undefined2 *)((int)this + 0xe) = *(undefined2 *)((int)param_1 + 0xe);
  *(undefined2 *)((int)this + 0xc) = *(undefined2 *)(param_1 + 3);
  *(undefined1 *)((int)this + 0xe) = *(undefined1 *)((int)param_1 + 0xe);
  *(undefined4 *)((int)this + 0x10) = param_1[4];
  *(undefined8 *)((int)this + 0x14) = *(undefined8 *)(param_1 + 5);
  *(undefined2 *)((int)this + 0x1c) = *(undefined2 *)(param_1 + 7);
  *(undefined1 *)((int)this + 0x1e) = *(undefined1 *)((int)param_1 + 0x1e);
  *(undefined1 *)((int)this + 0x1f) = *(undefined1 *)((int)param_1 + 0x1f);
  *(undefined1 *)((int)this + 0x20) = *(undefined1 *)(param_1 + 8);
  *(undefined1 *)((int)this + 0x21) = *(undefined1 *)((int)param_1 + 0x21);
  *(undefined1 *)((int)this + 0x22) = *(undefined1 *)((int)param_1 + 0x22);
  return this;
}


