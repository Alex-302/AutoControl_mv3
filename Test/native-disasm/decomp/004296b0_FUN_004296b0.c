// FUN_004296b0 @ 004296b0 size=232 callers=1

void __fastcall FUN_004296b0(char *param_1)

{
  undefined4 uVar1;
  char *pcVar2;
  uint *puVar3;
  void *this;
  uint local_30;
  uint local_2c;
  char *local_28;
  int local_24;
  int local_20;
  int local_1c;
  int local_18 [5];
  
  if (*param_1 == '\x02') {
    FUN_00434120(param_1,&local_28);
    FUN_004340a0(this,local_18);
    uVar1 = FUN_004383a0(&local_28,local_18);
    if ((char)uVar1 == '\0') {
      do {
        pcVar2 = FUN_00433bc0(&local_28);
        FUN_004536b0(pcVar2,&local_30);
        for (puVar3 = DAT_004a2514; puVar3 != DAT_004a2518; puVar3 = puVar3 + 1) {
          if (*puVar3 == local_30) {
            if (puVar3 != DAT_004a2518) {
              FUN_0045b0e0(puVar3,puVar3 + 1,(int)DAT_004a2518 - (int)(puVar3 + 1));
              DAT_004a2518 = DAT_004a2518 + -1;
            }
            break;
          }
        }
        if (*local_28 == '\x01') {
          local_2c = local_2c & 0xffffff00;
          FUN_00447660(&local_24);
        }
        else if (*local_28 == '\x02') {
          local_20 = local_20 + 0x10;
        }
        else {
          local_1c = local_1c + 1;
        }
        uVar1 = FUN_004383a0(&local_28,local_18);
        if ((char)uVar1 != '\0') {
          return;
        }
      } while( true );
    }
  }
  else {
    DAT_004a2518 = DAT_004a2514;
  }
  return;
}


