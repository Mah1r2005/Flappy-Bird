#include "iGraphics.h"
#include <bits/stdc++.h>


Image img;

Image frames[1];
Sprite sprite;

/*
function iDraw() is called again and again by the system.
*/

bool game=0;
bool start_game=0;
bool homepage=1;
bool highscore=0;
bool credit=0;
bool gameover=0;

double obstacle_diff=400;
double obstacle_gap=170;
double width=70;
int score=0;


double x[]={1000,1000+obstacle_diff+width,1000+2*(obstacle_diff+width)};
double y[]={350,200,300};
double height[]={500-y[0],500-y[1],500-y[2]};

int speed=10;

void loadResources()
{
   iInitSprite(&sprite, 0xFFFFFF);
   iLoadFramesFromFolder(frames, "pakhi");
   iChangeSpriteFrames(&sprite, frames, 1);
   iSetSpritePosition(&sprite, 420 , 230);
}

void iDraw()
{
    // place your drawing codes here
    iShowImage(0, 0, "background.png");
    iShowLoadedImage(0, 0, &img);
    if(homepage){
	iSetColor(255, 0, 0);
    iTextAdvanced(380, 360, "Start Game",.33, 1.0);
    iTextAdvanced(380, 300, "High Scores",.33, 1.0);
    iTextAdvanced(440, 240, "Credit",.33, 1.0);
    iTextAdvanced(460, 180, "Exit",.33, 1.0);
    }

    if(start_game){
        //upper
        iSetColor(80, 200, 120);
        iFilledRectangle(x[0], y[0], width, height[0]);
        iFilledRectangle(x[1], y[1], width, height[1]);
        iFilledRectangle(x[2], y[2], width, height[2]);
        //lower
        iFilledRectangle(x[0], 0, width, 500-height[0]-obstacle_gap);
        iFilledRectangle(x[1], 0, width, 500-height[1]-obstacle_gap);
        iFilledRectangle(x[2], 0, width, 500-height[2]-obstacle_gap);

    }

     if(game || start_game){
        iShowSprite(&sprite);
        iSetColor(255, 0, 0);
        char str[4];
        sprintf(str,"Score: %d", score);
        iTextAdvanced(900,480,str,.15, 1.0);
    }

   if(game && !start_game){
     iTextAdvanced(175, 180, "Tap anywhere to start the game",.33, 1.0);
   }

   if(gameover){
     iTextAdvanced(225, 300, "GAME OVER",.66, 1.0);
     iTextAdvanced(400, 200, "Restart",.33, 1.0);
     iTextAdvanced(380, 140, "Main page",.33, 1.0);
     iTextAdvanced(440, 80, "Exit",.33, 1.0);
   }
}


/*
function iMouseMove() is called when the user moves the mouse.
(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my)
{    //printf("x = %d, y = %d\n", mx, my);
    // place your codes here
}

/*
function iMouseDrag() is called when the user presses and drags the mouse.
(mx, my) is the position where the mouse pointer is.
*/
void iMouseDrag(int mx, int my)
{

}

/*
function iMouse() is called when the user presses/releases the mouse.
(mx, my) is the position where the mouse pointer is.
*/


void iMouse(int button, int state, int mx, int my)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if(start_game){
            sprite.y+=50;
        }

       if(game){
          start_game=1; game=0;
        }

        if(homepage){
        if(mx>=380 && mx<=620 && my>=357 && my<=390 ){game=1; homepage=0;}
        if(mx>=380 && mx<=637 && my>=295 && my<=339 ){highscore=1; homepage=0;}
        if(mx>=437 && mx<=558 && my>=235 && my<=273 ){credit=1; homepage=0;}
        if(mx>=460 && mx<=528 && my>=176 && my<=220 ){exit(0);}
        }




    }
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        // place your codes here
    }
}

/*
function iMouseWheel() is called when the user scrolls the mouse wheel.
dir = 1 for up, -1 for down.
*/
void iMouseWheel(int dir, int mx, int my)
{
    // place your code here
}

/*
function iKeyboard() is called whenever the user hits a key in keyboard.
key- holds the ASCII value of the key pressed.
*/
void iKeyboard(unsigned char key)
{
    switch (key)
    {
    case 'q':
        // do something with 'q'
        break;
     case ' ':
        if(game){start_game=1; game=0;}
        if(start_game){sprite.y+=50;}
        break;
    default:
        break;
    }
}

/*
function iSpecialKeyboard() is called whenver user hits special keys likefunction
keys, home, end, pg up, pg down, arraows etc. you have to use
appropriate constants to detect them. A list is:
GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11,
GLUT_KEY_F12, GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN,
GLUT_KEY_PAGE_UP, GLUT_KEY_PAGE_DOWN, GLUT_KEY_HOME, GLUT_KEY_END,
GLUT_KEY_INSERT */
void iSpecialKeyboard(unsigned char key)
{
    switch (key)
    {
    case GLUT_KEY_END:
        exit(0);
        break;
    default:
        break;
    }
}

void obstacle(){
  //upper obstacle;
  if(start_game){
  sprite.y-=20;

  x[0]-=speed+(score/10)*10;
  x[1]-=speed+(score/10)*10;
  x[2]-=speed+(score/10)*10;

  if(x[0]+obstacle_diff<=0){x[0]=1000; y[0]=rand()%200+200; height[0]=500-y[0];}
  if(x[1]+obstacle_diff<=0){x[1]=x[0]+obstacle_diff+width; y[1]=rand()%200+200; height[1]=500-y[1];}
  if(x[2]+obstacle_diff<=0){x[2]=x[1]+obstacle_diff+width; y[2]=rand()%200+200; height[2]=500-y[2];}

   int temp=sprite.y;
   if(x[0]<=515 && x[0]+width>=420){
    if(temp>=y[0]-60||temp<=500-height[0]-obstacle_gap-10){gameover=1; start_game=0;}
    else{if(x[0]+speed+(score/10)*10>=515){score++;}}
   }
    else if(x[1]<=515 && x[1]+width>420){
        if(temp>=y[1]-60||temp<=500-height[1]-obstacle_gap-10){gameover=1; start_game=0;}
        else{if(x[1]+speed+(score/10)*10>=515){score++;}}
    }
    else if(x[2]<=515 && x[2]+width>420){
        if(temp>=y[2]-60||temp<=500-height[2]-obstacle_gap-10){gameover=1; start_game=0;}
        else{if(x[2]+speed+(score/10)*10>=515){score++;}}
    }

    if(sprite.y<=0){gameover=1; start_game=0;}

  }
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    // place your own initialization codes here.
    loadResources();
    iSetTimer(1,obstacle);

    iInitialize(1000, 500, "Flappy Bird");
    return 0;
}
