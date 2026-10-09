// FUN_004553d0 @ 004553d0 size=209 callers=8

int __thiscall FUN_004553d0(void *this,int param_1,int param_2)

{
  char cVar1;
  char *pcVar2;
  int iVar3;
  
  *(undefined4 *)((int)this + 0x44) = 0;
  if (param_2 == 0) {
    return 0;
  }
  do {
    cVar1 = *(char *)((int)this + 0x48);
    if (param_1 == 8) {
      if (7 < (byte)(cVar1 - 0x30U)) {
        return param_2;
      }
LAB_00455430:
      iVar3 = cVar1 + -0x30;
    }
    else {
      if (('/' < cVar1) && (cVar1 < ':')) goto LAB_00455430;
      if (param_1 != 0x10) {
        return param_2;
      }
      if ((byte)(cVar1 + 0x9fU) < 6) {
        iVar3 = cVar1 + -0x57;
      }
      else {
        if (5 < (byte)(cVar1 + 0xbfU)) {
          return param_2;
        }
        iVar3 = cVar1 + -0x37;
      }
    }
    if (iVar3 == -1) {
      return param_2;
    }
    param_2 = param_2 + -1;
    *(int *)((int)this + 0x44) = *(int *)((int)this + 0x44) * param_1 + iVar3;
    pcVar2 = *(char **)this;
    if (pcVar2 != *(char **)((int)this + 8)) {
      if (((*pcVar2 == '\\') && (pcVar2 = pcVar2 + 1, pcVar2 != *(char **)((int)this + 8))) &&
         ((((*(uint *)((int)this + 0x50) & 8) == 0 && ((*pcVar2 == '(' || (*pcVar2 == ')')))) ||
          (((*(uint *)((int)this + 0x50) & 0x10) == 0 && ((*pcVar2 == '{' || (*pcVar2 == '}'))))))))
      {
        *(char **)this = pcVar2;
      }
      *(int *)this = *(int *)this + 1;
    }
    FUN_00449160(this);
    if (param_2 == 0) {
      return 0;
    }
  } while( true );
}


