#include "Snake.h"

Snake::Snake()
{
  // Start from a known state
  reset();
}

void Snake::start()
{
  while (!io.startPressed())
  {
    int x = random(0,4);
    int y = random(0,4);
    int z = random(0,4);
    cube.bufferLED(x,y,z);
    cube.display();
    cube.clearBuffer();
  }
  init();
}

void Snake::update()
{
  io.saveDir();
  // Repeat the display and input polling for the duration of one frame
  unsigned long startTime = millis();
  unsigned long elapsed = 0;
  int blinkCounter = 0;
  while (elapsed < frameTime)
  {
    // Blink the food LED every 10 updates
    if (blinkCounter++ % 10 == 0)
    {
      cube.toggleLED(food.x, food.y, food.z);
    }
    cube.display();
    io.update();
    elapsed = millis() - startTime;
  }
  // Reset the buffer and prepare data for the next frame
  cube.clearBuffer();
  logic();

  // If the snake dies, pause the display before ending the game
  if (dead)
  {
    cube.bufferFromMatrix(m);
    cube.bufferLED(food.x, food.y, food.z);
    startTime = millis();
    elapsed = 0;
    while (elapsed < 1000)
    {
      cube.display();
      elapsed = millis() - startTime;
    }
  }
}

void Snake::reset()
{
  snake.clear();
  cube.reset();

  // Reset the map matrix
  for (byte x = 0; x < 4; x++)
  {
    for (byte y = 0; y < 4; y++)
    {
      for (byte z = 0; z < 4; z++)
      {
        m[x][y][z] = 0;
      }
    }
  }
}

void Snake::init()
{
  // Disable any active LEDs
  cube.reset();
  
  // Init runtime variables
  io.init();
  dead = false;
  frameTime = 500;
  
  // Init snake location
  snake.push_front({0, 0, 0});
  m[snake.front().x][snake.front().y][snake.front().z] = 1;
  
  // Spawn a food
  generateFood();
  
  // Illuminate the snake and food LEDs
  cube.bufferFromMatrix(m);
}

void Snake::logic()
{
  int snakesize = snake.size();
  Coord newhead;
  //Take the snake deque 
  //move the head based on the direction
  //remove the back every tick

  //If eat a food
  // add to head of snake????
  // generate new food some place else
  
  
  if( io.getDir() == xpos ) {
    newhead.x = (snake.at(0)).x + 1;
    newhead.y = (snake.at(0)).y;
    newhead.z = (snake.at(0)).z;
  }
  if( io.getDir() == xneg ) {
    newhead.x = (snake.at(0)).x - 1;
    newhead.y = (snake.at(0)).y;
    newhead.z = (snake.at(0)).z;
  }
  if( io.getDir() == ypos ) {
    newhead.x = (snake.at(0)).x;
    newhead.y = (snake.at(0)).y + 1;
    newhead.z = (snake.at(0)).z;
  }
  if( io.getDir() == yneg ) {
    newhead.x = (snake.at(0)).x;
    newhead.y = (snake.at(0)).y - 1;
    newhead.z = (snake.at(0)).z;
  }
  if( io.getDir() == zpos ) {
    newhead.x = (snake.at(0)).x;
    newhead.y = (snake.at(0)).y;
    newhead.z = (snake.at(0)).z + 1;
  }
  if( io.getDir() == zneg ) {
    newhead.x = (snake.at(0)).x;
    newhead.y = (snake.at(0)).y;
    newhead.z = (snake.at(0)).z - 1;
  }
  
  
  
  if(newhead.x == food.x && newhead.y == food.y && newhead.z == food.z){
    snake.push_front(newhead);
    generateFood();
  }
  else{
    snake.push_front(newhead);
    snake.pop_back();
  }
  for(int i = 0; i < snakesize; i++){
    cube.bufferLED((snake.at(i)).x, (snake.at(i)).y, (snake.at(i)).z);
  }
   
  cube.display();

  
}

void Snake::generateFood()
{
  // Find an available slot for the food

  //NEED to RANDOMLY assign a spot that's not the starting spot of the snake
  int x = random(0,4);
  int y = random(0,4);
  int z = random(0,4);
  food.x = x;
  food.y = y;
  food.z = z;
}
