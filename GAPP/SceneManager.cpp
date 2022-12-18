/* Start Header -------------------------------------------------------
Copyright (C) <current year in format 2022> DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.
File Name: SceneManager.cpp
Purpose: For managing scenes
Language: c++
Platform: x64
Project: junsu.jang, CS300, Assignment 3 - Dynamic Environment Mapping
Author: Junsu Jang, junsu.jang, 0055891
Creation date: 09/27/2022
End Header --------------------------------------------------------*/
#include "pch.h"
#include "framework.h"
#include "SceneManager.h"
#include "Scene.h"

void SceneManager::BindScene(int i, Scene& scene)
{
	scenes[i] = &scene;
}

void SceneManager::Init()
{
}

void SceneManager::Update(double dt)
{
	switch (nowState)
	{
	case SceneManager::SceneManagerState::start:
		if (nextScene == nullptr) {
			nowState = SceneManagerState::Exit;
			//log error
		}
		else
		{
			nowState = SceneManagerState::Load;
		}
		break;
	case SceneManager::SceneManagerState::Load:
		prevScene = nowScene;
		nowScene = nextScene;
		nowScene->Load();
		nowState = SceneManagerState::Update;
		break;
	case SceneManager::SceneManagerState::Update:
		if (nowScene != nextScene) {
			nowState = SceneManagerState::Unload;
		}
		else {
			nowScene->Update(dt);
			nowScene->Draw();
		}
		break;
	case SceneManager::SceneManagerState::Unload:
		nowState = SceneManagerState::Load;
		nowScene->Unload();
		break;
	case SceneManager::SceneManagerState::Exit:
		if (nowScene != nullptr) { nowScene->Unload(); }
		break;
	default:
		break;
	}
}

void SceneManager::setNextScene(int i)
{
	if (scenes.find(i) == scenes.end()) {
		std::cerr << "No " << i << "th scene exist" << std::endl;
		return;
	}
	nextScene = scenes[i];
}
