#include "IVRFramework/base_widget/eMdiArea.h"
#include <QWidget>
#include <QMdiSubWindow>
//#include "eIContentView.h"

using namespace IVRFramework;

IVRFramework::eMdiArea::eMdiArea(QWidget* parent)
	: QMdiArea(parent)
{
	setTabsClosable(false);
	setAcceptDrops(true);
	setMouseTracking(true);
}

IVRFramework::eMdiArea::~eMdiArea()
{

}

void IVRFramework::eMdiArea::paintEvent(QPaintEvent* paintEvent)
{
// 	Q_UNUSED(paintEvent);
// 	QPainter painter(viewport());
// 	QStyleOption opt;
// 	opt.init(this);
// 	if (paintEvent->rect().intersects(opt.rect))
// 	{
// 		style()->drawPrimitive((QStyle::PrimitiveElement)CommonStyle::PE_Workspace, &opt, &painter, this);
// 	}
}

void IVRFramework::eMdiArea::dropEvent(QDropEvent* event)
{

}

void IVRFramework::eMdiArea::dragEnterEvent(QDragEnterEvent* event)
{

}

void IVRFramework::eMdiArea::dragMoveEvent(QDragMoveEvent *event)
{

}

//eIContentView* IVRFramework::eMdiArea::ActivedContentView()
//{
//	return nullptr;
//}
//
//void IVRFramework::eMdiArea::AddContentView(eIContentView* pContentView)
//{
//
//}
//
//QVector<eIContentView*> IVRFramework::eMdiArea::ContentViewList()
//{
//	QVector<eIContentView*> vContentViewList;
//
//	QList<QMdiSubWindow*> subList = this->subWindowList();
//	unsigned int sizeNum = subList.size();
//	for (auto itr = subList.begin(); itr != subList.end(); itr++)
//	{
//		eIContentView *pContentView = dynamic_cast<eIContentView*>((*itr)->widget());
//		vContentViewList.push_back(pContentView);
//	}
//	return vContentViewList;
//}
