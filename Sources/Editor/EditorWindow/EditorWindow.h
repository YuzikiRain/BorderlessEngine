#pragma once

namespace BorderlessEditor
{
	class EditorWindow
	{
	public:
		virtual void Open();
		void BeginDraw();
		virtual void Draw();
		void EndDraw();
		const char* name = "Window";
		bool  isOpen;
	};
}