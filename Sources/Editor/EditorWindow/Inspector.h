#pragma once
#include <EditorWindow/EditorWindow.h>
#include "Component.h"

using namespace BorderlessEngine;

namespace BorderlessEditor
{
	class Inspector : public EditorWindow
	{
	public:
		Inspector();
		void Draw();

	private:
		void DrawComponent(Component* component);
	};
}
