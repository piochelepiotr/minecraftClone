#ifndef GAME_STATE_H
#define GAME_STATE_H

class GameState
{
  public:
    GameState();
    ~GameState();
    void pause();
    void play();
    bool isPaused() const { return m_paused; }

  private:
    bool m_paused;
};

#endif // GAME_STATE_H
