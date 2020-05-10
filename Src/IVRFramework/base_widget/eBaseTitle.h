#pragma once

#include "IVRFramework/ivrframework_global.h"
#include <QWidget>
#include <QIcon>

class QMenuBar;
class QToolButton;
class QPushButton;
class QHBoxLayout;

namespace IVRFramework
{
	class IVRFRAMEWORK_EXPORT eBaseTitle : public QWidget
	{
		Q_OBJECT
	public:
		eBaseTitle(QString title, QWidget* parent = nullptr);
		~eBaseTitle();

	public:
		void setHeight(int height);
		int getHeight();
		void setTitleName(const QString& name);
		QString getTitleName();
		void setIcon(const QIcon& icon);

		void setMiniBtnVisible(bool isVisible);
		void setMaxBtnVisible(bool isVisible);
		void setCloseBtnVisible(bool isVisible);

	signals:
		void sigMiniBtnClicked();
		void sigMaxBtnClicked();
		void sigCloseBtnClicked();

	protected:
		QToolButton* m_titleBtn;
		QHBoxLayout* m_containerHbox;
		QPushButton* m_minBtn;
		QPushButton* m_maxBtn;
		QPushButton* m_closeBtn;
	};
}

