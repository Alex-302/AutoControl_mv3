// FUN_00448980 @ 00448980 size=184 callers=1

void * __thiscall FUN_00448980(void *this,int *param_1)

{
  void *pvVar1;
  int iVar2;
  uint uVar3;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047e5a0;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  *(undefined4 *)this = 0;
  *(undefined4 *)((int)this + 4) = 0;
  *(undefined4 *)((int)this + 8) = 0;
  uVar3 = param_1[1] - *param_1 >> 4;
  *(undefined4 *)this = 0;
  *(undefined4 *)((int)this + 4) = 0;
  *(undefined4 *)((int)this + 8) = 0;
  if (uVar3 != 0) {
    if (0xfffffff < uVar3) {
                    /* WARNING: Subroutine does not return */
      FUN_00458ec4("vector<T> too long");
    }
    pvVar1 = FUN_0043fde0(uVar3);
    *(void **)this = pvVar1;
    *(void **)((int)this + 4) = pvVar1;
    local_8 = 0;
    *(uint *)((int)this + 8) = uVar3 * 0x10 + *(int *)this;
    iVar2 = FUN_00455290(*param_1,param_1[1],(int)pvVar1);
    *(int *)((int)this + 4) = iVar2;
  }
  ExceptionList = local_10;
  return this;
}


