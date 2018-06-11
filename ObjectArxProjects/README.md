# Настройка проекта ObjectARX из пустого проекта в MSVS 2015 для AutoCAD 2017

Среды: MSVS 2015. Autocad 2017. Platform x64.

1. Открываем Студию. New Project -> Visual C++ -> Empty Project

```
Имя проекта: ArxEmpty
Папка с проектом: D:\MSVSProjects\ARXProjects\ArxEmpty
```

2. Project -> Properties -> Configuration Manager

```
Platform -> Win32 => <New...> => меняем с Win32 на x64 (ставим галочку на *Create new Solution Platforms) => Ok
Configuration оставляю Debug,  Platform меняю на x64. Active Solution Platform меняю на x64 => Ok
Close
В текущем окне настроек выставляется:
Configuration - Debug; Platform - x64.
```

3. Configuration Properties -> General

```
Outpu Directory выставляю
$(SolutionDir)$(Platform)\$(Configuration)\
Intermidate Directory
$(Platform)\$(Configuration)\
Target Name
$(ProjectName)

Target Extension меняю с .dll на
.arx

Platform Toolset для моего случая оставляю
Visual Studio 2015 (v140)

Configuration Type
Dynamic Library (.dll)

Use of MFC:
Use MFC in a Static Library

Character Set:
Use Multi-Byte Character Set
Common Language Runtime Support:
No Common Language Runtime Support
Whole Program Optimization:
Use Link Time Code Generation
```

4. Configuration Properties -> Debugging

```
Command
C:\Program Files\Autodesk\AutoCAD 2017\acad.exe
Command Arguments
/product ACAD
```

5.1 Configuration Properties -> VC++ Directories

```
General -> Include  Directories
C:\Autodesk\Autodesk_ObjectARX_2017_Win_64_and_32_Bit\inc;C:\Autodesk\Autodesk_ObjectARX_2017_Win_64_and_32_Bit\inc-$(Platform);
Library Directories
C:\Autodesk\Autodesk_ObjectARX_2017_Win_64_and_32_Bit\lib-$(Platform);
```

5.2 АЛЬТЕРНАТИВНЫЙ ВАРИАНТ УКАЗАНИЯ ПУТЕЙ ДО ЗАГОЛВОЧНЫХ ФАЙЛОВ И БИБЛИОТЕК (LIB):

```
Configuration Properties -> C/C++ -> General

Additional Include Directories добавляем
C:\Autodesk\Autodesk_ObjectARX_2018_Win_64_and_32_Bit\inc;C:\Autodesk\Autodesk_ObjectARX_2018_Win_64_and_32_Bit\inc-x64;%(AdditionalIncludeDirectories)

Configuration Properties -> Linker -> General

Additional Library Directories добавляем
C:\Autodesk\Autodesk_ObjectARX_2018_Win_64_and_32_Bit\lib-x64;%(AdditionalLibraryDirectories)
```

6. Далее в Configuration Properties -> C/C++ -> General

```
Debug Information Format:
Сменил
Program Database for Edit And Continue (/ZI)
на 
C7 compatible (/Z7)
```

7. Configuration Properties -> C/C++ -> Code Generation

```
Runtime Library:
Multi-threaded Debug DLL (/MDd)
Smaller Type Check
No
```

8. Configuration Properties -> Linker -> Input

```
Additional Dependencies добавил:
rxapi.lib;acdb21.lib;accore.lib;ac1st21.lib;
Module Definition File:
ArxEmpty.def
```

9. Добавил в проект 2 файла

```
ArxEmpty.cpp
ArxEmpty.def
```

10. ArxEmpty.def в def файл добавил код:

```
; LIBRARY "ArxEmpty.arx"
EXPORTS     
  acrxEntryPoint	PRIVATE
  acrxGetApiVersion	PRIVATE
```

11. ArxEmpty.cpp в cpp файл добавил код:

```
#include <aced.h>
#include <rxregsvc.h>
#include <acutads.h>
#include <adscodes.h>


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
```

12. Жму Build Solution

Собралось с некоторым числом Warning-ов:

```
1>------ Build started: Project: ArxEmpty, Configuration: Debug x64 ------
1>cl : Command line warning D9007: '/Gm' requires '/Zi or /ZI'; option ignored
1>  ArxEmpty.cpp
1>LINK : warning LNK4075: ignoring '/INCREMENTAL' due to '/LTCG' specification
1>     Creating library D:\MSVSProjects\ARXProjects\ArxEmpty\x64\Debug\ArxEmpty.lib and object D:\MSVSProjects\ARXProjects\ArxEmpty\x64\Debug\ArxEmpty.exp
1>LIBCMTD.lib(initializers.obj) : warning LNK4098: defaultlib 'msvcrt.lib' conflicts with use of other libs; use /NODEFAULTLIB:library
1>  Generating code
1>  Finished generating code
1>rxapi.lib(libinit.obj) : warning LNK4099: PDB 'rxapi.pdb' was not found with 'rxapi.lib(libinit.obj)' or at 'D:\MSVSProjects\ARXProjects\ArxEmpty\x64\Debug\rxapi.pdb'; linking object as if no debug info
1>  ArxEmpty.vcxproj -> D:\MSVSProjects\ARXProjects\ArxEmpty\x64\Debug\ArxEmpty.arx
1>  ArxEmpty.vcxproj -> D:\MSVSProjects\ARXProjects\ArxEmpty\x64\Debug\ArxEmpty.pdb (Partial PDB)
========== Build: 1 succeeded, 0 failed, 0 up-to-date, 0 skipped ==========
```

14. ArxEmpty.arx файл собрался.

15. Запускаю Автокад

```
New Drawing
Печатаю команду
ARX
Выбираю Load
Выбираю созданный в папке в /x64/Debug/ArxEmpty.arx
ARX-файл

Во всплывшем окне жму "Always Load"
```

15. Модуль Arx загрузился, но свою зарегистрированную команду ASTART или АСТАРТ я не вижу, когда печатаю её в консоли Автокада.
