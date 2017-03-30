/*
  Trinket 5v (not pro) has a keyboard to create randomized text.
  Ideal as a password generator. 

  Once loaded, give it about 5 to 10 seconds for it to generate
  the randomized texts. 
  
  requires the following adafruit library: 
  https://github.com/adafruit/Adafruit-Trinket-USB/
*/

#include <TrinketKeyboard.h>

void setup()
{
  // start USB stuff 
  TrinketKeyboard.begin();
  randomSeed(millis()); // multiple randomSeeding
  randomSeed(random());
  randomSeed(millis());
  randomSeed(random());
}

void loop()
{
  unsigned long secs_to_wait = random(5, 10); // generate a random amount of time
  unsigned long time_stamp = millis();
  while (millis() < (time_stamp + (secs_to_wait * 1000))) // wait the random amount of time
  {
    TrinketKeyboard.poll();
    randomSeed(millis());
    randomSeed(random());
    // the poll function must be called at least once every 10 ms
    // or cause a keystroke
    // if it is not, then the computer may think that the device
    // has stopped working, and give errors
  }
  TrinketKeyboard.print("=== randomizer ===");
  TrinketKeyboard.typeChar((char)10); // type out a random character (valid ASCII)
  
  int char_matrix[][2] = {
      {48, 57},   // number 48, 57
      {65, 90},   // upper 65, 90
      {97, 122},  // lower 97, 122
      {33, 126}   // full range 33, 126
    };

  for(int y = 0; y < 4; y++) {
    for(int x = 0; x < 32; x++) {
      randomSeed(millis());
      randomSeed(random());

      int matrix_idx = 0;
      if (y < 2) { 
        // first two strings are are simple passwords without special chars
        matrix_idx = random(0,3);
        randomSeed(random());
        TrinketKeyboard.typeChar((char)random(char_matrix[matrix_idx][0], char_matrix[matrix_idx][1]));
      }
      else {
        // last two strings are are complex passwords
        TrinketKeyboard.typeChar((char)random(char_matrix[3][0], char_matrix[3][1]));
      }
    }
    TrinketKeyboard.typeChar((char)10);    
  }

}



