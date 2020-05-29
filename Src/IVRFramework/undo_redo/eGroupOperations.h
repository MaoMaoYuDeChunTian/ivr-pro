#pragma once
#include <QList>
#include "IVRFramework/undo_redo/eIOperation.h"
#include "IVRFramework/ivrframework_global.h"

namespace IVRFramework
{
class IVRFRAMEWORK_EXPORT eGroupOperations : public eIOperation
{
public:
	eGroupOperations();
	virtual ~eGroupOperations();
	virtual void Do();
	virtual void Undo();
	virtual const QString& GetDescription();
	virtual void SetDescription(const QString& strDescription);
	virtual void AddOperation(eIOperation* ptrOpt);

protected:
	QList<eIOperation*> m_lstOpt;
};

}
