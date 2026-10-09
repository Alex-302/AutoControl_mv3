// DloadObtainSection @ 0047711e size=131 callers=1

/* Library Function - Single Match
    void * __stdcall DloadObtainSection(unsigned long *,unsigned long *)
   
   Library: Visual Studio 2015 Release */

void * DloadObtainSection(ulong *param_1,ulong *param_2)

{
  int iVar1;
  uint uVar2;
  
  if ((0xd < *(uint *)(IMAGE_DOS_HEADER_00400000.e_program +
                      IMAGE_DOS_HEADER_00400000.e_lfanew + 0x34)) &&
     (*(int *)(&UNK_00400080.field_0x60 + IMAGE_DOS_HEADER_00400000.e_lfanew) != 0)) {
    iVar1 = IMAGE_DOS_HEADER_00400000.e_lfanew + 0x400018 +
            (uint)*(ushort *)
                   ((int)IMAGE_DOS_HEADER_00400000.e_res_4_ +
                   (IMAGE_DOS_HEADER_00400000.e_lfanew - 8));
    uVar2 = 0;
    if (*(ushort *)(IMAGE_DOS_HEADER_00400000.e_magic + IMAGE_DOS_HEADER_00400000.e_lfanew + 6) != 0
       ) {
      do {
        if ((*(uint *)(iVar1 + 0xc) <=
             *(uint *)(IMAGE_DOS_HEADER_00400000.e_magic +
                      *(int *)(&UNK_00400080.field_0x60 + IMAGE_DOS_HEADER_00400000.e_lfanew) + 0xc)
            ) && (*(uint *)(IMAGE_DOS_HEADER_00400000.e_magic +
                           *(int *)(&UNK_00400080.field_0x60 + IMAGE_DOS_HEADER_00400000.e_lfanew) +
                           0xc) < (uint)(*(int *)(iVar1 + 8) + *(int *)(iVar1 + 0xc)))) {
          *param_1 = *(ulong *)(iVar1 + 8);
          *param_2 = *(ulong *)(iVar1 + 0x24);
          return (void *)(*(int *)(iVar1 + 0xc) + 0x400000);
        }
        uVar2 = uVar2 + 1;
        iVar1 = iVar1 + 0x28;
      } while (uVar2 < *(ushort *)
                        (IMAGE_DOS_HEADER_00400000.e_magic + IMAGE_DOS_HEADER_00400000.e_lfanew + 6)
              );
    }
  }
  return (void *)0x0;
}


