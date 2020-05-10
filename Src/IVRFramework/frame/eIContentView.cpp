#include "eIContentView.h"
#include <QWidget>
#include <QEvent>
#include "eIToolCommand.h"
#include "eIContentEventListener.h"

using namespace IVRFramework;

eIToolCommand* ptrTempTool = NULL;//临时变量

IVRFramework::eIContentView::eIContentView()
	:m_ptrCurrentTool(nullptr)
	,m_ptrPreviousTool(nullptr)
{

}

IVRFramework::eIContentView::~eIContentView()
{

}

eIToolCommand* IVRFramework::eIContentView::GetCurrentTool()
{
	return m_ptrCurrentTool;
}

void IVRFramework::eIContentView::SetCurrentTool(eIToolCommand* ptrTool)
{
	if (m_ptrCurrentTool == ptrTool)
	{
		return;
	}

	//取消前一个工具激活状态
	if (m_ptrCurrentTool)
	{
		m_ptrCurrentTool->Deactivate();
	}
	//记下前一个工具
	m_ptrPreviousTool = m_ptrCurrentTool;

	//设置当前工具
	m_ptrCurrentTool = ptrTool;

	//激活当前工具
	if (m_ptrCurrentTool)
	{
		if (!m_ptrCurrentTool->Activate())
		{
			m_ptrCurrentTool = NULL;
		}
	}

	//光标设置
	if (m_ptrCurrentTool == NULL && dynamic_cast<QWidget*>(this) != NULL)
	{
		dynamic_cast<QWidget*>(this)->setCursor(QCursor(Qt::ArrowCursor));
	}
}

void IVRFramework::eIContentView::RegistContentListener(eIContentEventListener* pListener)
{
	for (int i = 0; i < m_uiEventHandles.size(); ++i)
	{
		if (m_uiEventHandles[i] == pListener)
		{
			return;
		}
	}
	pListener->m_pContentView = this;
	m_uiEventHandles.push_back(pListener);
}

void IVRFramework::eIContentView::RemoveContentListener(eIContentEventListener* pListener)
{
	auto it = m_uiEventHandles.begin();
	while (it != m_uiEventHandles.end())
	{
		if ((*it) == pListener)
		{
			m_uiEventHandles.erase(it);
			break;
		}

		it++;
	}
}

bool IVRFramework::eIContentView::FindContentListener(eIContentEventListener* pListener)
{
	for (int i = 0; i < m_uiEventHandles.size(); ++i)
	{
		if (m_uiEventHandles[i] == pListener)
		{
			return true;
		}
	}
	return false;
}

eIContentEventListener* IVRFramework::eIContentView::FindContentListener(QString eventHandleName)
{
	for (int i = 0; i < m_uiEventHandles.size(); ++i)
	{
		if (m_uiEventHandles[i]->Get_ClassName() == eventHandleName)
		{
			return m_uiEventHandles[i];
		}
	}
	return nullptr;
}

QVector<eIContentEventListener*>& IVRFramework::eIContentView::GetContentListeners()
{
	return m_uiEventHandles;
}

void IVRFramework::eIContentView::OnEnterEvent(QEvent* event)
{
	if (m_ptrCurrentTool && m_ptrCurrentTool->IsEnable())
		m_ptrCurrentTool->OnEnterEvent(event);
}

void IVRFramework::eIContentView::OnLeaveEvent(QEvent* event)
{
	if (m_ptrCurrentTool && m_ptrCurrentTool->IsEnable())
		m_ptrCurrentTool->OnLeaveEvent(event);
}

void IVRFramework::eIContentView::OnKeyPressEvent(QKeyEvent* event)
{
// 	if (event->key() == Qt::Key_Shift)
// 	{
// 		if (m_ptrPreviousTool != NULL && m_ptrCurrentTool != NULL)
// 		{
// 			ptrTempTool = m_ptrCurrentTool;
// 			SetCurrentTool(m_ptrPreviousTool);
// 		}
// 	}
// 	if (m_ptrCurrentTool && m_ptrCurrentTool->IsEnable())
// 	{
// 		m_ptrCurrentTool->OnKeyDown(event);
// 	}
}

void IVRFramework::eIContentView::OnKeyReleaseEvent(QKeyEvent* event)
{
//  	if (event->key() == Qt::Key_Shift)
//  	{
//  		if (m_ptrPreviousTool != NULL && m_ptrCurrentTool != NULL)
//  		{
//  			m_ptrPreviousTool = m_ptrCurrentTool;
//  			SetCurrentTool(ptrTempTool);
//  		}
//  	}
//  	if (m_ptrCurrentTool && m_ptrCurrentTool->IsEnable())
//  	{
//  		m_ptrCurrentTool->OnKeyUp(event);
//  	}
}

void IVRFramework::eIContentView::OnMouseDoubleClickEvent(QMouseEvent* event)
{
	if (m_ptrCurrentTool && m_ptrCurrentTool->IsEnable())
		m_ptrCurrentTool->OnDoubleClick(event);
}

void IVRFramework::eIContentView::OnMousePressEvent(QMouseEvent* event)
{
	if (m_ptrCurrentTool && m_ptrCurrentTool->IsEnable())
	{
		m_ptrCurrentTool->OnMouseDown(event);
	}
	for (int i = 0; i < m_uiEventHandles.size(); ++i)
	{
		if (m_uiEventHandles[i]->IsActive())
		{
			m_uiEventHandles[i]->onMousePressEvent(event);
		}
	}
}

void IVRFramework::eIContentView::OnMouseReleaseEvent(QMouseEvent* event)
{
	if (m_ptrCurrentTool && m_ptrCurrentTool->IsEnable())
	{
		m_ptrCurrentTool->OnMouseUp(event);
	}
	for (int i = 0; i < m_uiEventHandles.size(); ++i)
	{
		if (m_uiEventHandles[i]->IsActive())
		{
			m_uiEventHandles[i]->onMouseReleaseEvent(event);
		}
	}
}

void IVRFramework::eIContentView::OnMouseMoveEvent(QMouseEvent* event)
{
//  	if (m_ptrCurrentTool && m_ptrCurrentTool->IsEnable())
//  	{
//  		if (event->buttons() != Qt::NoButton)
//  		{
//  			m_ptrCurrentTool->OnMouseMove(event);
//  		}
//  		else
//  		{
//  			m_ptrCurrentTool->OnJustMouseMove(event);
//  		}
//  	}
//  	for (int i = 0; i < m_uiEventHandles.size(); ++i)
//  	{
//  		if (m_uiEventHandles[i]->IsActive())
//  		{
//  			m_uiEventHandles[i]->onMouseMoveEvent(event);
//  		}
//  	}
	//ePluginManager::GetInstance()->DispatchEvent(NULL, eEventContentViewMouseMove, this);
}

void IVRFramework::eIContentView::OnWheelEvent(QWheelEvent* event)
{
	if (m_ptrCurrentTool && m_ptrCurrentTool->IsEnable())
	{
		m_ptrCurrentTool->OnWheelEvent(event);
	}
	for (int i = 0; i < m_uiEventHandles.size(); ++i)
	{
		if (m_uiEventHandles[i]->IsActive())
		{
			m_uiEventHandles[i]->onWheelEvent(event);
		}
	}
}

void IVRFramework::eIContentView::OnResizeEvent(QResizeEvent *event)
{

}

