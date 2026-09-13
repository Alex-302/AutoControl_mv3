// FUN_004340a0 @ 004340a0 size=124 callers=58

undefined4 * __thiscall FUN_004340a0(void *this,undefined4 *param_1)

{
  *param_1 = this;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  param_1[3] = 0;
  if (*(char *)this == '\x01') {
    param_1[1] = 0;
  }
  else if (*(char *)this == '\x02') {
    param_1[2] = 0;
  }
  else {
    param_1[3] = 0;
  }
  if (*(char *)this != '\x01') {
    if (*(char *)this != '\x02') {
      param_1[3] = 1;
      return param_1;
    }
    param_1[2] = *(undefined4 *)(*(int *)((int)this + 8) + 4);
    return param_1;
  }
  param_1[1] = **(undefined4 **)((int)this + 8);
  return param_1;
}


