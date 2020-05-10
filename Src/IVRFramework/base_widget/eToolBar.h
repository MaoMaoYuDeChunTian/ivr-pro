#pragma once
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QAction>
#include <QtWidgets/QPushButton>
#include <QToolBar>
#include "IVRFramework/ivrframework_global.h"

namespace IVRFramework
{
class IVRFRAMEWORK_EXPORT eToolBar : public QFrame
{
	Q_OBJECT
public:
	eToolBar(QWidget* parent = 0, Qt::WindowFlags f = 0);
	~eToolBar();

public:
	bool IsAutoHide();
	void SetIsAutoHide(bool bIsAutoHide);
	QToolBar* GetToolBar();

private:
	void setupUi();
	void createConnection();

	protected slots:
		void slotClose(bool checked);
		void slotMinimize(bool checked);
		void slotMenuBarMinimize(bool checked);

protected:
	virtual bool eventFilter(QObject *watched, QEvent *event);
	virtual void paintEvent(QPaintEvent *event);

private:
	QPushButton *m_AppIcon;
	QLabel *m_AppTitle;
	QToolBar *m_Toolbar;
	QPushButton *m_btnClose;
	QPushButton *m_btnMin;
	QPushButton *m_btnMenuBarMinimize;
	bool m_bIsAutoHide;
};
}