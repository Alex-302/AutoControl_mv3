// FUN_0040c030 @ 0040c030 size=343 callers=1

int * __fastcall FUN_0040c030(int *param_1,undefined4 param_2,undefined4 *param_3)

{
  uint *puVar1;
  short sVar2;
  int iVar3;
  undefined2 uVar4;
  UINT UVar5;
  undefined4 **ppuVar6;
  undefined4 uVar7;
  undefined4 *_Memory;
  int iVar8;
  uint uVar9;
  uint in_stack_00000014;
  uint in_stack_00000018;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00479f38;
  local_10 = ExceptionList;
  local_8 = 0;
  ExceptionList = &local_10;
  FUN_00432ba0(param_1,in_stack_00000014 * 2);
  uVar9 = 0;
  if (in_stack_00000014 != 0) {
    iVar8 = 0;
    do {
      iVar3 = *param_1;
      ppuVar6 = &param_3;
      if (7 < in_stack_00000018) {
        ppuVar6 = (undefined4 **)param_3;
      }
      sVar2 = *(short *)((int)ppuVar6 + uVar9 * 2);
      uVar4 = 0;
      *(undefined4 *)(iVar8 + 0x1c + iVar3) = 1;
      *(undefined4 *)(iVar8 + iVar3) = 1;
      if (sVar2 == 10) {
        uVar4 = 0xd;
      }
      *(undefined2 *)(iVar8 + 0x20 + iVar3) = uVar4;
      *(undefined2 *)(iVar8 + 4 + iVar3) = uVar4;
      if (sVar2 != 10) {
        ppuVar6 = &param_3;
        if (7 < in_stack_00000018) {
          ppuVar6 = (undefined4 **)param_3;
        }
        uVar4 = *(undefined2 *)((int)ppuVar6 + uVar9 * 2);
      }
      else {
        UVar5 = MapVirtualKeyA(0xd,0);
        uVar4 = (short)UVar5;
      }
      *(undefined2 *)(iVar8 + 0x22 + iVar3) = uVar4;
      *(undefined2 *)(iVar8 + 6 + iVar3) = uVar4;
      uVar7 = 4;
      if (sVar2 == 10) {
        uVar7 = 0;
      }
      uVar9 = uVar9 + 1;
      *(undefined4 *)(iVar8 + 0x24 + iVar3) = uVar7;
      *(undefined4 *)(iVar8 + 8 + iVar3) = uVar7;
      *(undefined4 *)(iVar8 + 0x2c + iVar3) = param_2;
      *(undefined4 *)(iVar8 + 0x10 + iVar3) = param_2;
      puVar1 = (uint *)(iVar8 + 0x24 + iVar3);
      *puVar1 = *puVar1 | 2;
      iVar8 = iVar8 + 0x38;
    } while (uVar9 < in_stack_00000014);
  }
  if (7 < in_stack_00000018) {
    if (0x7fffffff < in_stack_00000018 + 1) {
                    /* WARNING: Subroutine does not return */
      FUN_00465fb2();
    }
    _Memory = param_3;
    if (0xfff < (in_stack_00000018 + 1) * 2) {
      if (((uint)param_3 & 0x1f) != 0) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
      _Memory = (undefined4 *)param_3[-1];
      if (param_3 <= _Memory) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
      if ((uint)((int)param_3 - (int)_Memory) < 4) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
      if (0x23 < (uint)((int)param_3 - (int)_Memory)) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
    }
    FID_conflict__free(_Memory);
  }
  ExceptionList = local_10;
  return param_1;
}


