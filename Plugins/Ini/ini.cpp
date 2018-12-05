//uff which should i include? which one can be deleted? more research is needed!
#include "Ini.hpp"

#include "API/Version.hpp"
#include "API/CAppManager.hpp"
#include "API/CExoString.hpp"
#include "API/CNWSClient.hpp"

#include "API/Constants.hpp"
#include "API/CServerExoApp.hpp"

#include "API/Functions.hpp"
#include "API/Globals.hpp"

#include "Services/Config/Config.hpp"
#include "Services/Hooks/Hooks.hpp"

#include "ViewPtr.hpp"
#include "nwnxlite.h"
#include "mysql.h"
#include "string.h"
#include "assert.h"
#include "string.h"

using namespace NWNXLib;
using namespace NWNXLib::API;

NWNX_PLUGIN_ENTRY Plugin::Info* PluginInfo()
{
    return new Plugin::Info
    {
        "Ini",
        "Trying to get users to read/write Ini-Files with NWScript binding.",
        1,
        false
    };
}

NWNX_PLUGIN_ENTRY Plugin* PluginLoad(Plugin::CreateParams params)
{
    g_plugin = new Ini::Ini(params);
    return g_plugin;
}

//copied from old c++ source as first test?!
int CIniReader::ReadInteger(char* sSection, char* sKey, int iDefaultValue)
{
    int iResult = GetPrivateProfileInt(sSection,  sKey, iDefaultValue, m_sFileName); 
    return iResult;
}
