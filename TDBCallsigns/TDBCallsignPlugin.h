// CCDS-R PlugIn © 2024 by Joshua Seagrave is licensed under CC BY-NC-SA 4.0. To view a copy of this license, visit https://creativecommons.org/licenses/by-nc-sa/4.0/
#include "StdAfx.h"
#pragma once

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

