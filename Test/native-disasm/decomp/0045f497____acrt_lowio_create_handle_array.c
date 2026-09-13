// ___acrt_lowio_create_handle_array @ 0045f497 size=122 callers=1

/* Library Function - Single Match
    ___acrt_lowio_create_handle_array
   
   Library: Visual Studio 2015 Release */

undefined4 * ___acrt_lowio_create_handle_array(void)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  puVar2 = __calloc_base(0x40,0x30);
  if (puVar2 == (undefined4 *)0x0) {
    puVar2 = (undefined4 *)0x0;
  }
  else if (puVar2 != puVar2 + 0x300) {
    puVar3 = puVar2 + 8;
    do {
      ___acrt_InitializeCriticalSectionEx_12((LPCRITICAL_SECTION)(puVar3 + -8),4000,0);
      puVar3[-2] = 0xffffffff;
      *puVar3 = 0;
      puVar3[1] = 0;
      puVar1 = puVar3 + 4;
      puVar3[2] = 0xa0a0000;
      *(undefined1 *)(puVar3 + 3) = 10;
      *(byte *)((int)puVar3 + 0xd) = *(byte *)((int)puVar3 + 0xd) & 0xf8;
      *(undefined1 *)((int)puVar3 + 0xe) = 0;
      puVar3 = puVar3 + 0xc;
    } while (puVar1 != puVar2 + 0x300);
  }
  FID_conflict__free((void *)0x0);
  return puVar2;
}


