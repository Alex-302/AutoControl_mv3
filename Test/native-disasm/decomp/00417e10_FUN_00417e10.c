// FUN_00417e10 @ 00417e10 size=252 callers=5

void __thiscall FUN_00417e10(void *this,char param_1)

{
  int *piVar1;
  int iVar2;
  bool bVar3;
  char local_2c [8];
  undefined4 local_24;
  undefined4 uStack_20;
  undefined4 local_1c;
  undefined4 local_18;
  char local_12;
  char local_11;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047a018;
  local_10 = ExceptionList;
  bVar3 = false;
  local_18 = 0;
  ExceptionList = &local_10;
  *(undefined1 *)((int)this + 0x34) = 0;
  if (*(int *)((int)this + 0x24) == 0) {
LAB_00417e77:
    local_11 = '\0';
  }
  else {
    if ((param_1 != '\0') && (*(int *)((int)this + 0x30) != 0)) {
      FUN_00416bd0(&local_12,
                   *(HWND *)(&DAT_004a2470 + *(int *)(*(int *)ThreadLocalStoragePointer + 4) * 4));
      bVar3 = true;
      iVar2 = FUN_00416d60(*(int *)((int)this + 0x30));
      if (iVar2 == 0) goto LAB_00417e77;
    }
    local_11 = '\x01';
  }
  if ((bVar3) && (local_12 != '\0')) {
    CloseClipboard();
  }
  if (local_11 != '\0') {
    FUN_0040fb40((UINT_PTR *)((int)this + 0x28),'\x01');
    local_1c = CONCAT31(local_1c._1_3_,param_1);
    local_2c[0] = '\x04';
    _local_24 = CONCAT44(local_18,local_1c);
    local_8 = 0;
    if (*(int **)((int)this + 0x24) == (int *)0x0) {
                    /* WARNING: Subroutine does not return */
      FUN_00458e87();
    }
    (**(code **)(**(int **)((int)this + 0x24) + 8))(local_2c);
    FUN_00434820(local_2c);
    piVar1 = *(int **)((int)this + 0x24);
    if (piVar1 != (int *)0x0) {
      (**(code **)(*piVar1 + 0x10))(piVar1 != this);
      *(undefined4 *)((int)this + 0x24) = 0;
    }
  }
  ExceptionList = local_10;
  return;
}


