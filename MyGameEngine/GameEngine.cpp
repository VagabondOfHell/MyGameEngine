#include "GameEngine.h"
#include "SceneManager.h"

GameEngine::GameEngine(void)
{
	gameClock = Clock();
	sceneManager = new SceneManager();
}


GameEngine::~GameEngine(void)
{
}

void GameEngine::OnStart()
{
	renderer->Initialize();

	//start the clock
	gameClock.StartClock();
}

void GameEngine::PreRender(float time)
{
	renderer->ClearRenderer();
}

void GameEngine::Render()
{
	sceneManager->RenderScene();
}

void GameEngine::PostRender()
{
	//swap buffers
	renderer->SwapBuffer();
}

void GameEngine::OnEnd()
{

}

float GameEngine::GetElapsedMilliseconds()const
{
	//get the milliseconds that have passed
	return gameClock.GetMilliseconds();
}

void GameEngine::LogMessage(LogPriority priority, std::string message)
{
	//log the message with the specified priority and message
	Logger::GetInstance().LogMessage(message, priority);
}

void GameEngine::SetRenderer(AbstractRenderer* _renderer)
{
	//set the renderer
	renderer = _renderer;
}