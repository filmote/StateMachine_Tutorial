#include <Arduboy2.h>
Arduboy2 arduboy;

enum GameState {
  Title_Init,
  Title,
  PlayGame_Init,
  PlayGame,
};

struct TitleScreenVars {

  int8_t counter = 0;

};


TitleScreenVars titleScreenVars;
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

  titleScreenVars.counter = 26;
  gameState = GameState::Title;

}

void title() {

	// Handle input ..

	if (arduboy.justPressed(A_BUTTON)) {
    gameState = GameState::PlayGame_Init;
	}


  // Update Counter ..

  titleScreenVars.counter++;

  if (titleScreenVars.counter == 127) {

    titleScreenVars.counter = -127;

  }


  // Render screen ..

  arduboy.setCursor(titleScreenVars.counter, 20);
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
    gameState = GameState::PlayGame_Init;
	}


  // Render screen ..

  arduboy.setCursor(32, 30);
  arduboy.print(F("Play Game!"));

}