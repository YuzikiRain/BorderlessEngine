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
		virtual void Close();

		const char *name = "Window";
		bool isOpen;
	};
}