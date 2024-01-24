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
	// ��������͵ƹ�
	actor->setView(m_camera); // ������ͼ����
	actor->getShaderProgram()->setLighting(m_lighting);
	// �����m_actor������
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
