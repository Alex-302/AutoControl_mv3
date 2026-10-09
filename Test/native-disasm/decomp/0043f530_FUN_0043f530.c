// FUN_0043f530 @ 0043f530 size=136 callers=1

void __thiscall FUN_0043f530(void *this,uint param_1)

{
  char *pcVar1;
  undefined1 *puVar2;
  uint uVar3;
  char *pcVar4;
  
  puVar2 = FUN_0043fde0(param_1);
  FUN_00450230(*(undefined1 **)this,*(undefined1 **)((int)this + 4),puVar2);
  pcVar1 = *(char **)((int)this + 4);
  pcVar4 = *(char **)this;
  uVar3 = (int)pcVar1 - (int)pcVar4;
  if (pcVar4 != (char *)0x0) {
    for (; pcVar4 != pcVar1; pcVar4 = pcVar4 + 0x10) {
      FUN_00434820(pcVar4);
    }
    FUN_00402430(*(void **)this,*(int *)((int)this + 8) - (int)*(void **)this >> 4,0x10);
  }
  *(undefined1 **)((int)this + 8) = puVar2 + param_1 * 0x10;
  *(undefined1 **)((int)this + 4) = puVar2 + (uVar3 & 0xfffffff0);
  *(undefined1 **)this = puVar2;
  return;
}


