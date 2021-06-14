#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "snake.h"
#include "grid.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include <string>
#include "renderer.h"
#include "indexBuffer.h"
#include "vertexBuffer.h"
#include "vertexArray.h"
#include "shader.h"
#include "vertexBufferLayout.h"
#include "texture.h"
#include "prey.h"
#include "line.h"
//#include "test.h"

const int screenWidth = 800;
const int screenheight = 600;

snake s;

static void key_Callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window,GLFW_TRUE);
    }

    if (key == GLFW_KEY_W && action == GLFW_PRESS)
    {
        s.setCurrentKey(GLFW_KEY_W);
    }

    if (key == GLFW_KEY_A && action == GLFW_PRESS)
    {
        s.setCurrentKey(GLFW_KEY_A);
    }

    if (key == GLFW_KEY_S && action == GLFW_PRESS)
    {
        s.setCurrentKey(GLFW_KEY_S);
    } 

    if (key == GLFW_KEY_D && action == GLFW_PRESS)
    {
        s.setCurrentKey(GLFW_KEY_D);
    }
   
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(screenWidth, screenheight, "spellsnake", NULL, NULL);
   
    glfwSetKeyCallback(window, key_Callback);
    //glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
   
    glfwSwapInterval(7);

    //setting window background black
    glClearColor(0.0,0.0,0.0,1.0);

    //initializing glew after the context::::::::::::::::::::::::::::::::::::
    glewInit();
    std::cout << glGetString(GL_VERSION) << std::endl;

    {//kind of unnessary scope just to terminate a bug of window not closing
              
    prey p;
    grid g;
    line l;
    vertexArray vap;
    vertexArray vas;
    vertexArray vag;
    vertexArray val;
    vertexBufferLayout layout_s;
    vertexBufferLayout layout_g;
    vertexBufferLayout layout_p;
    vertexBufferLayout layout_l;
    renderer render;

    p.indicesData();
    vertexBuffer vbp(nullptr, p.sizeOfData(), GL_DYNAMIC_DRAW);
    layout_p.push<float>(2); //arguments for out arrtibPointer float for type and 2 for vertex size rest of datas are handeled by the class
    layout_p.push<float>(2); //second push for texture
    vap.addBuffer(vbp,layout_p);//passing layout to our vertex array anong with buffers. this will take care of binding stuff and adding attribs
    indexBuffer ibp(p.indicesData(), p.countOfIndices() , GL_STATIC_DRAW);

    unsigned int* indexSnakedata = s.indicesData();
    vertexBuffer vbs(nullptr , 150 * 8 * sizeof(float) , GL_DYNAMIC_DRAW); //setting max size of the buffer
    layout_s.push<float>(2);
    vas.addBuffer(vbs, layout_s);
    indexBuffer ibs(s.indicesData(), s.countOfIndices() , GL_STATIC_DRAW);
    
    vertexBuffer vbl(l.vertexData(), l.sizeOfData(), GL_STATIC_DRAW);
    layout_l.push<float>(2);
    val.addBuffer(vbl, layout_l);
    indexBuffer ibl(l.indicesData(), l.countOfIndices(), GL_STATIC_DRAW);
    
    g.setGridSize(screenWidth, screenheight);
    g.vertexData();
    g.indicesData();
    vertexBuffer vbg(g.vertexData(), g.sizeOfData(),GL_STATIC_DRAW);
    layout_g.push<float>(2); 
    vag.addBuffer(vbg, layout_g);
    indexBuffer ibg(g.indicesData(), g.countOfIndices(), GL_STATIC_DRAW);


    shader shade("resources/shaders/snake.shader");
    shader gridShader("resources/shaders/grid.shader");
    shade.bind();
    gridShader.bind();
   
  
    //screen loop comming ahead::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    texture textures("resources/textures/spritesheet.png");
    textures.bind(0);

    shade.unbind();
    gridShader.unbind();

    vap.unbind();
    vbp.unBind();
    ibp.unBind();

    vag.unbind();
    vbg.unBind();
    ibg.unBind();

    vas.unbind();
    vbs.unBind();
    ibs.unBind();

    glm::vec3 translationA(0,0,0);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));//view is constant for now so keeping it out of the loop
    //making proj matrix and binding our shaders with uniforms
    glm::mat4 proj = glm::ortho(0.0f, (float)screenWidth, 0.0f, (float)screenheight, -1.0f, 1.0f);
    //in case if we use normalized coordinates glm::mat4 proj = glm::ortho(-ratio, ratio, -1.0f, 1.0f, -1.0f, 1.0f);
    glm::mat4 model = glm::translate(glm::mat4(1.0f), translationA);
    glm::mat4 mvp = proj * view * model; //remember this multiplication needs to happen in this order because opengl expects it

    //extracting random coordinates from prey class and initializing an array
    float* randomCoordinates = nullptr;
    unsigned int collisionCase = 3; //case 3 or case 2 collisions resets the random coordinates 
  
    randomCoordinates = (float*)p.randomCoordinate();
    p.parseWordList();
 
    /*
    float* preyVertexData = (float*)p.vertexData();
    unsigned int* preyIndexData = (unsigned int*)p.indicesData();
    for (int i = 0; i < 80; i=i+4)
    {
        std::cout << *(preyVertexData + i) << " " << *(preyVertexData + i+1) << "        " << *(preyVertexData + i+2) << " " << *(preyVertexData +i+ 3) << std::endl;
    }

    std::cout << std::endl << std::endl << std::endl;

    for (int i = 0; i < 24; i = i + 5)
    {
        std::cout << *(preyIndexData+ i) << " " << *(preyIndexData + i + 1) << " " << *(preyIndexData + i + 2) << " " << *(preyIndexData + i + 3) << " " << *(preyIndexData + i + 4)<< " " << *(preyIndexData + i + 5)<< std::endl;
    }
    */
    
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glViewport(0, 0, screenWidth, screenheight);
        render.clear();

        //rendering grid
        gridShader.bind();
        gridShader.setUniform4f("u_color", 0.0f, 0.0f, 0.5f, 0.8f);
        gridShader.setUniformMatrix4fv("u_MVP", mvp);
        render.draw(vag, ibg, GL_LINES);

        //rendering line
        gridShader.bind();
        gridShader.setUniform4f("u_color", 0.0f, 0.3f, 0.5f, 0.8f);
        gridShader.setUniformMatrix4fv("u_MVP", mvp);
        render.draw(val, ibl, GL_LINES);

        unsigned int preyCollisionOrder = p.matchRancoordinateWithIndex();
        s.setCollisionOrd(preyCollisionOrder);
        collisionCase = s.preyCollision();
        if (collisionCase == 3 || collisionCase == 2)//case 3 or case 2 collisions resets the random coordinates
        {
            randomCoordinates = (float*)p.randomCoordinate();
            p.parseWordList();
            collisionCase = 0;
            p.setCollisionOrder(collisionCase);
        }
        //p.setCollisionOrder(collisionOrder);
       
        //batching all 5 preys in one draw call
        vbp.bind();
        glBufferSubData(GL_ARRAY_BUFFER, 0, p.sizeOfData(), p.vertexData());
        shade.bind();
        shade.setUniformMatrix4fv("u_MVP", mvp);
        shade.setUniform1i("u_Texture", 0);
        shade.setUniform2f("v_TextureCoordinateShift", 0.0 , 0.0);
        render.draw(vap, ibp, GL_TRIANGLES);

        /*
        if(collisionOrder < 1)
        {       
            glm::vec3 translationB(randomXandY[0], randomXandY[5], 0);
            glm::mat4 modelPrey0 = glm::translate(glm::mat4(1.0f), translationB);
            glm::mat4 mvpSnake0 = proj * view * modelPrey0; //remember this multiplication needs to happen in this order because opengl expects it
            shade.bind();
            shade.setUniformMatrix4fv("u_MVP", mvpSnake0);
            shade.setUniform1i("u_Texture", 0);
            shade.setUniform2f("v_TextureCoordinateShift", 0 * (1 / 26.0f), 0.0);
            render.draw(vap, ibp, GL_TRIANGLES);       
        }
        */
     
        //rendering snake
        vbs.bind();
        ibs.bind();
        vas.bind();

        const void* vertexdata = s.vertexData();
        glBufferSubData(GL_ARRAY_BUFFER, 0, s.sizeOfData(), vertexdata);
        gridShader.bind();
        gridShader.setUniformMatrix4fv("u_MVP", mvp);
        gridShader.setUniform4f("u_color", 0.0f, 0.3f, 0.8f, 1.0f);
        glDrawElements(GL_TRIANGLES, s.indexCountForCurrentLength(), GL_UNSIGNED_INT, nullptr);
   
        //never forget to free snake data
        delete[] vertexdata;
       

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();

    }
    }
    glfwTerminate();
    return 0;
}
