// FUN_00468593 @ 00468593 size=408 callers=1

undefined4 * __cdecl FUN_00468593(int param_1)

{
  wchar_t *_Dst;
  int iVar1;
  ushort uVar2;
  int *piVar3;
  bool bVar4;
  undefined4 *_Memory;
  undefined4 *puVar5;
  errno_t eVar6;
  ushort *puVar7;
  uint uVar8;
  ushort *puVar9;
  bool bVar10;
  undefined4 *local_10;
  undefined **local_8;
  
  bVar4 = true;
  _Memory = __malloc_base(0x6a6);
  puVar5 = (undefined4 *)0x0;
  if (_Memory != (undefined4 *)0x0) {
    _Dst = (wchar_t *)(_Memory + 1);
    *_Dst = L'\0';
    *_Memory = 1;
    FUN_004684d2(_Dst,0x351,3);
    local_8 = &PTR_u_LC_COLLATE_00485c84;
    local_10 = (undefined4 *)(param_1 + 0x30);
    do {
      eVar6 = _wcscat_s(_Dst,0x351,L";");
      if (eVar6 != 0) {
                    /* WARNING: Subroutine does not return */
        __invoke_watson((wchar_t *)0x0,(wchar_t *)0x0,(wchar_t *)0x0,0,0);
      }
      puVar7 = (ushort *)*local_10;
      puVar9 = (ushort *)local_10[4];
      do {
        uVar2 = *puVar7;
        bVar10 = uVar2 < *puVar9;
        if (uVar2 != *puVar9) {
LAB_0046863f:
          uVar8 = -(uint)bVar10 | 1;
          goto LAB_00468644;
        }
        if (uVar2 == 0) break;
        uVar2 = puVar7[1];
        bVar10 = uVar2 < puVar9[1];
        if (uVar2 != puVar9[1]) goto LAB_0046863f;
        puVar7 = puVar7 + 2;
        puVar9 = puVar9 + 2;
      } while (uVar2 != 0);
      uVar8 = 0;
LAB_00468644:
      local_8 = local_8 + 3;
      bVar4 = (bool)(bVar4 & ~(uVar8 != 0));
      FUN_004684d2(_Dst,0x351,3);
      local_10 = local_10 + 4;
    } while ((int)local_8 < 0x485cb4);
    if (bVar4) {
      FID_conflict__free(_Memory);
      piVar3 = *(int **)(param_1 + 0x28);
      if (piVar3 != (int *)0x0) {
        LOCK();
        iVar1 = *piVar3;
        *piVar3 = iVar1 + -1;
        UNLOCK();
        if (iVar1 + -1 == 0) {
          FID_conflict__free(*(void **)(param_1 + 0x28));
        }
      }
      piVar3 = *(int **)(param_1 + 0x24);
      if (piVar3 != (int *)0x0) {
        LOCK();
        iVar1 = *piVar3;
        *piVar3 = *piVar3 + -1;
        UNLOCK();
        if (iVar1 == 1) {
          FID_conflict__free(*(void **)(param_1 + 0x24));
        }
      }
      *(undefined4 *)(param_1 + 0x24) = 0;
      *(undefined4 *)(param_1 + 0x1c) = 0;
      *(undefined4 *)(param_1 + 0x28) = 0;
      *(undefined4 *)(param_1 + 0x20) = 0;
      puVar5 = *(undefined4 **)(param_1 + 0x40);
    }
    else {
      piVar3 = *(int **)(param_1 + 0x28);
      if (piVar3 != (int *)0x0) {
        LOCK();
        iVar1 = *piVar3;
        *piVar3 = iVar1 + -1;
        UNLOCK();
        if (iVar1 + -1 == 0) {
          FID_conflict__free(*(void **)(param_1 + 0x28));
        }
      }
      piVar3 = *(int **)(param_1 + 0x24);
      if (piVar3 != (int *)0x0) {
        LOCK();
        iVar1 = *piVar3;
        *piVar3 = *piVar3 + -1;
        UNLOCK();
        if (iVar1 == 1) {
          FID_conflict__free(*(void **)(param_1 + 0x24));
        }
      }
      *(undefined4 *)(param_1 + 0x24) = 0;
      puVar5 = _Memory + 1;
      *(undefined4 *)(param_1 + 0x1c) = 0;
      *(undefined4 **)(param_1 + 0x28) = _Memory;
      *(undefined4 **)(param_1 + 0x20) = puVar5;
    }
  }
  return puVar5;
}


