/*
* breeze License
* Copyright (C) 2014-2018 YaweiZhang <yawei.zhang@foxmail.com>.
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
#pragma warning(disable:4996)
#pragma warning(disable:4819)
#define WIN32_LEAN_AND_MEAN
#include <WS2tcpip.h>
#include <WinSock2.h>
#include <windows.h>
#include <io.h>
#include <shlwapi.h>
#include <process.h>
#include <direct.h>
#include <glad/glad.h>
#include <gl/GL.h>


#include <iomanip>
#include <string.h>
#include <signal.h>
#include <time.h>
#include <cstdint>

#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include <algorithm>
#include <limits>

#include <functional>
#include <memory>
#include <unordered_map>
#include <chrono>
#include <random>

#include <string>
#include <set>
#include <vector>
#include <list>
#include <map>
#include <array>



#include "log4z/log4z.h"
using namespace zsummer::log4z;

 
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



#define SCREEN_X 640
#define SCREEN_Y 640

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

struct Pixel
{
    double r;
    double g;
    double b;

    double x;
    double y;
    double z;
};

using Vector3 = std::tuple<double, double, double>;

class TestRange
{
public:
    TestRange() {}
    ~TestRange() {}
public:
    static const int SCALAR_NUM = 1000;
    static const int SCALAR_BEGIN = SCALAR_NUM / -2;
    static const int SCALAR_END = SCALAR_NUM / 2;
    static const int PIXELS_SIZE = SCALAR_NUM* SCALAR_NUM*2;
    
    void Test(Vector3 dir)
    {
        for (int i = SCALAR_BEGIN; i < SCALAR_END; i++)
        {
            for (int j = SCALAR_BEGIN; j < SCALAR_END; j++)
            {
                if (_len < PIXELS_SIZE)
                {
                    _pixels[_len++] = { 0.0f, 1.0f, 1.0f, i*2.0f / SCALAR_NUM, 0.0f, j * 2.0f / SCALAR_NUM };
                }
                if (_len < PIXELS_SIZE)
                {
                    _pixels[_len++] = { 1.0f, 1.0f, 1.0f, i*2.0f / SCALAR_NUM, 0.0f, j * 2.0f / SCALAR_NUM };
                }
            }
        }
    }

public:
    std::array<Pixel, PIXELS_SIZE>  _pixels;
    size_t _len = 0;
};
TestRange g_tr;


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
    srand((unsigned int)time(NULL));


    ILog4zManager::getPtr()->start();



    GLFWwindow * window;


    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        exit(EXIT_FAILURE);
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    window = glfwCreateWindow(SCREEN_X, SCREEN_Y, "Simple example", NULL, NULL);
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
        glClear(GL_COLOR_BUFFER_BIT);
        glShadeModel(GL_SMOOTH);
        g_tr._len = 0;
        double begin_time = std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::steady_clock::now().time_since_epoch()).count();
        static double last_time = begin_time;
        static double frame_count = 0;
        static double last_count = 0;
        frame_count++;
        Vector3 dir = { 0, 0, 0 };
        double radian = (float)fmod(begin_time, 20.0) / 20.0f * 3.141592654*2.0f;
        std::get<0>(dir) = cos(radian);
        std::get<2>(dir) = sin(radian);
        double begin_time2 = std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::steady_clock::now().time_since_epoch()).count();
        g_tr.Test(dir);
        double now = std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::steady_clock::now().time_since_epoch()).count();
        
        glBegin(GL_POINTS);
        for (int i=0; i < g_tr._len; i++)
        {
            glColor3f(g_tr._pixels[i].r, g_tr._pixels[i].g, g_tr._pixels[i].b);
            glVertex3f(g_tr._pixels[i].x, g_tr._pixels[i].z, g_tr._pixels[i].y);
        }
        glEnd();
        glfwSwapBuffers(window);
        glfwPollEvents();

        if (now - last_time  > 1.0f)
        {
            char title[100] = { 0 };
            sprintf(title, "fps:<%lf>  lapse1:<%lf> lapse2:<%lf> lapse:<%lf> count:<%lf>", 
                frame_count /(now - last_time), begin_time2 - begin_time, now - begin_time2, now - begin_time
                , (g_tr._len - last_count)/ (now - last_time));
            glfwSetWindowTitle(window, title);
            last_time = now;
            last_count = g_tr._len;
            frame_count = 0.0f;
        }
    }

    glfwDestroyWindow(window);
    glGetError();
    glfwTerminate();
    exit(EXIT_SUCCESS);
}

void example()
{
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
    glVertex2f(1, 1);
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
}