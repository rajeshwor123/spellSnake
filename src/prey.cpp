#include "prey.h"
#include "snake.h"
#include<iostream>
#include<fstream>
#include <string>
#include<map>

prey::prey() : collisionOrder(0) , indexCount(0)
{
    ranWordLength = 0;
    coordinatesToBeRemoved[0] = 800.0f;
    coordinatesToBeRemoved[1] = 800.0f;
    randomCoordinates[0] = 0;
    indexOrder[0] = 0;
    size = 80 * sizeof(float);
    count = 6;
    spriteWidth = 1 / 26.0f;
    int count = 0;
    char j = 'a';
    for (char i = 'A'; i <= 'Z'; i++)
    {
        charMap[i] = count;
        charMap[j] = count;
        count++;
        j++;
    }

}

const void* prey::vertexData()
{
    /*
    static float positions1[] = {
         x,  y,               0.0f,  0.0f,
         x + 20, y,           (1 / 26.0f), 0.0f,
         x + 20, y + 20,      (1 / 26.0f), 1.0f,
         x, y + 20,           0.0f,  1.0f
    };
    */
    float x;
    float y;
    static float positions[80];
    int textureOffset = 0;
    unsigned int objCount = 0;
    int vertexOffset = 20;

    for(int i = 0 ; i < 80; i = i + 16 )
    {
        if(coordinatesToBeRemoved[0] == randomCoordinates[objCount] && coordinatesToBeRemoved[1] == randomCoordinates[objCount+10])
        {
            x = 0;
            y = 0;
            vertexOffset = 0;
        }
        else
        {
            x = randomCoordinates[objCount];
            y = randomCoordinates[objCount + 10];
            vertexOffset = 20;
            textureOffset = indexOrder[objCount];
        }
        
        /*
        if (collisionOrder < objCount+1)
        {
            x = randomCoordinates[objCount];
            y = randomCoordinates[objCount+10];
            vertexOffset = 20;
        }
        else
        {
            x = 0;
            y = 0;
            vertexOffset = 0;
        }
        */
        positions[i+0] =x ;
        positions[i+1] =y ;
        positions[i+2] = spriteWidth * textureOffset;
        positions[i+3] = 0.0f;
        positions[i+4] = x+vertexOffset;
        positions[i+5] = y;
        positions[i+6] = (spriteWidth * textureOffset) + spriteWidth;
        positions[i+7] = 0.0f;
        positions[i+8] =x+vertexOffset ;
        positions[i+9] = y+vertexOffset;
        positions[i+10] = (spriteWidth * textureOffset) + spriteWidth;
        positions[i+11] = 1.0f;
        positions[i+12] = x;
        positions[i+13] = y+vertexOffset;
        positions[i+14] = spriteWidth * textureOffset;
        positions[i+15] = 1.0f;

        objCount++;
        //textureOffset++;
        
    }
return positions;

}
unsigned int* prey::indicesData()
{
    /*
    static unsigned int indices[] = {
     0,1,2,
     2,3,0
    };
    return indices;
    */
    static unsigned int indices[30];
    unsigned int i = 0;
    unsigned int offset = 0;
    for (float y = 0; y <= 4; y = y + 1)
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

const float* prey::randomCoordinate()
{
    snake s;
    float snakeX = s.getXCoordinates();
    float snakeY = s.getYCoordinates();
    int x = 0;
    srand((unsigned int)(time(nullptr)));//seeding unique unsigned integer for random number generation

    for(int i = 0 ; i < 10 ; i++)
    {
        x = rand() % 780;
        x = x - (x % 20);
        for(int j = 0 ; j < i ; j++)
        {
            if ( x == (int)randomCoordinates[j] || x == (int)snakeX )
                i--;
        }
        randomCoordinates[i] = (float)x;
    }

    int y = 0;
    for (int i = 10; i < 20; i++)
    {
        y = rand() % 540;
        y = y - (y % 20);
        for (int j = 5; j < i; j++)
        {
            if ( y == (int)randomCoordinates[j] || y == (int)snakeY )
                i--;
        }
        randomCoordinates[i] = (float)y;
    }

    //first 10 coordinates are x_coord last 10 are y_coord
    return randomCoordinates;
}

unsigned int* prey::parseWordList()
{
    srand((unsigned int)(time(nullptr)));
    int x = rand() % 2;
    std::ifstream stream("resources/wordList/wordList.txt");
    std::string line;
    unsigned int count = 0;
    std::string randomWord;

    while(getline(stream , line))
    {
        randomWord = line;
        if(count == x)
        {
            break;
        }
        count = count + 1;
    }

     //std::cout << randomWord[0]<<" "<< randomWord[1] << " " << randomWord[2] << " " << randomWord[3] << " " << randomWord[4] << " " << randomWord[5]<< std::endl;

    for(unsigned int i = 0; i < randomWord.length(); i++ )
    {
        indexOrder[i] = charMap[randomWord[i]];
    }

    for (unsigned int i = 0; i < randomWord.length(); i++)
    {
        //first 10 random coordinates are x coord and last 10 are y coord
        coIndexMap[{randomCoordinates[i], randomCoordinates[i + 10]}] = indexOrder[i];
    }
    
    /*
    for (unsigned int i = 0; i < randomWord.length(); i++)
    {
        std::cout << indexOrder[i] << " ";
    }
    std::cout << std::endl;
    for ( auto& t : coIndexMap)
        std::cout << t.first.first<<", "<< t.first.second << " = " << t.second << std::endl;
    std::cout << std::endl << std::endl;
    */
    ranWordLength = randomWord.length();
    return indexOrder;
}

unsigned int prey::matchRancoordinateWithIndex()
{   
    snake s;
    float snakeX = s.getXCoordinates();
    float snakeY = s.getYCoordinates();
   
    for(unsigned int i = 0; i < ranWordLength ; i++)
    {
        if(snakeX == randomCoordinates[i] && snakeY == randomCoordinates[i+10])
        {
            collisionOrder++;
            if(coIndexMap[{ randomCoordinates[i], randomCoordinates[i+10] }] == indexOrder[indexCount])
            {
                coordinatesToBeRemoved[0] = randomCoordinates[i];
                coordinatesToBeRemoved[1] = randomCoordinates[i+10];
                randomCoordinates[i] = 1000.0f;
                randomCoordinates[i + 10] = 1000.0f;
                indexCount++;
            }
            else
            {
                collisionOrder = 0;
                indexCount = 0;
                return 3; //case 3 for unordered collision
            }
        }
    }
    if (collisionOrder == ranWordLength)
    {
        return 2;//collision order complete
    }
    else if (collisionOrder == 0)
    {
        return 0;//no collision
    }
    else if (collisionOrder < ranWordLength && collisionOrder > 0)
    {
        return 1;//unit collision
    }
}

