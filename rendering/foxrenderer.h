#pragma once

#include <vector>
#include <memory>
/**
 * @brief 渲染器类负责将模型渲染.
 * 内部主要添加了灯光和相机，将相机类和灯光类还有着色器程序都归类到这个类中.
 * 渲染器类包含默认的相机和灯光
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
	// 添加Actor
	void addActor(std::shared_ptr<FoxActor> actor);
	// 绘制所有的Actor
	void renderer();

	// 清空

private:
	std::shared_ptr<FoxCamera> m_camera; // 相机
	std::shared_ptr<FoxLighting> m_lighting; // 灯光
	sptr_Actors m_actors; // 多个actor
};
