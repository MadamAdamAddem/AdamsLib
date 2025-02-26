#pragma once
#include "Rendering.hpp"
#include "Scene.hpp"

struct Mouse
{

  int x = 0, y = 0;
  int prevX = 0, prevY = 0;
  bool isPressed = false;

}typedef Mouse;


/*
  Call as condition for main while loop.
  Returns false when user clicks to exit program.
  Takes user input and adds to keyboardInputs vector.
  Clears keyboard and mouse vectors every frame.
  Works in combination with reduceFrames() to handle FPS control.
  Call before all main logic/rendering functions.
*/
bool handleEvents();


/*
  Only works if handleEvents() is called before this function,
  and if this function is called after main game logic/rendering functions.
  Reduces the framerate to match the desired frames per second.
  Returns number of ms of lag over the desired frametime, 0 if running perfectly fine
*/
Uint32 reduceFrames(Uint32 desiredFPS);

extern Mouse mouse;
extern bool takeTextInput;
