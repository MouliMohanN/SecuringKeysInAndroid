//
// Created by Mouli N on 2019-06-26.
//

#include <jni.h>
#include <string>
using namespace std;

extern "C" JNIEXPORT jstring JNICALL Java_com_example_securingkeysinandroid_SecringKeysActivity_encryptKey(
        JNIEnv *env,
        jobject ,
        jstring  encryptedKey_InJString) {


    const jclass stringClass = env->GetObjectClass(encryptedKey_InJString);
    const jmethodID getBytes = env->GetMethodID(stringClass, "getBytes", "(Ljava/lang/String;)[B");
    const jbyteArray stringJbytes = (jbyteArray) env->CallObjectMethod(encryptedKey_InJString, getBytes, env->NewStringUTF("UTF-8"));

    size_t length = (size_t) env->GetArrayLength(stringJbytes);
    jbyte* pBytes = env->GetByteArrayElements(stringJbytes, NULL);

    std::string encryptedKey_InCppString = std::string((char *)pBytes, length);
    env->ReleaseByteArrayElements(stringJbytes, pBytes, JNI_ABORT);

    env->DeleteLocalRef(stringJbytes);
    env->DeleteLocalRef(stringClass);


    string encryptedKey = "";
    int salt = 4;
    int asciiMinValue = 32;
    int asciiMaxValue = 126;

    // traverse text
    for (int i=0;i<encryptedKey_InCppString.length();i++)
    {
        // apply transformation to each character
        int asciiCipher = int (encryptedKey_InCppString[i]) + salt;
        if (asciiCipher > asciiMaxValue) {
            int diffValue = asciiCipher - asciiMaxValue;
            asciiCipher = asciiMinValue + diffValue;
        }
        encryptedKey += char(asciiCipher);
    }

    return env->NewStringUTF(encryptedKey.c_str());
}

extern "C" JNIEXPORT jstring JNICALL Java_com_example_securingkeysinandroid_SecringKeysActivity_decryptKey(
        JNIEnv *env,
        jobject ,
        jstring  decryptedKey_InJString
        ) {

    const jclass stringClass = env->GetObjectClass(decryptedKey_InJString);
    const jmethodID getBytes = env->GetMethodID(stringClass, "getBytes", "(Ljava/lang/String;)[B");
    const jbyteArray stringJbytes = (jbyteArray) env->CallObjectMethod(decryptedKey_InJString, getBytes, env->NewStringUTF("UTF-8"));

    size_t length = (size_t) env->GetArrayLength(stringJbytes);
    jbyte* pBytes = env->GetByteArrayElements(stringJbytes, NULL);

    std::string decryptedKey_InCppString = std::string((char *)pBytes, length);
    env->ReleaseByteArrayElements(stringJbytes, pBytes, JNI_ABORT);

    env->DeleteLocalRef(stringJbytes);
    env->DeleteLocalRef(stringClass);


    string decryptedKey = "";
    int salt = 4;
    int asciiMinValue = 33;
    int asciiMaxValue = 127;

    // traverse text
    for (int i=0;i<decryptedKey_InCppString.length();i++)
    {
        // apply transformation to each character
        int asciiCipher = int (decryptedKey_InCppString[i]) - salt;
        if (asciiCipher < asciiMinValue) {
            int diffValue = asciiMinValue - asciiCipher;
            asciiCipher = asciiMaxValue - diffValue;
        }
        decryptedKey += char(asciiCipher);
    }
    return env->NewStringUTF(decryptedKey.c_str());
}