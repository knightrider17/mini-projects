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

// Объявления функций
static void initApp(void);
static void unloadApp(void);
static void our_app1(void);

// Функция initApp
static void initApp()
{
	// регистрация новой команды ASTART в группе BOOK
	acedRegCmds->addCommand(L"BOOK", // имя группы команд
		L"ASTART", // первое имя команды
		L"АСТАРТ", // второе имя команды (обычно локализованное)
		ACRX_CMD_TRANSPARENT, // может работать в прозрачном режиме
		our_app1); // имя вызываемой функции
}

// Функция unloadApp
static void unloadApp()
{
	acedRegCmds->removeGroup(L"BOOK"); // удаление группы BOOK
}

// Пользовательская функция our_app1
static void our_app1()
{
	acedAlert(L"Простая команда\nдля AutoCAD 2015");
}


// Главная экспортируемая функция acrxEntryPoint
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
