#include <aced.h>
#include <rxregsvc.h>
#include <acutads.h>
#include <adscodes.h>

//*

// This peace of code will make your project to NOT NEED the
// *.def file anymore, you can exclude def-file from the project
// and it will build correctly

#if !defined(_WIN64) && !defined (_AC64)
#pragma comment(linker, "/export:_acrxGetApiVersion,PRIVATE")
#else
#pragma comment(linker, "/export:acrxGetApiVersion,PRIVATE")
#endif
//*/

// ���������� �������
static void initApp(void);
static void unloadApp(void);
static void our_app1(void);

// ������� initApp
static void initApp()
{
	// ����������� ����� ������� ASTART � ������ BOOK
	acedRegCmds->addCommand(L"BOOK", // ��� ������ ������
		L"ASTART", // ������ ��� �������
		L"������", // ������ ��� ������� (������ ��������������)
		ACRX_CMD_TRANSPARENT, // ����� �������� � ���������� ������
		our_app1); // ��� ���������� �������
}

// ������� unloadApp
static void unloadApp()
{
	acedRegCmds->removeGroup(L"BOOK"); // �������� ������ BOOK
}

// ���������������� ������� our_app1
static void our_app1()
{
	acedAlert(L"������� �������\n��� AutoCAD 2015");
}


// ������� �������������� ������� acrxEntryPoint
extern "C" AcRx::AppRetCode
acrxEntryPoint(AcRx::AppMsgCode msg, void* pkt)
{
	switch (msg)
	{
	case AcRx::kInitAppMsg:
		acrxUnlockApplication(pkt);
		acrxRegisterAppMDIAware(pkt);
		initApp();
		break;
	case AcRx::kUnloadAppMsg:
		unloadApp();
		break;
	default:
		break;
	}
	return AcRx::kRetOK;
}
