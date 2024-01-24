#include "foxrenderer.h"

#include "foxcamera.h"
#include "foxlighting.h"
#include "foxactor.h"
#include "foxshaderprogram.h"


FoxRenderer::FoxRenderer()
{
	m_camera = std::make_shared<FoxCamera>(QVector3D(0.0f, 0.0f, 6.0f));
	m_lighting = std::make_shared<FoxLighting>();
}

FoxRenderer::~FoxRenderer()
{

}

void FoxRenderer::addActor(std::shared_ptr<FoxActor> actor)
{
	// 设置相机和灯光
	actor->setView(m_camera); // 设置视图矩阵
	actor->getShaderProgram()->setLighting(m_lighting);
	// 添加至m_actor队列中
	m_actors.push_back(actor);
}

void FoxRenderer::renderer()
{
	for (auto& actor : m_actors)
	{
		actor->draw();
	}
}

std::vector<std::shared_ptr<FoxActor>> FoxRenderer::getActors()
{
	return m_actors;
}

void FoxRenderer::clearActors()
{
	m_actors.clear();
}

void FoxRenderer::setCameraZoom(float yoffset)
{
	m_camera->wheelScrollEvent(yoffset);
}

float FoxRenderer::getCameraZoom()
{
	return m_camera->getCameraZoom();
}
