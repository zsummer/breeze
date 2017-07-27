/*
* breeze License
* Copyright (C) 2014-2017 YaweiZhang <yawei.zhang@foxmail.com>.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#define _GLFW_WIN32
#include <common.h>
#include <utls.h>
#include <balance.h>
using namespace zsummer::log4z;
using namespace zsummer::mysql;
 
#include <glad/glad.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#include <include/GLFW/glfw3.h>
#include <include/GLFW/glfw3native.h>
#include <linmath.h>

#include <stdlib.h>
#include <stdio.h>


#pragma comment(lib, "OpenGL32")
#pragma comment(lib, "GLu32")


static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main(void)
{
#ifndef _WIN32
    //! linux下需要屏蔽的一些信号
    signal(SIGHUP, SIG_IGN);
    signal(SIGALRM, SIG_IGN);
    signal(SIGPIPE, SIG_IGN);
    signal(SIGXCPU, SIG_IGN);
    signal(SIGXFSZ, SIG_IGN);
    signal(SIGPROF, SIG_IGN);
    signal(SIGVTALRM, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
    signal(SIGCHLD, SIG_IGN);
    setenv("TZ", "GMT-8", 1);
#else
    //system("chcp 65001");
#endif
    srand((ui32)time(NULL));


    ILog4zManager::getPtr()->start();
    SessionManager::getRef().start();

    GLFWwindow* window;


    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        exit(EXIT_FAILURE);
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwSetKeyCallback(window, key_callback);

    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glfwSwapInterval(1);

    LOGI("GL_VERSION:" << (const char*)glGetString(GL_VERSION));

    while (!glfwWindowShouldClose(window))
    {
        glShadeModel(GL_SMOOTH);

        /* Draw a triangle */
        glBegin(GL_TRIANGLES);

        glColor3f(1.0, 0.0, 0.0);    // Red
        glVertex3f(0.0, 1.0, 0.0);

        glColor3f(0.0, 1.0, 0.0);    // Green
        glVertex3f(-1.0, -1.0, 0.0);

        glColor3f(0.0, 0.0, 1.0);    // Blue
        glVertex3f(1.0, -1.0, 0.0);

        glEnd();


        //glEnable(GL_LINE_STIPPLE);
        //glLineStipple(1, 1);
        glColor3f(1.0, 1.0, 1.0);    // Red
        glLineWidth(1);


        glBegin(GL_LINES);
        glVertex2f(0, 0);
        glColor3f(1.0, 0.0, 1.0);    // Red
        glVertex2f(1,1);
        glEnd();


        glBegin(GL_LINES);
        glVertex3f(0, 1, 0);
        glColor3f(0.0, 0.0, 1.0);    // Red
        glVertex3f(1, 0, 1);
        glEnd();


        glBegin(GL_POINTS);
        glColor3f(0.0, 1.0f, 1.0f);   
        glVertex3f(0, 0, 0);
        glEnd();

        glBegin(GL_POINTS);
        glColor3f(0.0, 1.0f, 1.0f);
        glVertex3f(0.8f, 0.8f, 0.8f);
        glEnd();

        glBegin(GL_POINTS);
        glColor3f(0.0, 1.0f, 1.0f);
        glVertex3f(0, 0.8f, 0);
        glEnd();

        glBegin(GL_POINTS);
        glColor3f(0.0, 1.0f, 1.0f);
        glVertex3f(0, 0, 0.8f);
        glEnd();

        glBegin(GL_POINTS);
        glColor3f(0.0, 1.0f, 1.0f);
        glVertex3f(0.8f, 0, 0);
        glEnd();

        glBegin(GL_POINTS);
        glColor3f(0.0, 1.0f, 1.0f);
        glVertex3f(0.8f, 0.8f, 0);
        glEnd();

        glBegin(GL_POINTS);
        glColor3f(0.0, 1.0f, 1.0f);
        glVertex3f(0, 0.8f, 0.8f);
        glEnd();

        glBegin(GL_POINTS);
        glColor3f(0.0, 1.0f, 1.0f);
        glVertex3f(0.8f, 0, 0.8f);
        glEnd();



        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glGetError();
    glfwTerminate();
    exit(EXIT_SUCCESS);
}

