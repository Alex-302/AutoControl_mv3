// FUN_00450670 @ 00450670 size=49 callers=3

void * __thiscall FUN_00450670(void *this,undefined4 *param_1)

{
  *(undefined4 *)this = *param_1;
  *(undefined4 *)((int)this + 0x10) = param_1[4];
  FUN_00450dd0((void *)((int)this + 4),param_1 + 1);
  FUN_004507e0((void *)((int)this + 0x14),param_1 + 5);
  return this;
}


