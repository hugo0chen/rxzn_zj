#ifndef DEFINE_H_
#define DEFINE_H_

#define	uchar 	unsigned char
#define uint	unsigned int
#define INT8U   unsigned char
#define INT16U  unsigned int
#define ulong   unsigned long


#define MAX_DATA_SIZE 255

#define ZJ_PARA_FLASH_ADDR 0x01000
/*�����洢��ַ*/
#define MAC_H_ADDR			1
#define MAC_L_ADDR			2
#define ID_H_ADDR			3
#define ID_L_ADDR			4
#define WEIGH_INIT_1_ADDR	5
#define WEIGH_INIT_2_ADDR	6
#define WEIGH_INIT_3_ADDR	7
#define WEIGH_INIT_4_ADDR	8
#define SYS_CH_ADDR			9


/*type����*/
#define CH_REG	0x10	//Ƶ��ƥ��

#define CALL	0x21	//����
#define ACK		0x21	//Ӧ��
#define C_REG	0x22	//����������
#define A_REG	0x23	//Ӧ��������

#define START	0x30	//��Һ��ʼ
#define RUN		0x31	//��Һ������
#define STOP	0x32	//��Һ����
#define BEAT	0x33	//��Һ��Ԫ�����ź�

#define W_REG	0x34	//��Һ��Ԫ����

#define ZZ_ACK	0x36	//��ת��Ӧ��

/*ϵͳ״̬ */
#define VOL_10		0x01
#define VOL_25		0x02
#define VOL_50		0x03
#define SYS_NULL	0xB0
#define SYS_STRAT	0xB1
#define SYS_RUN		0xB2
#define SYS_STOP	0xB3
#define SYS_REG		0xB4
#define SYS_TEST	0xB5
#define SYS_SCAN	0xB6
#define SYS_SLEEP	0xBF
#define MODE_P		1
#define MODE_G		0

#define	HEAD_H	    0x88
#define	HEAD_L	    0xCC

//************ASCLLָ��*************
#define	SOH			1		//���⿪ʼ
#define	STX			2		//���Ŀ�ʼ
#define	ETX			3		//���Ľ���
#define	ENQ			5		//����
#define	BEL			7		//����
#define	NAK			21		//�ܾ�����
#define	SYN			22		//ͬ������
#define	ETB			23		//��������
#define	ESC			27		//���
#define	DEL			127		//ɾ��
#define	ERR			24		//ȡ��������
#define	SET			16		//����״̬
#define	SUB			0x1a	//�油������
#define	LF			0x0a	//����
#define	CR			0x0d	//�س�


#define RDY		    0xE1
#define EOT		    0xE0	//�������

#define W_SLEEP		0xF1
#define W_UNSLEEP	0xF0

#define	TRUE	    1
#define	FALSE	    0

#define MSG_LEN          13  // total length of message, first two octets are 0
#define MSG_HDR_H        2   // message header high byte postion
#define MSG_HDR_L        3   // message header low byte postion
#define MSG_DEV_ID       4   // device identifier
#define MSG_OP_TYPE      5   // operation type
#define MSG_BODY_0       6   // message body octet 0
#define MSG_BODY_1       7   // message body octet 1
#define MSG_BODY_2       8   // message body octet 2
#define MSG_BODY_3       9   // message body octet 3
#define MSG_BODY_4       10  // message body octet 4
#define MSG_BODY_5       11  // message body octet 5

#define CPU_F            ((double)8000000) 
#define Delay_ms(x)      __delay_cycles((long)(CPU_F *(double)(x)/1000))

#endif /* DEFINE_H_ */
