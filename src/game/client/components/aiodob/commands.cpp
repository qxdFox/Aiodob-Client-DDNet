
#include <engine/console.h>

#include <game/client/gameclient.h>

#include <base/system.h>

#include "aiodob.h"
#include "../../../../engine/shared/config.h"

void CAiodob::ConVotekick(IConsole::IResult *pResult, void *pUserData)
{
	CAiodob *pSelf = (CAiodob *)pUserData;
	pSelf->Votekick(pResult->GetString(0), pResult->NumArguments() > 1 ? pResult->GetString(1) : "");
}

void CAiodob::ConServerRainbowSpeed(IConsole::IResult *pResult, void *pUserData)
{
	CAiodob *pSelf = (CAiodob *)pUserData;
	
	char aBuf[8];
	str_format(aBuf, sizeof(aBuf), "%d", pSelf->m_RainbowSpeed);

	if(pResult->NumArguments() > 0)
		pSelf->m_RainbowSpeed = pResult->GetInteger(0);
	else
		pSelf->GameClient()->aMessage(aBuf);
}

void CAiodob::ConServerRainbowSaturation(IConsole::IResult *pResult, void *pUserData)
{
	CAiodob *pSelf = (CAiodob *)pUserData;

	char aBuf[8];
	str_format(aBuf, sizeof(aBuf), "%d", pSelf->m_Saturation);

	if(pResult->NumArguments() > 0)
		pSelf->m_Saturation= pResult->GetInteger(0);
	else
		pSelf->GameClient()->aMessage(aBuf);
}

void CAiodob::ConServerRainbowLightness(IConsole::IResult *pResult, void *pUserData)
{
	CAiodob *pSelf = (CAiodob *)pUserData;

	char aBuf[8];
	str_format(aBuf, sizeof(aBuf), "%d", pSelf->m_Lightness);

	if(pResult->NumArguments() > 0)
		pSelf->m_Lightness = pResult->GetInteger(0);
	else
		pSelf->GameClient()->aMessage(aBuf);
}

void CAiodob::Votekick(const char *pName, char *pReason)
{
	int ClientId;
	char Id[8];

	for(ClientId = 0; ClientId < MAX_CLIENTS; ClientId++)
	{
		if(str_comp(pName, GameClient()->m_aClients[ClientId].m_aName) == 0)
		{
			str_format(Id, sizeof(Id), "%d", ClientId);
			GameClient()->m_Voting.Callvote("kick", Id, pReason);
			return;
		}
	}
	if(ClientId == MAX_CLIENTS)
	{
		GameClient()->aMessage("No player with this name found.");
		return;
	}
}

void CAiodob::ConTempWar(IConsole::IResult *pResult, void *pUserData)
{
	CAiodob *pSelf = (CAiodob *)pUserData;
	pSelf->TempWar(pResult->GetString(0), pResult->NumArguments() > 1 ? pResult->GetString(1) : "");
}
void CAiodob::ConUnTempWar(IConsole::IResult *pResult, void *pUserData)
{
	CAiodob *pSelf = (CAiodob *)pUserData;
	pSelf->UnTempWar(pResult->GetString(0), pResult->NumArguments() > 1 ? pResult->GetString(1) : "");
}

void CAiodob::ConTempHelper(IConsole::IResult *pResult, void *pUserData)
{
	CAiodob *pSelf = (CAiodob *)pUserData;
	pSelf->TempHelper(pResult->GetString(0), pResult->NumArguments() > 1 ? pResult->GetString(1) : "");
}
void CAiodob::ConUnTempHelper(IConsole::IResult *pResult, void *pUserData)
{
	CAiodob *pSelf = (CAiodob *)pUserData;
	pSelf->UnTempHelper(pResult->GetString(0), pResult->NumArguments() > 1 ? pResult->GetString(1) : "");
}

void CAiodob::ConTempMute(IConsole::IResult *pResult, void *pUserData)
{
	CAiodob *pSelf = (CAiodob *)pUserData;
	pSelf->TempMute(pResult->GetString(0), pResult->NumArguments() > 1 ? pResult->GetString(1) : "");
}
void CAiodob::ConUnTempMute(IConsole::IResult *pResult, void *pUserData)
{
	CAiodob *pSelf = (CAiodob *)pUserData;
	pSelf->UnTempMute(pResult->GetString(0), pResult->NumArguments() > 1 ? pResult->GetString(1) : "");
}

void CAiodob::ConSaveSkin(IConsole::IResult *pResult, void *pUserData)
{
	CAiodob *pSelf = (CAiodob *)pUserData;
	pSelf->SaveSkin();
}
void CAiodob::ConRestoreSkin(IConsole::IResult *pResult, void *pUserData)
{
	CAiodob *pSelf = (CAiodob *)pUserData;
	pSelf->RestoreSkin();
}

void CAiodob::TempWar(const char *pName, char *pReason)
{
	CTempEntry Entry(pName, "", "");
	str_copy(Entry.m_aTempWar, pName);

	char aBuf[128];
	str_format(aBuf, sizeof(aBuf), "Added \"%s\" to the Temp War List", pName);
	GameClient()->aMessage(aBuf);

	m_TempEntries.push_back(Entry);

}

void CAiodob::UnTempWar(const char *pName, char *pReason)
{
	if(str_comp(pName, "") == 0)
		return;

	char aBuf[128];
	str_format(aBuf, sizeof(aBuf), "couldn't find \"%s\" on the Temp War List", pName);
	CTempEntry Entry("", "", pName);

	auto it = std::find(m_TempEntries.begin(), m_TempEntries.end(), Entry);
	if(it != m_TempEntries.end())
	{
		for(CTempEntry &Entries : m_TempEntries)
		{
			for(auto it = m_TempEntries.begin(); it != m_TempEntries.end();)
			{
				bool IsDuplicate = !str_comp(it->m_aTempWar, pName);

				if(IsDuplicate)
					it = m_TempEntries.erase(it);
				else
					++it;

				if(!str_comp(Entries.m_aTempWar, pName))
					str_format(aBuf, sizeof(aBuf), "Removed \"%s\" from the Temp War List", pName);
			}
		}
	}
	GameClient()->aMessage(aBuf);
}

void CAiodob::TempHelper(const char *pName, char *pReason)
{
	CTempEntry Entry("", pName, "");
	str_copy(Entry.m_aTempHelper, pName);

	char aBuf[128];
	str_format(aBuf, sizeof(aBuf), "Added \"%s\" to the Temp Helper List", pName);
	GameClient()->aMessage(aBuf);
	m_TempEntries.push_back(Entry);
}

void CAiodob::UnTempHelper(const char *pName, char *pReason)
{
	if(str_comp(pName, "") == 0)
		return;

	char aBuf[128];
	str_format(aBuf, sizeof(aBuf), "couldn't find \"%s\" on the Temp Helper List", pName);
	CTempEntry Entry("", "", pName);

	auto it = std::find(m_TempEntries.begin(), m_TempEntries.end(), Entry);
	if(it != m_TempEntries.end())
	{
		for(CTempEntry &Entries : m_TempEntries)
		{
			for(auto it = m_TempEntries.begin(); it != m_TempEntries.end();)
			{
				bool IsDuplicate = !str_comp(it->m_aTempHelper, pName);

				if(IsDuplicate)
					it = m_TempEntries.erase(it);
				else
					++it;

				if(!str_comp(Entries.m_aTempHelper, pName))
					str_format(aBuf, sizeof(aBuf), "Removed \"%s\" from the Temp Helper List", pName);
			}
		}
	}
	GameClient()->aMessage(aBuf);
}

void CAiodob::TempMute(const char *pName, char *pReason)
{
	CTempEntry Entry("", "", pName);
	str_copy(Entry.m_aTempMute, pName);

	char aBuf[128];
	str_format(aBuf, sizeof(aBuf), "Added \"%s\" to the Temp Mute List", pName);
	GameClient()->aMessage(aBuf);
	m_TempEntries.push_back(Entry);
}

void CAiodob::UnTempMute(const char *pName, char *pReason)
{
	if(str_comp(pName, "") == 0)
		return;

	char aBuf[128];
	str_format(aBuf, sizeof(aBuf), "couldn't find \"%s\" on the Temp Mute List", pName);
	CTempEntry Entry("", "", pName);

	auto it = std::find(m_TempEntries.begin(), m_TempEntries.end(), Entry);
	if(it != m_TempEntries.end())
	{
		for(CTempEntry &Entries : m_TempEntries)
		{
			for(auto it = m_TempEntries.begin(); it != m_TempEntries.end();)
			{
				bool IsDuplicate = !str_comp(it->m_aTempMute, pName);

				if(IsDuplicate)
					it = m_TempEntries.erase(it);
				else
					++it;

				if(!str_comp(Entries.m_aTempMute, pName))
					str_format(aBuf, sizeof(aBuf), "Removed \"%s\" from the Temp Mute List", pName);
			}
		}
	}
	GameClient()->aMessage(aBuf);
}

void CAiodob::RestoreSkin()
{
	if(!g_Config.m_ClServerRainbow)
	{
		if(g_Config.m_ClDummy)
		{
			str_copy(g_Config.m_ClDummySkin, g_Config.m_ClSavedDummySkin, sizeof(g_Config.m_ClDummySkin));
			str_copy(g_Config.m_ClDummyName, g_Config.m_ClSavedDummyName, sizeof(g_Config.m_ClDummyName));
			str_copy(g_Config.m_ClDummyClan, g_Config.m_ClSavedDummyClan, sizeof(g_Config.m_ClDummyClan));
			g_Config.m_ClDummyCountry = g_Config.m_ClSavedDummyCountry;
			g_Config.m_ClDummyUseCustomColor = g_Config.m_ClSavedDummyUseCustomColor;
			g_Config.m_ClDummyColorBody = g_Config.m_ClSavedDummyColorBody;
			g_Config.m_ClDummyColorFeet = g_Config.m_ClSavedDummyColorFeet;
			GameClient()->aMessage("Restored Dummy Skin");
			m_pClient->SendDummyInfo(false);
		}
		else
		{
			str_copy(g_Config.m_ClPlayerSkin, g_Config.m_ClSavedPlayerSkin, sizeof(g_Config.m_ClPlayerSkin));
			str_copy(g_Config.m_PlayerName, g_Config.m_ClSavedName, sizeof(g_Config.m_PlayerName));
			str_copy(g_Config.m_PlayerClan, g_Config.m_ClSavedClan, sizeof(g_Config.m_PlayerClan));
			g_Config.m_PlayerCountry = g_Config.m_ClSavedCountry;
			g_Config.m_ClPlayerUseCustomColor = g_Config.m_ClSavedPlayerUseCustomColor;
			g_Config.m_ClPlayerColorBody = g_Config.m_ClSavedPlayerColorBody;
			g_Config.m_ClPlayerColorFeet = g_Config.m_ClSavedPlayerColorFeet;
			GameClient()->aMessage("Restored Main Skin");
			m_pClient->SendInfo(false);
		}
	}
	else
		GameClient()->aMessage("Can't Restore! Rainbow mode is enabled.");
	
}

void CAiodob::SaveSkin()
{
	if(!g_Config.m_ClServerRainbow)
	{
		if(g_Config.m_ClDummy)
		{
			str_copy(g_Config.m_ClSavedDummySkin, g_Config.m_ClDummySkin, sizeof(g_Config.m_ClSavedDummySkin));
			str_copy(g_Config.m_ClSavedDummyName, g_Config.m_ClDummyName, sizeof(g_Config.m_ClSavedDummyName));
			str_copy(g_Config.m_ClSavedDummyClan, g_Config.m_ClDummyClan, sizeof(g_Config.m_ClSavedDummyClan));
			g_Config.m_ClSavedDummyCountry = g_Config.m_ClDummyCountry;
			g_Config.m_ClSavedDummyUseCustomColor = g_Config.m_ClDummyUseCustomColor;
			g_Config.m_ClSavedDummyColorBody = g_Config.m_ClDummyColorBody;
			g_Config.m_ClSavedDummyColorFeet = g_Config.m_ClDummyColorFeet;
			GameClient()->aMessage("Saved Dummy Skin");
			m_pClient->SendDummyInfo(false);
		}
		else
		{
			str_copy(g_Config.m_ClSavedPlayerSkin, g_Config.m_ClPlayerSkin, sizeof(g_Config.m_ClSavedPlayerSkin));
			str_copy(g_Config.m_ClSavedName, g_Config.m_PlayerName, sizeof(g_Config.m_ClSavedName));
			str_copy(g_Config.m_ClSavedClan, g_Config.m_PlayerClan, sizeof(g_Config.m_ClSavedClan));
			g_Config.m_ClSavedCountry = g_Config.m_PlayerCountry;
			g_Config.m_ClSavedPlayerUseCustomColor = g_Config.m_ClPlayerUseCustomColor;
			g_Config.m_ClSavedPlayerColorBody = g_Config.m_ClPlayerColorBody;
			g_Config.m_ClSavedPlayerColorFeet = g_Config.m_ClPlayerColorFeet;
			GameClient()->aMessage("Saved Main Skin");
			m_pClient->SendInfo(false);
		}
	}
	else GameClient()->aMessage("Can't Save! Rainbow mode is enabled.");
}

void CAiodob::OnConsoleInit()
{
	Console()->Register("votekick", "s[name] ?r[reason]", CFGFLAG_CLIENT, ConVotekick, this, "Call a votekick");

	Console()->Register("addtempwar", "s[name] ?r[reason]", CFGFLAG_CLIENT, ConTempWar, this, "temporary War");
	Console()->Register("deltempwar", "s[name]", CFGFLAG_CLIENT, ConUnTempWar, this, "remove temporary War");

	Console()->Register("addtemphelper", "s[name] ?r[reason]", CFGFLAG_CLIENT, ConTempHelper, this, "temporary Helper");
	Console()->Register("deltemphelper", "s[name]", CFGFLAG_CLIENT, ConUnTempHelper, this, "remove temporary Helper");

	Console()->Register("addtempmute", "s[name] ?r[reason]", CFGFLAG_CLIENT, ConTempMute, this, "temporary Mute");
	Console()->Register("deltempmute", "s[name]", CFGFLAG_CLIENT, ConUnTempMute, this, "remove temporary Mute");

	Console()->Register("restoreskin", "", CFGFLAG_CLIENT, ConRestoreSkin, this, "Save Your Current Info (Skin, name, etc.)");
	Console()->Register("saveskin", "", CFGFLAG_CLIENT, ConSaveSkin, this, "Restore Your Saved Info");

	Console()->Register("server_rainbow_speed", "?s[speed]", CFGFLAG_CLIENT, ConServerRainbowSpeed, this, "Rainbow Speed of Server side rainbow mode (default = 10)");
	Console()->Register("server_rainbow_sat", "?s[Sat]", CFGFLAG_CLIENT, ConServerRainbowSaturation, this, "Rainbow Saturation of Server side rainbow mode (default = 10)");
	Console()->Register("server_rainbow_lht", "?s[Lht]", CFGFLAG_CLIENT, ConServerRainbowLightness, this, "Rainbow Lightness of Server side rainbow mode (default = 10)");
}

// Stuff to Fix Later
/*
void OnlineInfo()
{
	char aBuf[512];
	char active[512];
	int NumberWars = 0;
	int NumberWarsAfk = 0;
	for(auto &Client : GameClient()->m_aClients)
	{
		bool War = GameClient()->m_WarList.IsAnyWar(Client.m_aName, Client.m_aClan);
		if(!Client.m_Active)
			continue;
		if(!GameClient()->m_WarList.IsHelperlist(Client.m_aName) && !GameClient()->m_WarList.IsTeamlist(Client.m_aName) && !GameClient()->m_WarList.IsClanTeamlist(Client.m_aClan))
			if(War)
				NumberWars++;
		if(Client.m_Afk && War)
			NumberWarsAfk++;
	}
	int NumberTeams = 0;
	int NumberTeamsAfk = 0;
	for(auto &Client : GameClient()->m_aClients)
	{
		bool Team = GameClient()->m_WarList.IsAnyTeam(Client.m_aName, Client.m_aClan);
		if(!Client.m_Active)
			continue;
		if(!GameClient()->m_WarList.IsHelperlist(Client.m_aName) && !GameClient()->m_WarList.IsWarlist(Client.m_aName) && !GameClient()->m_WarList.IsTempWarlist(Client.m_aName) && !GameClient()->m_WarList.IsClanWarlist(Client.m_aClan))
			if(Team)
				NumberTeams++;
		if(Client.m_Afk && Team)
			NumberTeamsAfk++;
	}
	int NumberHelpers = 0;
	int NumberHelpersAfk = 0;
	for(auto &Client : GameClient()->m_aClients)
	{
		if(!Client.m_Active)
			continue;
		if(!GameClient()->m_WarList.IsHelperlist(Client.m_aName))
			continue;
		NumberHelpers++;
		if(Client.m_Afk)
			NumberHelpersAfk++;
	}
	int NumberMutes = 0;
	int NumberMutesAfk = 0;
	for(auto &Client : GameClient()->m_aClients)
	{
		if(!Client.m_Active)
			continue;
		if(!GameClient()->m_WarList.IsMutelist(Client.m_aName))
			continue;
		NumberMutes++;
		if(Client.m_Afk)
			NumberMutes++;
	}
	str_format(aBuf, sizeof(aBuf), "[online] %d Teams | %d Wars | %d Helpers | %d Mutes", NumberTeams, NumberWars, NumberHelpers, NumberMutes);
	str_format(active, sizeof(active), "[active] %d Teams | %d Wars | %d Helpers | %d Mutes", NumberTeams - NumberTeamsAfk, NumberWars - NumberWarsAfk, NumberHelpers - NumberHelpersAfk, NumberMutes - NumberMutesAfk);
	m_pClient->m_Chat.AddLine(-3, 0, aBuf);
	m_pClient->m_Chat.AddLine(-3, 0, active);
}*/