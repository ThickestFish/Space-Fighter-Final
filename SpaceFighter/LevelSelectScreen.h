#pragma once
#include "KatanaEngine.h"

class LevelSelectScreen : public MainMenuScreen
{
public:
    LevelSelectScreen() {} // Constructor for LevelSelectScreen

    virtual void LoadContent(ResourceManager& resourceManager);

	/** @brief Unload the content for the screen. */
	virtual void Update(const GameTime& gameTime);

	/** @brief Render the screen.
		@param spriteBatch A reference to the game's sprite batch, used for rendering. */
	virtual void Draw(SpriteBatch& spriteBatch);
};