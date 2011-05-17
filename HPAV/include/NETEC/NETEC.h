//NETEC.h
#ifndef __NETEC_H__
#define __NETEC_H__

#include <NETEC/NETEC_Export.h>

class NETEC
{
public:
	typedef enum{
		BROTHER=0,
		PARENT,
		CHILD,
	}DOMAIN_TYPE;

	typedef enum{
		ERR_OK=0,
		ERR_DOMAIN_TYPE_UNMATCHED,
		ERR_DOMAIN_LEVEL_UNMATCHED,
	}ERR_CODE;
public:
	static const char*GetVersion(void);
};

//֡�ʿ���ģʽ
typedef enum
{
	FRAME_RATE_CONTROL_MODE_FULL=0,	//ȫ֡�ʿ���
	FRAME_RATE_CONTROL_MODE_HALF,	//��֡�ʿ���
	FRAME_RATE_CONTROL_MODE_AUTO,	//�Զ�֡�ʿ���
}FRAME_RATE_CONTROL_MODE;

typedef enum
{
	FRAME_TYPE_CONTROL_MODE_MAIN=0,	//����
	FRAME_TYPE_CONTROL_MODE_SUB,	//����
	FRAME_TYPE_CONTROL_MODE_QSUB,	//����
	FRAME_TYPE_CONTROL_MODE_NULL,	//NULL
}FRAME_TYPE_CONTROL_MODE;

#endif
