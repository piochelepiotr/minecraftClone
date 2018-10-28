#include "gameState.h"

GameState::GameState() : m_paused(false)
{

}

GameState::~GameState()
{
}

void GameState::pause()
{
    m_paused = true;
}

void GameState::play()
{
    m_paused = false;
}

