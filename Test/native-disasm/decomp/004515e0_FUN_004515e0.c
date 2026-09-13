// FUN_004515e0 @ 004515e0 size=136 callers=1

void __fastcall FUN_004515e0(int *param_1)

{
  char *pcVar1;
  
  FUN_00453e50((int)(param_1 + 9));
  if (param_1[0x13] == 0x5e) {
    *(uint *)(param_1[10] + 8) = *(uint *)(param_1[10] + 8) ^ 1;
    pcVar1 = (char *)*param_1;
    if (pcVar1 != (char *)param_1[2]) {
      if (((*pcVar1 == '\\') && (pcVar1 = pcVar1 + 1, pcVar1 != (char *)param_1[2])) &&
         ((((param_1[0x14] & 8U) == 0 && ((*pcVar1 == '(' || (*pcVar1 == ')')))) ||
          (((param_1[0x14] & 0x10U) == 0 && ((*pcVar1 == '{' || (*pcVar1 == '}')))))))) {
        *param_1 = (int)pcVar1;
      }
      *param_1 = *param_1 + 1;
    }
    FUN_00449160(param_1);
  }
  if (((param_1[0x14] & 0x20000000U) != 0) && (param_1[0x13] == 0x5d)) {
    FUN_00455950(param_1 + 9,0x5d);
    FUN_0044dfd0(param_1);
  }
  FUN_00453b50(param_1);
  return;
}


