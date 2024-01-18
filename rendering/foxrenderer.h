#pragma once

#include <vector>
#include <memory>
/**
 * @brief ��Ⱦ���ฺ��ģ����Ⱦ.
 * �ڲ���Ҫ����˵ƹ��������������͵ƹ��໹����ɫ�����򶼹��ൽ�������.
 * ��Ⱦ�������Ĭ�ϵ�����͵ƹ�
 */
class FoxCamera;
class FoxLighting;
class FoxActor;
class FoxRenderer
{
	using sptr_Actors = std::vector<std::shared_ptr<FoxActor>>;
public:
	FoxRenderer();
	~FoxRenderer();
	// ���Actor
	void addActor(std::shared_ptr<FoxActor> actor);
	// �������е�Actor
	void renderer();

	// ���

private:
	std::shared_ptr<FoxCamera> m_camera; // ���
	std::shared_ptr<FoxLighting> m_lighting; // �ƹ�
	sptr_Actors m_actors; // ���actor
};
