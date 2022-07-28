#pragma once
#include "EditorWindow/EditorWindow.h"

namespace BorderlessEditor
{
	class GameEditorWindow : public EditorWindow
	{
	public:
		GameEditorWindow();
		void Draw();

	private:
		unsigned int texture;
		unsigned int fbo;
	};
}
