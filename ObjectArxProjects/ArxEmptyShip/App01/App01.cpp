// �.�.�������, App01\App01.cpp
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

#include <acdocman.h> // ��� acDocManager

#include <dbents.h> // ��� ���� ���������� � ������ � ��
#include <geassign.h>  // ��� asDblArray
#include <migrtion.h> // ��� acdbCurDwg
#include <adscodes.h> // ��� RTNORM
#include <dbents.h> // ��� ���� ���������� � ������ � ��

#include "Ship.h"
#include "ShipJig.h"
//#include "StdAfx.h"
//#include <tchar.h> // _T() macros

// ���������� ����
// CAdUiBaseDialog , CAdUiDialog , CAcUiDialog,
//#include <acui.h>
//#include <adui.h>

// #include "MyDialog.h"


//#define _AFXDLL


// 2.5 ������� ���������, �������� � �����
// MFC

// ������ ELEMENTS (����� ��������� �������)
#define ELEMENTS(array) (sizeof(array)/sizeof((array)[0]))


// ���������� �������
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
							AcGePoint3d ptAft,	// ����� �� �����������
							AcGePoint3d ptFore, // ����� �� ���������
							double fHalfWidth,	// ���������� �����
							double fHeight,		// ������
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

// ���������������� ������� our_app1
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


// ���������������� ������� our_app1
static void draw_ship()
{
//		AcGePoint3d ptAft,	// ����� �� �����������
//		AcGePoint3d ptFor, // ����� �� ���������
//		double fHalfWidth,	// ���������� �����
//		double fHeight,		// ������

	int res = 0; // ��� ������� ���� ������

	////////////////////////////////////////////////////////////////////////
	ads_point pointAft;
	pointAft[X] = 0.0;
	pointAft[Y] = 0.0; 
	pointAft[Z] = 0.0;

	res = acedGetPoint(NULL, (L"\nPick a point on Arhshtevn: "), pointAft);
	if (res != RTNORM)
	{
		acedAlert(L"����� �� ����������� �� �������� !");
		//acdbFail(L"����������� ����� ������� \n � �������. ");
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
		acedAlert(L"����� �� ��������� �� �������� !");
		return;
	}
	AcGePoint3d ptFor(pointFor[X], pointFor[Y], pointFor[Z]);

	////////////////////////////////////////////////////////////////////////
	double fHalfWidth = 0.0;
	res = acedGetReal((L"\nPick half-width of the Ship: "), &fHalfWidth);
	if (res != RTNORM)
	{
		acedAlert(L"���������� ����� �� �������� !");
		return;
	}

	////////////////////////////////////////////////////////////////////////
	double fHeight = 0.0;
	res = acedGetReal((L"\nPick height of the Ship: "), &fHeight);
	if (res != RTNORM)
	{
		acedAlert(L"������ ����� �� �������� !");
		return;
	}


	AcDbObjectId idShip = 0; // ������� AddShip ������� ���� ��������

	AddShip(ptAft, ptFor, fHalfWidth, fHeight, idShip);

}

static void jig_ship()
{
	int res = 0; // ��� ������� ���� ������

	////////////////////////////////////////////////////////////////////////
	ads_point pointAft;
	pointAft[X] = 0.0;
	pointAft[Y] = 0.0; 
	pointAft[Z] = 0.0;

	res = acedGetPoint(NULL, (L"\nPick a point on Arhshtevn: "), pointAft);
	if (res != RTNORM)
	{
		acedAlert(L"����� �� ����������� �� �������� !");
		//acdbFail(L"����������� ����� ������� \n � �������. ");
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
		acedAlert(L"����� �� ��������� �� �������� !");
		return;
	}
	AcGePoint3d ptFor(pointFor[X], pointFor[Y], pointFor[Z]);



	AcGePoint3d p0 = AcGePoint3d(ptAft[X], ptAft[Y], ptAft[Z]);
	AcGePoint3d p1 = AcGePoint3d(ptFor[X], ptFor[Y], ptFor[Z]);

	ShipJig* pJig = new ShipJig(p0, p1);
	pJig->doIt();
	delete pJig;

}

// ���������� ��������� ��� ��������
// ���� � ���������� LISP-�������
struct func_entry
{
	ACHAR *func_name; int (*func) (struct resbuf *);
};

// ����������� ������ ���� � ���������� LISP-�������
// ���������� (���� ����������� � ������� acedRegFunc)
static struct func_entry func_table[] = {
	{L"funstart", our_lsp},
};


//extern CDlgMdless* g_pModeless;

//
// ���������������� ������� our_app1
static void our_app1()
{
	acedAlert(L"������� �������\n��� AutoCAD 2015");

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
// LISP-�������, ������� ����������
// � ������� ��������� (funstart)
static int our_lsp (resbuf* RB)
{
  acedAlert(L"������� LISP-�������\n��� AutoCAD 2015");
  acedRetReal(3.14);// � AutoCAD ���������� ����� 3.14
  return RTNORM;
}
// ���������� ������� LISP-������� � �������
// (�� ���������� LISP-���������)
// � ���������� C-������� �� ���������
static int dofun()
{
    struct resbuf *rb = NULL;
    int nfun, rc;

	// � ��� nfun == 0, � � ����� ������
	// �� ����� ������� �� LISP-��������� ���� ���������
	// ����� � ������� LISP-������� ����������.
	// ������������� ����������� nfun
    if ((nfun = acedGetFunCode()) < 0 || nfun >= ELEMENTS(func_table))
	{
        acdbFail(L"����������� ����� ������� � �������. ");
        return RTERROR;
    }
    // �������� ���������� LISP-�������;
	// ���� ������� ����������� �� ����������
    rb = acedGetArgs();

    // ���������� LISP-�������
    rc = (*func_table[nfun].func)(rb);
    acutRelRb(rb);
    return rc;
}



// ������� initApp
static void initApp()
{
	// ����������� ����� ������� ASTART � ������ BOOK
	acedRegCmds->addCommand(L"BOOK", // ��� ������ ������
		L"ASTART", // ������ ��� �������
		L"������", // ������ ��� ������� (������ ��������������)
		ACRX_CMD_TRANSPARENT, // ����� �������� � ���������� ������
		our_app1 // ��� ���������� �������
	);

	// ����������� ����� �������
	acedRegCmds->addCommand(L"GEOMETRY_OBJECTS", // ��� ������ ������
		L"CIRCLE_DRAW", // ������ ��� �������
		L"CIRCLE_DRAW", // ������ ��� ������� (������ ��������������)
		ACRX_CMD_TRANSPARENT, // ����� �������� � ���������� ������
		draw_circle // ��� ���������� �������
	);

	// ����������� ����� �������
	acedRegCmds->addCommand(L"REAL_OBJECTS", // ��� ������ ������
		L"SHIP_DRAW", // ������ ��� �������
		L"SHIP_DRAW", // ������ ��� ������� (������ ��������������)
		ACRX_CMD_TRANSPARENT, // ����� �������� � ���������� ������
		draw_ship // ��� ���������� �������
	);

	// ����������� ����� �������
	acedRegCmds->addCommand(L"REAL_OBJECTS", // ��� ������ ������
		L"SHIP_JIG", // ������ ��� �������
		L"SHIP_JIG", // ������ ��� ������� (������ ��������������)
		ACRX_CMD_TRANSPARENT, // ����� �������� � ���������� ������
		jig_ship // ��� ���������� �������
	);

}
// ������� unloadApp
static void unloadApp()
{
	acedRegCmds->removeGroup(L"BOOK"); // �������� ������ BOOK
}

//
// ������� �������������� ������� acrxEntryPoint
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
		Ship::rxInit(); // ��� ��� �������
		acrxBuildClassHierarchy();// � ���
		break;
	case AcRx::kUnloadAppMsg:
      unloadApp();
      break;
    case AcRx::kLoadDwgMsg:
      // ����������� LISP-������� funstart
      acedDefun(L"funstart", 0);
	  break;
    case AcRx::kInvkSubrMsg:
      //���������� ������� � ������� �������
	  dofun();
      break;

    default:
      break;
  }
  return AcRx::kRetOK;
}
