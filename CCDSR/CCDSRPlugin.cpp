//CCDS-R PlugIn © 2024 by Joshua Seagrave is licensed under CC BY-NC-SA 4.0. To view a copy of this license, visit https://creativecommons.org/licenses/by-nc-sa/4.0/
#include "StdAfx.h"
#include "CCDSRPlugin.h"

const int TAG_ITEM_CCDSR_CALLSIGN = 1; // ID for the CALLSIGN/SQUAWK tag item.
const int TAG_ITEM_CCDSR_LABEL = 2;    // ID for the LABEL item.

CCDSRPlugIn* pMyPlugIn = NULL;

Json::Value root = NULL;
Json::Value labels = NULL;
Json::Value callsigns = NULL; // initialization of variables, hopefully to be overwritten later, so we can check for thruthiness.

static bool isValidData(Json::Value _value)
{
    for (auto& el : _value) // iterate through every value in the JSON object.
    {
        if (el.asString().length() > 7 || el.asString().length() == 0) //CCDS labels and callsigns cannot exceed 7 characters and must have at least one character.
        {
            return false;
        }
    };
    
    return true;
}

CCDSRPlugIn::CCDSRPlugIn(void)
    : CPlugIn(EuroScopePlugIn::COMPATIBILITY_CODE,
        "CCDS-R Plugin",
        "1.0.0",
        "Joshua Seagrave",
        "CC BY-NC-SA 4.0")
{

    RegisterTagItemType("CCDS-R Callsign/Squawk", TAG_ITEM_CCDSR_CALLSIGN); // registering tag items and names in ES.
    RegisterTagItemType("CCDS-R Label", TAG_ITEM_CCDSR_LABEL);

    std::string filePath = "UK/Data/Plugin/CCDS-R/Settings/conversions.json"; // local path to the CCDS-R config file.

    std::ifstream conversionsFile(filePath, std::ifstream::binary); // opens a filestream to read the JSON file.

    if (!conversionsFile) // Have we failed to find the file?
    {
        pMyPlugIn->DisplayUserMessage( // send a message to the user notifying them of the problem.
            "CCDS-R",
            "",
            ("Error finding " + filePath + ". Custom Code-callsign conversions and labels will be non-functional.").c_str(),
            true,
            true,
            true,
            true,
            false
        );

        return; // done.
    }

    try
    {
        conversionsFile >> root; // parse JSON from file to a root object. will raise a Json::Exception if the JSON object is invalid.
    }

    catch (Json::Exception ) // catch the exception and send a message to the user notifying them of the problem.
    {
        pMyPlugIn->DisplayUserMessage(
            "CCDS-R",
            "",
            "Invalid JSON found. Custom Code-callsign conversions and labels will be non-functional.",
            true,
            true,
            false,
            false,
            false);

        return; // done.
    }

    if (!isValidData(root["labels"]) || !isValidData(root["callsigns"])) // are any of the CCDS-R configs in the JSON object invalid?
    {
        pMyPlugIn->DisplayUserMessage( // send a message to the user notifying them of the problem.
            "CCDS-R",
            "",
            "Invalid data found in the JSON file. Custom Code-callsign conversions and labels will be non-functional.",
            true,
            true,
            true,
            true,
            false
        );

        return; // done.
    };

    labels = root["labels"];
    callsigns = root["callsigns"];  // we've successfully validated everything, so we can overwrite these variables now.
                                    // if at any stage this has failed, these will remain NULL
                                    // and we will test for that eventuality down the line.

    pMyPlugIn->DisplayUserMessage(
        "CCDS-R",
        "",
        "CCDS-R plugin loaded successfully!",
        true,
        true,
        false,
        false,
        false
    );    
}

void CCDSRPlugIn::OnGetTagItem(           // this function gets called for every aircraft every single time the position updates.
    EuroScopePlugIn::CFlightPlan _plan,         // it needs to be fairly quick.
    EuroScopePlugIn::CRadarTarget _target,
    int _itemCode,
    int _tagData,
    char _itemString[16],
    int* _pColorCode,
    COLORREF* _pRGB, 
    double* _pFontSize)
{

    std::string squawk = _target.GetPosition().GetSquawk(); // so we can test it against our list.

    switch (_itemCode) // so we know which item is being queried.
    {
        case TAG_ITEM_CCDSR_LABEL:

            *_pColorCode = EuroScopePlugIn::TAG_COLOR_DEFAULT;

            // squawk found in JSON list of specials?
            if (labels && labels.isMember(squawk)) 
            {
                // display the correlated CCDS-R label.
                snprintf(_itemString, 16, "%s", labels[squawk].asCString());
                return; // done.
            }

            return; // done.

        case TAG_ITEM_CCDSR_CALLSIGN:

            // is the target correlated to a flight plan?
            if (_tagData == EuroScopePlugIn::TAG_DATA_CORRELATED)
            {
                // if the aircraft is correlated, we want to show the callsign.
                snprintf(_itemString, 16, "%s", _target.GetCallsign());
                return; // done.
            }

            // squawk found in JSON list of specials?
            if (callsigns && callsigns.isMember(squawk)) 
            {
                // display the correlated CCDS-R value.
                snprintf(_itemString, 16, "%s", callsigns[squawk].asCString());
                return; // done.
            }

            // if the aircraft is not correlated, we want to show the squawk.
            snprintf(_itemString, 16, "%s", squawk.c_str());
            return; // done.
    }

    return; // done.
}

void __declspec (dllexport)
EuroScopePlugInInit(EuroScopePlugIn::CPlugIn** ppPlugInInstance)
{
    *ppPlugInInstance = pMyPlugIn = new CCDSRPlugIn;
}

void __declspec (dllexport)
EuroScopePlugInExit(void)
{
    delete pMyPlugIn;
}
