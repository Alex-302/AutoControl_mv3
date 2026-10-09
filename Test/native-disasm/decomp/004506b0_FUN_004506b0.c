// FUN_004506b0 @ 004506b0 size=49 callers=3

void * __thiscall FUN_004506b0(void *this,undefined4 *param_1)

{
  *(undefined4 *)this = *param_1;
  *(undefined4 *)((int)this + 0x10) = param_1[4];
  FUN_00450dd0((void *)((int)this + 4),param_1 + 1);
  FUN_004506f0((void *)((int)this + 0x14),param_1 + 5);
  return this;
}


