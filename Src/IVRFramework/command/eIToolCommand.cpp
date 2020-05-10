#include "IVRFramework/command/eIToolCommand.h"
#include <QObject>
#include <QEvent>
#include <QWidget>
#include "IVRFramework/frame/eIContentView.h"
#include "IVRFramework/eService.h"
#include "IVRFramework/frame/eIContentManager.h"

using namespace IVRFramework;

IVRFramework::eIToolCommand::eIToolCommand()
{

}

IVRFramework::eIToolCommand::~eIToolCommand()
{

}

bool IVRFramework::eIToolCommand::IsChecked()
{
	eIContentView* pContentView = eService::GetInstance()->m_pContentManager->ActivedContentView();
	if (pContentView == NULL)
		return false;

	eIToolCommand* ptrTool = pContentView->GetCurrentTool();
	if (ptrTool && ptrTool == this)
		return true;

	return false;
}

void IVRFramework::eIToolCommand::Execute(QObject* sender, QString param)
{

}

QCursor IVRFramework::eIToolCommand::GetCursor()
{
	return QCursor();
}

bool IVRFramework::eIToolCommand::Activate()
{
	return true;
}

bool IVRFramework::eIToolCommand::Deactivate()
{
	return true;
}

bool IVRFramework::eIToolCommand::OnContextMenu(QContextMenuEvent* event)
{
	return false;
}

void IVRFramework::eIToolCommand::OnDoubleClick(QMouseEvent* event)
{

}

void IVRFramework::eIToolCommand::OnKeyDown(QKeyEvent* event)
{

}

void IVRFramework::eIToolCommand::OnKeyUp(QKeyEvent* event)
{

}

void IVRFramework::eIToolCommand::OnMouseDown(QMouseEvent* event)
{

}

void IVRFramework::eIToolCommand::OnMouseMove(QMouseEvent* event)
{

}

void IVRFramework::eIToolCommand::OnMouseUp(QMouseEvent* event)
{

}

void IVRFramework::eIToolCommand::OnJustMouseMove(QMouseEvent* event)
{

}

void IVRFramework::eIToolCommand::OnEnterEvent(QEvent* event)
{

}

void IVRFramework::eIToolCommand::OnLeaveEvent(QEvent* event)
{

}

bool IVRFramework::eIToolCommand::OnWheelEvent(QWheelEvent* event)
{
	return false;
}

void IVRFramework::eIToolCommand::SetCurrentCursor(const QCursor& cursor)
{
	m_pCursor = cursor;
	eIContentView* pContentView = eService::GetInstance()->m_pContentManager->ActivedContentView();
	if (pContentView == NULL)
	{
		return;
	}
	dynamic_cast<QWidget*>(pContentView)->setCursor(m_pCursor);
}
