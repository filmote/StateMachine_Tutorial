#include <Arduboy2.h>
Arduboy2 arduboy;

enum GameState {
  Title_Init,
  Title,
  PlayGame_Init,
  PlayGame,
};

GameState gameState = GameState::Title_Init;

void setup() {

  arduboy.boot();
  gameState = GameState::Title_Init; 

}

void loop() {

  if (!arduboy.nextFrame()) return;
  arduboy.pollButtons();
  arduboy.clear();

  switch (gameState) {

    case GameState::Title_Init:
      title_Init();
      [[fallthrough]]

    case GameState::Title:
      title();
      break;

    case GameState::PlayGame_Init: 
      playGame_Init();
      [[fallthrough]]

    case GameState::PlayGame: 
      playGame();
      break;

    default: break;  

  }

  arduboy.display();

}

// ----------------------------------------------------------------------------
//  Title state ..
//
void title_Init() {

  gameState = GameState::Title;

}

void title() {

  // Handle input ..

  if (arduboy.justPressed(A_BUTTON)) {
    gameState = GameState::PlayGame_Init;
  }

  // Render screen ..

  arduboy.setCursor(26, 20);
  arduboy.print(F("Title Screen!"));

  arduboy.setCursor(43, 40);
  arduboy.print(F("Press A"));

}


// ----------------------------------------------------------------------------
//  Game state ..
//
void playGame_Init() {

  gameState = GameState::PlayGame;

}

void playGame() { 

  // Handle input ..

  if (arduboy.justPressed(A_BUTTON)) {
    gameState = GameState::Title_Init;
  }


  // Render screen ..

  arduboy.setCursor(32, 30);
  arduboy.print(F("Play Game!"));

}