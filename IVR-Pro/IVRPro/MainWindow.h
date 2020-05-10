#pragma once

#include <QtWidgets/QMainWindow>
#include "IVRFramework/base_widget/eMainWindow.h"

class QMdiArea;
class QMdiSubWindow;
class QCloseEvent;

class MainWindow : public IVRFramework::eMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = Q_NULLPTR);

protected:

	protected Q_SLOTS:
	void slotSubWindowActivated(QMdiSubWindow* subWindow);

protected:
	void closeEvent(QCloseEvent* event) Q_DECL_OVERRIDE;

private:
	QMdiArea* m_mdiArea;
	QMdiSubWindow* m_oldSubWindow;
};
