/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */
#include <engine/graphics.h>
#include <engine/shared/config.h>
#include <engine/textrender.h>

#include <game/generated/client_data.h>
#include <game/generated/protocol.h>

#include <game/client/gameclient.h>
#include <game/client/prediction/entities/character.h>

#include "camera.h"
#include "controls.h"
#include "nameplates.h"

void CNamePlate::CNamePlateName::Update(CNamePlates &This, int Id, const char *pName, bool FriendMark, float FontSize)
{
	if(Id == m_Id &&
		str_comp(m_aName, pName) == 0 &&
		m_FriendMark == FriendMark && m_FontSize == FontSize)
		return;
	m_Id = Id;
	str_copy(m_aName, pName);
	m_FriendMark = FriendMark;
	m_FontSize = FontSize;

	// create namePlates at standard zoom
	float ScreenX0, ScreenY0, ScreenX1, ScreenY1;
	This.Graphics()->GetScreen(&ScreenX0, &ScreenY0, &ScreenX1, &ScreenY1);
	This.RenderTools()->MapScreenToInterface(This.m_pClient->m_Camera.m_Center.x, This.m_pClient->m_Camera.m_Center.y);

	CTextCursor Cursor;
	This.TextRender()->SetCursor(&Cursor, 0.0f, 0.0f, FontSize, TEXTFLAG_RENDER);
	This.TextRender()->DeleteTextContainer(m_TextContainerIndex);
	if(m_FriendMark)
	{
		This.TextRender()->TextColor(ColorRGBA(1.0f, 0.0f, 0.0f, 1.0f));
		This.TextRender()->CreateOrAppendTextContainer(m_TextContainerIndex, &Cursor, "♥");
	}
	This.TextRender()->TextColor(ColorRGBA(1.0f, 1.0f, 1.0f, 1.0f));
	char aBuf[16] = "";
	if(Id >= 0 && pName[0] != '\0' && FriendMark)
		str_format(aBuf, sizeof(aBuf), " %d: ", Id);
	else if(Id >= 0 && pName[0] != '\0')
		str_format(aBuf, sizeof(aBuf), "%d: ", Id);
	else if(Id >= 0 && FriendMark)
		str_format(aBuf, sizeof(aBuf), " %d", Id);
	else if(FriendMark && pName[0] != '\0')
		str_copy(aBuf, " ", sizeof(aBuf));
	if(aBuf[0] != '\0')
		This.TextRender()->CreateOrAppendTextContainer(m_TextContainerIndex, &Cursor, aBuf);
	if(pName[0] != '\0')
		This.TextRender()->CreateOrAppendTextContainer(m_TextContainerIndex, &Cursor, pName);

	This.Graphics()->MapScreen(ScreenX0, ScreenY0, ScreenX1, ScreenY1);
}

void CNamePlate::CNamePlateClan::Update(CNamePlates &This, const char *pClan, float FontSize)
{
	if(str_comp(m_aClan, pClan) == 0 &&
		m_FontSize == FontSize)
		return;
	str_copy(m_aClan, pClan);
	m_FontSize = FontSize;

	// create namePlates at standard zoom
	float ScreenX0, ScreenY0, ScreenX1, ScreenY1;
	This.Graphics()->GetScreen(&ScreenX0, &ScreenY0, &ScreenX1, &ScreenY1);
	This.RenderTools()->MapScreenToInterface(This.m_pClient->m_Camera.m_Center.x, This.m_pClient->m_Camera.m_Center.y);

	CTextCursor Cursor;
	This.TextRender()->SetCursor(&Cursor, 0.0f, 0.0f, FontSize, TEXTFLAG_RENDER);
	This.TextRender()->RecreateTextContainer(m_TextContainerIndex, &Cursor, m_aClan);

	This.Graphics()->MapScreen(ScreenX0, ScreenY0, ScreenX1, ScreenY1);
}

void CNamePlate::CNamePlateHookWeakStrongId::Update(CNamePlates &This, int Id, float FontSize)
{
	if(Id == m_Id && m_FontSize == FontSize)
		return;
	m_Id = Id;
	m_FontSize = FontSize;

	// create namePlates at standard zoom
	float ScreenX0, ScreenY0, ScreenX1, ScreenY1;
	This.Graphics()->GetScreen(&ScreenX0, &ScreenY0, &ScreenX1, &ScreenY1);
	This.RenderTools()->MapScreenToInterface(This.m_pClient->m_Camera.m_Center.x, This.m_pClient->m_Camera.m_Center.y);

	char aBuf[8];
	str_format(aBuf, sizeof(aBuf), "%d", m_Id);

	CTextCursor Cursor;
	This.TextRender()->SetCursor(&Cursor, 0.0f, 0.0f, FontSize, TEXTFLAG_RENDER);
	This.TextRender()->RecreateTextContainer(m_TextContainerIndex, &Cursor, aBuf);

	This.Graphics()->MapScreen(ScreenX0, ScreenY0, ScreenX1, ScreenY1);
}

// TClient

void CNamePlate::CNamePlateReason::Update(CNamePlates &This, const char *pReason, float FontSize)
{
	if(str_comp(m_aReason, pReason) == 0 && m_FontSize == FontSize)
		return;
	str_copy(m_aReason, pReason);
	m_FontSize = FontSize;
	float ScreenX0, ScreenY0, ScreenX1, ScreenY1;
	This.Graphics()->GetScreen(&ScreenX0, &ScreenY0, &ScreenX1, &ScreenY1);
	This.RenderTools()->MapScreenToInterface(This.m_pClient->m_Camera.m_Center.x, This.m_pClient->m_Camera.m_Center.y);
	CTextCursor Cursor;
	This.TextRender()->SetCursor(&Cursor, 0.0f, 0.0f, FontSize, TEXTFLAG_RENDER);
	This.TextRender()->RecreateTextContainer(m_TextContainerIndex, &Cursor, m_aReason);
	This.Graphics()->MapScreen(ScreenX0, ScreenY0, ScreenX1, ScreenY1);
}

// A-Client

void CNamePlate::CNamePlateOldWeakStrong::Update(CNamePlates &This, int Id, float FontSize)
{
	if(Id == m_Id && m_FontSize == FontSize)
		return;
	m_Id = Id;
	m_FontSize = FontSize;

	// create namePlates at standard zoom
	float ScreenX0, ScreenY0, ScreenX1, ScreenY1;
	This.Graphics()->GetScreen(&ScreenX0, &ScreenY0, &ScreenX1, &ScreenY1);
	This.RenderTools()->MapScreenToInterface(This.m_pClient->m_Camera.m_Center.x, This.m_pClient->m_Camera.m_Center.y);

	char aBuf[8];
	str_format(aBuf, sizeof(aBuf), "%d", m_Id);

	CTextCursor Cursor;
	This.TextRender()->SetCursor(&Cursor, 0.0f, 0.0f, FontSize, TEXTFLAG_RENDER);
	This.TextRender()->RecreateTextContainer(m_TextContainerIndex, &Cursor, aBuf);

	This.Graphics()->MapScreen(ScreenX0, ScreenY0, ScreenX1, ScreenY1);
}

void CNamePlates::OnMessage(int MsgType, void *pRawMsg)
{
	if(m_pClient->m_SuppressEvents)
		return;

	if(MsgType == NETMSGTYPE_SV_CHAT)
	{
		CNetMsg_Sv_Chat *pMsg = (CNetMsg_Sv_Chat *)pRawMsg;
		OnChatMessage(pMsg->m_ClientId, pMsg->m_Team, pMsg->m_pMessage);
	}
}

bool CNamePlates::LineShouldHighlight(const char *pLine, const char *pName)
{
	const char *pHL = str_utf8_find_nocase(pLine, pName);

	if(pHL)
	{
		int Length = str_length(pName);

		if(Length > 0 && (pLine == pHL || pHL[-1] == ' ') && (pHL[Length] == 0 || pHL[Length] == ' ' || pHL[Length] == '.' || pHL[Length] == '!' || pHL[Length] == ',' || pHL[Length] == '?' || pHL[Length] == ':'))
			return true;
	}

	return false;
}

void CNamePlates::OnChatMessage(int ClientId, int Team, const char *pMsg)
{
	if(ClientId < 0 || ClientId > MAX_CLIENTS)
		return;
	bool Highlighted = false;

	CRenderNamePlateData Data;
	// check for highlighted name
	if(Client()->State() != IClient::STATE_DEMOPLAYBACK)
	{
		if(m_pClient->m_aLocalIds[0] == -1)
			return;
		if(m_pClient->Client()->DummyConnected() && m_pClient->m_aLocalIds[1] == -1)
			return;
		if(ClientId >= 0 && ClientId != m_pClient->m_aLocalIds[0] && (!m_pClient->Client()->DummyConnected() || ClientId != m_pClient->m_aLocalIds[1]))
		{
			// main character
			Highlighted |= LineShouldHighlight(pMsg, m_pClient->m_aClients[m_pClient->m_aLocalIds[0]].m_aName);
		}
	}
	else
	{
		if(m_pClient->m_Snap.m_LocalClientId == -1)
			return;
		// on demo playback use local id from snap directly,
		// since m_aLocalIds isn't valid there
		Highlighted |= m_pClient->m_Snap.m_LocalClientId >= 0 && LineShouldHighlight(pMsg, m_pClient->m_aClients[m_pClient->m_Snap.m_LocalClientId].m_aName);
	}

	if(Team == 3) // whisper recv
		Highlighted = true;

	char Message[MAX_LINE_LENGTH];
	str_format(Message, sizeof(Message), "%s", pMsg);
	if(Team == 3)
		str_format(Message, sizeof(Message), "→ %s", pMsg);

	m_NameplatePlayers[ClientId].m_Time = time_get() + time_freq() * 3.0f + time_freq() * str_length(pMsg) / 30.0f;
	m_NameplatePlayers[ClientId].m_ChatTeam = Team;
	m_NameplatePlayers[ClientId].m_ChatHighlighted = Highlighted;

	const float FontSize = 18.0f + 20.0f * g_Config.m_ClNameplateChatBoxSize / 350.0f;

	m_aNamePlates[ClientId].m_ChatBox.Update(*this, Message, FontSize);
}

void CNamePlate::CNamePlateChatBox::Update(CNamePlates &This, const char *pMsg, float FontSize)
{
	if(str_comp(m_aMsg, pMsg) == 0 && m_FontSize == FontSize)
		return;
	str_copy(m_aMsg, pMsg);
	m_FontSize = FontSize;
	float ScreenX0, ScreenY0, ScreenX1, ScreenY1;
	This.Graphics()->GetScreen(&ScreenX0, &ScreenY0, &ScreenX1, &ScreenY1);
	This.RenderTools()->MapScreenToInterface(This.m_pClient->m_Camera.m_Center.x, This.m_pClient->m_Camera.m_Center.y);
	CTextCursor Cursor;
	This.TextRender()->SetCursor(&Cursor, 0.0f, 0.0f, FontSize, TEXTFLAG_RENDER);
	This.TextRender()->RecreateTextContainer(m_TextContainerIndex, &Cursor, m_aMsg);
	This.Graphics()->MapScreen(ScreenX0, ScreenY0, ScreenX1, ScreenY1);
}

void CNamePlates::RenderNamePlate(CNamePlate &NamePlate, const CRenderNamePlateData &Data)
{
	ColorRGBA OutlineColor = Data.m_OutlineColor.WithAlpha(Data.m_Alpha / 2.0f);
	ColorRGBA Color = Data.m_Color.WithAlpha(Data.m_Alpha);

	float YOffset = Data.m_Position.y - 38.0f;

	// Render directions
	TextRender()->SetRenderFlags(ETextRenderFlags::TEXT_RENDER_FLAG_NO_FIRST_CHARACTER_X_BEARING | ETextRenderFlags::TEXT_RENDER_FLAG_NO_LAST_CHARACTER_ADVANCE);
	if(Data.m_ShowDirection)
	{
		Graphics()->SetColor(1.0f, 1.0f, 1.0f, Data.m_Alpha);
		YOffset -= 6.5f; // TClient
		YOffset -= Data.m_FontSizeDirection;
		const vec2 ShowDirectionPos = vec2(Data.m_Position.x - Data.m_FontSizeDirection / 2.0f, YOffset + Data.m_FontSizeDirection / 2.0f);
		if(Data.m_DirLeft)
		{
			Graphics()->TextureSet(g_pData->m_aImages[IMAGE_ARROW].m_Id);
			Graphics()->QuadsSetRotation(pi);
			Graphics()->RenderQuadContainerAsSprite(m_DirectionQuadContainerIndex, 0, ShowDirectionPos.x - Data.m_FontSizeDirection, ShowDirectionPos.y, Data.m_FontSizeDirection, Data.m_FontSizeDirection);
		}
		if(Data.m_DirJump)
		{
			Graphics()->TextureSet(g_pData->m_aImages[IMAGE_ARROW].m_Id);
			Graphics()->QuadsSetRotation(pi * 1.5f);
			Graphics()->RenderQuadContainerAsSprite(m_DirectionQuadContainerIndex, 0, ShowDirectionPos.x, ShowDirectionPos.y - Data.m_FontSizeDirection / 2.0f, Data.m_FontSizeDirection, Data.m_FontSizeDirection);
		}
		if(Data.m_DirRight)
		{
			Graphics()->TextureSet(g_pData->m_aImages[IMAGE_ARROW].m_Id);
			Graphics()->QuadsSetRotation(0.0f);
			Graphics()->RenderQuadContainerAsSprite(m_DirectionQuadContainerIndex, 0, ShowDirectionPos.x + Data.m_FontSizeDirection, ShowDirectionPos.y, Data.m_FontSizeDirection, Data.m_FontSizeDirection);
		}
		Graphics()->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
		Graphics()->QuadsSetRotation(0.0f);
	}


	if((Data.m_pName && Data.m_pName[0] != '\0') || Data.m_ClientId >= 0 || Data.m_ShowFriendMark)
	{
		YOffset -= Data.m_FontSize;
		NamePlate.m_Name.Update(*this, Data.m_ClientId, Data.m_pName, Data.m_ShowFriendMark, Data.m_FontSize);
		// TClient
		if(Data.m_IsGame && Data.m_RealClientId >= 0)
		{
			if((g_Config.m_ClPingNameCircle || (m_pClient->m_Scoreboard.IsActive() && !m_pClient->m_Snap.m_apPlayerInfos[Data.m_RealClientId]->m_Local)) && (Client()->State() != IClient::STATE_DEMOPLAYBACK))
			{
				Graphics()->TextureClear();
				Graphics()->QuadsBegin();
				Graphics()->SetColor(color_cast<ColorRGBA>(ColorHSLA((300.0f - clamp(m_pClient->m_Snap.m_apPlayerInfos[Data.m_RealClientId]->m_Latency, 0, 300)) / 1000.0f, 1.0f, 0.5f, 0.8f)).WithAlpha(Data.m_Alpha));
				if((m_pClient->m_Snap.m_apPlayerInfos[Data.m_RealClientId]->m_Latency == 77 || m_pClient->m_Snap.m_apPlayerInfos[Data.m_RealClientId]->m_Latency == 76) && g_Config.m_ClAidsPingDetection)
					Graphics()->SetColor(0.f, 0.f, 0.f, 0.5f);
				float CircleSize = 7.0f;
				Graphics()->DrawCircle(Data.m_Position.x - TextRender()->GetBoundingBoxTextContainer(NamePlate.m_Name.m_TextContainerIndex).m_W / 2.0f - CircleSize, YOffset + Data.m_FontSize / 2.0f + 1.4f, CircleSize, 24);
				Graphics()->QuadsEnd();
			}
			// A-Client
			if((GameClient()->m_aClients[Data.m_RealClientId].m_IsMute && g_Config.m_ClMutedIcon))
			{
				ColorRGBA IconColor = color_cast<ColorRGBA, ColorHSLA>(ColorHSLA(g_Config.m_ClMutedColor));
				Graphics()->TextureClear();
				Graphics()->TextureSet(g_pData->m_aImages[IMAGE_MUTED_ICON].m_Id);
				Graphics()->SetColor(IconColor.WithAlpha(Data.m_Alpha));
				Graphics()->QuadsSetRotation(0);
				Graphics()->RenderQuadContainerAsSprite(m_DirectionQuadContainerIndex, 0, Data.m_Position.x + TextRender()->GetBoundingBoxTextContainer(NamePlate.m_Name.m_TextContainerIndex).m_W / 2.0f + 2, YOffset + 1.5f, Data.m_FontSize, Data.m_FontSize);
			}
		}

		if(Data.m_IsGame && Data.m_RealClientId >= 0)
		{
			// TClient / A-Client
			ColorRGBA WarColor = Color;

			if(m_pClient->m_aClients[Data.m_RealClientId].m_Friend && g_Config.m_ClDoFriendColors)
				WarColor = color_cast<ColorRGBA>(ColorHSLA(g_Config.m_ClFriendColor).WithAlpha(Data.m_Alpha));

			if(GameClient()->m_WarList.GetWarData(Data.m_RealClientId).IsWarClan)
				WarColor = GameClient()->m_WarList.GetClanColor(Data.m_RealClientId).WithAlpha(Data.m_Alpha);
			if(!Data.m_ShowClanWarInName && GameClient()->m_WarList.GetWarData(Data.m_RealClientId).IsWarName)
				WarColor = GameClient()->m_WarList.GetNameplateColor(Data.m_RealClientId).WithAlpha(Data.m_Alpha);
			else if(Data.m_ShowClanWarInName && GameClient()->m_WarList.GetWarData(Data.m_RealClientId).IsWarClan)
				WarColor = GameClient()->m_WarList.GetClanColor(Data.m_RealClientId).WithAlpha(Data.m_Alpha);

			if(GameClient()->m_Aiodob.m_TempPlayers[Data.m_RealClientId].IsTempWar)
				WarColor = GameClient()->m_WarList.m_WarTypes[1]->m_Color.WithAlpha(Data.m_Alpha);
			else if(GameClient()->m_Aiodob.m_TempPlayers[Data.m_RealClientId].IsTempHelper)
				WarColor = GameClient()->m_WarList.m_WarTypes[3]->m_Color.WithAlpha(Data.m_Alpha);

			if(NamePlate.m_Name.m_TextContainerIndex.Valid())
				TextRender()->RenderTextContainer(NamePlate.m_Name.m_TextContainerIndex, WarColor, OutlineColor, Data.m_Position.x - TextRender()->GetBoundingBoxTextContainer(NamePlate.m_Name.m_TextContainerIndex).m_W / 2.0f, YOffset);
		}

		if(Data.m_pClan && Data.m_pClan[0] != '\0')
		{
			YOffset -= Data.m_FontSizeClan;
			NamePlate.m_Clan.Update(*this, Data.m_pClan, Data.m_FontSizeClan);

			// TClient
			ColorRGBA WarColor = Color;

			if(Data.m_IsGame && Data.m_RealClientId >= 0 && GameClient()->m_WarList.GetWarData(Data.m_RealClientId).IsWarClan)
				WarColor = GameClient()->m_WarList.GetClanColor(Data.m_RealClientId).WithAlpha(Data.m_Alpha);

			if(NamePlate.m_Clan.m_TextContainerIndex.Valid())
				TextRender()->RenderTextContainer(NamePlate.m_Clan.m_TextContainerIndex, WarColor, OutlineColor, Data.m_Position.x - TextRender()->GetBoundingBoxTextContainer(NamePlate.m_Clan.m_TextContainerIndex).m_W / 2.0f, YOffset);
		}

		// TClient war reason
		if(Data.m_IsGame && !Data.m_IsLocal && Data.m_RealClientId >= 0 && g_Config.ms_ClWarList && GameClient()->m_WarList.GetWarData(Data.m_RealClientId).m_aReason[0] != '\0')
		{
			YOffset -= Data.m_FontSizeClan;
			NamePlate.m_Reason.Update(*this, GameClient()->m_WarList.GetWarData(Data.m_RealClientId).m_aReason, Data.m_FontSizeClan);
			if(NamePlate.m_Reason.m_TextContainerIndex.Valid())
				TextRender()->RenderTextContainer(NamePlate.m_Reason.m_TextContainerIndex, Data.m_Color.WithAlpha(Data.m_Alpha * 0.5f), Data.m_OutlineColor.WithAlpha(Data.m_Alpha / 4.0f), Data.m_Position.x - TextRender()->GetBoundingBoxTextContainer(NamePlate.m_Reason.m_TextContainerIndex).m_W / 2.0f, YOffset);
		}

		if(Data.m_OldNameplateId || Data.m_ShowHookWeakStrongId || (Data.m_ShowHookWeakStrong && Data.m_HookWeakStrong != TRISTATE::SOME)) // Don't show hook icon if there's no ID or hook strength to show
		{
			ColorRGBA HookWeakStrongColor;
			int StrongWeakSpriteId;
			switch(Data.m_HookWeakStrong)
			{
			case TRISTATE::ALL:
				HookWeakStrongColor = color_cast<ColorRGBA>(ColorHSLA(6401973));
				StrongWeakSpriteId = SPRITE_HOOK_STRONG;
				break;
			case TRISTATE::SOME:
				HookWeakStrongColor = ColorRGBA(1.0f, 1.0f, 1.0f);
				StrongWeakSpriteId = SPRITE_HOOK_ICON;
				break;
			case TRISTATE::NONE:
				HookWeakStrongColor = color_cast<ColorRGBA>(ColorHSLA(41131));
				StrongWeakSpriteId = SPRITE_HOOK_WEAK;
				break;
			default:
				dbg_assert(false, "Invalid hook weak/strong state");
				dbg_break();
			}
			HookWeakStrongColor.a = Data.m_Alpha;

			// A-Client Nameplates_ClientId
			if(Data.m_IsGame && !Data.m_IsLocal && g_Config.m_ClOldNameplateIds && g_Config.m_ClNamePlates)
			{
				const float FontSize = 18.0f + 20.0f * g_Config.m_ClNamePlatesStrongSize / 100.0f;
				YOffset -= FontSize;

				NamePlate.m_OldWeakStrongId.Update(*this, Data.m_RealClientId, FontSize);

				if(NamePlate.m_OldWeakStrongId.m_TextContainerIndex.Valid())
				{
					if(g_Config.m_ClStrongWeakColorId)
						TextRender()->RenderTextContainer(NamePlate.m_OldWeakStrongId.m_TextContainerIndex, HookWeakStrongColor, OutlineColor, Data.m_Position.x - TextRender()->GetBoundingBoxTextContainer(NamePlate.m_OldWeakStrongId.m_TextContainerIndex).m_W / 2.0f, YOffset);
					else
						TextRender()->RenderTextContainer(NamePlate.m_OldWeakStrongId.m_TextContainerIndex, ColorRGBA(1.0f, 1.0f, 1.0f).WithAlpha(Data.m_Alpha), OutlineColor, Data.m_Position.x - TextRender()->GetBoundingBoxTextContainer(NamePlate.m_OldWeakStrongId.m_TextContainerIndex).m_W / 2.0f, YOffset);
				}
			}

			YOffset -= Data.m_FontSizeHookWeakStrong;
			float ShowHookWeakStrongIdSize = 0.0f;
			if(Data.m_ShowHookWeakStrongId)
			{
				NamePlate.m_WeakStrongId.Update(*this, Data.m_HookWeakStrongId, Data.m_FontSizeHookWeakStrong);
				if(NamePlate.m_WeakStrongId.m_TextContainerIndex.Valid())
				{
					ShowHookWeakStrongIdSize = TextRender()->GetBoundingBoxTextContainer(NamePlate.m_WeakStrongId.m_TextContainerIndex).m_W;
					float X = Data.m_Position.x - ShowHookWeakStrongIdSize / 2.0f;
					if(Data.m_ShowHookWeakStrong)
						X += Data.m_FontSizeHookWeakStrong * 0.75f;
					TextRender()->TextColor(HookWeakStrongColor);
					TextRender()->RenderTextContainer(NamePlate.m_WeakStrongId.m_TextContainerIndex, HookWeakStrongColor, OutlineColor, X, YOffset);
				}
			}
			if(Data.m_ShowHookWeakStrong)
			{
				Graphics()->TextureSet(g_pData->m_aImages[IMAGE_STRONGWEAK].m_Id);
				Graphics()->QuadsBegin();

				Graphics()->SetColor(HookWeakStrongColor);
				RenderTools()->SelectSprite(StrongWeakSpriteId);

				const float StrongWeakImgSize = Data.m_FontSizeHookWeakStrong * 1.5f;
				float X = Data.m_Position.x;
				if(Data.m_ShowHookWeakStrongId)
					X -= ShowHookWeakStrongIdSize / 2.0f;
				RenderTools()->DrawSprite(X, YOffset + StrongWeakImgSize / 2.7f, StrongWeakImgSize);
				Graphics()->QuadsEnd();
			}
		}

		// A-Client Chat Box
		if(Data.m_IsGame && Data.m_RealClientId >= 0 && g_Config.m_ClNameplateChatBox)
		{
			CNameplateChatData ChatData = m_NameplatePlayers[Data.m_RealClientId];

			if(ChatData.m_ChatTeam == 2 || !GameClient()->m_aClients[Data.m_RealClientId].m_IsMute)
				return;

			if(g_Config.m_ClNameplateChatBoxFriends && !m_pClient->m_aClients[Data.m_RealClientId].m_Friend)
				return;

			float Time = (static_cast<float>(ChatData.m_Time) - time_get());
			float Max = 1.0f;
			float Blend = clamp(Time / time_freq(), 0.0f, Max) / Max;

			float BoxAlpha = 0.7f;
			float TextAlpha = 1.0f;

			ColorRGBA ChatBoxColor = ColorRGBA(0.0f, 0.0f, 0.0f, BoxAlpha);
			ColorRGBA TextColor = ColorRGBA(1.0f, 1.0f, 1.0f, TextAlpha);

			if(ChatData.m_ChatHighlighted || ChatData.m_ChatTeam == 3)
			{
				TextColor = color_cast<ColorRGBA>(ColorHSLA(g_Config.m_ClMessageHighlightColor));
				ChatBoxColor.s = TextColor.s / 4;
			}
			else if(ChatData.m_ChatTeam == 1)
			{
				TextColor = color_cast<ColorRGBA>(ColorHSLA(g_Config.m_ClMessageTeamColor));
				ChatBoxColor.s = TextColor.s / 4;
			}

			const float FontSize = 18.0f + 20.0f * g_Config.m_ClNameplateChatBoxSize / 350.0f;
			YOffset -= FontSize;

			if(NamePlate.m_ChatBox.m_TextContainerIndex.Valid() && Blend > 0)
			{
				const bool OtherTeam = m_pClient->IsOtherTeam(Data.m_RealClientId);
				if(OtherTeam)
				{
					float OthersAlpha = (float)g_Config.m_ClShowOthersAlpha / 100;

					if((float)g_Config.m_ClShowOthersAlpha / 100 <= 0.7f)
						BoxAlpha = 0.7f;
					TextAlpha = 0.80f;
				}
				ChatBoxColor.a = BoxAlpha * 0.75f * Blend;
				TextColor.a = BoxAlpha * TextAlpha * Blend;

				Graphics()->SetColor(ChatBoxColor);

				Graphics()->TextureClear();

				// All of these are magic numbers, so if you read this don't even try to figure them out - I have no clue either
				int xPosLeft = (Data.m_Position.x - TextRender()->GetBoundingBoxTextContainer(NamePlate.m_ChatBox.m_TextContainerIndex).m_W / 2.0f) - FontSize / 2.15f;
				int xPosRight = TextRender()->GetBoundingBoxTextContainer(NamePlate.m_ChatBox.m_TextContainerIndex).m_W + FontSize;
				int yPosBottom = TextRender()->GetBoundingBoxTextContainer(NamePlate.m_ChatBox.m_TextContainerIndex).m_H - FontSize * 1.45f;
				int yPosTop = TextRender()->GetBoundingBoxTextContainer(NamePlate.m_ChatBox.m_TextContainerIndex).m_H + FontSize * 1.1f;
				int ContainerIndex = Graphics()->CreateRectQuadContainer(xPosLeft, yPosBottom, xPosRight, yPosTop, 8, IGraphics::CORNER_ALL);
				

				Graphics()->RenderQuadContainerEx(ContainerIndex, 0, -1, -2, YOffset + g_Config.m_ClNameplateChatBoxSize / 10.0f);

				TextRender()->RenderTextContainer(NamePlate.m_ChatBox.m_TextContainerIndex, TextColor.WithAlpha(Blend * TextAlpha), ColorRGBA(0.0f, 0.0f, 0.0f, Blend), (Data.m_Position.x - TextRender()->GetBoundingBoxTextContainer(NamePlate.m_ChatBox.m_TextContainerIndex).m_W / 2.0f) - 2, YOffset + g_Config.m_ClNameplateChatBoxSize / 10.0f); // Draw backgrounds for messages in one batch
			}
		}
	}

	TextRender()->TextColor(TextRender()->DefaultTextColor());
	TextRender()->TextOutlineColor(TextRender()->DefaultTextOutlineColor());

	TextRender()->SetRenderFlags(0);
}

void CNamePlates::RenderNamePlateGame(vec2 Position, const CNetObj_PlayerInfo *pPlayerInfo, float Alpha, bool ForceAlpha)
{
	CRenderNamePlateData Data;

	const auto &ClientData = m_pClient->m_aClients[pPlayerInfo->m_ClientId];
	const bool OtherTeam = m_pClient->IsOtherTeam(pPlayerInfo->m_ClientId);

	bool ShowNamePlate = pPlayerInfo->m_Local ? g_Config.m_ClNamePlatesOwn : g_Config.m_ClNamePlates;

	// TClient
	Data.m_RealClientId = pPlayerInfo->m_ClientId;
	Data.m_IsGame = true;
	bool ClanPlateOverride = g_Config.m_ClWarList && g_Config.m_ClWarListShowClan && GameClient()->m_WarList.GetWarData(pPlayerInfo->m_ClientId).IsWarClan;
	bool ShowClanPlate = g_Config.m_ClNamePlatesClan || ClanPlateOverride;
	bool ShowClanWarInName = g_Config.m_ClWarList && !ShowClanPlate && GameClient()->m_WarList.GetWarData(pPlayerInfo->m_ClientId).IsWarClan && !GameClient()->m_WarList.GetWarData(pPlayerInfo->m_ClientId).IsWarName;
	Data.m_ShowClanWarInName = ShowClanWarInName;
	Data.m_IsLocal = pPlayerInfo->m_Local;

	Data.m_Position = Position;
	Data.m_ClientId = ShowNamePlate && g_Config.m_ClNamePlatesIds ? pPlayerInfo->m_ClientId : -1;
	Data.m_pName = ShowNamePlate ? m_pClient->m_aClients[pPlayerInfo->m_ClientId].m_aName : nullptr;
	Data.m_ShowFriendMark = ShowNamePlate && g_Config.m_ClNamePlatesFriendMark && m_pClient->m_aClients[pPlayerInfo->m_ClientId].m_Friend;
	Data.m_FontSize = 18.0f + 20.0f * g_Config.m_ClNamePlatesSize / 100.0f;

	Data.m_pClan = ShowNamePlate && ShowClanPlate ? m_pClient->m_aClients[pPlayerInfo->m_ClientId].m_aClan : nullptr;
	Data.m_FontSizeClan = 18.0f + 20.0f * g_Config.m_ClNamePlatesClanSize / 100.0f;

	Data.m_FontSizeHookWeakStrong = 18.0f + 20.0f * g_Config.m_ClNamePlatesStrongSize / 100.0f;
	Data.m_FontSizeDirection = 18.0f + 20.0f * g_Config.m_ClDirectionSize / 100.0f;

	Data.m_Alpha = Alpha;
	if(!ForceAlpha)
	{
		if(g_Config.m_ClNamePlatesAlways == 0)
			Data.m_Alpha *= clamp(1.0f - std::pow(distance(m_pClient->m_Controls.m_aTargetPos[g_Config.m_ClDummy], Position) / 200.0f, 16.0f), 0.0f, 1.0f);
		if(OtherTeam)
			Data.m_Alpha *= (float)g_Config.m_ClShowOthersAlpha / 100.0f;
	}

	Data.m_Color = ColorRGBA(1.0f, 1.0f, 1.0f);
	Data.m_OutlineColor = ColorRGBA(0.0f, 0.0f, 0.0f);

	if(g_Config.m_ClNamePlatesTeamcolors)
	{
		if(m_pClient->IsTeamPlay())
		{
			if(ClientData.m_Team == TEAM_RED)
				Data.m_Color = ColorRGBA(1.0f, 0.5f, 0.5f);
			else if(ClientData.m_Team == TEAM_BLUE)
				Data.m_Color = ColorRGBA(0.7f, 0.7f, 1.0f);
		}
		else
		{
			const int Team = m_pClient->m_Teams.Team(pPlayerInfo->m_ClientId);
			if(Team)
				Data.m_Color = m_pClient->GetDDTeamColor(Team, 0.75f);
		}
	}

	int ShowDirectionConfig = g_Config.m_ClShowDirection;
#if defined(CONF_VIDEORECORDER)
	if(IVideo::Current())
		ShowDirectionConfig = g_Config.m_ClVideoShowDirection;
#endif
	Data.m_DirLeft = Data.m_DirJump = Data.m_DirRight = false;
	switch(ShowDirectionConfig)
	{
	case 0: // off
		Data.m_ShowDirection = false;
		break;
	case 1: // others
		Data.m_ShowDirection = !pPlayerInfo->m_Local;
		break;
	case 2: // everyone
		Data.m_ShowDirection = true;
		break;
	case 3: // only self
		Data.m_ShowDirection = pPlayerInfo->m_Local;
		break;
	default:
		dbg_assert(false, "ShowDirectionConfig invalid");
		dbg_break();
	}
	if(Data.m_ShowDirection)
	{
		if(Client()->State() != IClient::STATE_DEMOPLAYBACK &&
			Client()->DummyConnected() && pPlayerInfo->m_ClientId == m_pClient->m_aLocalIds[!g_Config.m_ClDummy])
		{
			const auto &InputData = m_pClient->m_Controls.m_aInputData[!g_Config.m_ClDummy];
			Data.m_DirLeft = InputData.m_Direction == -1;
			Data.m_DirJump = InputData.m_Jump == 1;
			Data.m_DirRight = InputData.m_Direction == 1;
		}
		else if(Client()->State() != IClient::STATE_DEMOPLAYBACK && pPlayerInfo->m_Local) // always render local input when not in demo playback
		{
			const auto &InputData = m_pClient->m_Controls.m_aInputData[g_Config.m_ClDummy];
			Data.m_DirLeft = InputData.m_Direction == -1;
			Data.m_DirJump = InputData.m_Jump == 1;
			Data.m_DirRight = InputData.m_Direction == 1;
		}
		else
		{
			const auto &Character = m_pClient->m_Snap.m_aCharacters[pPlayerInfo->m_ClientId];
			Data.m_DirLeft = Character.m_Cur.m_Direction == -1;
			Data.m_DirJump = Character.m_Cur.m_Jumped & 1;
			Data.m_DirRight = Character.m_Cur.m_Direction == 1;
		}
	}

	Data.m_ShowHookWeakStrong = g_Config.m_Debug || g_Config.m_ClNamePlatesStrong > 0;
	Data.m_HookWeakStrong = TRISTATE::SOME;
	Data.m_ShowHookWeakStrongId = false;
	Data.m_HookWeakStrongId = false;
	// A-Client
	Data.m_OldNameplateId = false;

	if(g_Config.m_ClOldNameplateIds)
		Data.m_OldNameplateId = true;

	const bool Following = (m_pClient->m_Snap.m_SpecInfo.m_Active && !GameClient()->m_MultiViewActivated && m_pClient->m_Snap.m_SpecInfo.m_SpectatorId != SPEC_FREEVIEW);
	if(m_pClient->m_Snap.m_LocalClientId != -1 || Following)
	{
		const int SelectedId = Following ? m_pClient->m_Snap.m_SpecInfo.m_SpectatorId : m_pClient->m_Snap.m_LocalClientId;
		const CGameClient::CSnapState::CCharacterInfo &Selected = m_pClient->m_Snap.m_aCharacters[SelectedId];
		const CGameClient::CSnapState::CCharacterInfo &Other = m_pClient->m_Snap.m_aCharacters[pPlayerInfo->m_ClientId];
		if(Selected.m_HasExtendedData && Other.m_HasExtendedData)
		{
			if(SelectedId != pPlayerInfo->m_ClientId)
				Data.m_HookWeakStrong = Selected.m_ExtendedData.m_StrongWeakId > Other.m_ExtendedData.m_StrongWeakId ? TRISTATE::ALL : TRISTATE::NONE;
			Data.m_ShowHookWeakStrongId = g_Config.m_Debug || g_Config.m_ClNamePlatesStrong == 2;
			if(Data.m_ShowHookWeakStrongId)
				Data.m_HookWeakStrongId = Other.m_ExtendedData.m_StrongWeakId;
		}
	}

	GameClient()->m_NamePlates.RenderNamePlate(m_aNamePlates[pPlayerInfo->m_ClientId], Data);
}

void CNamePlates::RenderNamePlatePreview(vec2 Position)
{
	const float FontSize = 18.0f + 20.0f * g_Config.m_ClNamePlatesSize / 100.0f;
	const float FontSizeClan = 18.0f + 20.0f * g_Config.m_ClNamePlatesClanSize / 100.0f;

	const float FontSizeDirection = 18.0f + 20.0f * g_Config.m_ClDirectionSize / 100.0f;
	const float FontSizeHookWeakStrong = 18.0f + 20.0f * g_Config.m_ClNamePlatesStrongSize / 100.0f;

	CRenderNamePlateData Data;

	Data.m_Position = Position;
	Data.m_Color = g_Config.m_ClNamePlatesTeamcolors ? m_pClient->GetDDTeamColor(13, 0.75f) : TextRender()->DefaultTextColor();
	Data.m_OutlineColor = TextRender()->DefaultTextOutlineColor();
	Data.m_Alpha = 1.0f;
	Data.m_pName = g_Config.m_ClNamePlates ? g_Config.m_PlayerName : nullptr;
	Data.m_ShowFriendMark = g_Config.m_ClNamePlates && g_Config.m_ClNamePlatesFriendMark;
	Data.m_OldNameplateId = g_Config.m_ClNamePlates && g_Config.m_ClOldNameplateIds ? 1 : -1;
	Data.m_ClientId = g_Config.m_ClNamePlates && g_Config.m_ClNamePlatesIds ? 1 : -1;
	Data.m_FontSize = FontSize;
	Data.m_pClan = g_Config.m_ClNamePlates && g_Config.m_ClNamePlatesClan ? g_Config.m_PlayerClan : nullptr;
	Data.m_FontSizeClan = FontSizeClan;

	Data.m_ShowDirection = g_Config.m_ClShowDirection != 0 ? true : false;
	Data.m_DirLeft = Data.m_DirJump = Data.m_DirRight = true;
	Data.m_FontSizeDirection = FontSizeDirection;

	Data.m_ShowHookWeakStrong = g_Config.m_ClNamePlatesStrong >= 1;
	Data.m_HookWeakStrong = TRISTATE::ALL;
	Data.m_ShowHookWeakStrongId = g_Config.m_ClNamePlatesStrong >= 2;
	Data.m_HookWeakStrongId = 1;
	Data.m_FontSizeHookWeakStrong = FontSizeHookWeakStrong;

	CNamePlate NamePlate;
	GameClient()->m_NamePlates.RenderNamePlate(NamePlate, Data);
	NamePlate.DeleteTextContainers(*TextRender());
}

void CNamePlates::OnRender()
{
	if(Client()->State() != IClient::STATE_ONLINE && Client()->State() != IClient::STATE_DEMOPLAYBACK)
		return;

	int ShowDirection = g_Config.m_ClShowDirection;
#if defined(CONF_VIDEORECORDER)
	if(IVideo::Current())
		ShowDirection = g_Config.m_ClVideoShowDirection;
#endif
	if(!g_Config.m_ClNamePlates && ShowDirection == 0)
		return;

	// get screen edges to avoid rendering offscreen
	float ScreenX0, ScreenY0, ScreenX1, ScreenY1;
	Graphics()->GetScreen(&ScreenX0, &ScreenY0, &ScreenX1, &ScreenY1);
	// expand the edges to prevent popping in/out onscreen
	//
	// it is assumed that the namePlate and all its components fit into a 800x800 box placed directly above the tee
	// this may need to be changed or calculated differently in the future
	ScreenX0 -= 400;
	ScreenX1 += 400;
	// ScreenY0 -= 0;
	ScreenY1 += 800;

	for(int i = 0; i < MAX_CLIENTS; i++)
	{
		const CNetObj_PlayerInfo *pInfo = m_pClient->m_Snap.m_apPlayerInfos[i];
		if(!pInfo)
		{
			continue;
		}

		if(m_pClient->m_aClients[i].m_SpecCharPresent)
		{
			// Each player can also have a spec char whose namePlate is displayed independently
			const vec2 RenderPos = m_pClient->m_aClients[i].m_SpecChar;
			// don't render offscreen
			if(in_range(RenderPos.x, ScreenX0, ScreenX1) && in_range(RenderPos.y, ScreenY0, ScreenY1))
			{
				if(!g_Config.m_ClRenderNameplateSpec)
				{
					RenderNamePlateGame(RenderPos, pInfo, 0.4f, true);
				}
			}
		}
		if(m_pClient->m_Snap.m_aCharacters[i].m_Active)
		{
			// Only render namePlates for active characters
			const vec2 RenderPos = m_pClient->m_aClients[i].m_RenderPos;
			// don't render offscreen
			if(in_range(RenderPos.x, ScreenX0, ScreenX1) && in_range(RenderPos.y, ScreenY0, ScreenY1))
			{
				RenderNamePlateGame(RenderPos, pInfo, 1.0f, false);
			}
		}
	}
}

void CNamePlates::ResetNamePlates()
{
	for(auto &NamePlate : m_aNamePlates)
	{
		NamePlate.DeleteTextContainers(*TextRender());
		NamePlate.Reset();
	}
}

void CNamePlates::OnWindowResize()
{
	ResetNamePlates();
}

void CNamePlates::OnInit()
{
	ResetNamePlates();

	// Quad for the direction arrows above the player
	m_DirectionQuadContainerIndex = Graphics()->CreateQuadContainer(false);
	RenderTools()->QuadContainerAddSprite(m_DirectionQuadContainerIndex, 0.0f, 0.0f, 1.0f);
	Graphics()->QuadContainerUpload(m_DirectionQuadContainerIndex);
}
