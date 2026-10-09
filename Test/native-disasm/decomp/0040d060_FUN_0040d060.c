// FUN_0040d060 @ 0040d060 size=501 callers=2

void __fastcall FUN_0040d060(DWORD *param_1)

{
  DWORD *this;
  bool bVar1;
  int iVar2;
  HANDLE hObject;
  uint uVar3;
  undefined4 extraout_ECX;
  char *pcVar4;
  char local_54 [8];
  undefined8 local_4c;
  undefined1 local_44 [16];
  char local_34 [16];
  char local_24 [16];
  char local_14 [4];
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047a17e;
  local_10 = ExceptionList;
  local_54[0] = '\0';
  local_4c = 0;
  ExceptionList = &local_10;
  FUN_00451110(local_54,(uint *)"exeName");
  this = param_1 + 1;
  local_8 = 0;
  FUN_00440c80(local_44,this);
  local_8 = 1;
  FUN_00434b50(local_24,local_54,local_34,'\x01','\x02');
  local_8 = CONCAT31(local_8._1_3_,3);
  _eh_vector_destructor_iterator_(local_54,0x10,2,FUN_00434820);
  local_8 = 4;
  FUN_00434b50(local_34,local_24,local_14,'\x01','\x02');
  local_8 = CONCAT31(local_8._1_3_,5);
  FUN_00408600(0x2c1,local_34);
  FUN_00434820(local_34);
  local_8 = 0xffffffff;
  _eh_vector_destructor_iterator_(local_24,0x10,1,FUN_00434820);
  if (param_1[5] != 0) {
    DAT_004a2446 = 1;
    iVar2 = FUN_0043aad0(this,(byte *)"msedge",extraout_ECX,6);
    if (iVar2 == 0) {
      DAT_004a23c4 = 1;
      PTR_s___Google_Chrome_0049da04 = s___Microsoft_Edge_0048d0e8;
      ExceptionList = local_10;
      return;
    }
    bVar1 = FUN_00440970((byte *)this,(byte *)"brave.exe");
    if (bVar1) {
      PTR_s___Google_Chrome_0049da04 = s___Brave_0048d108;
      ExceptionList = local_10;
      return;
    }
    bVar1 = FUN_00440970((byte *)this,(byte *)"slimjet.exe");
    if (bVar1) {
      hObject = OpenProcess(0x410,0,*param_1);
      uVar3 = FUN_004070b0(hObject);
      CloseHandle(hObject);
      bVar1 = (char)uVar3 == '\0';
      PTR_s_Chrome_RenderWidgetHostHWND_0049d9f0 = s_Slimjet_RenderWidgetHostHWND_0048d164;
      pcVar4 = "Slimjet64_";
      if (bVar1) {
        pcVar4 = "Slimjet_";
      }
      PTR_s_Chrome__0049da10 = pcVar4;
      pcVar4 = "Slimjet64_WidgetWin_";
      if (bVar1) {
        pcVar4 = "Slimjet_WidgetWin_";
      }
      PTR_s_Chrome_WidgetWin__0049d9f8 = pcVar4;
      ExceptionList = local_10;
      return;
    }
    bVar1 = FUN_00440970((byte *)this,(byte *)"Arc.exe");
    if (bVar1) {
      DAT_004a23c6 = 1;
      PTR_s_Chrome__0049da10 = s_WinUIDesktopWin32WindowClass_0048d18c;
      PTR_s_Chrome_WidgetWin__0049d9f8 = s_WinUIDesktopWin32WindowClass_0048d18c;
      PTR_s_Chrome_RenderWidgetHostHWND_0049d9f0 = s_Chrome_WidgetWin_1_0048d1ac;
    }
  }
  ExceptionList = local_10;
  return;
}


