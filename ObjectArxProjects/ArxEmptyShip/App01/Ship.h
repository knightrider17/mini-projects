//-----------------------------------------------------------------------------
//----- Ship.h : Declaration of the Ship
//-----------------------------------------------------------------------------
#ifndef SHIP__H
#define SHIP__H


#ifdef CUSTDBX_MODULE
#define DLLIMPEXP __declspec(dllexport)
#else
//----- Note: we don't use __declspec(dllimport) here, because of the
//----- "local vtable" problem with msvc. If you use __declspec(dllimport),
//----- then, when a client dll does a new on the class, the object's
//----- vtable pointer points to a vtable allocated in that client
//----- dll. If the client dll then passes the object to another dll,
//----- and the client dll is then unloaded, the vtable becomes invalid
//----- and any virtual calls on the object will access invalid memory.
//-----
//----- By not using __declspec(dllimport), we guarantee that the
//----- vtable is allocated in the server dll during the ctor and the
//----- client dll does not overwrite the vtable pointer after calling
//----- the ctor. And, since we expect the server dll to remain in
//----- memory indefinitely, there is no problem with vtables unexpectedly
//----- going away.
#define DLLIMPEXP
#endif

//-----------------------------------------------------------------------------
#include "dbmain.h"

//-----------------------------------------------------------------------------
//class DLLIMPEXP Ship : public AcDbEntity

class Ship : public AcDbEntity
{
public:
	ACRX_DECLARE_MEMBERS(Ship) ;

protected:
	static Adesk::UInt32 kCurrentVersionNumber;

public:
	// �������� ������
	AcGePoint3d m_ptAft; // ����� �� �����������
	AcGePoint3d m_ptFore; // ����� �� ���������
	double m_fHw; // ���������� �����
	double m_fHeight; // ������
	// ������������ ������
	double m_fL; // ����� �� �����
	AcGeVector3d m_vecU, m_vecV, m_vecW;// ��������� ������� �� ���� X,Y,Z
	// ������������ ������� �����
	Adesk::Int32 m_nBaseline; // ����� ����� ��������� ����� �����
	AcGePoint3dArray m_arBaseline; // ������ ����� �����
	Adesk::Int32 m_nBulwark; // ����� ����� ����� ����������
	AcGePoint3dArray m_arBulwark; // ������ ����� ����������

public:
	Ship () ;
	Ship (AcGePoint3d, AcGePoint3d, double, double);
	Ship (const Ship&);
	virtual ~Ship();

	//----- ��������� AcDbObject
	//- �������� DWG-������������
	virtual Acad::ErrorStatus dwgOutFields (AcDbDwgFiler *pFiler) const ; // 2.1 dwgOutFields
	virtual Acad::ErrorStatus dwgInFields (AcDbDwgFiler *pFiler) ; // 2.1 dwgInFields

	//- �������� DXF-������������
	virtual Acad::ErrorStatus dxfOutFields (AcDbDxfFiler *pFiler) const ;
	virtual Acad::ErrorStatus dxfInFields (AcDbDxfFiler *pFiler) ;

	//----- ��������� AcDbEntity
	//- �������� �������
protected:
	virtual void subViewportDraw (AcGiViewportDraw *mode) ;
	virtual Adesk::UInt32 subViewportDrawLogicalFlags (AcGiViewportDraw *vd) ;
	virtual Adesk::Boolean subWorldDraw (AcGiWorldDraw *mode) ; // 2.1 subWorldDraw
	virtual Adesk::UInt32 subSetAttributes (AcGiDrawableTraits *traits) ;

	//- �������� ����� ��������� ��������
public:
	virtual Acad::ErrorStatus subGetOsnapPoints (
		AcDb::OsnapMode osnapMode,
		Adesk::GsMarker gsSelectionMark,
		const AcGePoint3d &pickPoint,
		const AcGePoint3d &lastPoint,
		const AcGeMatrix3d &viewXform,
		AcGePoint3dArray &snapPoints,
		AcDbIntArray &geomIds) const ;
	//virtual Acad::ErrorStatus subGetOsnapPoints (
	//	AcDb::OsnapMode osnapMode,
	//	Adesk::GsMarker gsSelectionMark,
	//	const AcGePoint3d &pickPoint,
	//	const AcGePoint3d &lastPoint,
	//	const AcGeMatrix3d &viewXform,
	//	AcGePoint3dArray &snapPoints,
	//	AcDbIntArray &geomIds,
	//	const AcGeMatrix3d &insertionMat) const ;

	//- �������� ���������� �����
	virtual Acad::ErrorStatus subGetGripPoints (AcGePoint3dArray &gripPoints, AcDbIntArray &osnapModes, AcDbIntArray &geomIds) const ; // 2.3 subGetGripPoints
	virtual Acad::ErrorStatus subMoveGripPointsAt (const AcDbIntArray &indices, const AcGeVector3d &offset) ; // 2.3 subMoveGripPoints
	//virtual Acad::ErrorStatus subGetGripPoints (
	//	AcDbGripDataPtrArray &grips, const double curViewUnitSize, const int gripSize, 
	//	const AcGeVector3d &curViewDir, const int bitflags) const ;
	//virtual Acad::ErrorStatus subMoveGripPointsAt (const AcDbVoidPtrArray &gripAppData, const AcGeVector3d &offset, const int bitflags) ;

	// ���� ������
	// ������� ������ (LIST)
	virtual void subList(void) const;
	// ������� ������ ��������������
	virtual Acad::ErrorStatus subTransformBy(const AcGeMatrix3d& xform); // 2.2 subTransformBy
	// �����������
	Acad::ErrorStatus subExplode(AcDbVoidPtrArray& entitySet) const; // 2.4
	// ���������� �������� ����� ��� ���������
	void storePoints(void);// ������������ m_arBaseline, m_arBulwark;

} ;

#ifdef CUSTDBX_MODULE
ACDB_REGISTER_OBJECT_ENTRY_AUTO(Ship)
#endif

#endif