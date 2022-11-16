#pragma once
#include "EditorWindow/EditorWindow.h"
#include "GameObject.h"

namespace BorderlessEditor
{
	class SceneEditorWindow : public EditorWindow
	{
	public:
		SceneEditorWindow();
		void Draw();

	private:
		unsigned int texture;
		unsigned int fbo;
		BorderlessEngine::GameObject *cameraGameObject;
	};
}
