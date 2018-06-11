// Н.Н.Полещук, App01\App01.cpp
#include <aced.h>
#include <rxregsvc.h>
#include <acutads.h>

//#include <aced.h>
//#include <rxregsvc.h>

//#include <afxdllx.h>
//#include <rxmfcapi.h>
//#include <geray3d.h>
//#include <dbsol3d.h>
//#include <dbapserv.h>

#include <acdocman.h> // для acDocManager

#include <dbents.h> // Для всех примитивов и работы с БД
#include <geassign.h>  // для asDblArray
#include <migrtion.h> // для acdbCurDwg
#include <adscodes.h> // для RTNORM
#include <dbents.h> // Для всех примитивов и работы с БД

#include "Ship.h"
#include "ShipJig.h"
//#include "StdAfx.h"
//#include <tchar.h> // _T() macros

// Диалоговые окна
// CAdUiBaseDialog , CAdUiDialog , CAcUiDialog,
//#include <acui.h>
//#include <adui.h>

// #include "MyDialog.h"


//#define _AFXDLL


// 2.5 задание положения, диаметра и длины
// MFC

// макрос ELEMENTS (число элементов массива)
#define ELEMENTS(array) (sizeof(array)/sizeof((array)[0]))


// Объявления функций
static void initApp (void);
static void unloadApp (void);
static void our_app1 (void);
static int our_lsp (struct resbuf*);
static int dofun (void);





AcDbBlockTableRecord* getModelSpace(AcDb::OpenMode mode)
{
	AcDbBlockTableRecord* Blok = NULL;
	AcDbBlockTable *pBlockTable;

	Acad::ErrorStatus es;

	//AcDbDatabase * pDb = acdbHostApplicationServices()->workingDatabase();
	AcApDocument* pDoc = acDocManager->curDocument();

	es = acDocManager->lockDocument(pDoc);
	if (es != Acad::eOk)
	{
		//ads_alert(_T("Failed to lock the document!"));
		ads_alert((L"Failed to lock the document!"));
		return NULL; //Adesk::kFalse;
	}

	AcDbDatabase* pDb = pDoc->database();

	es = pDb->getBlockTable(pBlockTable, AcDb::kForRead);
	if (es != Acad::eOk)
	{
		//ads_alert(_T("Failed to get block table!"));
		ads_alert((L"Failed to get block table!"));
		return NULL;
	}

	if (!pDb)
	{
		return NULL;
	}

	AcDbBlockTable* pTbl = NULL;
	if ((es = pDb->getBlockTable(pTbl, AcDb::kForRead)) != Acad::eOk)
	{
		return NULL;
	}
	if ((es = pTbl->getAt(ACDB_MODEL_SPACE, Blok, mode)) != Acad::eOk)
	{
		pTbl->close();
		return NULL;
	}
	pTbl->close();

	return Blok;

}


Acad::ErrorStatus Add(AcDbEntity * pEnt, AcDbBlockTableRecord* Blok)
{
	if (!pEnt)
	{
		return Acad::eNullEntityPointer;
	}

	Acad::ErrorStatus es;
	if (!Blok)
	{
		Blok = getModelSpace(AcDb::kForWrite);
		if (!Blok) return Acad::eInvalidOwnerObject;
	}
	if (Blok->isWriteEnabled() == Adesk::kFalse)
	{
		AcDbObject* pObj = NULL;
		es = acdbOpenObject(pObj, Blok->objectId(), AcDb::kForWrite);
		Blok = AcDbBlockTableRecord::cast(pObj);
	}
	if ((es = Blok->appendAcDbEntity(pEnt)) != Acad::eOk)
	{
		Blok->close();
		return es;
	}
	Blok->close();
	return Acad::eOk;
}


Acad::ErrorStatus AddCircle(AcGePoint3d center, ads_real radius, AcDbObjectId& id, bool close = true)
{
	AcDbBlockTableRecord* pBlock = NULL;
	Acad::ErrorStatus es;

	AcDbCircle* pCirEnt = new AcDbCircle();
	AcDbText* pText = new AcDbText();

	pCirEnt->setCenter(center);
	pCirEnt->setRadius(radius);
	es = Add(pCirEnt, pBlock);

	if (close) es = pCirEnt->close();
	id = pCirEnt->objectId();

	return es;
}



//Acad::ErrorStatus AddShip(AcGePoint3d Pa, AcGePoint3d Pf, double hw, double hz, AcDbObjectId& id, bool close = true)
Acad::ErrorStatus AddShip (
							AcGePoint3d ptAft,	// точка на ахтерштевне
							AcGePoint3d ptFore, // точка на форштевне
							double fHalfWidth,	// полуширина судна
							double fHeight,		// высота
							AcDbObjectId& id,
							bool close = true
						)
{
	AcDbBlockTableRecord* pBlock = NULL;
	Acad::ErrorStatus es;

	Ship* pShip = new Ship(ptAft, ptFore, fHalfWidth, fHeight);

	//pShip->setsetCenter(center);

	es = Add(pShip, pBlock);

	if (close) es = pShip->close();
	id = pShip->objectId();

	return es;
}

// Пользовательская функция our_app1
static void draw_circle()
{
	AcDbObjectId idCircle = 0;
	
	ads_point Ptc;
	Ptc[X] = 0.0; Ptc[Y] = 0.0; Ptc[Z] = 0.0;
	if (acedGetPoint(NULL, _T("\nPick a point for the center: "), Ptc) != RTNORM) return;
	AcGePoint3d ptCenter(Ptc[X], Ptc[Y], Ptc[Z]);
	
	ads_real radius;
	if (acedGetReal(_T("\nPick radius of the circle: "), &radius) != RTNORM) return;
	
	AddCircle(ptCenter, radius, idCircle);
}


// Пользовательская функция our_app1
static void draw_ship()
{
//		AcGePoint3d ptAft,	// точка на ахтерштевне
//		AcGePoint3d ptFor, // точка на форштевне
//		double fHalfWidth,	// полуширина судна
//		double fHeight,		// высота

	int res = 0; // для анализа кода ошибок

	////////////////////////////////////////////////////////////////////////
	ads_point pointAft;
	pointAft[X] = 0.0;
	pointAft[Y] = 0.0; 
	pointAft[Z] = 0.0;

	res = acedGetPoint(NULL, (L"\nPick a point on Arhshtevn: "), pointAft);
	if (res != RTNORM)
	{
		acedAlert(L"Точка на ахтерштевне не получена !");
		//acdbFail(L"Невозможный номер функции \n в таблице. ");
		return;
	}
	AcGePoint3d ptAft(pointAft[X], pointAft[Y], pointAft[Z]);

	////////////////////////////////////////////////////////////////////////
	ads_point pointFor;
	pointFor[X] = 0.0;
	pointFor[Y] = 0.0;
	pointFor[Z] = 0.0;

	res = acedGetPoint(NULL, (L"\nPick a point on Forshtevn: "), pointFor);
	if (res != RTNORM)
	{
		acedAlert(L"Точка на форштевне не получена !");
		return;
	}
	AcGePoint3d ptFor(pointFor[X], pointFor[Y], pointFor[Z]);

	////////////////////////////////////////////////////////////////////////
	double fHalfWidth = 0.0;
	res = acedGetReal((L"\nPick half-width of the Ship: "), &fHalfWidth);
	if (res != RTNORM)
	{
		acedAlert(L"Полуширина судна не получена !");
		return;
	}

	////////////////////////////////////////////////////////////////////////
	double fHeight = 0.0;
	res = acedGetReal((L"\nPick height of the Ship: "), &fHeight);
	if (res != RTNORM)
	{
		acedAlert(L"Высота судна не получена !");
		return;
	}


	AcDbObjectId idShip = 0; // функция AddShip требует этот параметр

	AddShip(ptAft, ptFor, fHalfWidth, fHeight, idShip);

}

static void jig_ship()
{
	int res = 0; // для анализа кода ошибок

	////////////////////////////////////////////////////////////////////////
	ads_point pointAft;
	pointAft[X] = 0.0;
	pointAft[Y] = 0.0; 
	pointAft[Z] = 0.0;

	res = acedGetPoint(NULL, (L"\nPick a point on Arhshtevn: "), pointAft);
	if (res != RTNORM)
	{
		acedAlert(L"Точка на ахтерштевне не получена !");
		//acdbFail(L"Невозможный номер функции \n в таблице. ");
		return;
	}
	AcGePoint3d ptAft(pointAft[X], pointAft[Y], pointAft[Z]);

	////////////////////////////////////////////////////////////////////////
	ads_point pointFor;
	pointFor[X] = 0.0;
	pointFor[Y] = 0.0;
	pointFor[Z] = 0.0;

	res = acedGetPoint(NULL, (L"\nPick a point on Forshtevn: "), pointFor);
	if (res != RTNORM)
	{
		acedAlert(L"Точка на форштевне не получена !");
		return;
	}
	AcGePoint3d ptFor(pointFor[X], pointFor[Y], pointFor[Z]);



	AcGePoint3d p0 = AcGePoint3d(ptAft[X], ptAft[Y], ptAft[Z]);
	AcGePoint3d p1 = AcGePoint3d(ptFor[X], ptFor[Y], ptFor[Z]);

	ShipJig* pJig = new ShipJig(p0, p1);
	pJig->doIt();
	delete pJig;

}

// объявление структуры для хранения
// имен и указателей LISP-функций
struct func_entry
{
	ACHAR *func_name; int (*func) (struct resbuf *);
};

// стандартный массив имен и указателей LISP-функций
// приложения (чаще заполняется с помощью acedRegFunc)
static struct func_entry func_table[] = {
	{L"funstart", our_lsp},
};


//extern CDlgMdless* g_pModeless;

//
// Пользовательская функция our_app1
static void our_app1()
{
	acedAlert(L"Простая команда\nдля AutoCAD 2015");

	//CAcModuleResourceOverride resOverride;
	//CMyDialog dlg;
	//dlg.DoModal();

	//CAcModuleResourceOverride resOverride;

	/*
	CSomeInfo dlg;
	dlg.DoModal();

	/*
	CAcModuleResourceOverride resOverride;
	g_pModeless = new CDlgMdless;
	g_pModeless->Create(IDD_DLGMDLESS);
	g_pModeless->ShowWindow(SW_SHOWNORMAL);
	//*/

}

//
// LISP-функция, которая вызывается
// с помощью выражения (funstart)
static int our_lsp (resbuf* RB)
{
  acedAlert(L"Простая LISP-функция\nдля AutoCAD 2015");
  acedRetReal(3.14);// в AutoCAD возвращаем число 3.14
  return RTNORM;
}
// вычисление индекса LISP-функции в таблице
// (по введенному LISP-выражению)
// и выполнение C-функции по указателю
static int dofun()
{
    struct resbuf *rb = NULL;
    int nfun, rc;

	// У нас nfun == 0, а в общем случае
	// по имени функции из LISP-выражения надо вычислить
	// номер в таблице LISP-функций приложения.
	// Дополнительно проверяется nfun
    if ((nfun = acedGetFunCode()) < 0 || nfun >= ELEMENTS(func_table))
	{
        acdbFail(L"Невозможный номер функции в таблице. ");
        return RTERROR;
    }
    // проверка аргументов LISP-функции;
	// наша функция аргументами не пользуется
    rb = acedGetArgs();

    // выполнение LISP-функции
    rc = (*func_table[nfun].func)(rb);
    acutRelRb(rb);
    return rc;
}



// Функция initApp
static void initApp()
{
	// регистрация новой команды ASTART в группе BOOK
	acedRegCmds->addCommand(L"BOOK", // имя группы команд
		L"ASTART", // первое имя команды
		L"АСТАРТ", // второе имя команды (обычно локализованное)
		ACRX_CMD_TRANSPARENT, // может работать в прозрачном режиме
		our_app1 // имя вызываемой функции
	);

	// регистрация новой команды
	acedRegCmds->addCommand(L"GEOMETRY_OBJECTS", // имя группы команд
		L"CIRCLE_DRAW", // первое имя команды
		L"CIRCLE_DRAW", // второе имя команды (обычно локализованное)
		ACRX_CMD_TRANSPARENT, // может работать в прозрачном режиме
		draw_circle // имя вызываемой функции
	);

	// регистрация новой команды
	acedRegCmds->addCommand(L"REAL_OBJECTS", // имя группы команд
		L"SHIP_DRAW", // первое имя команды
		L"SHIP_DRAW", // второе имя команды (обычно локализованное)
		ACRX_CMD_TRANSPARENT, // может работать в прозрачном режиме
		draw_ship // имя вызываемой функции
	);

	// регистрация новой команды
	acedRegCmds->addCommand(L"REAL_OBJECTS", // имя группы команд
		L"SHIP_JIG", // первое имя команды
		L"SHIP_JIG", // второе имя команды (обычно локализованное)
		ACRX_CMD_TRANSPARENT, // может работать в прозрачном режиме
		jig_ship // имя вызываемой функции
	);

}
// Функция unloadApp
static void unloadApp()
{
	acedRegCmds->removeGroup(L"BOOK"); // удаление группы BOOK
}

//
// Главная экспортируемая функция acrxEntryPoint
/*
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
//*/
extern "C" AcRx::AppRetCode
acrxEntryPoint(AcRx::AppMsgCode msg, void* pkt)
{
	switch (msg)
	{
	case AcRx::kInitAppMsg:
		acrxUnlockApplication(pkt);
		acrxRegisterAppMDIAware(pkt);
		initApp();
		Ship::rxInit(); // вот эту строчку
		acrxBuildClassHierarchy();// и эту
		break;
	case AcRx::kUnloadAppMsg:
      unloadApp();
      break;
    case AcRx::kLoadDwgMsg:
      // регистрация LISP-функции funstart
      acedDefun(L"funstart", 0);
	  break;
    case AcRx::kInvkSubrMsg:
      //вычисление индекса в таблице функций
	  dofun();
      break;

    default:
      break;
  }
  return AcRx::kRetOK;
}
