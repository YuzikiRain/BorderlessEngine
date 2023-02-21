#pragma once

#include <rttr/registration>
using namespace rttr;

namespace BorderlessEngine
{
	class GameObject;
	class Component
	{
		friend GameObject;

	public:
		// 至少有一个虚函数，否则不会被编译器认为是多态类型而无法将父类转换成子类
		virtual GameObject *GetGameObject() { return gameObject; }
		void SetGameObject(GameObject *gameObject) { this->gameObject = gameObject; }

	protected:
	private:
		GameObject *gameObject = 0;

		RTTR_ENABLE()
	};
}