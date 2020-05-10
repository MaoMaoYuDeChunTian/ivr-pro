#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include "IVRFramework/eBaseWidget.h"
#include "IVRFramework/ivrframework_global.h"

namespace IVRFramework
{
class IVRFRAMEWORK_EXPORT eAutoHideWidget : public eBaseWidget
{
	Q_OBJECT

public:
	enum Direction
	{
		None,
		TOP,
		Down,
		Left,
		Right
	};
	//相对位置
	enum RelatePos
	{
		L,//左
		Mid,//中
		R//右
	};

public:
	eAutoHideWidget(QWidget *parent = 0, Qt::WindowFlags flags = 0);
	~eAutoHideWidget();

public:
	void SetAttr(Direction direction, bool bIsAutoHide);
	void SetRelatePos(RelatePos relatePos, int offset);
	void InitState(QPoint pos, bool bIsHide);
	QPushButton* GetButtonCtrl();
protected:
	bool eventFilter(QObject *watched, QEvent *event);
	void leaveEvent(QEvent *event);
	void enterEvent(QEvent *event);
	void showEvent(QShowEvent *event);
	void closeEvent(QCloseEvent *event);

private:
	bool isCanHide();
	void hideWidget();
	void showWidget();
	void updateCtrButtonPos();
	void onEnter();
	void onLeave();

protected slots:
	void slotClick();

protected:
	//控制按钮
	QPushButton* m_btnCtrl;
	//自动隐藏到哪边
	Direction m_enDriection;
	//是否自动隐藏
	bool m_bIsAutoHide;
	//当前状态
	bool m_bIsHide;
	//父窗体的宽度
	int m_nParentWidth;
	//灵敏度
	int m_nSusceptibility;
	//动画时长
	int m_nAnimaDuration;
	//相对位置
	RelatePos m_relatePos;
	//相对偏移量
	int m_offset;
	//窗体是否关闭
	bool m_bClose;
};
}
