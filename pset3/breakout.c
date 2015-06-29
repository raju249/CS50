//
// breakout.c
//
// Computer Science 50
// Problem Set 3
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include <spl/gevents.h>
#include <spl/gobjects.h>
#include <spl/gwindow.h>

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// brick width and height
#define BRICK_WIDTH 40
#define BRICK_HEIGHT 10

// paddle height and width
#define PADDLE_HEIGHT 10
#define PADDLE_WIDTH 60

// space between bricks in pixels
#define BRICK_SPACE 4

// lives
#define LIVES 3

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);
void reverse(double *vel);

int main(void)
{
    
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;

    // keep playing until game over
    
    // moving the ball
    waitForClick();
    double magnitude = (drand48() + 1) / 50;
    int direction = (rand() % 2) * 2 - 1;
	double velocity_x = direction * magnitude;
	double velocity_y = .05;
	
    while (lives > 0 && bricks > 0)
    {
        // TODO
        // handling the mouse event
        GEvent event = getNextEvent(MOUSE_EVENT);

        // if we heard one
        if (event != NULL)
        {
            
            // if the event was movement
            if (getEventType(event) == MOUSE_MOVED)
            {
                // ensure circle follows top cursor
                double x = getX(event) - PADDLE_WIDTH / 2;
                setLocation(paddle, x, HEIGHT - 50);
            }
            if (getX(paddle) + PADDLE_WIDTH >= WIDTH)
            {
                setLocation(paddle,WIDTH - PADDLE_WIDTH,HEIGHT - 50);
            }
            if (getX(paddle) <= 0)
            {
                setLocation(paddle, 0, HEIGHT - 50);
            }
        }
        // moving the ball and updating its positon
        move(ball, velocity_x, velocity_y);
        
        // detecting collisions between ball and window
        if (getX(ball) + getWidth(ball) >= WIDTH)
        {
            reverse(&velocity_x);
        }
        else if (getY(ball) + getWidth(ball) >= HEIGHT)
        {
            lives--;
            waitForClick();
			if (lives == 0)
			{
			    GLabel label = newGLabel("Game Over");
                setFont(label, "Calibri-40");
                setLocation(label,WIDTH / 4, HEIGHT / 2  + 10);
	            setColor(label, "RED");
                add(window, label);
                pause(2000);
                closeGWindow(window);
			}
			setLocation(ball, WIDTH / 2 - RADIUS, HEIGHT / 2 - RADIUS);
		    setLocation(paddle, getX(paddle), HEIGHT - 50);
		    
			
        }
        else if (getY(ball) <= 0)
        {
            reverse(&velocity_y);
        }
        else if (getX(ball) <= 0)
        {
            reverse(&velocity_x);
        }
        
        // checking collision between ball and bricks OR paddle
        // check for ball hitting the paddle
        GObject collisionObject = detectCollision(window, ball);  
        
		/// check for ball hitting bricks
		if (collisionObject != NULL && strcmp(getType(collisionObject), "GRect") == 0)
        {
            reverse(&velocity_y);
            if (collisionObject != paddle)
            {
                removeGWindow(window, collisionObject);
                bricks--;
                points++;
                updateScoreboard(window, label, points);
                
            }
        }
        
    }

    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    // TODO
    // drawing bricks
    
    string colour[5] = {"RED", "ORANGE", "CYAN", "GREEN", "BLUE"};
    int offset = 30;
    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLS; j++)
        {
            GRect rect = newGRect((BRICK_SPACE + j*(BRICK_SPACE + BRICK_WIDTH)), (BRICK_SPACE + i*(BRICK_SPACE + BRICK_HEIGHT) + offset),BRICK_WIDTH,BRICK_HEIGHT);
            setFilled(rect, true);
            setColor(rect, colour[i]);
            add(window, rect);
        }
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    // TODO
    // draws the ball at the center of the window
    GOval oval = newGOval(WIDTH / 2 - RADIUS, HEIGHT / 2 - RADIUS ,RADIUS*2, RADIUS*2);
    setFilled(oval, true);
    setColor(oval, "BLACK");
    add(window, oval);
    return oval;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    // TODO
    // paddle at the center
    GRect rect = newGRect(WIDTH / 2 - PADDLE_WIDTH/2, HEIGHT - 50, PADDLE_WIDTH, PADDLE_HEIGHT);
    setFilled(rect, true);
    setColor(rect, "BLACK");
    add(window, rect);
    return rect;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    // TODO
    GLabel label = newGLabel("0");
    setFont(label, "Calibri-40");
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
	setColor(label, "GRAY");
    add(window, label);

    return label;
    
}

/**
 * reverses the direction of the ball 
 */
void reverse(double *vel)
{
    *vel *= -1;
    return;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
