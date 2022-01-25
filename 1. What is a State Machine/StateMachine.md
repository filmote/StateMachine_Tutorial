# Overview

What on earth is a StateMachine and why do I want to build one?

These are two great questions and in this tutorial I will show how to build a state machine and explain why it is critical to building anything more than even the simplest game on the Arduboy platform.

Think about how most games are structured.  You start on a title screen and select to play the game.  While playing the game, you may select to view your inventory before battling a monster.  If your battle is unsuccessful, you progress to a game over screen and maybe even are allowed to enter your details on a high score screen.  Each of these 'screens' - the title screen, game play screen, inventory screen, game over screen and high score screen - are states in the game.  The execution of code progresses from one state to another (and sometimes back again!) in response to the user's actions.

Even if your code is totally unstructured, you have probably already built a number of states into a game you have written without even realising it.

In this tutorial, I will present a structured approach to building a state machine that is scaled (downwards!) to the Arduboy.  Splitting code logically into separate states will help you segregate code making it easier to follow and maintain.
  


## Creating a State

To keep it simple, our sample program will start with two states - a title and a game play screen.  Later you will add a third screen, a high score screen, and add the plumbing for the user to move between the states.


Reviewing the code, you will see two functions that relate to the title screen, `title_Init()` and `title()`, and two more that handle the game play, `playGame_Init()` and `playGame()`.  The function declarations for the game play screen are shown below for reference.

```cpp
void playGame_Init() {
  
  // Initialise variables and get ready for the state ..

}

void playGame() {

  // Handle the users actions and render the screen ..

}
```

As you can see, each state has two basic functions.  

The one suffixed with `_Init` is called as the program transitions into that state and can be used to initialise variables before the actual state is executed.  This is similar in concept to the Arduino's `setup()` however it is executed every time we transition into the state.

The second function is executed continually after the initial invocation of the `_Init` function is called.  Again, this is analogous to the `loop()` function of every Arduino program.

An example of the use of these functions is shown below.  The `lives` and `score` variables are initialised in before game play has begun.

```cpp
void playGame_Init() {
  
  score = 0;
  lives = 3;

}

void playGame() {

  if (touchingEnemy()) lives--;
  if (touchingGold())  score++;

}
```

Our state functions are really simple, but how do we string them together?

## Creating the State Engine

We need to track the current state as the program progresses from screen to screen.  This can be achieved using an `enum` as shown below.  

```cpp
enum GameState {
  Title_Init,
  Title,
  PlayGame_Init,
  PlayGame,
};

GameState gameState = GameState::Title_Init;
```

You will notice that I have kept the state names the same as the function names that we declared earlier.  

The variable that is going to track our current state, `gameState`, is initially set to `GameState::Title_Init` as this is the first screen we want the player to see.

We can now use this variable in our `loop()` to control which state to show.


```cpp
void loop() {

  ...
  
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

  ...

}
```

What is that `[[fallthrough]]` I hear you ask?  Well, in Arduino-land it does nothing.  Huh?  After executing the `Title_Init` state we want the `Title` state to execute immediately.  Had we put a `break` in place of the `[[fallthrough]]`, the code would wait until the next iteration of the loop to execute the `Title` state which may cause the screen to not be rendered, resulting in a black screen for a moment,

I could have omitted the `[[fallthrough]]` line altogether and the code will work the same.  You will notice that the compiler warns you that there is a potential issue with the code falling through - even though in this case we want that behaviour.  The Arduino compiler uses C++ 11 - quite an old version - however in later versions of C++, 17 or greater, this statement will suppress the warning.  I like to leave it in the code as it reminds me that I left the `break` statement off intentionally!

The progression between the states is performed within the states themselves.

As you can see below, in addition to any other work the `_Init()` function does the `gameState` must be updated to the next state name otherwise it will repeat the initialisation forever.  In the 'main' state function, `title()`, we react to the player pressing a button to start the game and changing the `gameState` variable to the initialisation state `GameState::PlayGame_Init`.

```cpp
void title_Init() {
  
  ...
  gameState = GameState::Title;

}

void title() {

  if (arduboy.justPressed(A_BUTTON)) {
    gameState = GameState::PlayGame_Init;
  }

}
```

So let's add a High Score state!

> Your Turn:<br/><br/>
> Add a new state called High Scrore to the program.  To do this, you will need to add two functions `highScore_Init()` and `highScore()`.  You will then need to add the states to the `GameState` enum and change the `loop()` to accommodate these extra states.<br/><br/>
> From the title screen, detect the player pressing the B button and move directly to the high score screen.  From the game play screen, pressing A should take you to the new high score screen, not the title.  Finally, pressing A from the high score screen should return you to the title screen.

Hopefully, this simple tutorial has shown you how to construct a simple state machine that will make structuring your next epic game easier!

In the next topic, we will look at a simple way to organise state specific variables.