#pragma once

#include "IVRFramework/command/eICommand.h"

using namespace IVRFramework;

class TestCommand : public eICommand
{
	DECLARE_CLASS(TestCommand)
public:
	TestCommand();
	~TestCommand();

public:
	virtual bool IsEnable();
	virtual void Execute(QObject* sender, QString param);

};

