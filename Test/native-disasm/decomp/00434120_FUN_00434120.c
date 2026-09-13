// FUN_00434120 @ 00434120 size=142 callers=32

undefined4 * __thiscall FUN_00434120(void *this,undefined4 *param_1)

{
  char cVar1;
  
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
  cVar1 = *(char *)this;
  if (cVar1 == '\0') {
    param_1[3] = 1;
    return param_1;
  }
  if (cVar1 == '\x01') {
    param_1[1] = *(undefined4 *)**(undefined4 **)((int)this + 8);
    return param_1;
  }
  if (cVar1 != '\x02') {
    param_1[3] = 0;
    return param_1;
  }
  param_1[2] = **(undefined4 **)((int)this + 8);
  return param_1;
}


