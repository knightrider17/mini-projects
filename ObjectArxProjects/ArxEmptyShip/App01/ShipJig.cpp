#include "StdAfx.h"
#include "ShipJig.h"

ShipJig::ShipJig(AcGePoint3d& pt0, AcGePoint3d& pt1) : AcEdJig()
{
	m_pt0 = pt0; m_pt1 = pt1;
	m_hw = 0.0; m_h = 0.0;
	mPromptCounter = 0;
	m_pShipObj = NULL;
}

AcDbEntity* ShipJig::entity() const
{
	return m_pShipObj;
}

Adesk::Boolean ShipJig::update()
{ // ������������� ������� ��� ������� �������� ����� (dragging)
	switch (mPromptCounter)
	{
	case 0: // ������ ����� (������ 0)
		m_pShipObj->m_fHw = m_hw;
		m_pShipObj->m_fHeight = 0.0;
		m_pShipObj->storePoints();
		break;
	case 1: // ������ ������� (������ > 0)
		m_pShipObj->m_fHeight = m_h; // ������� acquireDist
		m_pShipObj->storePoints();
		break;
	}
	return Adesk::kTrue;
}

AcEdJig::DragStatus ShipJig::sampler()
{
	DragStatus stat;
	setUserInputControls((UserInputControls)
		(AcEdJig::kAccept3dCoordinates));
	// ����� ��� ���������� ��������� �-�� Z �������-��

	if (mPromptCounter == 0)
	{
		// �������� ������ ���������� �����
		static double hwidth;
		stat = acquireDist(m_hw, m_pt1);
		// ���� ��������� m_hw
		if (hwidth != m_hw)  hwidth = m_hw;
		else if (stat == AcEdJig::kNormal)
			return AcEdJig::kNoChange;
	}
	else if (mPromptCounter == 1)
	{ // �������� ������ ������ �������
		static double height;
		stat = acquireDist(m_h, m_pt1);
		// ���� ��������� m_h
		if (height != m_h)  height = m_h;
		else if (stat == AcEdJig::kNormal)
			return AcEdJig::kNoChange;
	}
	return stat;
}

AcDbObjectId ShipJig::doIt()
{
	AcDbObjectId id = NULL; // ������� NULL (��� �������)
	m_pShipObj = new Ship();// ������ � ��������� �� ���������
	m_pShipObj->m_ptAft = m_pt0;
	m_pShipObj->m_ptFore = m_pt1;
	m_pShipObj->m_fL = m_pt0.distanceTo(m_pt1);
	m_pShipObj->m_vecU = m_pt1.asVector() - m_pt0.asVector();
	m_pShipObj->m_vecU.normalize();
	m_pShipObj->m_vecV = AcGeVector3d(-(m_pShipObj->m_vecU).y, (m_pShipObj->m_vecU).x, 0.0);
	m_pShipObj->m_vecW = AcGeVector3d(0.0, 0.0, 1.0);

	setDispPrompt(L"\n����������, ��: ");
	AcEdJig::DragStatus stat = drag();// �������� sampler

									  // ���� ������ ������� Esc - ����� ������
	if (stat == AcEdJig::kCancel)// <Esc>
	{
		acutPrintf(L"���������� �� ������. ");
		delete m_pShipObj; m_pShipObj = NULL;
		return id;
	}

	mPromptCounter++;// � ���������� �������
	setDispPrompt(L"\n������, ��: ");
	stat = drag(); // ��� ��� sampler � mPromptCounter == 1
				   // ���� ������ ������� Esc - ����� ������
	if (stat == AcEdJig::kCancel)// <Esc>
	{
		acutPrintf(L"������ �� ������. ");
		delete m_pShipObj; m_pShipObj = NULL;
		return id;
	}

	id = append(); // ����� AcEdJig::append
	return id; // ���������� ObjectId ������������ � ������ �������
}
