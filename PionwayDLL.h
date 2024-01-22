// ------------------------------------------------------------------------
// This is the header file for C/C++ compilation of the Pionway DLL
// import library.  This file must be included within any C/C++ source
// which references the Pionway DLL methods.
//
//------------------------------------------------------------------------
// Copyright (c) 2005-2010 Pionway Incorporated
// $Rev: 0001 $ $Date: 2013-12-20 22:25:30 -0800 (Fri, 20 Dec 2013) $
//------------------------------------------------------------------------

#ifndef __Pionway_h__
#define __Pionway_h__

// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the Pionway_EXPORT
// symbol defined on the command line.  This symbol should not be defined on any project
// that uses this DLL.

#ifdef Pionway_EXPORT
#define Pionway_EXPORT __declspec(dllexport)
#else
#define Pionway_EXPORT __declspec(dllimport)
#ifdef _MSC_VER
#pragma comment(lib, "Pionway")
#endif
#endif //Pionway_EXPORT

//DLL��������ʹ��__stdcall
#define DLL_ENTRY   __stdcall

typedef unsigned int  UINT32;
typedef unsigned char UINT8;

//----------------------------------------------------------------
//Pionway_pchar����
//----------------------------------------------------------------
#if defined(_WIN32)&&(_UNICODE)
typedef wchar_t const * Pionway_pchar;
#elif defined(_WIN32)
typedef const char * Pionway_pchar
#else
typedef const char * Pionway_pchar;
#endif

#ifdef __cplusplus
#include <string>
#include <vector>
#include <stdexcept>

extern "C" {
#endif // __cplusplus

    //�����ָ������Pionway_HANDLE
    typedef void* Pionway_HANDLE;
    //���岼������
    typedef int Bool;

    //������Ĵ��ų���
#define PRODUCT_SERIAL_NUMBER_LENGTH    10
    //��������豸ID����
#define MAX_DEVICE_ID_LENGTH            32
    //������İ忨�ַ�������
#define MAX_PRODUCT_NAME_LENGTH         32

#define MAX_PRODUCT_ID_LENGTH           8

    //�����߼�����Ϊ���߼�
#ifndef TRUE
#define TRUE    1
#define FALSE   0
#endif

//����忨����ö�ٱ���
    typedef enum {
        PW_BOARD_UNKNOWM        = 0,
        PW_BOARD_XMS6301_LX45   = 1,
        PW_BOARD_XMS6301_LX75   = 2,
        PW_BOARD_XMS6301_LX100  = 3,
        PW_BOARD_XMS6301_LX150  = 4,
        PW_BOARD_XMS6302_LX45   = 5,
        PW_BOARD_XMS6302_LX75   = 6,
        PW_BOARD_XMS6302_LX100  = 7,
        PW_BOARD_XMS6302_LX150  = 8
} pwBoardModel;

//���������ö�ٱ���
typedef enum {
    PW_NO_ERR                       = 0,//����
    PW_FAILED                       = -1,//ʧ��
    PW_TIMEOUT                      = -2,//��ʱ
    PW_DONE_NOT_HIGH                = -3,//FPGA Done��û������
    PW_TRANSFER_ERROR               = -4,//�������
    PW_COMMUNICATION_ERROR          = -5,//ͨ�Ŵ���
    PW_INVALID_BITSTREAM            = -6,//FPGA bit���ļ���Ч
    PW_FILE_ERROR                   = -7,//�ļ�����
    PW_DEVICE_NOT_OPEN              = -8,//�豸���ܴ�
    PW_INVALID_ENDPOINT             = -9,//��Ч�Ķ˵�
    PW_INVALID_BLOCK_SIZE           = -10,//��Ч�Ŀ��С
    PW_I2C_RESTRICTED_ADDRESS       = -11,//I2C��ַ����
    PW_I2C_BIT_ERROR                = -12,//I2C�������
    PW_I2C_NACK                     = -13,//I2C Nack�źŴ���
    PW_I2C_UNKNOWN_STATUS           = -14,//I2C���ڲ�ȷ��״̬
    PW_UNSUPPORTED_FEATURE          = -15,//��֧�ֵĹ���
    PW_FIFO_UNDERFLOW               = -16,//FIFO�����
    PW_FIFO_OVERFLOW                = -17,//FIFO�����
    PW_DATA_ALIGNMENT_ERROR         = -18,//���ݶ������
    PW_INVALID_RESET_PROFILE        = -19,//��Ч�ĸ�λ����
    PW_INVALID_PARAMETER            = -20,//��Ч�Ĳ���
    PW_MODULE_OFF_LINE              = -21,//�豸������
    PW_FIRMWARE_UPDATE_COMPLETED    = -22 //�̼��Ѿ�����
} pwErrorCode;

    //����Ҫ�Ĳ��������ݽṹ�궨��
#ifndef PIONWAY_DEFINE
#define PW_MAX_DEVICE_ID_LENGTH     (33)    // 32-byte content + NULL termination
#define PW_SERIAL_NUMBER_LENGTH     (11)    // 10-byte content + NULL termination
#define PW_MAX_PRODUCT_NAME_LENGTH  (33)    // 32-byte content + NULL termination
#define PW_MAX_PRODUCT_ID_LENGTH    (9)     // 8-byte content + NULL termination

    // Pionway_USBSpeed types
#define PW_USBSPEED_UNKNOWN (0)
#define PW_USBSPEED_FULL    (1)
#define PW_USBSPEED_HIGH    (2)
#define PW_USBSPEED_SUPER   (3)

    // Pionway_Interface types
#define PW_INTERFACE_UNKNOWN    (0)
#define PW_INTERFACE_USB20      (2)
#define PW_INTERFACE_USB30      (3)

    // Pionway_Product types
#define PW_PRODUCT_UNKNOWM          (0)
#define PW_PRODUCT_XMS6301_LX45     (1)
#define PW_PRODUCT_XMS6301_LX75     (2)
#define PW_PRODUCT_XMS6301_LX100    (3)
#define PW_PRODUCT_XMS6301_LX150    (4)
#define PW_PRODUCT_XMS6302_LX45     (5)
#define PW_PRODUCT_XMS6302_LX75     (6)
#define PW_PRODUCT_XMS6302_LX100    (7)
#define PW_PRODUCT_XMS6302_LX150    (8)

typedef struct {
    char    deviceID[PW_MAX_DEVICE_ID_LENGTH];
    char    serialNumber[PW_SERIAL_NUMBER_LENGTH];
    char    productName[PW_MAX_PRODUCT_NAME_LENGTH];
    char    productID[PW_MAX_PRODUCT_ID_LENGTH];
    int     usbSpeedMode;
    int     firmwareMajorVersion;
    int     firmwareMinorVersion;
    int     hdlMajorVersion;
    int     hdlMinorVersion;
} pwTDeviceInfo;

#endif //Pionway_DEFINE

    //-------------------------------------------------------------------------------------------
    // Pionway������������
    //-------------------------------------------------------------------------------------------

    Pionway_EXPORT Pionway_HANDLE   DLL_ENTRY    Pionway_Construct();
    Pionway_EXPORT void             DLL_ENTRY    Pionway_Destruct(Pionway_HANDLE hnd);

    Pionway_EXPORT pwErrorCode      DLL_ENTRY    Pionway_GetDeviceCount(Pionway_HANDLE hnd, int *device_count);
    Pionway_EXPORT void             DLL_ENTRY    Pionway_GetDeviceListSerial(Pionway_HANDLE hnd, int num, char *buf);
    Pionway_EXPORT pwErrorCode      DLL_ENTRY    Pionway_OpenBySerial(Pionway_HANDLE hnd, const char *serial);
    Pionway_EXPORT pwErrorCode      DLL_ENTRY    Pionway_SetTimeout(Pionway_HANDLE hnd, int timeout);
    Pionway_EXPORT pwBoardModel     DLL_ENTRY    Pionway_GetDeviceListModel(Pionway_HANDLE hnd, int num);
    Pionway_EXPORT pwBoardModel     DLL_ENTRY    Pionway_GetBoardModel(Pionway_HANDLE hnd);
    Pionway_EXPORT pwErrorCode      DLL_ENTRY    Pionway_GetDeviceInfo(Pionway_HANDLE hnd, pwTDeviceInfo *info);
    Pionway_EXPORT pwErrorCode      DLL_ENTRY    Pionway_SetDeviceID(Pionway_HANDLE hnd, const char *strID);

    Pionway_EXPORT pwErrorCode      DLL_ENTRY    Pionway_SetWireInValue(Pionway_HANDLE hnd, int epAddr, unsigned long val, unsigned long mask);
    Pionway_EXPORT pwErrorCode      DLL_ENTRY    Pionway_UpdateWireIns(Pionway_HANDLE hnd);
    Pionway_EXPORT pwErrorCode      DLL_ENTRY    Pionway_GetWireInValue(Pionway_HANDLE hnd, int epAddr, UINT32 *val);

    Pionway_EXPORT pwErrorCode      DLL_ENTRY    Pionway_UpdateWireOuts(Pionway_HANDLE hnd);
    Pionway_EXPORT pwErrorCode      DLL_ENTRY    Pionway_GetWireOutValue(Pionway_HANDLE hnd, int epAddr, UINT32 *val);

    Pionway_EXPORT pwErrorCode      DLL_ENTRY    Pionway_ActivateTriggerIn(Pionway_HANDLE hnd, int epAddr, int bit);
    Pionway_EXPORT pwErrorCode      DLL_ENTRY    Pionway_UpdateTriggerOuts(Pionway_HANDLE hnd);
    Pionway_EXPORT pwErrorCode      DLL_ENTRY    Pionway_IsTriggered(Pionway_HANDLE hnd, int epAddr, unsigned long mask, bool *is_triggered);

    Pionway_EXPORT pwErrorCode      DLL_ENTRY    Pionway_WriteToPipeIn(Pionway_HANDLE hnd, int epAddr, long length, unsigned char *data, long *count);
    Pionway_EXPORT pwErrorCode      DLL_ENTRY    Pionway_ReadFromPipeOut(Pionway_HANDLE hnd, int epAddr, long length, unsigned char *data, long *count);

    Pionway_EXPORT pwErrorCode      DLL_ENTRY    Pionway_WriteToBlockPipeIn(Pionway_HANDLE hnd, int epAddr, int blocksize, long length, unsigned char *data, long *count);
    Pionway_EXPORT pwErrorCode      DLL_ENTRY    Pionway_ReadFromBlockPipeOut(Pionway_HANDLE    hnd, int epAddr, int blocksize, long length, unsigned char *data, long *count);

    Pionway_EXPORT pwErrorCode      DLL_ENTRY    Pionway_FlashEraseSector(Pionway_HANDLE hnd, UINT32  address);
    Pionway_EXPORT pwErrorCode      DLL_ENTRY    Pionway_FlashRead(Pionway_HANDLE hnd, UINT32  address, UINT32  length, UINT8  *buf);
    Pionway_EXPORT pwErrorCode      DLL_ENTRY    Pionway_FlashWrite(Pionway_HANDLE hnd, UINT32  address, UINT32  length, UINT8  * buf);

    Pionway_EXPORT pwErrorCode      DLL_ENTRY    Pionway_FX3FirmwareUpdate(Pionway_HANDLE hnd, const char *fileame);

    Pionway_EXPORT pwErrorCode      DLL_ENTRY    Pionway_ConfigureFPGA(Pionway_HANDLE hnd, const char *strFilename);

    Pionway_EXPORT pwErrorCode      DLL_ENTRY    Pionway_Close(Pionway_HANDLE hnd);
    Pionway_EXPORT bool             DLL_ENTRY    Pionway_IsOpen(Pionway_HANDLE hnd);
    Pionway_EXPORT bool             DLL_ENTRY    Pionway_IsPionwayEnabled(Pionway_HANDLE hnd);

    Pionway_EXPORT pwErrorCode      DLL_ENTRY    Pionway_FpgaSpiFlashProgram(Pionway_HANDLE hnd,int filemode, const char *filename);


#ifdef __cplusplus
} // extern "C"

#if !defined(Pionway_DEFINE)

//------------------------------------------------------------------------
// Pionway C++ ��װ��
//------------------------------------------------------------------------
class CPionway
{
public:
    Pionway_HANDLE h;
    enum BoardModel
    {
        BOARD_UNKNOWM       = 0,
        BOARD_XMS6301_LX45  = 1,
        BOARD_XMS6301_LX75  = 2,
        BOARD_XMS6301_LX100 = 3,
        BOARD_XMS6301_LX150 = 4,
        BOARD_XMS6302_LX45  = 5,
        BOARD_XMS6302_LX75  = 6,
        BOARD_XMS6302_LX100 = 7,
        BOARD_XMS6302_LX150 = 8
    };

    //���������ö�ٱ���
    enum ErrorCode
    {
        NO_ERR                      =  0,//����
        FAILED                      = -1,//ʧ��
        TIMEOUT                     = -2,//��ʱ
        DONE_NOT_HIGH               = -3,//FPGA Done��û������
        TRANSFER_ERROR              = -4,//�������
        COMMUNICATION_ERROR         = -5,//ͨ�Ŵ���
        INVALID_BITSTREAM           = -6,//FPGA bit���ļ���Ч
        FILE_ERROR                  = -7,//�ļ�����
        DEVICE_NOT_OPEN             = -8,//�豸���ܴ�
        INVALID_ENDPOINT            = -9,//��Ч�Ķ˵�
        INVALID_BLOCK_SIZE          = -10,//��Ч�Ŀ��С
        I2C_RESTRICTED_ADDRESS      = -11,//I2C��ַ����
        I2C_BIT_ERROR               = -12,//I2C�������
        I2C_NACK                    = -13,//I2C Nack�źŴ���
        I2C_UNKNOWN_STATUS          = -14,//I2C���ڲ�ȷ��״̬
        UNSUPPORTED_FEATURE         = -15,//��֧�ֵĹ���
        FIFO_UNDERFLOW              = -16,//FIFO�����
        FIFO_OVERFLOW               = -17,//FIFO�����
        DATA_ALIGNMENT_ERROR        = -18,//���ݶ������
        INVALID_RESET_PROFILE       = -19,//��Ч�ĸ�λ����
        INVALID_PARAMETER           = -20,//��Ч�Ĳ���
        MODULE_OFF_LINE             = -21,//�豸������
        FIRMWARE_UPDATE_COMPLETED   = -22
    };
private:
    //bool to_bool(Bool x);
    //Bool from_bool(bool x);

    explicit CPionway(Pionway_HANDLE hnd);

public:
    CPionway();
    ~CPionway();
    ErrorCode GetDeviceCount(int *device_count);
    std::string GetDeviceListSerial(int num);
    BoardModel GetDeviceListModel(int num);
    BoardModel GetBoardModel();
    ErrorCode OpenBySerial(std::string str = "");
    ErrorCode SetTimeout(int timeout);
    ErrorCode GetDeviceInfo(pwTDeviceInfo *info);
    ErrorCode SetDeviceID(const std::string& str);

    ErrorCode SetWireInValue(int epAddr, UINT32 val, UINT32 mask = 0xffffffff);
    ErrorCode UpdateWireIns();
    ErrorCode GetWireInValue(int epAddr, UINT32 *val);

    ErrorCode UpdateWireOuts();
    ErrorCode GetWireOutValue(int epAddr, UINT32 *val);

    ErrorCode ActivateTriggerIn(int epAddr, int bit);
    ErrorCode UpdateTriggerOuts();
    ErrorCode IsTriggered(int epAddr, UINT32 mask, bool *is_triggered);

    ErrorCode WriteToPipeIn(int epAddr, long length, unsigned char *data, long *count);
    ErrorCode ReadFromPipeOut(int epAddr, long length, unsigned char *data, long *count);
    ErrorCode WriteToBlockPipeIn(int epAddr, int blocksize, long length, unsigned char *data, long *count);
    ErrorCode ReadFromBlockPipeOut(int epAddr, int blocksize, long length, unsigned char *data, long *count);

    ErrorCode FlashEraseSector(UINT32  address);
    ErrorCode FlashRead(UINT32  address, UINT32  length, UINT8  *buf);
    ErrorCode FlashWrite(UINT32  address, UINT32  length, UINT8  * buf);

    ErrorCode FX3FirmwareUpdate(const char *filename);
    ErrorCode ConfigureFPGA(const std::string strFilename);

    ErrorCode Close();
    bool IsOpen();
    bool IsPionwayEnabled();

    ErrorCode FpgaSpiFlashProgram(int filemode, const char *filename);
};

//------------------------------------------------------------------------
// Pionway C++ ��װ��
//------------------------------------------------------------------------
inline CPionway::CPionway(Pionway_HANDLE hnd)
{
    h = hnd;
}

inline CPionway::CPionway()
{
    h = Pionway_Construct();
}
inline CPionway::~CPionway()
{
    Pionway_Destruct(h);
}

inline CPionway::ErrorCode CPionway::GetDeviceCount(int *device_count)
{
    return((CPionway::ErrorCode)Pionway_GetDeviceCount(h, device_count));
}

inline std::string CPionway::GetDeviceListSerial(int num)
{
    char str[PRODUCT_SERIAL_NUMBER_LENGTH + 1];
    Pionway_GetDeviceListSerial(h, num, str);
    str[PRODUCT_SERIAL_NUMBER_LENGTH] = '\0';
    return(std::string(str));
}

inline CPionway::BoardModel CPionway::GetDeviceListModel(int num)
{
    return((CPionway::BoardModel)Pionway_GetDeviceListModel(h, num));
}

inline CPionway::BoardModel CPionway::GetBoardModel()
{
    return((CPionway::BoardModel)Pionway_GetBoardModel(h));
}

inline CPionway::ErrorCode CPionway::OpenBySerial(std::string str)
{
    return((CPionway::ErrorCode) Pionway_OpenBySerial(h, str.c_str()));
}

inline CPionway::ErrorCode CPionway::SetTimeout(int timeout)
{
    return((CPionway::ErrorCode)Pionway_SetTimeout(h, timeout));
}

inline CPionway::ErrorCode CPionway::GetDeviceInfo(pwTDeviceInfo *info)
{
    return((CPionway::ErrorCode) Pionway_GetDeviceInfo(h, info));
}

inline CPionway::ErrorCode CPionway::SetDeviceID(const std::string& str)
{
    return((CPionway::ErrorCode)Pionway_SetDeviceID(h, str.c_str()));
}

inline CPionway::ErrorCode CPionway::SetWireInValue(int epAddr, UINT32 val, UINT32 mask)
{
    return((CPionway::ErrorCode) Pionway_SetWireInValue(h, epAddr, val, mask));
}

inline CPionway::ErrorCode CPionway::UpdateWireIns()
{
    return((CPionway::ErrorCode)Pionway_UpdateWireIns(h));
}

inline CPionway::ErrorCode CPionway::GetWireInValue(int epAddr, UINT32 *val)
{
    return((CPionway::ErrorCode)Pionway_GetWireInValue(h, epAddr, val));
}

inline CPionway::ErrorCode CPionway::UpdateWireOuts()
{
    return((CPionway::ErrorCode)Pionway_UpdateWireOuts(h));
}

inline CPionway::ErrorCode CPionway::GetWireOutValue(int epAddr, UINT32 *val)
{
    return((CPionway::ErrorCode)Pionway_GetWireOutValue(h, epAddr, val));
}

inline CPionway::ErrorCode CPionway::ActivateTriggerIn(int epAddr, int bit)
{
    return((CPionway::ErrorCode) Pionway_ActivateTriggerIn(h, epAddr, bit));
}
inline CPionway::ErrorCode CPionway::UpdateTriggerOuts()
{
    return((CPionway::ErrorCode)Pionway_UpdateTriggerOuts(h));
}
inline CPionway::ErrorCode CPionway::IsTriggered(int epAddr, UINT32 mask, bool *is_triggered)
{
    return((CPionway::ErrorCode)Pionway_IsTriggered(h, epAddr, mask, is_triggered));
}

inline CPionway::ErrorCode CPionway::WriteToPipeIn(int epAddr, long length, unsigned char *data, long *count)
{
    return((CPionway::ErrorCode)Pionway_WriteToPipeIn(h, epAddr, length, data, count));
}

inline  CPionway::ErrorCode CPionway::ReadFromPipeOut(int epAddr, long length, unsigned char *data, long *count)
{
    return((CPionway::ErrorCode)Pionway_ReadFromPipeOut(h, epAddr, length, data, count));
}

inline CPionway::ErrorCode CPionway::WriteToBlockPipeIn(int epAddr, int blocksize, long length, unsigned char *data, long *count)
{
    return((CPionway::ErrorCode)Pionway_WriteToBlockPipeIn(h, epAddr, blocksize, length, data, count));
}

inline CPionway::ErrorCode CPionway::ReadFromBlockPipeOut(int epAddr, int blocksize, long length, unsigned char *data, long *count)
{
    return((CPionway::ErrorCode)Pionway_ReadFromBlockPipeOut(h, epAddr, blocksize, length, data, count));
}

inline CPionway::ErrorCode CPionway::FlashEraseSector(UINT32  address)
{
    return((CPionway::ErrorCode)Pionway_FlashEraseSector(h, address));
}
inline CPionway::ErrorCode CPionway::FlashRead(UINT32  address, UINT32  length, UINT8  *buf)
{
    return((CPionway::ErrorCode)Pionway_FlashRead(h, address, length, buf));
}

inline CPionway::ErrorCode CPionway::FlashWrite(UINT32  address, UINT32  length, UINT8  *buf)
{
    return((CPionway::ErrorCode)Pionway_FlashWrite(h, address, length, buf));
}

inline CPionway::ErrorCode CPionway::FX3FirmwareUpdate(const char *filename)
{
    return((CPionway::ErrorCode)Pionway_FX3FirmwareUpdate(h, filename));
}

inline     CPionway::ErrorCode CPionway::ConfigureFPGA(const std::string strFilename)
{
    return((CPionway::ErrorCode)Pionway_ConfigureFPGA(h, strFilename.c_str()));
}

inline CPionway::ErrorCode CPionway::Close()
{
    return((CPionway::ErrorCode) Pionway_Close(h));
}

inline bool CPionway::IsOpen()
{
    return ((bool)Pionway_IsOpen(h));
}

inline bool CPionway::IsPionwayEnabled()
{
    return ((bool)Pionway_IsPionwayEnabled(h));
}

inline CPionway::ErrorCode CPionway::FpgaSpiFlashProgram(int filemode,const char *filename)
{
    return((CPionway::ErrorCode) Pionway_FpgaSpiFlashProgram(h,filemode, filename));
}


#endif // !defined(Pionway_DEFINE)

#endif // __cplusplus

#endif // __Pionway_h__