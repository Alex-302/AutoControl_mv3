// FUN_00456730 @ 00456730 size=269 callers=1

/* WARNING: Removing unreachable block (ram,0x00456804) */
/* WARNING: Removing unreachable block (ram,0x004567db) */
/* WARNING: Removing unreachable block (ram,0x0045680e) */
/* WARNING: Removing unreachable block (ram,0x00456813) */
/* WARNING: Removing unreachable block (ram,0x00456820) */

void __fastcall FUN_00456730(char *param_1,ulonglong *param_2)

{
  char cVar1;
  uint *puVar2;
  ulonglong uVar3;
  undefined1 local_54 [24];
  undefined1 local_3c [24];
  undefined **local_24;
  undefined8 local_20;
  undefined4 *local_18;
  undefined1 local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047e8e0;
  local_10 = ExceptionList;
  cVar1 = *param_1;
  if ((cVar1 != '\x05') && (cVar1 != '\x06')) {
    if (cVar1 == '\a') {
      ExceptionList = &local_10;
      uVar3 = FUN_00477def();
      *param_2 = uVar3;
      ExceptionList = local_10;
      return;
    }
    ExceptionList = &local_10;
    puVar2 = (uint *)FUN_00438430(param_1,local_3c);
    local_8 = 0;
    local_18 = (undefined4 *)FUN_00442600(local_54,(uint *)"type must be number, but is ",puVar2);
    local_8 = CONCAT31(local_8._1_3_,1);
    if (0xf < (uint)local_18[5]) {
      local_18 = (undefined4 *)*local_18;
    }
    local_24 = std::exception::vftable;
    local_20 = 0;
    local_14 = 1;
    ___std_exception_copy(&local_18,(undefined4 *)&local_20);
    local_24 = &PTR_FUN_0048eee8;
                    /* WARNING: Subroutine does not return */
    __CxxThrowException_8((int *)&local_24,&DAT_0049a03c);
  }
  *(undefined4 *)param_2 = *(undefined4 *)(param_1 + 8);
  *(undefined4 *)((int)param_2 + 4) = *(undefined4 *)(param_1 + 0xc);
  return;
}


