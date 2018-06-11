//-----------------------------------------------------------------------------
//----- Ship.cpp : Implementation of Ship
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "Ship.h"

//-----------------------------------------------------------------------------
Adesk::UInt32 Ship::kCurrentVersionNumber = 1 ;

//-----------------------------------------------------------------------------
ACRX_DXF_DEFINE_MEMBERS (
	Ship,
	AcDbEntity,
	AcDb::kDHL_CURRENT,
	AcDb::kMReleaseCurrent, 
	AcDbProxyEntity::kNoOperation,
	SHIP,
CUSTDBXAPP
|Product Desc:     A description for your object
|Company:          Your company name
|WEB Address:      Your company WEB site address
)

//-----------------------------------------------------------------------------
Ship::Ship () : AcDbEntity ()
{
	m_ptAft = AcGePoint3d(0.0, 0.0, 0.0);
	m_ptFore = AcGePoint3d(1.0, 0.0, 0.0);
	m_fHw = 1.0;
	m_fHeight = 1.0;
	storePoints();
}

//Ship::Ship(AcGePoint3d Pa, AcGePoint3d Pf, double hw, double hz) : AcDbEntity()
Ship::Ship(	AcGePoint3d Pa, // ����� �� �����������
			AcGePoint3d Pf, // ����� �� ���������
			double hw,		// ���������� �����
			double hz		// ������
		  ) : AcDbEntity()
{
	m_ptAft = Pa;
	m_ptFore = Pf;
	m_fHw = hw;
	m_fHeight = hz;
	storePoints();
}

Ship::Ship(const Ship& o)
{
	m_ptAft = o.m_ptAft;
	m_ptFore = o.m_ptFore;
	m_fL = o.m_fL;
	m_fHeight = o.m_fHeight;
	m_fHw = o.m_fHw;
	m_vecU = o.m_vecU;
	m_vecV = o.m_vecV;
	m_vecW = o.m_vecW;
	m_nBaseline = o.m_nBaseline;
	m_arBaseline = o.m_arBaseline;
	m_nBulwark = o.m_nBulwark;
	m_arBulwark = o.m_arBulwark;
}

Ship::~Ship()
{
}

//-----------------------------------------------------------------------------
//----- ��������� AcDbObject
//- �������� DWG-������������
Acad::ErrorStatus Ship::dwgOutFields (AcDbDwgFiler *pFiler) const
{
	assertReadEnabled();
	//----- ������ ����� ��������� ������ ������-��������.
	Acad::ErrorStatus es = AcDbEntity::dwgOutFields (pFiler);

	if ( es != Acad::eOk )
		return (es);
	//----- ������� ���������� ��������� ����� ������ �������
	es = pFiler->writeUInt32(Ship::kCurrentVersionNumber);
	if ( es != Acad::eOk )
		return (es);
	//----- ����� ����������
	//.....
	pFiler->writeItem(m_ptAft);
	pFiler->writeItem(m_ptFore);
	pFiler->writeItem(m_fHw);
	pFiler->writeItem(m_fHeight);
	pFiler->writeItem(m_fL);
	pFiler->writeItem(m_vecU);
	pFiler->writeItem(m_vecV);
	pFiler->writeItem(m_vecW);
	// ������������� int � Adesk::Int32
	Adesk::Int32 aNum = (Adesk::Int32)m_nBaseline;
	pFiler->writeInt32(aNum);

	if (m_nBaseline > 0)
	{	for (int i = 0; i < m_nBaseline; i++)
		{ pFiler->writeItem(m_arBaseline.at(i)); }
	}

	// ������������� int � Adesk::Int32
	aNum = (Adesk::Int32)m_nBulwark;
	pFiler->writeInt32(aNum);

	if (m_nBulwark > 0)
	{	for (int i = 0; i < m_nBulwark; i++)
		{ pFiler->writeItem(m_arBulwark.at(i)); }
	}

	return (pFiler->filerStatus ());
}

Acad::ErrorStatus Ship::dwgInFields (AcDbDwgFiler *pFiler)
{
	assertWriteEnabled () ;
	//----- ������ ����� ��������� ������ ������-��������.
	Acad::ErrorStatus es =AcDbEntity::dwgInFields (pFiler) ;
	if ( es != Acad::eOk )
		return (es) ;
	//----- ������� ��������� ����� ������ �������
	Adesk::UInt32 version =0 ;
	if ( (es = pFiler->readUInt32 (&version)) != Acad::eOk )
		return (es) ;
	if ( version > Ship::kCurrentVersionNumber )
		return (Acad::eMakeMeProxy) ;
	//- ���������������� ��������� ��� ������, ���� ������� ������
	// ���������� ������� �� ����� ������������ ��� ���������� ������.
	//if ( version < Ship::kCurrentVersionNumber )
	//	return (Acad::eMakeMeProxy) ;
	//----- ������ ����������
	//.....
	pFiler->readItem(&m_ptAft);
	pFiler->readItem(&m_ptFore);
	pFiler->readItem(&m_fHw);
	pFiler->readItem(&m_fHeight);
	pFiler->readItem(&m_fL);
	pFiler->readItem(&m_vecU);
	pFiler->readItem(&m_vecV);
	pFiler->readItem(&m_vecW);

	int i; AcGePoint3d pti;
	Adesk::Int32 aNum;
	pFiler->readInt32(&aNum);
	m_nBaseline = (int)aNum;
	if (m_nBaseline > 0)
	{
		m_arBaseline.removeAll(); // !!! ����� �������� ������ �����
		                          // ������������ �� ���������
		for (i = 0; i < m_nBaseline; i++)
		{
			pFiler->readItem(&pti);
			m_arBaseline.append(pti);
		}
	}

	pFiler->readInt32(&aNum);
	m_nBulwark = (int)aNum;
	if (m_nBulwark > 0)
	{
		m_arBulwark.removeAll(); // !!! ����� �������� ������ �����
		                         // ������������ �� ���������
		for (i = 0; i < m_nBulwark; i++)
		{
			pFiler->readItem(&pti);
			m_arBulwark.append(pti);
		}
	}

	return (pFiler->filerStatus ()) ;
}

//- �������� DXF-������������
Acad::ErrorStatus Ship::dxfOutFields (AcDbDxfFiler *pFiler) const
{
	assertReadEnabled () ;
	//----- ������ ����� ��������� ������ ������-��������.
	Acad::ErrorStatus es =AcDbEntity::dxfOutFields (pFiler) ;
	if ( es != Acad::eOk )
		return (es) ;
	es =pFiler->writeItem (AcDb::kDxfSubclass, _RXST("Ship")) ;
	if ( es != Acad::eOk )
		return (es) ;
	//----- ������� ���������� ��������� ����� ������ �������
	if ( (es =pFiler->writeUInt32 (kDxfInt32, Ship::kCurrentVersionNumber)) != Acad::eOk )
		return (es) ;
	//----- ����� ����������
	//.....
	pFiler->writeItem(AcDb::kDxfXCoord, m_ptAft);//10
	pFiler->writeItem(AcDb::kDxfXCoord + 1, m_ptFore);//11
	pFiler->writeItem(AcDb::kDxfReal, m_fHw);//40
	pFiler->writeItem(AcDb::kDxfReal + 1, m_fHeight);//41
	pFiler->writeItem(AcDb::kDxfReal + 2, m_fL);//42
	pFiler->writeItem(AcDb::kDxfXCoord + 5, m_vecU);//15
	pFiler->writeItem(AcDb::kDxfXCoord + 6, m_vecV);//16
	pFiler->writeItem(AcDb::kDxfNormalX, m_vecW);//210

	pFiler->writeItem(AcDb::kDxfInt32 + 1, m_nBaseline);//91
	if (m_nBaseline > 0)
		for (int i = 0; i < m_nBaseline; i++)
			pFiler->writeItem(AcDb::kDxfXCoord + 2, m_arBaseline.at(i));//12

	pFiler->writeItem(AcDb::kDxfInt32 + 2, m_nBulwark);//92
	if (m_nBulwark > 0)
		for (int i = 0; i < m_nBulwark; i++)
			pFiler->writeItem(AcDb::kDxfXCoord + 3, m_arBulwark.at(i));//13

	return (pFiler->filerStatus ()) ;
}

Acad::ErrorStatus Ship::dxfInFields (AcDbDxfFiler *pFiler)
{
	assertWriteEnabled () ;
	//----- ������ ����� ��������� ������ ������-��������.
	Acad::ErrorStatus es =AcDbEntity::dxfInFields (pFiler) ;
	if ( es != Acad::eOk || !pFiler->atSubclassData (_RXST("Ship")) )
		return (pFiler->filerStatus ()) ;
	//----- ������� ��������� ����� ������ �������
	struct resbuf rb ;
	pFiler->readItem (&rb) ;
	if ( rb.restype != AcDb::kDxfInt32 ) {
		pFiler->pushBackItem () ;
		pFiler->setError (Acad::eInvalidDxfCode,
			_RXST("\nError: expected group code %d (version #)"), AcDb::kDxfInt32) ;
		return (pFiler->filerStatus ()) ;
	}
	Adesk::UInt32 version =(Adesk::UInt32)rb.resval.rlong ;
	if ( version > Ship::kCurrentVersionNumber )
		return (Acad::eMakeMeProxy) ;
	//- ���������������� ��������� ��� ������, ���� ������� ������
	// ���������� ������� �� ����� ������������ ��� ���������� ������.
	//if ( version < Ship::kCurrentVersionNumber )
	//	return (Acad::eMakeMeProxy) ;
	//----- ������ DXF-��������� ����� ��������,
	// ����� �� �� ������� �� ������� �� �����������
	AcGePoint3d pti;

	while (es == Acad::eOk && (es = pFiler->readResBuf(&rb)) == Acad::eOk) {
		switch ( rb.restype ) {
			//----- ������ ���������� � �������� DXF-���� (������ ����)
			//case AcDb::kDxfXCoord:
			//	if ( version == 1 )
			//		cen3d =asPnt3d (rb.resval.rpoint) ;
			//	else 
			//		cen2d =asPnt2d (rb.resval.rpoint) ;
			//	break ;
			//.....
		case AcDb::kDxfXCoord://10 m_ptAft
			m_ptAft = asPnt3d(rb.resval.rpoint);
			break;
		case (AcDb::kDxfXCoord + 1) ://11 m_ptFore
			m_ptFore = asPnt3d(rb.resval.rpoint);
			break;
		case (AcDb::kDxfXCoord + 5) ://15 m_vecU
			m_vecU = asVec3d(rb.resval.rpoint);
			break;
		case (AcDb::kDxfXCoord + 6) ://16 m_vecV
			m_vecV = asVec3d(rb.resval.rpoint);
			break;
		case (AcDb::kDxfNormalX) ://210 m_vecW
			m_vecW = asVec3d(rb.resval.rpoint);
			break;
		case (AcDb::kDxfReal) ://40 m_fHw
			m_fHw = rb.resval.rreal;
			break;
		case (AcDb::kDxfReal + 1) ://41 m_fHeight
			m_fHeight = rb.resval.rreal;
			break;
		case (AcDb::kDxfReal + 2) ://42 m_fL
			m_fL = rb.resval.rreal;
			break;
		case (AcDb::kDxfInt32 + 1) ://91 m_nBaseline
			m_nBaseline = rb.resval.rint;
			if (m_arBaseline.length() > 0) m_arBaseline.removeAll();
			if (m_nBaseline > 0)
				for (int i = 0; i < m_nBaseline; i++)
				{
				pFiler->readResBuf(&rb);
				pti = AcGePoint3d(rb.resval.rpoint[X], rb.resval.rpoint[Y], rb.resval.rpoint[Z]);
				m_arBaseline.append(pti);
				}
			break;
		case (AcDb::kDxfInt32 + 2) ://92 m_nBulwark
			m_nBulwark = rb.resval.rint;
			if (m_arBulwark.length() > 0) m_arBulwark.removeAll();
			if (m_nBulwark > 0)
				for (int i = 0; i < m_nBulwark; i++)
				{
				pFiler->readResBuf(&rb);
				pti = AcGePoint3d(rb.resval.rpoint[X], rb.resval.rpoint[Y], rb.resval.rpoint[Z]);
				m_arBulwark.append(pti);
				}
			break;

			default:
				//----- ������������ DXF-������. �������� �������,
				// ����� �������� ��� ��������� ��� ���
				pFiler->pushBackItem () ;
				es =Acad::eEndOfFile ;
				break ;
		}
	}
	//----- � ���� ����� ���������� es ������ ��������� eEndOfFile
	//----- - ��� �� readResBuf() ��� �� �������. ���� ���,
	//----- �� ������ �� ������ � �� ������ ���������� �����.
	if ( es != Acad::eEndOfFile )
		return (Acad::eInvalidResBuf) ;

	return (pFiler->filerStatus ()) ;
}

//-----------------------------------------------------------------------------
//----- ��������� AcDbEntity
Adesk::Boolean Ship::subWorldDraw (AcGiWorldDraw *mode)
{
	assertReadEnabled () ;

	Acad::ErrorStatus es;

	mode->geometry().polyline(m_nBaseline, m_arBaseline.asArrayPtr());
	mode->geometry().polyline(m_nBulwark, m_arBulwark.asArrayPtr());

	AcGePoint3d* pLine = new AcGePoint3d[2];
	for (int i = 0; i < m_nBaseline; i++)
	{
		pLine[0] = m_arBaseline.at(i);
		pLine[1] = m_arBulwark.at(i);
		mode->geometry().polyline(2, pLine);
	}

	pLine[0] = m_ptAft; pLine[1] = m_ptFore;
	mode->geometry().polyline(2, pLine);
	delete[] pLine;

	// �������� �����
	mode->subEntityTraits().setColor(1);
	ACHAR* strStyle = L"Arial";
	ACHAR* pTxt = L"SHIP";
	AcGePoint3d txtPos = AcGePoint3d(m_arBaseline[2]) + m_vecW * 0.7 * m_fHeight;
	double fH = 0.25 * m_fHeight; // ������ ������ (1/4 ������ �����)
	AcGiTextStyle* pTs = new AcGiTextStyle();
	es = fromAcDbTextStyle(*pTs, strStyle);
	int ret;
	if (es == Acad::eOk) ret = pTs->loadStyleRec();

	// ������ ����
	pTs->setTextSize(fH);
	// ������ ������������ ��������������� �� ������
	AcGePoint2d ex = pTs->extents(pTxt, Adesk::kTrue, -1, Adesk::kFalse);
	double fScale = 0.25 * m_fL / ex.x;
	pTs->setXScale(fScale);
	// ��������� ������ pTxt � ����� txtPos
	mode->geometry().text(txtPos, -m_vecV, m_vecU, pTxt, -1, Adesk::kFalse, *pTs);
	txtPos = AcGePoint3d(m_arBaseline[5]) + m_vecW * 0.7 * m_fHeight;
	mode->geometry().text(txtPos, m_vecV, -m_vecU, pTxt, -1, Adesk::kFalse, *pTs);
	delete pTs;

	return Adesk::kTrue; // 

	//------ ������� Adesk::kFalse ���������� ����� subViewportDraw()
	//return (Adesk::kFalse) ;
}

void Ship::subViewportDraw (AcGiViewportDraw *mode)
{
	assertReadEnabled () ;
	AcDbEntity::subViewportDraw (mode) ;
}

Adesk::UInt32 Ship::subViewportDrawLogicalFlags (AcGiViewportDraw *vd)
{
	assertReadEnabled () ;
	return (AcDbEntity::subViewportDrawLogicalFlags (vd)) ;
}

Adesk::UInt32 Ship::subSetAttributes (AcGiDrawableTraits *traits)
{
	assertReadEnabled () ;
	return (AcDbEntity::subSetAttributes (traits)) ;
}

	//- �������� ����� ��������� ��������
Acad::ErrorStatus Ship::subGetOsnapPoints (
	AcDb::OsnapMode osnapMode,
	Adesk::GsMarker gsSelectionMark,
	const AcGePoint3d &pickPoint,
	const AcGePoint3d &lastPoint,
	const AcGeMatrix3d &viewXform,
	AcGePoint3dArray &snapPoints,
	AcDbIntArray &geomIds) const
{
	assertReadEnabled () ;
	return (AcDbEntity::subGetOsnapPoints (osnapMode, gsSelectionMark, pickPoint, lastPoint, viewXform, snapPoints, geomIds)) ;
}

//Acad::ErrorStatus Ship::subGetOsnapPoints (
//	AcDb::OsnapMode osnapMode,
//	Adesk::GsMarker gsSelectionMark,
//	const AcGePoint3d &pickPoint,
//	const AcGePoint3d &lastPoint,
//	const AcGeMatrix3d &viewXform,
//	AcGePoint3dArray &snapPoints,
//	AcDbIntArray &geomIds,
//	const AcGeMatrix3d &insertionMat) const
//{
//	assertReadEnabled () ;
//	return (AcDbEntity::subGetOsnapPoints (osnapMode, gsSelectionMark, pickPoint, lastPoint, viewXform, snapPoints, geomIds, insertionMat)) ;
//}

//- �������� ���������� �����
Acad::ErrorStatus Ship::subGetGripPoints ( AcGePoint3dArray &gripPoints, AcDbIntArray &osnapModes, AcDbIntArray &geomIds) const
{
	assertReadEnabled () ;
	//----- ���� ������� ������ ���������� ������ � ��� ������,
	// ���� ������ ������� subGetGripPoints(), ����������� ����,
	// ������ eNotImplemented (���������� �� ���������)

	gripPoints.append(m_ptAft);
	gripPoints.append(m_ptFore);
	gripPoints.append(m_arBaseline.at(2));
	gripPoints.append(m_arBaseline.at(3));
	gripPoints.append(m_arBulwark.at(2));
	gripPoints.append(m_arBulwark.at(3));
	return Acad::eOk;

	//return (AcDbEntity::subGetGripPoints (gripPoints, osnapModes, geomIds)) ;
}

Acad::ErrorStatus Ship::subMoveGripPointsAt (const AcDbIntArray &indices, const AcGeVector3d &offset)
{
	assertWriteEnabled () ;
	//----- ���� ������� ������ ���������� ������ � ��� ������,
	// ���� ������ ������� subMoveGripPointsAt(), ����������� ����,
	// ������ eNotImplemented (���������� �� ���������)

	return (AcDbEntity::subMoveGripPointsAt (indices, offset)) ;
}

//Acad::ErrorStatus Ship::subGetGripPoints (
//	AcDbGripDataPtrArray &grips, const double curViewUnitSize, const int gripSize, 
//	const AcGeVector3d &curViewDir, const int bitflags
//) const {
//	assertReadEnabled () ;
//
//	//----- If you return eNotImplemented here, that will force AutoCAD to call
//	//----- the older getGripPoints() implementation. The call below may return
//	//----- eNotImplemented depending of your base class.
//	return (AcDbEntity::subGetGripPoints (grips, curViewUnitSize, gripSize, curViewDir, bitflags)) ;
//}
//
//Acad::ErrorStatus Ship::subMoveGripPointsAt (
//	const AcDbVoidPtrArray &gripAppData, const AcGeVector3d &offset,
//	const int bitflags
//)
//{
//	assertWriteEnabled () ;
//
//	//----- If you return eNotImplemented here, that will force AutoCAD to call
//	//----- the older getGripPoints() implementation. The call below may return
//	//----- eNotImplemented depending of your base class.
//	return (AcDbEntity::subMoveGripPointsAt (gripAppData, offset, bitflags)) ;
//}

// ������� ������ (LIST) ��� ������ �������
void Ship::subList() const
{
	assertReadEnabled();
	AcDbEntity::subList();
	acutPrintf(_T("\n� ���\n-----"));
	acutPrintf(_T("\n����� �� �����������: (%.1f, %.1f, %.1f)"), m_ptAft[X], m_ptAft[Y], m_ptAft[Z]);
	acutPrintf(_T("\n����� �� ���������:   (%.1f, %.1f, %.1f)"), m_ptFore[X], m_ptFore[Y], m_ptFore[Z]);
	acutPrintf(_T("\n�����:  %.3f"), m_fL);
	acutPrintf(_T("\n������: %.3f"), 2.0 * m_fHw);
	acutPrintf(_T("\n������: %.3f"), m_fHeight);

	acutPrintf(_T("\n\n� ������� ���\n-------------"));
	struct resbuf UCS, WCS;
	UCS.restype = RTSHORT; UCS.resval.rint = 1;// �������
	WCS.restype = RTSHORT; WCS.resval.rint = 0;
	ads_point temp;
	acedTrans(asDblArray(m_ptAft), &WCS, &UCS, 0, temp);
	acutPrintf(_T("\n����� �� �����������: (%.1f, %.1f, %.1f)"), temp[X], temp[Y], temp[Z]);
	acedTrans(asDblArray(m_ptFore), &WCS, &UCS, 0, temp);
	acutPrintf(_T("\n����� �� ���������:   (%.1f, %.1f, %.1f)\n"), temp[X], temp[Y], temp[Z]);
	acutPrintf(_T("\n�������� ����� �� �����:"));
	for (int i = 0; i < m_nBaseline; i++)
	{
		acedTrans(asDblArray(m_arBaseline.at(i)), &WCS, &UCS, 0, temp);
		acutPrintf(_T("\n ����� %d:  (%.1f, %.1f, %.1f)"), i, temp[X], temp[Y], temp[Z]);
	}
	acutPrintf(_T("\n�������� ����� �� ����������:"));
	for (int i = 0; i < m_nBulwark; i++)
	{
		acedTrans(asDblArray(m_arBulwark.at(i)), &WCS, &UCS, 0, temp);
		acutPrintf(_T("\n ����� %d:  (%.1f, %.1f, %.1f)"), i, temp[X], temp[Y], temp[Z]);
	}
	acutPrintf(_T("\n"));
}

// ����� ��������� �������������� � ������� �������
Acad::ErrorStatus Ship::subTransformBy(const AcGeMatrix3d& xform)
{
	assertWriteEnabled();
	double oldL = m_fL;
	m_ptAft.transformBy(xform);
	m_ptFore.transformBy(xform);
	m_vecU.transformBy(xform); m_vecU.normalize();
	m_vecV.transformBy(xform); m_vecV.normalize();
	// ����� ������� ������ m_vecV ��������� �� ������ ����, ��� �������� � ���������� �������
	// ���������� ��������� ��������� ������������
	if ((m_vecU.crossProduct(m_vecV)).z < 0.0) m_vecV = -m_vecV;
	m_vecW = AcGeVector3d(0.0, 0.0, 1.0);
	m_fL = m_ptAft.distanceTo(m_ptFore);
	double k = m_fL / oldL; // �-� ���������������
	m_fHw *= k; m_fHeight *= k;
	// ����� �����
	storePoints();
	return Acad::eOk;
}

// �����������
Acad::ErrorStatus Ship::subExplode(AcDbVoidPtrArray& entitySet) const
{
	assertReadEnabled();

	AcDbLine* line;
	// ������� �����
	for (int i = 0; i < 8; i++)
	{   // �������������� ������� ������������� �������
		line = new AcDbLine();
		line->setStartPoint(m_arBaseline.at(i));
		line->setEndPoint(m_arBaseline.at(i + 1));
		// ����������� ������ ������� (����� ���������, ����� ������ AutoCAD)
		line->setNormal(m_vecW);// ������� �� ��� Z (����� � ������ �������)
		entitySet.append(line); // ���������� � ����� ����� ����������
	}
	// ������������ �������
	for (int i = 0; i < 8; i++)
	{   // ������������ ������� ������������� �������
		line = new AcDbLine();
		line->setStartPoint(m_arBaseline.at(i));
		line->setEndPoint(m_arBulwark.at(i));
		// ����������� ������ �������
		line->setNormal(m_vecW);
		entitySet.append(line); // ���������� � ����� ����� ����������
	}
	// ������ �����
	for (int i = 0; i < 8; i++)
	{   // �������������� ������� ������������� �������
		line = new AcDbLine();
		line->setStartPoint(m_arBulwark.at(i));
		line->setEndPoint(m_arBulwark.at(i + 1));
		// ����������� ������ �������
		line->setNormal(m_vecW);
		entitySet.append(line); // ���������� � ����� ����� ����������
	}

	return Acad::eOk;
}

// ���������� �������� ����� ����� ���������
void Ship::storePoints()
{
	m_fL = m_ptAft.distanceTo(m_ptFore);
	m_vecU = m_ptFore.asVector() - m_ptAft.asVector(); m_vecU.normalize();
	m_vecV = AcGeVector3d(-m_vecU.y, m_vecU.x, 0.0); m_vecV.normalize();
	m_vecW = AcGeVector3d(0.0, 0.0, 1.0);

	// ��� � ���
	if (m_arBaseline.length() > 0) m_arBaseline.removeAll();
	m_arBaseline.append(m_ptAft);//0
	m_arBaseline.append(m_ptAft - m_vecV * m_fHw * 0.5);//1
	m_arBaseline.append(m_arBaseline.at(1) + m_vecU * m_fL * 0.25 - m_vecV * m_fHw * 0.5);//2
	m_arBaseline.append(m_arBaseline.at(2) + m_vecU * m_fL * 0.25);//3
	m_arBaseline.append(m_ptFore);//4
	m_arBaseline.append(m_ptFore - m_vecU * m_fL * 0.5 + m_vecV * m_fHw);//5

	m_arBaseline.append(m_arBaseline.at(5) - m_vecU * m_fL * 0.25);//6
	m_arBaseline.append(m_ptAft + m_vecV * m_fHw * 0.5);//7
	m_arBaseline.append(m_ptAft);//8

	if (m_arBulwark.length() > 0) m_arBulwark.removeAll();
	for (int i = 0; i < 9; i++)
	{
		if (i == 0 || i == 1 || i == 7 || i == 8)
			m_arBulwark.append(m_arBaseline.at(i) + m_vecW * m_fHeight - m_vecU * 0.25 * m_fHeight);// 0 1 7 8
		else
			if (i == 4) m_arBulwark.append(m_arBaseline.at(i) + m_vecW * 1.5 * m_fHeight + m_vecU * 1.5 * m_fHeight);//4
			else m_arBulwark.append(m_arBaseline.at(i) + m_vecW * m_fHeight);// 2 3 5 6
	}

	m_nBaseline = m_arBaseline.length();
	m_nBulwark = m_arBulwark.length();
}
