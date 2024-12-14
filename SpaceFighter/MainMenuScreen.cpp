
#include "MainMenuScreen.h"
#include "GameplayScreen.h"
#include "LevelSelectScreen.h" //Adds [Alexander]'s level select header file. 
// I am placing my comments all over the place to show where I made changes. So if a normal function of the game isn't working then you can look at my comments to
// see if I made a change that could have caused it.

MainMenuScreen::MainMenuScreen()
{
	// when the screen is removed, quit the game
	SetOnRemove([this](){ GetGame()->Quit(); });

	SetTransitionInTime(1);
	SetTransitionOutTime(0.5f);

	Show();
}

void MainMenuScreen::LoadContent(ResourceManager& resourceManager)
{
	// Logo
	m_pTexture = resourceManager.Load<Texture>("Textures\\Logo.png");
	m_texturePosition = Game::GetScreenCenter() - Vector2::UNIT_Y * 150;

	// Create the menu items // [Alexander] changed COUNT from 2 to 3 in order to make room for my ne menu option
	const int COUNT = 3;
	MenuItem *pItem;
	Font::SetLoadSize(20, true);
	Font *pFont = resourceManager.Load<Font>("Fonts\\Ethnocentric.ttf"); // Changed Font [CHRISTIAN]

	SetDisplayCount(COUNT);

	enum Items { START_GAME, Level_Select, QUIT }; //Added Level Select to the list of items [Alexander]
    std::string text[COUNT] = { "Start Game", "Level Select", "Quit"}; //Added Level Select to the menu [Alexander]

	for (int i = 0; i < COUNT; i++)
	{
		pItem = new MenuItem(text[i]);
		pItem->SetPosition(Vector2(100, 100 + 50 * i));
		pItem->SetFont(pFont);
		pItem->SetColor(Color::BLUE);
		pItem->SetSelected(i == 0);
		AddMenuItem(pItem);
	}

	// when "Start Game" is selected, replace the "SetRemoveCallback" delegate
	// so that it doesn't quit the game (originally set in the constructor)
	GetMenuItem(START_GAME)->SetOnSelect([this](){
		SetOnRemove([this](){ AddScreen(new GameplayScreen()); });
		Exit();
	// [Alexander] Changes the Level Select menu item to go to the LevelSelectScreen
	});
	GetMenuItem(Level_Select)->SetOnSelect([this]() {
			SetOnRemove([this]() { AddScreen(new LevelSelectScreen()); });
			Exit();
	});

	// bind the Exit method to the quit menu item
	GetMenuItem(QUIT)->SetOnSelect(std::bind(&MainMenuScreen::Exit, this));
}

void MainMenuScreen::Update(const GameTime& gameTime)
{
	bool isSelected = false;
	float alpha = GetAlpha();
	float offset = sinf(gameTime.GetTotalTime() * 10) * 5 + 5;

	for (MenuItem* pItem : GetMenuItems())
	{
		pItem->SetAlpha(alpha);
		isSelected = pItem->IsSelected();
		pItem->SetColor(isSelected ? Color::CYAN : Color::GRAY);   // Changed Colors  [CHRISTIAN]
		pItem->SetTextOffset(isSelected ? Vector2::UNIT_X * offset : Vector2::ZERO);
	}

	MenuScreen::Update(gameTime);
}

	void MainMenuScreen::Draw(SpriteBatch& spriteBatch)
	{
		spriteBatch.Begin();
		spriteBatch.Draw(m_pTexture, m_texturePosition, Color::WHITE * GetAlpha(), m_pTexture->GetCenter());
		MenuScreen::Draw(spriteBatch);
		spriteBatch.End();
	}
