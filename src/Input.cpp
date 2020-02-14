#include <FishGUI/Input.hpp>

#include <iostream>
#if FISHENGINE_PLATFORM_APPLE
#	define GLFW_INCLUDE_GLCOREARB
#endif
#include <GLFW/glfw3.h>

#include <FishGUI/Widget.hpp>
#include <FishGUI/Window.hpp>

namespace FishGUI
{
	Input* 	Input::s_current = nullptr;

	void Input::Update()
	{
		if (m_firstMouseEvent != nullptr)
		{
			delete m_firstMouseEvent;
			m_firstMouseEvent = nullptr;
		}
		if (!m_mouseEvents.empty())
		{
			auto e = m_mouseEvents.front();
			m_mouseEvents.pop_front();
			m_window->OnMouseEvent(e);
			m_firstMouseEvent = e;
		}

		if (m_firstKeyEvent != nullptr)
		{
			delete m_firstKeyEvent;
			m_firstKeyEvent = nullptr;
		}
		if (!m_keyEvents.empty())
		{
			auto e = m_keyEvents.front();
			m_keyEvents.pop_front();
			m_window->OnKeyEvent(e);
			m_firstKeyEvent = e;
		}


		m_leftMouseButtonDoubleClicked = false;
		for (auto& s : m_mouseButtonStates)
		{
			if (s == MouseButtonState::Down)
				s = MouseButtonState::Held;
			else if (s == MouseButtonState::Up)
				s = MouseButtonState::None;
		}

		// dragging
		if (m_mouseButtonStates[0] == MouseButtonState::Held)
		{
			if (m_dragWidget != nullptr)
			{
				m_dragWidget->MouseDragEvent(m_mousePosition);
			}
		}
		else
		{
			m_dragWidget = nullptr;
		}

		// scroll
		m_scrolling = false;
		m_scroll.x = 0;
		m_scroll.y = 0;
	}

	void Cursor::Init()
	{
		for (int i = 0; i < static_cast<int>(CursorType::CursorCount); ++i) {
			m_glfwCursors[i] = glfwCreateStandardCursor(GLFW_ARROW_CURSOR + i);
		}
	}
}
