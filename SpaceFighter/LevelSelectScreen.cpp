//Alexander
#include "MainMenuScreen.h"
#include "GameplayScreen.h"
#include "LevelSelectScreen.h" //Added the LevelSelectScreen header file [Alexander]
void LevelSelectScreen::LoadContent(ResourceManager& resourceManager)
{
	// Logo
	m_pTexture = resourceManager.Load<Texture>("Textures\\Logo.png"); // HELL
	m_texturePosition = Game::GetScreenCenter() - Vector2::UNIT_Y * 150;

    const int COUNT = 3; //menu count is set to 2 here since we only have 2 menu items [Alexander]
    MenuItem* pItem;
    Font::SetLoadSize(20, true);
    Font* pFont = resourceManager.Load<Font>("Fonts\\arial.ttf");

    SetDisplayCount(COUNT);

    enum Items { Back, Level_01, Level_02, }; //Considering add a 'back' option to the menu [Alexander]
    std::string text[COUNT] = {"Back", "Level 1", "Level 2" }; // Note to add a 'back' option [Alexander]

    for (int i = 0; i < COUNT; i++)
    {
        pItem = new MenuItem(text[i]);
        pItem->SetPosition(Vector2(100, 100 + 50 * i));
        pItem->SetFont(pFont);
        pItem->SetColor(Color::BLUE);
        pItem->SetSelected(i == 0);
        AddMenuItem(pItem);
    }
	
	GetMenuItem(Back)->SetOnSelect([this]() {
		SetOnRemove([this]() { AddScreen(new MainMenuScreen()); });
		Exit();
		});
    GetMenuItem(Level_01)->SetOnSelect([this]() {
		SetOnRemove([this]() { AddScreen(new GameplayScreen()); });
		Exit();
	    });
	GetMenuItem(Level_02)->SetOnSelect([this]() {
		SetOnRemove([this]() { AddScreen(new GameplayScreen(1)); }); 
		Exit(); //Took an embarrassing amount of time to realize that I needed to add the parameter to the GameplayScreen constructor. Honestly though I'd have to remake the whole thing. [Alexander]
		});
}
// Updates the menu items, changes the color of the text and the offset of the text when it is selected.
// On an unrelated note, I decided to not change anything in this function simply because from a logical standpoint it doesn't make sense to change the look of the menu items
// when compared to the main menu.
void LevelSelectScreen::Update(const GameTime& gameTime)
{
	bool isSelected = false;
	float alpha = GetAlpha();
	float offset = sinf(gameTime.GetTotalTime() * 10) * 5 + 5;

	for (MenuItem* pItem : GetMenuItems())
	{
		pItem->SetAlpha(alpha);
		isSelected = pItem->IsSelected();
		pItem->SetColor(isSelected ? Color::WHITE : Color::BLUE);
		pItem->SetTextOffset(isSelected ? Vector2::UNIT_X * offset : Vector2::ZERO);
	}

	MenuScreen::Update(gameTime);
}

// Draws the logo. This made me want to kill myself because I was originally inheriting from the MainMenuScreen to cut corners.
// A null pointer ended up being created and breaking the game because it was trying to draw the logo from the MainMenuScreen without the texture being loaded.
// That was a nightmare because for whatever reason the error created by the null pointer was being directed in another spot of the code.
// I went through all the stages of grief by the time I discovered the issue. [Alexander]
void LevelSelectScreen::Draw(SpriteBatch& spriteBatch)
{
	spriteBatch.Begin();
	spriteBatch.Draw(m_pTexture, m_texturePosition, Color::WHITE * GetAlpha(), m_pTexture->GetCenter()); 
	MenuScreen::Draw(spriteBatch);
	spriteBatch.End();
}
