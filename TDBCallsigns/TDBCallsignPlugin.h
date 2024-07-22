#pragma once

#include <EuroScopePlugIn.h>
#include <string>
#include <json/json.h>
#include <fstream>

class CCDSRCallsignPlugIn : public EuroScopePlugIn::CPlugIn
{
public:
	CCDSRCallsignPlugIn(void);


	void OnGetTagItem(
		EuroScopePlugIn::CFlightPlan _plan,
		EuroScopePlugIn::CRadarTarget _target,
		int _itemCode,
		int _tagData,
		char _itemString[16],
		int* _pColorCode,
		COLORREF* _pRGB,
		double* _pFontSize
		);
};

