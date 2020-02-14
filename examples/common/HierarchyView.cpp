#include "HierarchyView.hpp"
#include <FishGUI/Draw.hpp>
#include <FishGUI/FishGUI.hpp>
#include <FishGUI/Theme.hpp>
#include <FishGUI/Input.hpp>

//#include <algorithm>

using namespace FishGUI;

HierarchyView::HierarchyView(const char* name) : Super(name)
{
	m_model = new HierarchyModel();
	m_imContext->ymargin = 0;
	m_root = new GameObject("Root");
	m_root->children.push_back(new GameObject("Main Camera"));
	m_root->children.push_back(new GameObject("Directional Light"));
	auto go = new GameObject("GameObject");
	m_root->children.push_back(go);
	for (int i = 0; i < 30; ++i)
	{
		go->AddChild(new GameObject("GameObject" + std::to_string(i)));
	}
	m_unfolded.insert(m_root);
	m_unfolded.insert(go);

	for (int i = 0; i < 10; ++i)
	{
		go = go->children[0];
		go->AddChild(new GameObject("Child" + std::to_string(i)));
	}

	m_selectionModel.SelectItem(m_root);
}
