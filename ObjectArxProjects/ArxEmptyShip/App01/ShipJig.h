#ifndef SHIP_JIG_H
#define SHIP_JIG_H //#endif

#include "Stdafx.h"
#include "Ship.h"

class ShipJig : public AcEdJig // 2.5 AcEdJig 
{
public:
    ShipJig(AcGePoint3d&, AcGePoint3d&);

private:  // данные класса
	AcGePoint3d  m_pt0;
	AcGePoint3d  m_pt1;
	double m_hw;
	double	m_h;
    int mPromptCounter;  // счетчик запросов (0 или 1)
    Ship*  m_pShipObj;

public:
    AcDbObjectId  doIt(); // 2.6 Jig
    virtual DragStatus  sampler();
    virtual Adesk::Boolean  update();
    virtual AcDbEntity*  entity() const;
};

#endif
