#pragma once
#include "Clock.h"
#include "Logger.h"
#include "AbstractRenderer.h"
#include "SceneGraph.h"
#include "ModelManager.h"

class GameEngine
{
private:
	Clock gameClock;

protected:
	AbstractRenderer* renderer;
	SceneManager* sceneManager;

public:
	ModelManager modelManager;

	GameEngine(void);
	virtual ~GameEngine(void);

	virtual void OnStart();
	virtual void PreRender(float time);
	virtual void Render();
	virtual void PostRender();
	virtual void OnEnd();

	///<summary>Gets the total elapsed milliseconds</summary>
	float GetElapsedMilliseconds()const;

	///<summary>Logs the message to the file</summary>
	///<param "priority">The priority to associate the message to</param>
	///<param "message">The message to log</param>
	void LogMessage(LogPriority priority, std::string message);

	///<summary>Sets the renderer to be used in the game engine</summary>
	///<param "renderer">the render to utilize</param>
	void SetRenderer(AbstractRenderer* renderer);
};

