// operator() @ 00468fd6 size=288 callers=1

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* Library Function - Single Match
    public: int __thiscall <lambda_275893d493268fdec8709772e3fcec0e>::operator()(void)const 
   
   Library: Visual Studio 2015 Release */

int __thiscall
<lambda_275893d493268fdec8709772e3fcec0e>::operator()
          (<lambda_275893d493268fdec8709772e3fcec0e> *this)

{
  uint *puVar1;
  byte bVar2;
  int iVar3;
  uint uVar4;
  uint *puVar5;
  sbyte sVar6;
  uint *puVar7;
  uint *puVar8;
  uint uVar9;
  uint *_Memory;
  uint local_18;
  
  puVar7 = (uint *)**(int **)this;
  if (puVar7 == (uint *)0x0) {
    iVar3 = -1;
  }
  else {
    local_18 = DAT_0049d070 & 0x1f;
    sVar6 = (sbyte)local_18;
    _Memory = (uint *)((*puVar7 ^ DAT_0049d070) >> sVar6 | (*puVar7 ^ DAT_0049d070) << 0x20 - sVar6)
    ;
    puVar7 = (uint *)((puVar7[1] ^ DAT_0049d070) >> sVar6 |
                     (puVar7[1] ^ DAT_0049d070) << 0x20 - sVar6);
    if ((_Memory != (uint *)0x0) && (puVar8 = puVar7, _Memory != (uint *)0xffffffff)) {
      do {
        sVar6 = (sbyte)local_18;
        bVar2 = 0x20U - sVar6 & 0x1f;
        uVar4 = (0U >> bVar2 | 0 << 0x20 - bVar2) ^ DAT_0049d070;
        do {
          puVar7 = puVar7 + -1;
          if (puVar7 < _Memory) {
            if (_Memory != (uint *)0xffffffff) {
              FID_conflict__free(_Memory);
            }
            bVar2 = 0x20 - ((byte)DAT_0049d070 & 0x1f) & 0x1f;
            uVar4 = (0U >> bVar2 | 0 << 0x20 - bVar2) ^ DAT_0049d070;
            *(uint *)**(undefined4 **)this = uVar4;
            *(uint *)(**(int **)this + 4) = uVar4;
            *(uint *)(**(int **)this + 8) = uVar4;
            goto LAB_004690e3;
          }
        } while (*puVar7 == uVar4);
        uVar9 = *puVar7 ^ DAT_0049d070;
        *puVar7 = uVar4;
        (*(code *)PTR_guard_check_icall_004805b0)();
        (*(code *)(uVar9 >> sVar6 | uVar9 << 0x20 - sVar6))();
        local_18 = DAT_0049d070 & 0x1f;
        uVar9 = *(uint *)**(int **)this ^ DAT_0049d070;
        uVar4 = ((uint *)**(int **)this)[1] ^ DAT_0049d070;
        sVar6 = (sbyte)local_18;
        puVar1 = (uint *)(uVar9 >> sVar6 | uVar9 << 0x20 - sVar6);
        puVar5 = (uint *)(uVar4 >> sVar6 | uVar4 << 0x20 - sVar6);
        if ((puVar1 != _Memory) || (puVar5 != puVar8)) {
          puVar7 = puVar5;
          _Memory = puVar1;
          puVar8 = puVar5;
        }
      } while( true );
    }
LAB_004690e3:
    iVar3 = 0;
  }
  return iVar3;
}


