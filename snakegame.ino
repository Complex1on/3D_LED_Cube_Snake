#include "Snake.h"

Snake snake;

void setup(){
  
}

void loop()
{
  snake.start();
  while (!snake.isDead())
  {
    snake.update();
  }
  snake.reset();      
}
