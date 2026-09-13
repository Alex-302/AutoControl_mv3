// FUN_0044dfd0 @ 0044dfd0 size=67 callers=45

void __fastcall FUN_0044dfd0(int *param_1)

{
  char *pcVar1;
  
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
  return;
}


