// FUN_004338f0 @ 004338f0 size=45 callers=1

void * __thiscall FUN_004338f0(void *this,char param_1)

{
  if (param_1 != '\0') {
    **(uint **)this = **(uint **)this | 1 << (*(uint *)((int)this + 4) & 0x1f);
    return this;
  }
  **(uint **)this = **(uint **)this & ~(1 << (*(uint *)((int)this + 4) & 0x1f));
  return this;
}


