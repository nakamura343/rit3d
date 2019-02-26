// rit3d.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
//#include <Windows.h>
#include <glad/glad.h>
#include "declare.h"

void example_light_shadow_1();
void example_light_shadow_2();
void example_light_shadow_3();
void example_light_shadow_4();
void example_light_shadow_5();
void example_skybox_1();

int main()
{
	Application::Instance()->setGameEntry(example_light_shadow_1);
	Application::Instance()->runRit3d("demo", 1000, 800);
	return 0;
}



