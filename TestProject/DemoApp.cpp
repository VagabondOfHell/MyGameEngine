#include "DemoApp.h"
#include "SceneManager.h"
#include "CollisionChecker.h"

DemoApp::DemoApp(void)
{
}


DemoApp::~DemoApp(void)
{
}

void DemoApp::OnStart()
{
	
	AllocConsole();
 FILE* pCout;
 freopen_s(&pCout, "conin$", "r", stdin);
 freopen_s(&pCout, "conout$", "w", stdout);
 freopen_s(&pCout, "conout$", "w", stderr);
 fclose(pCout);
 printf("Debugging Window:\n");

	GameEngine::OnStart();
	Camera* camera = new Camera();
	camera->SetPerspectiveMatrix(90, 16.0f/9.0f, 1.0f, 50.0f);
	camera->position = amVec3(0.0f, 0.0f, 5.0f);
	camera->up = amVec3(0.0f, 1.0f, 0.0f);
	camera->direction = amVec3(0.0f, 0.0f, 0.0f);
	
	sceneManager->SetActiveCamera(camera);
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	model = new SimpleModel();
	model->Initialize();
	modelManager.LoadCubeModel();
	model->ApplyMesh(modelManager.GetMesh("Cube"));

	modelNode = sceneManager->CreateRootChildSceneNode();
	modelNode->AttachModel(model);

	modelNodeChild = modelNode->CreateChildSceneNode();
	modelNodeChild->AttachModel(model);
	modelNodeChild->position = amVec3(2.0f, 0.0f, 0.0f);

	modelNodeChild2 = modelNodeChild->CreateChildSceneNode();
	modelNodeChild2->AttachModel(model);
	modelNodeChild2->position = amVec3(2.0f, 0.0f, 0.0f);
	
	modelNode->position = amVec3(0.0f, 0.0f, 0.0f);

	BoundingSphere sphere1(amVec3(), 1.0f);
	BoundingSphere sphere2(amVec3(5.0f, 0.0f, 0.0f), 1.0f);

	Ray ray(amVec3(0.0f, -5.0f, 0.0f), amVec3(0, 1, 0));

	if(CollisionChecker::SphereToSphereCollision(sphere1, sphere2))
		printf("true");

	if(CollisionChecker::SphereToRayCollision(sphere1, ray))
		printf("Ray Collision");
}

void DemoApp::PreRender(float time)
{
	GameEngine::PreRender(time);
}

float rotationAmount = 1.0f;

void DemoApp::Render()
{
	modelNode->position.x -= 1.0f;

	if(modelNode->position.x <= -20.0f)
		modelNode->position.x = 0.0f;

	GameEngine::Render();
	rotationAmount++;

	if(rotationAmount > 360)
		rotationAmount = 0;

	modelNode->orientation = amQuaternion(rotationAmount, 0.0f, 0.0f, 1.0f);
	modelNodeChild->orientation = amQuaternion(rotationAmount, 0.0f, 1.0f, 0.0f);
	modelNodeChild2->orientation = amQuaternion(rotationAmount, 1.0f, 0.0f, 0.0f);

	//renderer->RenderPrimitive(AbstractRenderer::Triangle);
	
	//renderer->RenderPrimitive(AbstractRenderer::Quad);
}

void DemoApp::PostRender()
{
	GameEngine::PostRender();
}

void DemoApp::OnEnd()
{
	GameEngine::OnEnd();
}