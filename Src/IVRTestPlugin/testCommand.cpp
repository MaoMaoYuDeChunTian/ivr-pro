#include "testCommand.h"
#include <QObject>
#include <QDialog>
#include <QMessageBox>
#include "IVRFramework/base_widget/eMainWindow.h"
#include "IVRFramework/eService.h"


TestCommand::TestCommand()
{

}

TestCommand::~TestCommand()
{

}

bool TestCommand::IsEnable()
{
	return true;
}

void TestCommand::Execute(QObject* sender, QString param)
{
	QMessageBox::about(eService::GetInstance()->m_pMainWindow, QObject::tr("tip"), QObject::tr("xin xi chuang ti wufa gaibian daxiao"));
	/*QDialog* _dialog = new QDialog(eService::GetInstance()->m_pMainWindow);
	_dialog->resize(500, 300);
	_dialog->setAttribute(Qt::WA_DeleteOnClose);
	_dialog->show();*/
}
