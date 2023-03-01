#pragma once
#include <EditorWindow/EditorWindow.h>
#include "Component.h"
#include <memory>

using namespace BorderlessEngine;

namespace BorderlessEditor
{
	class Inspector : public EditorWindow
	{
	public:
		Inspector();
		void Draw();

	private:
		void DrawComponent(std::shared_ptr<Component> componentPointer);
	};
}
