// FUN_00446250 @ 00446250 size=308 callers=3

undefined1 * __fastcall FUN_00446250(undefined1 *param_1,undefined4 param_2)

{
  switch(param_2) {
  case 0:
    FUN_004355e0(param_1,(uint *)"<uninitialized>");
    return param_1;
  case 1:
    FUN_004355e0(param_1,(uint *)"true literal");
    return param_1;
  case 2:
    FUN_004355e0(param_1,(uint *)"false literal");
    return param_1;
  case 3:
    FUN_004355e0(param_1,(uint *)"null literal");
    return param_1;
  case 4:
    FUN_004355e0(param_1,(uint *)"string literal");
    return param_1;
  case 5:
  case 6:
  case 7:
    FUN_004355e0(param_1,(uint *)"number literal");
    return param_1;
  case 8:
    FUN_004355e0(param_1,(uint *)&DAT_0048e10c);
    return param_1;
  case 9:
    FUN_004355e0(param_1,(uint *)&DAT_0048e110);
    return param_1;
  case 10:
    FUN_004355e0(param_1,(uint *)&DAT_0048e114);
    return param_1;
  case 0xb:
    FUN_004355e0(param_1,(uint *)&DAT_0048e118);
    return param_1;
  case 0xc:
    FUN_004355e0(param_1,(uint *)&DAT_0048e11c);
    return param_1;
  case 0xd:
    FUN_004355e0(param_1,(uint *)&DAT_0048e120);
    return param_1;
  case 0xe:
    FUN_004355e0(param_1,(uint *)"<parse error>");
    return param_1;
  case 0xf:
    FUN_004355e0(param_1,(uint *)"end of input");
    return param_1;
  default:
    *(undefined4 *)(param_1 + 0x14) = 0xf;
    *(undefined4 *)(param_1 + 0x10) = 0;
    *param_1 = 0;
    FUN_0043ace0(param_1,(uint *)"unknown token",0xd);
    return param_1;
  }
}


