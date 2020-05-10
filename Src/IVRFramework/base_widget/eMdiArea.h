/* Copyright (C) 2019, GDI. All rights reserved.
*
* File    : eMdiArea.h 
* Version : 2.0
* Author  : ZhaoY
*
* 场景容器
*/ 

#pragma once
#include "IVRFramework/ivrframework_global.h"
#include <QMdiArea>
#include <QVector>
#include "IVRFramework/frame/eIContentManager.h"

namespace IVRFramework {

	class eIContentView;

	class IVRFRAMEWORK_EXPORT eMdiArea : public QMdiArea, public eIContentManager
	{
		Q_OBJECT
	public:
		eMdiArea(QWidget* parent);
		virtual ~eMdiArea();

	protected:
		virtual void paintEvent(QPaintEvent* paintEvent);
		virtual void dropEvent(QDropEvent* event);
		virtual void dragEnterEvent(QDragEnterEvent* event);
		virtual void dragMoveEvent(QDragMoveEvent *event);

	public:
		virtual eIContentView* ActivedContentView();
		virtual void AddContentView(eIContentView* pContentView);
		virtual QVector<eIContentView*> ContentViewList();
	};

}