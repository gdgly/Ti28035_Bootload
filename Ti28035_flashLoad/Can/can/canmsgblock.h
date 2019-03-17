#ifndef CAN_CANMSGBLOCK_H_
#define CAN_CANMSGBLOCK_H_

#include"canport.h"

/* Can���ݰ�----------------------------------------------------------------------------------------*/
typedef struct{
    union COB_ID{
        Uint32 all;
        struct{
            Uint32 source   :10;            //Դ��ַ
            Uint32 target   :10;            //Ŀ�ĵ�ַ
            Uint32 protocol :4;         //Э������
            Uint32 isLast   :1;         //�Ƿ������һ������Ƭ
            Uint32 dataType :1;         //������д
            Uint32 prio     :3;         //�������ȼ�
        }bit;
    }cob_id;
    Uint16 len;
    Uint16 rtr;
    Uint16 data[4];
}Message;

/* ���ݽ������� ------------------------------------------------------------------------------*/
typedef struct MsgPieceTag{
    struct MsgPieceTag *pNext;
    Message msg;
}MsgPiece;

void Can_poolInit(void *poolSto, Uint16 poolSize, Uint16 blockSize);
void Can_msgInsert(MsgPiece *pm);
Uint16 Can_msgPop(Message *pMsg);
/* 2017.03.08 ��ȡ����Ԫ�ظ��� ����*/
Uint16 Can_msgNum(void);

extern MsgPiece canbuffSto[MSG_PIECE_NUM];
extern MemPool canPool;
extern MsgPiece *rCHead;
extern MsgPiece *sCHead;
#endif /* CAN_CANMSGBLOCK_H_ */
