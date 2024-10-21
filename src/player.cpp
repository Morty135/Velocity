#include "player.h"



player::player()
{
    playerSprites[0] = LoadTexture("resources/runAnim.png");
    defaultGravity = gravity;
}



player::~player()
{
    UnloadTexture(playerSprites[0]);
}


void player::draw()
{
    if(IsKeyDown(KEY_A))
    {
        if(velocity.x >= -maxVelocity.x)
        {
            velocity.x -= movementSpeed * GetFrameTime();
        }
    }
    if(IsKeyDown(KEY_D))
    {
        if(velocity.x >= maxVelocity.x)
        {
            velocity.x -= movementSpeed * GetFrameTime();
        }
        velocity.x += movementSpeed * GetFrameTime();
    }
    else
    {
        if(velocity.x > 0.1)
        {
            velocity.x -= horizontalDampening;
        }
        else if(velocity.x < -0.1)
        {
            velocity.x += horizontalDampening;
        }
        else
        {
            velocity.x = velocity.x;
        }
    }
    


    if(IsKeyDown(KEY_SPACE) && groundCheck == true)
    {
        velocity.y += -jumpForce;
    }

    position.x += velocity.x;
    position.y += velocity.y;

    collisonRec = {position.x-32, position.y - 64 ,64,128};

    DrawRectangleRec(collisonRec, {0,0,0,100});
    playerAnimator();
}



void player::collisionCheck(Rectangle * envRecs, int envRecsLenght)
{
    int colRecs = 0;
    for (int i = 0; i < envRecsLenght; i++)
    {
        Rectangle envRec = envRecs[i];
        if (CheckCollisionRecs(collisonRec, envRec))
        {
            colRecs++;
        }
    }
    if(colRecs > 0)
    {
        groundCheck = true;
        velocity.y = 0;
        gravity = 0;
    }
    else
    {
        groundCheck = false;
        if(velocity.y <= maxVelocity.y)
        {
            velocity.y += gravity;
        }
        gravity = defaultGravity;
    }
}


float frameTime = 0;
int i;

void player::playerAnimator()
{
    float spriteWidth = (float)playerSprites[0].width/8;
    Rectangle frameRec = { 0.0f, 0.0f, spriteWidth, 32.0f};
    std::cout << playerSprites[0].format;


    frameTime +=  17 * GetFrameTime();

    if(frameTime > 1)
    {
        frameTime = 0;
        i++;
    }
    if(velocity.x < 0)
    {
        frameRec = { 0.0f + spriteWidth * i, 0.0f, -spriteWidth, 32.0f};
    }
    else
    {
        frameRec = { 0.0f + spriteWidth * i, 0.0f, spriteWidth, 32.0f};
    }

    Rectangle destRec = { position.x, position.y, frameRec.width * playerSize, frameRec.height * playerSize };

    Vector2 origin = {32.0f, 64.0f };
    DrawTexturePro(playerSprites[0], frameRec, destRec, origin, 0.0f, WHITE);
}