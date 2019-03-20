#include "InputHandler.h"

InputHandler::InputHandler()
{
  pinMode(START, INPUT);
  pinMode(UP, INPUT);
  pinMode(DOWN, INPUT);
  pinMode(LEFT, INPUT);
  pinMode(RIGHT, INPUT);
}

void InputHandler::init()
{
  dir = prevDir = lastButtonPressed = xpos;
  timeOfUpRelease = timeOfDownRelease = 0;
  released = true;
}

bool InputHandler::startPressed()
{
  return digitalRead(START) ? true : false;
}

void InputHandler::update()
{
  if (digitalRead(UP))
  {
    // Detect double up press
    if (prevDir != zneg && lastButtonPressed == ypos && (millis() - timeOfUpRelease < 150))
    {
      dir = zpos;
    }
    // Prevent direction switch if a double up press just occurred
    else if (prevDir != yneg && (dir != zpos || (millis() - timeOfUpRelease > 400)))
    {
      dir = ypos;
    }
    lastButtonPressed = ypos;
    released = false;
  }
  else if (digitalRead(DOWN))
  {    
    // Detect double down press
    if (prevDir != zpos && lastButtonPressed == yneg && (millis() - timeOfDownRelease < 150))
    {
      dir = zneg;
    }
    // Prevent direction switch if a double down press just occurred
    else if (prevDir != ypos && (dir != zneg || (millis() - timeOfDownRelease > 400)))
    {
      dir = yneg;
    }
    lastButtonPressed = yneg;
    released = false;
  }
  else if (digitalRead(RIGHT))
  {    
    if (prevDir != xneg)
    {
      dir = xpos;
    }
    lastButtonPressed = xpos;
    released = false;
  }
  else if (digitalRead(LEFT))
  {    
    if (prevDir != xpos)
    {
      dir = xneg;
    }
    lastButtonPressed = xneg;
    released = false;
  }
  // Detect up or down button releases
  else if (!released)
  {
    if (lastButtonPressed == ypos)
    {
      timeOfUpRelease = millis();
    }
    else if (lastButtonPressed == yneg)
    {
      timeOfDownRelease = millis();
    }
    released = true;
  }
}
