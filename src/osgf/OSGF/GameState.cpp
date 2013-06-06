#include "GameState.h"
#include "Game.h"
void GameState::Render()const
{
	mGame.ClearColorDephtStencil(mClearColor,mClearDepthValue,
		mClearStencilValue);
	
}
