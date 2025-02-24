#pragma once
#include "Rendering.hpp"
#include "Scene.hpp"


/*
  Call as condition for main while loop.
  Returns false when user clicks to exit program.
  Takes user input and adds to keyboardInputs vector.
  Clears keyboardInputs vector every frame.
  Works in combination with reduceFrames() to handle FPS control.
  Call before all main logic/rendering functions.
*/
bool handleEvents();


/*
  Only works if handleEvents() is called before this function,
  and if this function is called after main game logic/rendering functions.
  Reduces the framerate to match the desired frames per second.
*/
bool reduceFrames(Uint32 desiredFPS);
