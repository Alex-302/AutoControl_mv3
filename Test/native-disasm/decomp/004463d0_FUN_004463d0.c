// FUN_004463d0 @ 004463d0 size=251 callers=20

void __thiscall FUN_004463d0(void *this,int param_1)

{
  undefined1 *puVar1;
  int iVar2;
  int *piVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  int iVar6;
  undefined4 *puVar7;
  undefined8 uVar8;
  
  puVar1 = *(undefined1 **)((int)this + 0x38);
  iVar6 = *(int *)((int)this + 0x3c) - (int)puVar1;
  iVar2 = *(int *)((int)this + 0x40);
  if (*(int *)((int)this + 0x3c) == 0) {
    iVar6 = 0;
  }
  piVar3 = *(int **)this;
  if ((piVar3 == (int *)0x0) || ((*(byte *)(*(int *)(*piVar3 + 4) + 0xc + (int)piVar3) & 1) != 0)) {
    puVar7 = (undefined4 *)((int)this + 4);
    puVar5 = puVar7;
    if (0xf < *(uint *)((int)this + 0x18)) {
      puVar5 = (void *)*puVar7;
    }
    puVar4 = puVar7;
    if (0xf < *(uint *)((int)this + 0x18)) {
      puVar4 = (undefined4 *)*puVar7;
    }
    FUN_0044b050(puVar7,(int)puVar4,*(int *)((int)this + 0x14) + (int)puVar5,puVar1,
                 *(undefined1 **)((int)this + 0x44));
    FUN_0043aef0(puVar7,1,'\0');
    FUN_0043aef0(puVar7,param_1 - 1,'\x01');
  }
  else {
    puVar7 = (undefined4 *)((int)this + 4);
    FUN_004354d0(puVar7,0,(int)puVar1 - *(int *)((int)this + 0x34));
    puVar5 = (undefined4 *)((int)this + 0x1c);
    *(undefined4 *)((int)this + 0x2c) = 0;
    puVar4 = puVar5;
    if (0xf < *(uint *)((int)this + 0x30)) {
      puVar4 = (undefined4 *)*puVar5;
    }
    *(undefined1 *)puVar4 = 0;
    FUN_004495b0(*(int **)this,puVar5);
    uVar8 = FUN_0043b0c0(puVar7,puVar5,0,0xffffffff);
    FUN_00446660(puVar7,(int)((ulonglong)uVar8 >> 0x20),10);
  }
  puVar7 = (undefined4 *)((int)this + 4);
  if (0xf < *(uint *)((int)this + 0x18)) {
    puVar7 = (undefined4 *)*puVar7;
  }
  *(undefined4 **)((int)this + 0x34) = puVar7;
  *(int *)((int)this + 0x3c) = (int)puVar7 + iVar6;
  *(undefined4 **)((int)this + 0x38) = puVar7;
  *(int *)((int)this + 0x40) = (iVar2 - (int)puVar1) + (int)puVar7;
  *(int *)((int)this + 0x44) = *(int *)((int)this + 0x14) + (int)puVar7;
  return;
}


