#pragma once
#include <EditorWindow/EditorWindow.h>
#include "Component.h"
#include <memory>

using namespace std;
using namespace BorderlessEngine;

namespace BorderlessEditor
{
	class Inspector : public EditorWindow
	{
	public:
		Inspector();
		void Draw();

	private:
		void DrawComponent(shared_ptr<Component> componentPointer);
	};
}
