#include "IVRFramework/eStyle.h"
#include <QFile>
#include <QDir>
#include <QStyleFactory>

using namespace IVRFramework;


IVRFramework::eStyle::eStyle(QStyle *style)
	:QProxyStyle(style)
{

}


QStyle * IVRFramework::eStyle::baseStyle() const
{
	return styleBase();
}


void IVRFramework::eStyle::polish(QPalette &palette)
{
	// modify palette to dark
	palette.setColor(QPalette::Window, QColor(56, 56, 56));
	palette.setColor(QPalette::WindowText, Qt::lightGray);
	palette.setColor(QPalette::Disabled, QPalette::WindowText,QColor(127, 127, 127));
	palette.setColor(QPalette::Base, QColor(42, 42, 42));
	palette.setColor(QPalette::AlternateBase, QColor(66, 66, 66));
	palette.setColor(QPalette::ToolTipBase, Qt::white);
	palette.setColor(QPalette::ToolTipText, QColor(56, 56, 56));
	palette.setColor(QPalette::Text, Qt::red);
	palette.setColor(QPalette::Disabled, QPalette::Text, QColor(127, 127, 127));
	palette.setColor(QPalette::Dark, QColor(0, 0, 0));
	palette.setColor(QPalette::Shadow, QColor(20, 20, 20));
	palette.setColor(QPalette::Button, QColor("#2c2c2c"));
	palette.setColor(QPalette::ButtonText, Qt::white);
	palette.setColor(QPalette::Disabled, QPalette::ButtonText,QColor(127, 127, 127));
	palette.setColor(QPalette::BrightText, Qt::red);
	palette.setColor(QPalette::Link, QColor(42, 130, 218));
	palette.setColor(QPalette::Highlight, QColor(42, 130, 218));
	palette.setColor(QPalette::Disabled, QPalette::Highlight, QColor(80, 80, 80));
	palette.setColor(QPalette::HighlightedText, Qt::white);
	palette.setColor(QPalette::Disabled, QPalette::HighlightedText,QColor(127, 127, 127));
}

QStyle * IVRFramework::eStyle::styleBase(QStyle *style /*= Q_NULLPTR*/) const
{
	static QStyle* base =!style ? QStyleFactory::create(QStringLiteral("Fusion")) : style;
	return base;
}

IVRFramework::eStyle::eStyle()
	:eStyle(styleBase())
{

}

void eStyle::polish(QApplication *app)
{
  	QFile qfDarkstyle(QStringLiteral(":/darkstyle/darkstyle.qss"));
  	if (qfDarkstyle.open(QIODevice::ReadOnly | QIODevice::Text)) {
  		// set stylesheet
  		QString qsStylesheet = QString::fromLatin1(qfDarkstyle.readAll());
  		app->setStyleSheet(qsStylesheet);
  		qfDarkstyle.close();
  	}
}

