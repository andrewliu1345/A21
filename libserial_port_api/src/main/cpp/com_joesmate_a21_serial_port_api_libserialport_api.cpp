/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
#include <string.h>
#include "SerialPortHelp.h"
#include <android/log.h>
#include "CMD.h"
#include "com_joesmate_a21_serial_port_api_libserialport_api.h"
#include "ToolFun.h"
#include "FisCard.h"
#include "CodeKeyboard.h"

#define MAX_BUFFER_SIZE            (1024)

JNIEXPORT jint JNICALL Java_com_joesmate_a21_serial_1port_1api_libserialport_1api_device_1open
        (JNIEnv *env, jclass _class, jstring path, jint BaudRate) {
    jboolean iscopy = false;
    const char *path_utf = env->GetStringUTFChars(path, &iscopy);
    int fd = SerialPortHelp::dev_open(path_utf, BaudRate, 0);
    env->ReleaseStringUTFChars(path, path_utf);
    return fd;
}

JNIEXPORT jint JNICALL Java_com_joesmate_a21_serial_1port_1api_libserialport_1api_device_1set_1baud
        (JNIEnv *env, jclass _class, jint device, jint BaudRate) {
    if (device < 0)
        return device;
    return SerialPortHelp::set_opt(device, BaudRate, 8, 'N', 1);
}

JNIEXPORT void JNICALL Java_com_joesmate_a21_serial_1port_1api_libserialport_1api_device_1close
        (JNIEnv *env, jclass _class, jint device) {
    SerialPortHelp::dev_close(device);
}


JNIEXPORT jint JNICALL Java_com_joesmate_a21_serial_1port_1api_libserialport_1api_device_1write
        (JNIEnv *env, jclass _class, jint device, jbyteArray out, jint len) {
    if (device < 0)
        return device;
    SerialPortHelp::flush(device);
    jbyte *olddata = (jbyte *) env->GetByteArrayElements(out, 0);
    unsigned char *OutputRepor = new unsigned char[len];
    memset(OutputRepor, 0, len);
    memcpy(OutputRepor, olddata, len);
    env->ReleaseByteArrayElements(out, olddata, 0);
    int iRet = SerialPortHelp::dev_write(device, OutputRepor, len);
    delete[] OutputRepor;
    return iRet;
}


JNIEXPORT jint JNICALL Java_com_joesmate_a21_serial_1port_1api_libserialport_1api_device_1read
        (JNIEnv *env, jclass _class, jint device, jbyteArray in, jlong timeout) {
    if (!device)
        return device;
    unsigned char InputBuffer[4096] = {0};
    int len = SerialPortHelp::dev_read(device, InputBuffer, timeout);
    if (len < 0)
        len = -1;
    else
        env->SetByteArrayRegion(in, 0, len, (jbyte *) InputBuffer);

    return len;
}


JNIEXPORT jint JNICALL Java_com_joesmate_a21_serial_1port_1api_libserialport_1api_device_1read_1all
        (JNIEnv *env, jclass _class, jint device, jbyteArray in) {
    if (!device)
        return device;
    unsigned char InputBuffer[2000] = {0};
    int len = SerialPortHelp::dev_read_all(device, InputBuffer);
    if (len < 0)
        return len;
    env->SetByteArrayRegion(in, 0, len, (jbyte *) InputBuffer);
    return len;
}

JNIEXPORT void JNICALL Java_com_joesmate_a21_serial_1port_1api_libserialport_1api_flush
        (JNIEnv *env, jclass _class, jint device) {
    if (!device)
        return;
    SerialPortHelp::flush(device);

}

JNIEXPORT jint JNICALL
Java_com_joesmate_a21_serial_1port_1api_libserialport_1api_device_1ReadBaseMsg
        (JNIEnv *env, jclass _class, jint idevice, jbyteArray pucCHMsg, jbyteArray pucPHMsg,
         jlong OutTime) {
    unsigned long start_time = ToolFun::GetTickCount();
    unsigned long end_time = ToolFun::GetTickCount();
    unsigned long Subtime = 0;

    unsigned char InputReport[4096] = {0};
    int len = 0;
/*HANDLE idevice = device_open(VID, PID);*/
    if (!idevice) {
//device_close(idevice);
        return -1;
    }
    int iRet = 0;
    int srclen = 0;
    unsigned char send[64] = {0};
    //SerialPortHelp::flush(idevice);
//    srclen = sizeof(CMD::ActiveTypeB);
//    ToolFun::toPackData(0x60, CMD::ActiveTypeB, srclen, send, &srclen);
//    iRet = SerialPortHelp::dev_write(idevice, send, srclen);
//    if (iRet < 0) {
//        // return -1;
//    }
//    iRet = SerialPortHelp::dev_read(idevice, InputReport, 100);
//    if (iRet <= 0) {
////       // return -1;
//    }

    unsigned char CHMsg[258] = {0};
    unsigned char PHMsg[1024] = {0};
    __android_log_print(ANDROID_LOG_DEBUG,
                        "Java_com_joesmate_a21_serial_1port_1api_libserialport_1api_device_1ReadBaseMsg",
                        "读身份证1");

    SerialPortHelp::flush(idevice);
    srclen = sizeof(CMD::ReadIdInfo);
    memset(send, 0, 64);
    ToolFun::toPackData(0x60, CMD::ReadIdInfo, srclen, send, &srclen);
    iRet = SerialPortHelp::dev_write(idevice, send, srclen);
    if (iRet < 0) {
        return iRet;
    }
    __android_log_print(ANDROID_LOG_DEBUG,
                        "Java_com_joesmate_a21_serial_1port_1api_libserialport_1api_device_1ReadBaseMsg",
                        "读身份证2");
    while (true) {
        end_time = ToolFun::GetTickCount();
        Subtime = end_time - start_time;
        if (Subtime > OutTime) {
            __android_log_print(ANDROID_LOG_DEBUG,
                                "Java_com_joesmate_a21_serial_1port_1api_libserialport_1api_device_1ReadBaseMsg",
                                "读身份证超时");
            return -17;
        }
        memset(InputReport, 0, 4096);
        iRet = SerialPortHelp::dev_read(idevice, InputReport, 1000);

        if (iRet < 19) {
            continue;
        }
//        __android_log_print(ANDROID_LOG_DEBUG,
//                            "Java_com_joesmate_a21_serial_1port_1api_libserialport_1api_device_1ReadBaseMsg",
//                            "读身份证3");

        len = iRet;
        unsigned char chmsg[4096] = {0};
        memcpy(chmsg, InputReport, len);
//        __android_log_print(ANDROID_LOG_DEBUG,
//                            "Java_com_joesmate_a21_serial_1port_1api_libserialport_1api_device_1ReadBaseMsg",
//                            "len=%d,chmsg=%s",len,ToolFun::bytesToHexstring(chmsg, len));
        if (chmsg[1] != 0xAA || chmsg[2] != 0xAA || chmsg[3] != 0x96 || chmsg[4] != 0x69)
            continue;
        if (chmsg[9] != 0x90 || chmsg[10] != 0x01) {
            return -1;
        }
//        __android_log_print(ANDROID_LOG_DEBUG,
//                            "Java_com_joesmate_a21_serial_1port_1api_libserialport_1api_device_1ReadBaseMsg",
//                            "读身份证4");
        CHMsg[0] = 0xff;
        CHMsg[1] = 0xfe;
        memcpy(CHMsg + 2, chmsg + 14, 256);
        __android_log_print(ANDROID_LOG_DEBUG,
                            "Java_com_joesmate_a21_serial_1port_1api_libserialport_1api_device_1ReadBaseMsg",
                            "CHMsg=%s", ToolFun::bytesToHexstring(CHMsg, 258).c_str());
        memcpy(PHMsg, chmsg + 14 + 256, 1024);
        __android_log_print(ANDROID_LOG_DEBUG,
                            "Java_com_joesmate_a21_serial_1port_1api_libserialport_1api_device_1ReadBaseMsg",
                            "PHMsg=%s", ToolFun::bytesToHexstring(PHMsg, 1024).c_str());

        env->SetByteArrayRegion(pucCHMsg, 0, 258, (jbyte *) CHMsg);
        env->SetByteArrayRegion(pucPHMsg, 0, 1024, (jbyte *) PHMsg);
//device_close(idevice);
        return 0;
    }

}

JNIEXPORT jint JNICALL
Java_com_joesmate_a21_serial_1port_1api_libserialport_1api_device_1ReadBaseMsgFp
        (JNIEnv *env, jclass _class, jint idevice, jbyteArray pucCHMsg, jbyteArray pucPHMsg,
         jbyteArray pucFPMsg,
         jlong OutTime) {
    unsigned long start_time = ToolFun::GetTickCount();
    unsigned long end_time = ToolFun::GetTickCount();
    unsigned long Subtime = 0;

    unsigned char InputReport[4096] = {0};
    int len = 0;
/*HANDLE idevice = device_open(VID, PID);*/
    if (!idevice) {
//device_close(idevice);
        return -1;
    }
    int iRet = 0;
    int srclen = 0;
    unsigned char send[64] = {0};
    SerialPortHelp::flush(idevice);
//    srclen = sizeof(CMD::ActiveTypeB);
//    ToolFun::toPackData(0x60, CMD::ActiveTypeB, srclen, send, &srclen);
//    iRet = SerialPortHelp::dev_write(idevice, send, srclen);
//    if (iRet < 0) {
//        return -1;
//    }
//    iRet = SerialPortHelp::dev_read(idevice, InputReport, 100);
//    if (iRet <= 0) {
//        return -1;
//    }

    unsigned char CHMsg[258] = {0};
    unsigned char PHMsg[1024] = {0};
    unsigned char FPMsg[1024] = {0};
    __android_log_print(ANDROID_LOG_DEBUG,
                        "Java_com_joesmate_a21_serial_1port_1api_libserialport_1api_device_1ReadBaseMsg",
                        "读身份证1");

    SerialPortHelp::flush(idevice);
    srclen = sizeof(CMD::ReadIdInfo);
    memset(send, 0, 64);
    ToolFun::toPackData(0x60, CMD::ReadIdInfo, srclen, send, &srclen);
    iRet = SerialPortHelp::dev_write(idevice, send, srclen);
    if (iRet < 0) {
        return iRet;
    }
    __android_log_print(ANDROID_LOG_DEBUG,
                        "Java_com_joesmate_a21_serial_1port_1api_libserialport_1api_device_1ReadBaseMsg",
                        "读身份证2");
    while (true) {
        end_time = ToolFun::GetTickCount();
        Subtime = end_time - start_time;
        if (Subtime > OutTime) {
            return -1;
        }
        memset(InputReport, 0, 4096);
        iRet = SerialPortHelp::dev_read(idevice, InputReport, 5);

        if (iRet < 19) {
            continue;
        }
//        __android_log_print(ANDROID_LOG_DEBUG,
//                            "Java_com_joesmate_a21_serial_1port_1api_libserialport_1api_device_1ReadBaseMsg",
//                            "读身份证3");

        len = iRet;
        unsigned char chmsg[4096] = {0};
        memcpy(chmsg, InputReport, len);
//        __android_log_print(ANDROID_LOG_DEBUG,
//                            "Java_com_joesmate_a21_serial_1port_1api_libserialport_1api_device_1ReadBaseMsg",
//                            "len=%d,chmsg=%s",len,ToolFun::bytesToHexstring(chmsg, len));
        if (chmsg[1] != 0xAA || chmsg[2] != 0xAA || chmsg[3] != 0x96 || chmsg[4] != 0x69)
            continue;
        if (chmsg[9] != 0x90 || chmsg[10] != 0x01) {
            return -1;
        }
//        __android_log_print(ANDROID_LOG_DEBUG,
//                            "Java_com_joesmate_a21_serial_1port_1api_libserialport_1api_device_1ReadBaseMsg",
//                            "读身份证4");
        CHMsg[0] = 0xff;
        CHMsg[1] = 0xfe;
        memcpy(CHMsg + 2, chmsg + 14, 256);
        __android_log_print(ANDROID_LOG_DEBUG,
                            "Java_com_joesmate_a21_serial_1port_1api_libserialport_1api_device_1ReadBaseMsg",
                            "CHMsg=%s", ToolFun::bytesToHexstring(CHMsg, 258).c_str());

        memcpy(PHMsg, chmsg + 14 + 256, 1024);
        __android_log_print(ANDROID_LOG_DEBUG,
                            "Java_com_joesmate_a21_serial_1port_1api_libserialport_1api_device_1ReadBaseMsg",
                            "PHMsg=%s", ToolFun::bytesToHexstring(PHMsg, 1024).c_str());

        memcpy(FPMsg, chmsg + 14 + 256 + 1024, 1024);
        __android_log_print(ANDROID_LOG_DEBUG,
                            "Java_com_joesmate_a21_serial_1port_1api_libserialport_1api_device_1ReadBaseMsg",
                            "PHMsg=%s", ToolFun::bytesToHexstring(PHMsg, 1024).c_str());

        env->SetByteArrayRegion(pucCHMsg, 0, 258, (jbyte *) CHMsg);
        env->SetByteArrayRegion(pucPHMsg, 0, 1024, (jbyte *) PHMsg);
        env->SetByteArrayRegion(pucFPMsg, 0, 1024, (jbyte *) FPMsg);
        return 0;
    }

}

JNIEXPORT jint JNICALL Java_com_joesmate_a21_serial_1port_1api_libserialport_1api_card_1ADPU
        (JNIEnv *env, jclass _class, jint idevice, jint slen, jbyteArray datasend, jintArray rlen,
         jbyteArray datareceive, jint timeout) {
    jbyte *olddata = (jbyte *) env->GetByteArrayElements(datasend, 0);
    unsigned char send[1024] = {0};
    unsigned char receive[1024] = {0};
    int retlen[1] = {0};
    memcpy(send, olddata, slen);
    int iRet = FisCard::card_ADPU(idevice, slen, send, &retlen[0], receive, timeout);
    if (iRet != 0) {
        return -1;
    }
    env->SetIntArrayRegion(rlen, 0, 1, (jint *) retlen);
    env->SetByteArrayRegion(datareceive, 0, retlen[0], (jbyte *) receive);
    return 0;
}

JNIEXPORT jint JNICALL
Java_com_joesmate_a21_serial_1port_1api_libserialport_1api_device_1ReadBaseData
        (JNIEnv *env, jclass _class, jint idevice, jbyteArray pucData, jlong OutTime) {
    unsigned long start_time = ToolFun::GetTickCount();
    unsigned long end_time = ToolFun::GetTickCount();
    unsigned long Subtime = 0;

    unsigned char InputReport[4096] = {0};
    int len = 0;
/*HANDLE idevice = device_open(VID, PID);*/
    if (!idevice) {
//device_close(idevice);
        return -1;
    }

    int iRet = 0;
    int srclen = 0;
    unsigned char send[64] = {0};
    SerialPortHelp::flush(idevice);
//    srclen = sizeof(CMD::ActiveTypeB);
//    ToolFun::toPackData(0x60, CMD::ActiveTypeB, srclen, send, &srclen);
//    iRet = SerialPortHelp::dev_write(idevice, send, srclen);
//    if (iRet < 0) {
//       // return -1;
//    }
//    iRet = SerialPortHelp::dev_read(idevice, InputReport, 100);
//    if (iRet <= 0) {
//       // return -1;
//    }
    __android_log_print(ANDROID_LOG_DEBUG,
                        "Java_com_joesmate_a21_serial_1port_1api_libserialport_1api_device_1ReadBaseData",
                        "读身份证1");

    SerialPortHelp::flush(idevice);
    srclen = sizeof(CMD::ReadIdInfo);
    memset(send, 0, 64);
    ToolFun::toPackData(0x60, CMD::ReadIdInfo, srclen, send, &srclen);
    iRet = SerialPortHelp::dev_write(idevice, send, srclen);
    if (iRet < 0) {
        return iRet;
    }
    __android_log_print(ANDROID_LOG_DEBUG,
                        "Java_com_joesmate_a21_serial_1port_1api_libserialport_1api_device_1ReadBaseData",
                        "读身份证2");
    while (true) {
        end_time = ToolFun::GetTickCount();
        Subtime = end_time - start_time;
        if (Subtime > OutTime) {
            return -1;
        }
        memset(InputReport, 0, 4096);
        iRet = SerialPortHelp::dev_read(idevice, InputReport, 5);

        if (iRet < 19) {
            continue;
        }
        len = iRet;


//        __android_log_print(ANDROID_LOG_DEBUG,
//                            "Java_com_joesmate_a21_serial_1port_1api_libserialport_1api_device_1ReadBaseMsg",
//                            "len=%d,chmsg=%s",len,ToolFun::bytesToHexstring(chmsg, len));
        if (InputReport[1] != 0xAA || InputReport[2] != 0xAA || InputReport[3] != 0x96 ||
            InputReport[4] != 0x69)
            continue;
        env->SetByteArrayRegion(pucData, 0, len - 5, (jbyte *) (InputReport + 5));
        if (InputReport[9] != 0x90 || InputReport[10] != 0x01) {
            return -1;
        }
        return len - 5;
    }
}

JNIEXPORT jint JNICALL
Java_com_joesmate_a21_serial_1port_1api_libserialport_1api_device_1ReadBaseDataFp
        (JNIEnv *env, jclass _class, jint idevice, jbyteArray pucData, jlong OutTime) {
    unsigned long start_time = ToolFun::GetTickCount();
    unsigned long end_time = ToolFun::GetTickCount();
    unsigned long Subtime = 0;

    unsigned char InputReport[4096] = {0};
    int len = 0;
/*HANDLE idevice = device_open(VID, PID);*/
    if (!idevice) {
//device_close(idevice);
        return -1;
    }
    int iRet = 0;
    int srclen = 0;
    unsigned char send[64] = {0};
    SerialPortHelp::flush(idevice);
//    srclen = sizeof(CMD::ActiveTypeB);
//    ToolFun::toPackData(0x60, CMD::ActiveTypeB, srclen, send, &srclen);
//    iRet = SerialPortHelp::dev_write(idevice, send, srclen);
//    if (iRet < 0) {
//       // return -1;
//    }
//    iRet = SerialPortHelp::dev_read(idevice, InputReport, 100);
//    if (iRet <= 0) {
//        //return -1;
//    }

    __android_log_print(ANDROID_LOG_DEBUG,
                        "Java_com_joesmate_a21_serial_1port_1api_libserialport_1api_device_1ReadBaseData",
                        "读身份证1");

    SerialPortHelp::flush(idevice);
    srclen = sizeof(CMD::ReadIdInfo);
    memset(send, 0, 64);
    ToolFun::toPackData(0x60, CMD::ReadIdInfo, srclen, send, &srclen);
    iRet = SerialPortHelp::dev_write(idevice, send, srclen);
    if (iRet < 0) {
        return iRet;
    }
    __android_log_print(ANDROID_LOG_DEBUG,
                        "Java_com_joesmate_a21_serial_1port_1api_libserialport_1api_device_1ReadBaseData",
                        "读身份证2");
    while (true) {
        end_time = ToolFun::GetTickCount();
        Subtime = end_time - start_time;
        if (Subtime > OutTime) {
            return -1;
        }
        memset(InputReport, 0, 4096);
        iRet = SerialPortHelp::dev_read(idevice, InputReport, 5);

        if (iRet < 19) {
            continue;
        }
        len = iRet;


//        __android_log_print(ANDROID_LOG_DEBUG,
//                            "Java_com_joesmate_a21_serial_1port_1api_libserialport_1api_device_1ReadBaseMsg",
//                            "len=%d,chmsg=%s",len,ToolFun::bytesToHexstring(chmsg, len));
        if (InputReport[1] != 0xAA || InputReport[2] != 0xAA || InputReport[3] != 0x96 ||
            InputReport[4] != 0x69)
            continue;
        env->SetByteArrayRegion(pucData, 0, len - 5, (jbyte *) (InputReport + 5));
        if (InputReport[9] != 0x90 || InputReport[10] != 0x01) {
            return -1;
        }
        return len - 5;
    }
}

JNIEXPORT jint JNICALL Java_com_joesmate_a21_serial_1port_1api_libserialport_1api_GetAID
        (JNIEnv *env, jclass _class, jint idevice, jbyte cardno, jbyteArray _AIDList) {
    if (!idevice)
        return idevice;
    char aidlist[1024] = {0};
    unsigned char ictype = (unsigned char) cardno;
    __android_log_print(ANDROID_LOG_DEBUG,
                        "Java_com_joesmate_a21_serial_1port_1api_libserialport_1api_GetAID",
                        "getAid------------");
    int st = FisCard::GetAID(idevice, ictype, aidlist);
    if (st != 0)
        return -1;
    int len = strlen(aidlist);
    env->SetByteArrayRegion(_AIDList, 0, len, (jbyte *) aidlist);
    return 0;
}

JNIEXPORT jint JNICALL Java_com_joesmate_a21_serial_1port_1api_libserialport_1api_RestDefaultKey
        (JNIEnv *env, jclass _class, jint idevice, jbyteArray Mkey, jbyteArray Wkey) {

    unsigned char m_key[16] = {0};
    unsigned char w_key[16] = {0};
    _MW_KEY mwkey;
    //unsigned char index = (unsigned char) idevice;
    jbyte *m_Key = (jbyte *) env->GetByteArrayElements(Mkey, 0);
    jbyte *w_Key = (jbyte *) env->GetByteArrayElements(Wkey, 0);

    memcpy(m_key, m_Key, 16);
    memcpy(w_key, w_Key, 16);

    env->ReleaseByteArrayElements(Mkey, m_Key, 0);
    env->ReleaseByteArrayElements(Wkey, w_Key, 0);
    int iRet = 0;
    for (int i = 0; i < 16; ++i) {
        mwkey.MKeyIndex = i;
        mwkey.MKeyLength = 2;
        memcpy(mwkey.MKeyTab, m_key, 16);

        mwkey.WKeyIndex = i;
        mwkey.WKeyLength = 2;
        memcpy(mwkey.WKeyTab, w_key, 16);

        iRet = CodeKeyboard::FactoryReset(idevice, mwkey);
        iRet += iRet;
    }
    if (iRet == 0)
        return 0;
    else
        return -1;
}

JNIEXPORT jint JNICALL Java_com_joesmate_a21_serial_1port_1api_libserialport_1api_DownMKey
        (JNIEnv *env, jclass _class, jint idevice, jbyte Mindex, jbyte Mlength, jbyteArray Mkey) {
    unsigned char m_key[16] = {0};
    _ZMK key;
    jbyte *m_Key = (jbyte *) env->GetByteArrayElements(Mkey, 0);
    memcpy(m_key, m_Key, 16);
    key.MKeyIndex = (unsigned char) Mindex;
    key.MKeyLength = (unsigned char) Mlength;
    memcpy(key.MKeyTab, m_key, 16);
    env->ReleaseByteArrayElements(Mkey, m_Key, 0);
    return CodeKeyboard::DownLoadMKey(idevice, key);
}

JNIEXPORT jint JNICALL Java_com_joesmate_a21_serial_1port_1api_libserialport_1api_DownWKey
        (JNIEnv *env, jclass _class, jint idevice, jbyte Mindex, jbyte Windex, jbyte Wlength,
         jbyteArray Wkey) {
    unsigned char w_key[16] = {0};
    _ZWK key;
    jbyte *w_Key = (jbyte *) env->GetByteArrayElements(Wkey, 0);
    memcpy(w_key, w_Key, 16);
    key.MKeyIndex = (unsigned char) Mindex;
    key.WKeyIndex = (unsigned char) Windex;
    key.WKeyLength = (unsigned char) Wlength;
    memcpy(key.WKeyTab, w_key, 16);
    env->ReleaseByteArrayElements(Wkey, w_Key, 0);
    return CodeKeyboard::DownLoadWKey(idevice, key);
}

JNIEXPORT jint JNICALL Java_com_joesmate_a21_serial_1port_1api_libserialport_1api_ActiveKey
        (JNIEnv *env, jclass _class, jint idevice, jbyte Mindex, jbyte Windex) {
    _ACTWKey act;
    act.MKeyIndex = (unsigned char) Mindex;
    act.WKeyIndex = (unsigned char) Windex;
    return CodeKeyboard::ActiveWKey(idevice, act);
}


JNIEXPORT jint JNICALL Java_com_joesmate_a21_serial_1port_1api_libserialport_1api_Raw2Bmp
        (JNIEnv *env, jclass _class, jbyteArray raw, jint len, jbyteArray bmp, jint width,
         jint heigth) {
    int st = -1;

    unsigned char *cImage = new unsigned char[len];
    memset(cImage, 0, len);
    // memset(cImage, 0, sizeof(cImage));
    unsigned char *cBmp = new unsigned char[len + 1079];
    //memset(cBmp, 0, sizeof(cBmp));
//    jbyte *old = (jbyte *) env->GetByteArrayElements(raw, 0);
//    memcpy(cImage, old, 16);
    env->GetByteArrayRegion(raw, 0, len, (jbyte *) cImage);

    st = ToolFun::RAW2BMP(cImage, cBmp, width, heigth);
    if (st == 0) {
        env->SetByteArrayRegion(bmp, 0, len + 1079, (jbyte *) cBmp);
    }
    delete[] cImage;
    delete[] cBmp;
    return st;
}

JNIEXPORT jint JNICALL Java_com_joesmate_a21_serial_1port_1api_libserialport_1api_RF_1Control
        (JNIEnv *env, jclass _class, jint idevice, jbyte code) {
    unsigned char _code = (unsigned char) code;
    unsigned char cmd[9] = {0x00};
    unsigned char InputReport[4096] = {0};
    memcpy(cmd, CMD::RFControl, 9);
    cmd[8] = _code;
    unsigned char send[64] = {0};
    int srclen = 0;
    srclen = sizeof(CMD::RFControl);
    ToolFun::toPackData(0x60, cmd, srclen, send, &srclen);
    int iRet = SerialPortHelp::dev_write(idevice, send, srclen);
    if (iRet < 0) {
        return iRet;
    }
    iRet = SerialPortHelp::dev_read(idevice, InputReport, 100);
    if (iRet <= 0) {
        //return -1;
    }
    return -1;
}