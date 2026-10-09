// __except_handler4 @ 0045eb50 size=358 callers=4

/* Library Function - Single Match
    __except_handler4
   
   Library: Visual Studio 2015 Release */

undefined4 __cdecl __except_handler4(PEXCEPTION_RECORD param_1,PVOID param_2,undefined4 param_3)

{
  undefined *puVar1;
  uint uVar2;
  code *pcVar3;
  int iVar4;
  BOOL BVar5;
  uint uVar6;
  uint uVar7;
  PEXCEPTION_RECORD pEVar8;
  undefined4 uVar9;
  PEXCEPTION_RECORD local_20;
  undefined4 local_1c;
  int local_18;
  uint *local_14;
  undefined4 local_10;
  uint local_c;
  char local_5;
  
  local_5 = '\0';
  local_10 = 1;
  local_18 = (int)param_2 + 0x10;
  uVar6 = *(uint *)((int)param_2 + 8) ^ DAT_0049d070;
  local_c = uVar6;
  _ValidateLocalCookies();
  guard_check_icall();
  if ((param_1->ExceptionFlags & 0x66) == 0) {
    local_20 = param_1;
    local_1c = param_3;
    *(PEXCEPTION_RECORD **)((int)param_2 + -4) = &local_20;
    uVar7 = *(uint *)((int)param_2 + 0xc);
    if (*(uint *)((int)param_2 + 0xc) == 0xfffffffe) {
      return local_10;
    }
    do {
      iVar4 = uVar7 * 3 + 4;
      puVar1 = *(undefined **)(uVar6 + 4 + iVar4 * 4);
      local_14 = (uint *)(uVar6 + iVar4 * 4);
      uVar2 = *local_14;
      if (puVar1 != (undefined *)0x0) {
        iVar4 = _EH4_CallFilterFunc(puVar1);
        local_5 = '\x01';
        if (iVar4 < 0) {
          local_10 = 0;
          goto LAB_0045ec6e;
        }
        if (0 < iVar4) {
          if (((param_1->ExceptionCode == 0xe06d7363) &&
              (PTR____DestructExceptionObject_00483dc0 != (undefined *)0x0)) &&
             (BVar5 = __IsNonwritableInCurrentImage((PBYTE)&PTR____DestructExceptionObject_00483dc0)
             , puVar1 = PTR____DestructExceptionObject_00483dc0, BVar5 != 0)) {
            uVar9 = 1;
            pEVar8 = param_1;
            guard_check_icall();
            (*(code *)puVar1)(pEVar8,uVar9);
          }
          _EH4_GlobalUnwind2(param_2,param_1);
          if (*(uint *)((int)param_2 + 0xc) != uVar7) {
            _EH4_LocalUnwind((int)param_2,uVar7,(int)param_2 + 0x10,&DAT_0049d070);
          }
          *(uint *)((int)param_2 + 0xc) = uVar2;
          _ValidateLocalCookies();
          _EH4_TransferToHandler((undefined *)local_14[2]);
          pcVar3 = (code *)swi(3);
          uVar9 = (*pcVar3)();
          return uVar9;
        }
      }
      uVar6 = local_c;
      uVar7 = uVar2;
    } while (uVar2 != 0xfffffffe);
    if (local_5 == '\0') {
      return local_10;
    }
  }
  else {
    if (*(int *)((int)param_2 + 0xc) == -2) {
      return local_10;
    }
    _EH4_LocalUnwind((int)param_2,0xfffffffe,(int)param_2 + 0x10,&DAT_0049d070);
  }
LAB_0045ec6e:
  _ValidateLocalCookies();
  return local_10;
}


