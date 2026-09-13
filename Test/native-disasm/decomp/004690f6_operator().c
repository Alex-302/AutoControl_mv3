// operator() @ 004690f6 size=321 callers=1

/* Library Function - Single Match
    public: int __thiscall <lambda_4e60a939b0d047cfe11ddc22648dfba9>::operator()(void)const 
   
   Library: Visual Studio 2015 Release */

int __thiscall
<lambda_4e60a939b0d047cfe11ddc22648dfba9>::operator()
          (<lambda_4e60a939b0d047cfe11ddc22648dfba9> *this)

{
  LPCVOID pvVar1;
  uint uVar2;
  uint uVar3;
  void *pvVar4;
  byte bVar5;
  uint *puVar6;
  LPCVOID pvVar7;
  uint *puVar8;
  uint uVar9;
  uint *puVar10;
  
  puVar6 = (uint *)**(int **)this;
  if (puVar6 == (uint *)0x0) {
    return -1;
  }
  bVar5 = (byte)DAT_0049d070 & 0x1f;
  puVar10 = (uint *)((puVar6[1] ^ DAT_0049d070) >> bVar5 |
                    (puVar6[1] ^ DAT_0049d070) << 0x20 - bVar5);
  puVar8 = (uint *)((puVar6[2] ^ DAT_0049d070) >> bVar5 | (puVar6[2] ^ DAT_0049d070) << 0x20 - bVar5
                   );
  pvVar7 = (LPCVOID)((*puVar6 ^ DAT_0049d070) >> bVar5 | (*puVar6 ^ DAT_0049d070) << 0x20 - bVar5);
  pvVar1 = pvVar7;
  if (puVar10 != puVar8) goto LAB_004691f0;
  uVar9 = (int)puVar8 - (int)pvVar7 >> 2;
  uVar2 = 0x200;
  if (uVar9 < 0x201) {
    uVar2 = uVar9;
  }
  uVar2 = uVar2 + uVar9;
  if (uVar2 == 0) {
    uVar2 = 0x20;
  }
  if (uVar2 < uVar9) {
LAB_00469177:
    uVar2 = uVar9 + 4;
    pvVar1 = FUN_00473270(pvVar7,uVar2,4);
    FID_conflict__free((void *)0x0);
    if (pvVar1 == (LPVOID)0x0) {
      return -1;
    }
  }
  else {
    pvVar1 = FUN_00473270(pvVar7,uVar2,4);
    FID_conflict__free((void *)0x0);
    if (pvVar1 == (LPVOID)0x0) goto LAB_00469177;
  }
  puVar10 = (uint *)((int)pvVar1 + uVar9 * 4);
  puVar8 = (uint *)((int)pvVar1 + uVar2 * 4);
  bVar5 = 0x20 - ((byte)DAT_0049d070 & 0x1f) & 0x1f;
  uVar2 = (0U >> bVar5 | 0 << 0x20 - bVar5) ^ DAT_0049d070;
  uVar9 = ~-(uint)(puVar8 < puVar10) & (uint)((int)puVar8 + (3 - (int)puVar10)) >> 2;
  if (uVar9 != 0) {
    uVar3 = 0;
    puVar6 = puVar10;
    do {
      uVar3 = uVar3 + 1;
      *puVar6 = uVar2;
      puVar6 = puVar6 + 1;
    } while (uVar3 != uVar9);
  }
LAB_004691f0:
  uVar2 = __crt_fast_encode_pointer<>(**(uint **)(this + 4));
  *puVar10 = uVar2;
  pvVar4 = __crt_fast_encode_pointer<void*>(pvVar1);
  *(void **)**(undefined4 **)this = pvVar4;
  pvVar4 = __crt_fast_encode_pointer<void*>(puVar10 + 1);
  *(void **)(**(int **)this + 4) = pvVar4;
  pvVar4 = __crt_fast_encode_pointer<void*>(puVar8);
  *(void **)(**(int **)this + 8) = pvVar4;
  return 0;
}


