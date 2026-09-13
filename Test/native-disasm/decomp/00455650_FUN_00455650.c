// FUN_00455650 @ 00455650 size=89 callers=3

undefined1 __thiscall FUN_00455650(void *this,char param_1)

{
  if (param_1 == 'f') {
    *(undefined4 *)((int)this + 0x44) = 0xc;
    return 1;
  }
  if (param_1 == 'n') {
    *(undefined4 *)((int)this + 0x44) = 10;
    return 1;
  }
  if (param_1 == 'r') {
    *(undefined4 *)((int)this + 0x44) = 0xd;
    return 1;
  }
  if (param_1 == 't') {
    *(undefined4 *)((int)this + 0x44) = 9;
    return 1;
  }
  if (param_1 == 'v') {
    *(undefined4 *)((int)this + 0x44) = 0xb;
    return 1;
  }
  return 0;
}


