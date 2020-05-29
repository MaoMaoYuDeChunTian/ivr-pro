#pragma once
#include <QString>
#include "IVRFramework/ivrframework_global.h"

namespace IVRFramework
{

class IVRFRAMEWORK_EXPORT eIOperation
{
public:
	virtual bool CanRedo();
	virtual bool CanUndo();
	virtual void Do();
	virtual void Redo();
	virtual void Undo();
	virtual const QString& GetDescription();

protected:
	eIOperation();
	virtual ~eIOperation();

protected:
	QString m_strDescription;
	bool m_bDone;
};

}
