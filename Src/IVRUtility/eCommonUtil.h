/* Copyright (C) 2019, GDI. All rights reserved.
*
* File    : eCommonUtil.h
* Version : 2.0
* Author  : ZhaoY
*
* 工具方法类
*/

#pragma once


#include "ivrutility_global.h"
#include <QDomComment>
class QFile;

namespace IVRUtility
{
	class IVRUTILITY_EXPORT eCommonUtil
	{
	public:
		static QFile* OpenXml(QString filePath, QDomDocument& document, QDomElement& dRoot);
	};
}
