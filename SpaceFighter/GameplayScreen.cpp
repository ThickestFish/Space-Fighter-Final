
#include "GameplayScreen.h"
#include "MainMenuScreen.h"
#include "Level.h"
#include "Level01.h"
#include "Level02.h" // [Alexander] Added Level02.h

GameplayScreen::GameplayScreen(const int levelIndex)
	: m_levelIndex(levelIndex)
{
	SetTransitionInTime(1);
	SetTransitionOutTime(3);

	SetOnRemove([this](){ AddScreen(new MainMenuScreen()); });

	Show();
}

void GameplayScreen::LoadContent(ResourceManager& resourceManager)
{
	m_pResourceManager = &resourceManager;
	LoadLevel(m_levelIndex);
}

void GameplayScreen::LoadLevel(const int levelIndex)
{
	if (m_pLevel) delete m_pLevel;

	switch (levelIndex)
	{
	case 0: m_pLevel = new Level01(); break; // This here handles the level selection.
	case 1: m_pLevel = new Level02(); break; // [Alexander] Added Level02 to the list of levels
	// case 2: m_pLevel = new Level03(); break;
	default:
		m_pLevel = new Level01(); break; // [Alexander] decided to add a default level to the list of levels in case something goes wrong.
	}

	m_pLevel->SetGameplayScreen(this);
	m_pLevel->LoadContent(*m_pResourceManager);
}

void GameplayScreen::HandleInput(const InputState& input)
{
	m_pLevel->HandleInput(input);
}

void GameplayScreen::Update(const GameTime& gameTime)
{
	m_pLevel->Update(gameTime);
}

void GameplayScreen::Draw(SpriteBatch& spriteBatch)
{
	spriteBatch.Begin();

	m_pLevel->Draw(spriteBatch);

	spriteBatch.End();
}
