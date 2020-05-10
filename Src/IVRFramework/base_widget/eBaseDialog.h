/* Copyright (C) 2019, GDI. All rights reserved.
*
* File    : .h
* Version : 2.0
* Author  : ZhaoY
*
*
*/

#pragma once

#include <QDialog>
#include <QtWidgets/QStyleOption>
#include "IVRFramework/ivrframework_global.h"

class QPushButton;
class QLabel;
class QVBoxLayout;
class QHBoxLayout;
class QMouseEvent;

namespace IVRFramework {

	class eFramelessHelper;

	class IVRFRAMEWORK_EXPORT eBaseDialog : public QDialog
	{
		Q_OBJECT
	public:
		eBaseDialog(QWidget* parent = 0, Qt::WindowFlags f = 0);
		virtual ~eBaseDialog();

		void SetTitleHeight(int height);
		void SetTitleName(const QString& name);
		void setMinBtnVisible(bool bVisible);
		void setMaxBtnVisible(bool bVisible);
		void setCloseBtnVisible(bool bVisible);

		void SetWidgetMoveble(bool isable);
		void SetWidgetResizeble(bool isable);

		void SetContentWidget(QWidget* w);
		void SetTitleContentWidget(QWidget* w);

	protected:
		virtual void mouseDoubleClickEvent(QMouseEvent *event);

	private:
		void SetUpUi();

	signals:
		void sigDialogClosed();

		protected slots:
		void onClosed();
		void onMinSize();
		void onMaxResize();

	private:
		int m_TitleHeight;
		eFramelessHelper* m_pHelper;

		QLabel* m_Title;
		QWidget* m_TitleBar;
		QWidget* m_TitleContainer;
		QPushButton* m_BtnMinimize;//最小化按钮
		QPushButton* m_BtnMaximize;//最大化按钮
		QPushButton* m_BtnClose;//关闭按钮

		QVBoxLayout* m_ContentLayout;
		QHBoxLayout* m_TitleContentLayout;
	};
}