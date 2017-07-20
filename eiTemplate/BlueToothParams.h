/************************************************************************/
/*本文件定义了生成一个蓝牙信号所需要的各种参数                          */
/************************************************************************/
#ifndef BLUETOOTHPARAMS
#define BLUETOOTHPARAMS

#define bluetooth_pi 3.141592653589793 

enum Packettype {
	ID			=	0,
	NuLLpack	=   1,
	POLL		=	2,
	FHS			=	3,
	HV1			=	4,
	HV2			=	5,
	HV3			=	6,
	DM1			=	7,
	DH1			=	8,
	DM3			=	9,
	DH3			=	10,
	DM5			=	11,
	DH5			=	12,
	AUX1		=	13
};

enum Transtype  {
	BlueTooth_SCO = 0,
	BlueTooth_ACL = 1
};

class BlueToothParams
{
public:
	// data rate
	double Rs;
	// carrier waves frequence
	double fc;
	//modulation index
	double BTb;
	//EFC state
	char efc_state[6];//5+1
	//CRC state
	char crc_state[17];//16+1
	//HEC state
	char hec_state[9];//8+1
	//Oversample
	int oversample;
	//LAP adderess
	char Lapadder[25];//24+1
	// Packet type
	Packettype packettype;
	// Transport type
	Transtype transtype;
	//payload len
	int datainmaxlen;

	BlueToothParams()
	{
		Rs = 1e6;
		fc = 2.4 * 1e9;
		BTb  = 0.35;
		oversample = 10;
		packettype = HV1;
		datainmaxlen=80;
		transtype = BlueTooth_SCO;
		strncpy(efc_state,"00000",6);
		strncpy(crc_state,"0000000000000000",17);
		strncpy(hec_state,"00000000",9);
		strncpy(Lapadder,"000000000000000000000000",25);
	}
	BlueToothParams(Packettype type)
	{
		switch(type)
		{
		case ID:
			datainmaxlen=0;
			break;

		case NuLLpack:
			datainmaxlen=0;
			break;

		case POLL:
			datainmaxlen=0;
			break;

		case HV1:
			datainmaxlen=80;
			break;

		case HV2:
			datainmaxlen=160;
			break;

		case HV3:
			datainmaxlen=240;
			break;

		case DM1:
			datainmaxlen=17;
			break;

		case DH1:
			datainmaxlen=27;
			break;

		case DM3:
			datainmaxlen=121;
			break;

		case DH3:
			datainmaxlen=183;
			break;

		case DM5:
			datainmaxlen=224;
			break;

		case DH5:
			datainmaxlen=339;
			break;

		case AUX1:
			datainmaxlen=29*8;
			break;

		default:
			assert(false);
			break;
		}
	}
};

#endif