// FUN_00454bb0 @ 00454bb0 size=48 callers=1

void __thiscall FUN_00454bb0(void *this,undefined1 *param_1,undefined1 *param_2)

{
  uint uVar1;
  undefined1 uVar2;
  void *pvVar3;
  void *pvStack_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0047ea30;
  pvStack_10 = ExceptionList;
  local_8 = 0;
  ExceptionList = &pvStack_10;
FUN_00454be0:
  do {
    while( true ) {
      if (param_1 == param_2) {
        ExceptionList = pvStack_10;
        return;
      }
      uVar2 = *param_1;
      if (~*(uint *)((int)this + 0x10) < 2) {
                    /* WARNING: Subroutine does not return */
        FUN_00458ec4("string too long");
      }
      uVar1 = *(uint *)((int)this + 0x10) + 1;
      if (uVar1 == 0xffffffff) {
                    /* WARNING: Subroutine does not return */
        FUN_00458ec4("string too long");
      }
      if (uVar1 <= *(uint *)((int)this + 0x14)) break;
      FUN_0043f5f0(this,uVar1);
      if (uVar1 != 0) goto LAB_00454c2f;
LAB_00454cba:
      param_1 = param_1 + 1;
    }
    if (uVar1 == 0) {
      *(undefined4 *)((int)this + 0x10) = 0;
      if (*(uint *)((int)this + 0x14) < 0x10) {
        param_1 = param_1 + 1;
        *(undefined1 *)this = 0;
      }
      else {
        param_1 = param_1 + 1;
        **(undefined1 **)this = 0;
      }
      goto FUN_00454be0;
    }
LAB_00454c2f:
    pvVar3 = this;
    if (0xf < *(uint *)((int)this + 0x14)) {
      pvVar3 = *(void **)this;
    }
    *(undefined1 *)((int)pvVar3 + *(int *)((int)this + 0x10)) = uVar2;
    *(uint *)((int)this + 0x10) = uVar1;
    if (*(uint *)((int)this + 0x14) < 0x10) {
      *(undefined1 *)((int)this + uVar1) = 0;
      goto LAB_00454cba;
    }
    param_1 = param_1 + 1;
    *(undefined1 *)(*(int *)this + uVar1) = 0;
  } while( true );
}


