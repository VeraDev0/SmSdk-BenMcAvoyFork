#include "SmSdk/CharacterManager.hpp"
#include "SmSdk/MyPlayer.hpp"

Character* MyPlayer::getCharacter() const
{
	if (!this->m_player)
		return nullptr;

	return CharacterManager::GetCharacter(this->m_player->m_iCharacterId);
}