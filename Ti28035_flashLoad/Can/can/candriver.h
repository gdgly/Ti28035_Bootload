#ifndef CAN_CANDRIVER_H_
#define CAN_CANDRIVER_H_
#include"canport.h"
#include"canmsgblock.h"

/* �������趨--------------------------------------------------------------------------------------*/
#define DATA_COMMAND            0
#define DATA_REQUEST            1
#define MAX_MSG_PRIO            7           //���ܸı�


#define ERROR_MSG               0
#define PART_MSG                1
#define COMPLETE_MSG            2
#define NO_MSG                  3

/* ���ݽ�������ı�ͷ���� ---------------------------------------------------------------------------*/
#if(DEVICE_TYPE == SYSTEM)
    #define MSG_SRC_NUM             ((SYSTEM_NUM - 1) + POWER_NUM + MONITOR_NUM) * 8
#endif

#if(DEVICE_TYPE == POWER)
    #define MSG_SRC_NUM             (SYSTEM_NUM + MONITOR_NUM) * 8
#endif

#if(DEVICE_TYPE == MONITOR)
    #define MSG_SRC_NUM             (SYSTEM_NUM + POWER_NUM) * 8
#endif


/* Ŀ�ĵ�ַ----------------------------------------------------------------------------------------*/
typedef struct{
    Uint16 type;            //����
    Uint16 ID;              //ID
}Address;

/* ����������ͷ-------------------------------------------------------------------------------------*/
typedef struct {
    Uint8   prio;           //���ȼ�
    Address dest;           //Ŀ�ĵ�ַ
    Uint8   protocol;       //����Э��
    Uint8   dataType;       //������д
    Uint16  len;            //���ݳ���
}SendImfor;


/* ��ʼ������ ������������������������������������������������������������������������������������������������������*/
void Can_nodeInit(Uint16 type, Uint16 ID, Uint16 masterID, Uint16 broadcastMask);
void Can_globalInit(void);
Uint16 Can_push(SendImfor *sendImfor, void *pMsg);
Pair Can_driverFilterCalc(NodeImfor *nodeimfor);
void Can_getNodeImfor(NodeImfor *nodeImfor, Uint16 data);
Uint16 Can_msgPro(Message *msg);

/* ����Ŀ�ĵ�ַ�趨���� ������������������������������������������������������������������������������������������*/
#if(DEVICE_TYPE == POWER)
    void Can_RequestSendToMaster(SendImfor *sendImfor,
            Uint8 prio, Uint8 protocol, Uint16 len);
    void Can_CommandSendToMaster(SendImfor *sendImfor,
            Uint8 prio, Uint8 protocol, Uint16 len);
    void Can_RequestSendToMonitor(SendImfor *sendImfor,
                Uint8 prio, Uint8 protocol, Uint16 len);
    void Can_CommandSendToMonitor(SendImfor *sendImfor,
                Uint8 prio, Uint8 protocol, Uint16 len);
#endif

#if(DEVICE_TYPE == SYSTEM)
    void Can_RequestSendToSlave(SendImfor *sendImfor, Uint16 ID,
            Uint8 prio, Uint8 protocol, Uint16 len);
    void Can_CommandSendToSlave(SendImfor *sendImfor, Uint16 ID,
            Uint8 prio, Uint8 protocol, Uint16 len);
    void Can_RequestBroadcastToSlave(SendImfor *sendImfor,
            Uint8 prio, Uint8 protocol, Uint16 len);
    void Can_CommandBroadcastToSlave(SendImfor *sendImfor,
            Uint8 prio, Uint8 protocol, Uint16 len);
    void Can_RequestSendToMonitor(SendImfor *sendImfor,
            Uint8 prio, Uint8 protocol, Uint16 len);
    void Can_CommandSendToMonitor(SendImfor *sendImfor,
                Uint8 prio, Uint8 protocol, Uint16 len);
#endif

#if(DEVICE_TYPE == MONITOR)
    void Can_RequestSendToMaster(SendImfor *sendImfor,
            Uint8 prio, Uint8 protocol, Uint16 len);
    void Can_CommandSendToMaster(SendImfor *sendImfor,
            Uint8 prio, Uint8 protocol, Uint16 len);
    void Can_RequestSendToSlave(SendImfor *sendImfor, Uint16 ID,
            Uint8 prio, Uint8 protocol, Uint16 len);
    void Can_CommandSendToSlave(SendImfor *sendImfor, Uint16 ID,
            Uint8 prio, Uint8 protocol, Uint16 len);
    void Can_RequestBroadcastToSlave(SendImfor *sendImfor,
            Uint8 prio, Uint8 protocol, Uint16 len);
    void Can_CommandBroadcastToSlave(SendImfor *sendImfor,
            Uint8 prio, Uint8 protocol, Uint16 len);

#endif

extern NodeImfor canNode;
extern MsgPiece *receiveMsgLinks[MSG_SRC_NUM];
extern ReceiveImfor receiveImfor;
extern volatile Uint16 isMBoxEmpty;

#endif /* CAN_CANDRIVER_H_ */
