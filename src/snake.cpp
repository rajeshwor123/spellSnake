#include "snake.h"
#include<iostream>
#include <vector>
#include "GLFW/glfw3.h"
#include "prey.h"
#include <Windows.h>

prey p;
snake::snake() : currentKey(GLFW_KEY_UNKNOWN),score(0), collisionOrder(0),boarderCollisionOrder(0),selfCollisionOrder(0),snakeLength(2),indexCountForCurrentLen(0)
    {

    //size = 60 * 8 *sizeof(float);
    size = 0;
    count = 0;
    x[0] = 400.0f;
    y[0] = 280.0f;

    }

const void* snake::vertexData()
{

    for (unsigned int i = snakeLength - 1; i > 0; i-- )
    {
        x[i] = x[i - 1];
        y[i] = y[i - 1];
    }

    if (currentKey == GLFW_KEY_UNKNOWN)
    {

    }
    else if (currentKey == GLFW_KEY_W)
    {
        y[0] = y[0] + 20;
    }
    else if (currentKey == GLFW_KEY_A)
    {
        x[0] = x[0] - 20;
    }
    else if (currentKey == GLFW_KEY_S)
    {
        y[0] = y[0] - 20;
    }
    else if (currentKey == GLFW_KEY_D)
    {
        x[0] = x[0] + 20;
    }

    boarderCollision();

    float* position = new float[snakeLength * 8];
    unsigned int j = 0;
    indexCountForCurrentLen = 0;
    for (unsigned int i = 0; i < snakeLength; i++)
    {
        position[j] = x[i];
        position[j+1] = y[i];
        position[j+2] = x[i] + 20;
        position[j+3] = y[i];
        position[j+4] = x[i] + 20;
        position[j+5] = y[i] + 20;
        position[j+6] = x[i];
        position[j+7] = y[i] + 20;

        indexCountForCurrentLen = indexCountForCurrentLen + 6;
        j = j + 8;
    
    }   

    if(snakeLength >= 3)
        selfCollision();
        
        size = j * sizeof(float);
        return position;
       
    }

    unsigned int* snake::indicesData()
    {
        /*
        static unsigned int indices[] = {
         0,1,2,
         2,3,0
        };
        return indices;
        */

        static unsigned int indices[900];
        unsigned int i = 0;
        unsigned int offset = 0;
        for (int y = 0; y < 150 ; y = y + 1)
        {
            indices[i] = 0 + offset;
            indices[i + 1] = 1 + offset;
            indices[i + 2] = 2 + offset;
            indices[i + 3] = 2 + offset;
            indices[i + 4] = 3 + offset;
            indices[i + 5] = 0 + offset;

            offset = offset + 4;
            i = i + 6;
        }
        count = i;
        return indices;
    }

    void snake::selfCollision()
    {
        for(unsigned int i = 1 ; i < snakeLength ; i++)
        {
           // std::cout << x[0] << "   " << x[i] << std::endl;
           
           if(x[0] == x[i] && y[0] == y[i])
           {
               selfCollisionOrder = 1;
               gameOver();
           }
            
        }
    }

    void snake::boarderCollision()
    {
        if (x[0] < 0.0f || x[0] > 780.0f || y[0] < 0.0f || y[0] > 540.0f)
        {
            boarderCollisionOrder = 1;
            gameOver();
        }
    }
    unsigned int snake::preyCollision()
    {
        if (selfCollisionOrder == 1)
        {
            selfCollisionOrder = 0;
            return 3;
        }
        if(boarderCollisionOrder == 1)
        {
            boarderCollisionOrder = 0;
            return 3;
        }
        if(collisionOrder == 0)
        {
            return collisionOrder;
        }
        else if (collisionOrder == 1 )
        {
            if(snakeLength != 150)
                snakeLength++;
            score = score + 1;
            return collisionOrder;

        }
        else if (collisionOrder == 2)
        {
            if(snakeLength != 150)
                snakeLength++;
            score = score + 1;
            return collisionOrder; //reset random coordinates for case 2
        }

        else if (collisionOrder == 3)
        {
            gameOver();
            return collisionOrder;//reset random coordinates for case 3
        }
        //////////////////////////////////////////////////keeping old collision code just for reference
        /*
        //ranXandy[10] first 5 elements denote x coordinates next 5 ,y coordinates
        if (x[0] == *(ranXandY) && y[0] == *(ranXandY + 10) && collisionOrder == 0)
        {
            collisionOrder = 1;
            snakeLength = snakeLength + 1;
            return collisionOrder;
        }
        else if (x[0] == *(ranXandY + 1) && y[0] == *(ranXandY + 11))
        {
            if (collisionOrder == 1)
            {
                collisionOrder = 2;
                snakeLength = snakeLength + 1;
                return collisionOrder;
            }
            else if(collisionOrder < 1)
            {
                gameOver();
                return 5;
            }
        }
        else if (x[0] == *(ranXandY + 2) && y[0] == *(ranXandY + 12) )
        {
            if (collisionOrder == 2)
            {
                collisionOrder = 3;
                snakeLength = snakeLength + 1;
                return collisionOrder;
            }
            else if (collisionOrder < 2)
            {
                gameOver();
                return 5;
            }
        }
        else if (x[0] == *(ranXandY + 3) && y[0] == *(ranXandY + 13))
        {
            if (collisionOrder == 3)
            {
                collisionOrder = 4;
                snakeLength = snakeLength + 1;
                return collisionOrder;
            }
            else if (collisionOrder < 3)
            {
                gameOver();
                return 5;
            }
        }
        else if (x[0] == *(ranXandY + 4) && y[0] == *(ranXandY + 14))
        {
            if (collisionOrder == 4)
            {
                collisionOrder = 0;
                snakeLength = snakeLength + 1;
                return 5;
            }
            else if (collisionOrder < 4)
            {
                gameOver();
                return 5;
            }
        }
        else return collisionOrder;
        *//////////////////////////////////////////////////////////////////////////////////
    }
    
    void snake::gameOver()
    {
        snakeLength = 2;
        currentKey = GLFW_KEY_UNKNOWN;
        x[0] = 400.0f;
        y[0] = 280.f;
      
        int msgboxID = MessageBox(
            NULL,
            (LPCWSTR)L" Try again",
            (LPCWSTR)L"GAME OVER",
            MB_ICONWARNING | MB_OK | MB_DEFBUTTON2
        );

        score = 0;

    }



