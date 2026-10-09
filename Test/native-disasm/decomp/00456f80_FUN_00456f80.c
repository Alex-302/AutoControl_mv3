// FUN_00456f80 @ 00456f80 size=320 callers=1

void __thiscall FUN_00456f80(void *this,int param_1)

{
  int iVar1;
  uint *puVar2;
  ushort uVar3;
  char *pcVar4;
  uint uVar5;
  error_type eVar6;
  
  if (param_1 == 0x3a) {
    eVar6 = 1;
  }
  else if (param_1 == 0x3d) {
    eVar6 = 0;
  }
  else {
    eVar6 = 0xe;
    if (param_1 == 0x2e) {
      eVar6 = 0;
    }
  }
  uVar5 = 0;
  puVar2 = *(uint **)this;
  iVar1 = *(int *)((int)this + 0x4c);
  while ((((iVar1 != 0x3a && (iVar1 != 0x3d)) && (iVar1 != 0x2e)) && (iVar1 != -1))) {
    pcVar4 = *(char **)this;
    if (pcVar4 != *(char **)((int)this + 8)) {
      if (((*pcVar4 == '\\') && (pcVar4 = pcVar4 + 1, pcVar4 != *(char **)((int)this + 8))) &&
         ((((*(uint *)((int)this + 0x50) & 8) == 0 && ((*pcVar4 == '(' || (*pcVar4 == ')')))) ||
          (((*(uint *)((int)this + 0x50) & 0x10) == 0 && ((*pcVar4 == '{' || (*pcVar4 == '}'))))))))
      {
        *(char **)this = pcVar4;
      }
      *(int *)this = *(int *)this + 1;
    }
    FUN_00449160(this);
    uVar5 = uVar5 + 1;
    iVar1 = *(int *)((int)this + 0x4c);
  }
  if (*(int *)((int)this + 0x4c) == param_1) {
    if (param_1 == 0x3a) {
      uVar3 = FUN_00456900(*(void **)((int)this + 0x3c),(byte *)puVar2,*(byte **)this,
                           (byte)((uint)*(undefined4 *)((int)this + 0x40) >> 8) & 1);
      if (uVar3 == 0) {
                    /* WARNING: Subroutine does not return */
        FUN_00458f04(1);
      }
      FUN_00456550((void *)((int)this + 0x24),*(int *)((int)this + 0x28),uVar3,'\0');
    }
    else if (param_1 == 0x3d) {
      if (puVar2 == *(uint **)this) {
                    /* WARNING: Subroutine does not return */
        FUN_00458f04(0);
      }
      FUN_00457380((void *)((int)this + 0x24),puVar2,*(uint **)this);
    }
    else if (param_1 == 0x2e) {
      if (puVar2 == *(uint **)this) {
                    /* WARNING: Subroutine does not return */
        FUN_00458f04(0);
      }
      FUN_00457850((undefined1 *)puVar2,(undefined1 *)*(uint **)this,uVar5,
                   (uint *)(*(int *)((int)this + 0x28) + 0x14));
    }
    FUN_0044dfd0(this);
    FUN_00451580(this,0x5d,eVar6);
    return;
  }
                    /* WARNING: Subroutine does not return */
  FUN_00458f04(eVar6);
}


