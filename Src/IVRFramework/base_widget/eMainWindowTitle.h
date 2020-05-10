#pragma once

#include "IVRFramework/ivrframework_global.h"
#include "IVRFramework/base_widget/eBaseTitle.h"

namespace IVRFramework
{
	class IVRFRAMEWORK_EXPORT eMainWindowTitle : public eBaseTitle
	{
		Q_OBJECT
	public:
		eMainWindowTitle(QString title,QWidget* parent = nullptr);
		~eMainWindowTitle();

	public:
		QMenuBar* getMenuBar();

	private:
		QMenuBar* m_menuBar;
	};
}

