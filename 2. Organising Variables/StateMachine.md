# Overview

In this section, we will look at how to organise variables in our state machine.  

As your games grow in complexity, you will invariably end up with numerous variables to support the various aspects (states!) of your game. It might not sound like much, but naming and remembering all the variable names you create can be quite arduous.  

This simple tutorial uses simple `structs` to group variables for a class together. When using the variables, the struct name is used to qualify them making it possible to have the same variable - such as a simple counter - available in each state with the same name but be independent of each other.


## Defining a Structure for a State

If you haven't already used a `struct` before, it is a simple way to group a bunch of related variables together. But as you will see later, we can add functions to the `struct` itself that operate on the variables within.

Below is a simple structure for a title screen.  As you can see it is rather unimpressive with a single `counter` variable. 

```cpp

struct TitleScreenVars {

  int8_t counter = 0;

};

TitleScreenVars titleScreenVars;

```

After the `struct` definition, we then define a variable using the structure type.  From then on, we can refer to the structure's variables using the following syntax:

```cpp
TitleScreenVars titleScreenVars;
titleScreenVars.counter = 5;

```

We can define structures for all our states.  The example below shows a struct with a few more variables - including one named `counter` which is a different variable to the one in the `TitleScreenVars` structure despite the same name.

```cpp
struct GamePlayVars {

  uint8_t counter = 0;
  uint8_t score = 0;
  uint8_t lives = 0;

  void reset() {
    score = 0;
    lives = 3;
  }
  
};
```

As mentioned earlier, we can add functions to the structure which can operate on the variables contained within.  For example, a `reset()` function will set our score and lives to the values we want at the start of a game.

```cpp
struct GamePlayVars {

  uint8_t counter = 0;
  uint8_t score = 0;
  uint8_t lives = 0;

  void reset() {
    score = 0;
    lives = 3;
  }
  
};
```

## Using the Structure Variables

To demonstrate how to use the structure variable, the title state from the previous section has been modified so that the words 'Title Screen!' will scroll left to right and wrap around the screen again.  This will be controlled by increasing the `counter` variable within the structure.

As we discussed in the previous section, we can use the `_Init()` function to initialise variables with default values prior to executing the state code. To ensure that the words start in the centre of the screen when the state is first displayed, the `counter` is set to `26` which, considering the length of the text to display, places it in the centre of the screen.

```cpp
void title_Init() {

  titleScreenVars.counter = 26;
  gameState = GameState::Title;

}
```

In our main state function, we simply increase the `counter` variable of the `titleScreenVars` structure using the qualified name (`titleScreenVars.counter`) and use it to position the text.

```cpp
void title() {

  ...

  // Update Counter ..

  titleScreenVars.counter++;

  if (titleScreenVars.counter == 127) {

    titleScreenVars.counter = -127;

  }


  // Render screen ..

  arduboy.setCursor(titleScreenVars.counter, 20);
  arduboy.print(F("Title Screen!"));

  ...

}
```
Simple right? 

Believe me, when you are building the next CyberPunk game you will need little tricks like this to help keep your sanity.

> Your Turn: <br/>
> Copy the `GamePlayVars` structure definition from above and add it to the program below the existing structure definition.  In the game play state, reset the variables in the `_Init()` function.  Increase the score continually in the main state function and render it on screen.

