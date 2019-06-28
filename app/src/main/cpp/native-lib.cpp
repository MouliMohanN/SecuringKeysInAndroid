//
// Created by Mouli N on 2019-06-26.
//

#include <jni.h>
#include <string>

extern "C" JNIEXPORT jstring JNICALL

Java_com_example_securingkeysinandroid_ui_trails_TrailsActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}
