// FUN_00438430 @ 00438430 size=208 callers=20

undefined1 * __thiscall FUN_00438430(void *this,undefined1 *param_1)

{
  switch(*(undefined1 *)this) {
  case 0:
    FUN_004355e0(param_1,(uint *)&DAT_0048de3c);
    return param_1;
  case 1:
    FUN_004355e0(param_1,(uint *)"object");
    return param_1;
  case 2:
    FUN_004355e0(param_1,(uint *)"array");
    return param_1;
  case 3:
    FUN_004355e0(param_1,(uint *)"string");
    return param_1;
  case 4:
    FUN_004355e0(param_1,(uint *)"boolean");
    return param_1;
  default:
    *(undefined4 *)(param_1 + 0x14) = 0xf;
    *(undefined4 *)(param_1 + 0x10) = 0;
    *param_1 = 0;
    FUN_0043ace0(param_1,(uint *)"number",6);
    return param_1;
  case 8:
    FUN_004355e0(param_1,(uint *)"discarded");
    return param_1;
  }
}


