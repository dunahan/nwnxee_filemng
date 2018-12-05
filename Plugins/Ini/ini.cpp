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

namespace Ini {

Player::Player(const Plugin::CreateParams& params)
    : Plugin(params)
{
// okay, like most plugins it seems to be good, if i register the (one) function(s) here first? but how exactly?
#define REGISTER(func) \
    GetServices()->m_events->RegisterEvent(#func, std::bind(&Ini::func, this, std::placeholders::_1))

    REGISTER(ReadInteger);

#undef REGISTER

//how do i get here around?
/*    GetServices()->m_hooks->RequestSharedHook
        <Functions::CNWSMessage__HandlePlayerToServerInputCancelGuiTimingEvent,
            int32_t, CNWSMessage*, CNWSPlayer*>(&HandlePlayerToServerInputCancelGuiTimingEventHook);
// do i need that? */
}

/*copied from old c++ source as help?! old style, how to get that work with new nwnx:ee
int CIniReader::ReadInteger(char* sSection, char* sKey, int iDefaultValue)
{
    int iResult = GetPrivateProfileInt(sSection,  sKey, iDefaultValue, m_sFileName); //okay, this is a definied  c++ func
    return iResult;
}*/
    
/* // a examle from another registered function of player plugin? how helpful could it get, for getting a integer?
ArgumentStack Player::ForcePlaceableExamineWindow(ArgumentStack&& args)
{
    ArgumentStack stack;
    if (auto *pPlayer = player(args))
    {
        const auto placeableId = Services::Events::ExtractArgument<Types::ObjectID>(args);

        auto *pMessage = static_cast<CNWSMessage*>(Globals::AppManager()->m_pServerExoApp->GetNWSMessage());
        if (pMessage)
        {
            pMessage->SendServerToPlayerExamineGui_PlaceableData(pPlayer, placeableId);
        }
        else
        {
            LOG_ERROR("Unable to get CNWSMessage");
        }
    }

    return stack;
}
//or is this the right way? from plugin damage...
int32_t Damage::OnApplyDamage(NWNXLib::API::CNWSEffectListHandler *pThis, NWNXLib::API::CNWSObject *pObject, NWNXLib::API::CGameEffect *pEffect, bool bLoadingGame)
{
    Damage& plugin = *g_plugin;
    auto posScript = plugin.GetServices()->m_perObjectStorage->Get<std::string>(pObject, "DAMAGE_EVENT_SCRIPT");
    std::string script = posScript ? *posScript : plugin.m_DamageScript;

    if (!script.empty())
    {
        // We only run the OnDamage event for creatures.
        if (Utils::AsNWSCreature(pObject))
        {
            // Prepare the data for the nwscript
            plugin.m_DamageData.oidDamager = pEffect->m_oidCreator;

            std::memcpy(plugin.m_DamageData.vDamage, pEffect->m_nParamInteger, sizeof(plugin.m_DamageData.vDamage));
            Utils::ExecuteScript(script, pObject->m_idSelf);
            std::memcpy(pEffect->m_nParamInteger, plugin.m_DamageData.vDamage, sizeof(plugin.m_DamageData.vDamage));
        }
    }

    return plugin.m_OnApplyDamageHook->CallOriginal<int32_t>(pThis, pObject, pEffect, bLoadingGame);
}
*/
