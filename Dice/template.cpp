#define UP    0
#define DOWN  1
#define FORE  2
#define BACK  3
#define RIGHT 4
#define LEFT  5

struct Dice
{
  int face[6];
  Dice(){}
  Dice(int up, int down, int fore, int back, int right, int left)
  {
    face[UP] = up; face[DOWN] = down;
    face[FORE]  = fore; face[BACK] = back;
    face[RIGHT] = right; face[LEFT] = left;
  }  
  void roll(int a, int b, int c, int d) {
    swap(face[a], face[c]);
    swap(face[b], face[d]);
    swap(face[c], face[d]);
  }
  void roll2fore() { roll(FORE, BACK, UP, DOWN); }
  void roll2back() { roll(BACK, FORE, UP, DOWN); }  
  void roll2right() { roll(RIGHT, LEFT, UP, DOWN); }
  void roll2left() { roll(LEFT, RIGHT, UP, DOWN); }
  void rotate_clockwise() { roll(FORE, BACK, RIGHT, LEFT); }
  void rotate_counterclockwise() { roll(FORE, BACK, LEFT, RIGHT); }
  void print_face()
  {
    printf("UP   : %d\n", face[UP]);
    printf("DOWN : %d\n", face[DOWN]);
    printf("FORE : %d\n", face[FORE]);
    printf("BACK : %d\n", face[BACK]);
    printf("RIGHT: %d\n", face[RIGHT]);
    printf("LEFT : %d\n", face[LEFT]);
  }
};

