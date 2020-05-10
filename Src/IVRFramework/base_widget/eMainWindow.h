/* Copyright (C) 2019, GDI. All rights reserved.
*
* File    : eMainWindow.h 
* Version : 2.0
* Author  : ZhaoY
*
* mainwindow 基类
*/ 


#pragma once

#include "IVRFramework/ivrframework_global.h"
#include <QMainWindow>
#include <QPoint>
#include <QIcon>
#include <QDockWidget>

class QToolBar;
class QMenuBar;
class QToolButton;
class QVBoxLayout;

namespace IVRFramework
{
	class eMainWindowTitle;
	class eFramelessHelper;

	class IVRFRAMEWORK_EXPORT eMainWindow : public QWidget
	{
		Q_OBJECT
	public:
		eMainWindow(QWidget* parent = nullptr);
		virtual ~eMainWindow();

		void setTitleHeight(int height);
		int getTitleHeight();
		void setTitleName(const QString& name);
		QString getTitleName();
		void setTitleIcon(const QIcon& icon);

		void setMinBtnVisible(bool bVisible);
		void setMaxBtnVisible(bool bVisible);
		void setCloseBtnVisible(bool bVisible);

		void setCentralWidget(QWidget* widget);
		void addDockWidget(Qt::DockWidgetArea area, QDockWidget *dockwidget);
		QMenuBar* GetMenuBar();
		QMainWindow* getQMainWindow();

	protected:
		virtual void mouseDoubleClickEvent(QMouseEvent *event);

	private:
		void SetUpUi();

	signals:
		void sigMainWindowClosed();

		protected slots:
		void onClosed();
		void onMinSize();
		void onMaxResize();

	private:
		QMainWindow* m_mainWindow;

		int m_TitleHeight;
		QWidget* m_mainWidget;
		eMainWindowTitle* m_titleWidget;
		eFramelessHelper* m_pHelper;
		QVBoxLayout* m_mainVbox;
	};
}
