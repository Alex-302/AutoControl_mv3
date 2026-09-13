// FUN_00457ca0 @ 00457ca0 size=173 callers=1

undefined1 * __thiscall FUN_00457ca0(void *this,undefined4 *param_1,undefined4 *param_2)

{
  uint uVar1;
  undefined1 *puVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047ec70;
  local_10 = ExceptionList;
  puVar2 = (undefined1 *)(((int)param_2 - (int)param_1) * 0x2aaaaaab);
  uVar1 = ((int)param_2 - (int)param_1) / 0x18;
  ExceptionList = &local_10;
  *(undefined4 *)this = 0;
  *(undefined4 *)((int)this + 4) = 0;
  *(undefined4 *)((int)this + 8) = 0;
  if (uVar1 != 0) {
    if (0xfffffff < uVar1) {
                    /* WARNING: Subroutine does not return */
      FUN_00458ec4("vector<T> too long");
    }
    puVar2 = FUN_0043fde0(uVar1);
    *(undefined1 **)this = puVar2;
    *(undefined1 **)((int)this + 4) = puVar2;
    local_8 = 0;
    *(uint *)((int)this + 8) = uVar1 * 0x10 + *(int *)this;
    puVar2 = FUN_00458340(param_1,param_2,puVar2);
    *(undefined1 **)((int)this + 4) = puVar2;
  }
  ExceptionList = local_10;
  return puVar2;
}


