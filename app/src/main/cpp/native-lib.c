#include <jni.h>
#include "HollowCore/Source/HollowCore.h"

JNIEXPORT jstring JNICALL
Java_com_hollowcore_hollowshapes_MainActivity_stringFromJNI(JNIEnv* env, jobject this) {
    HCStringRef hello = HCStringCreateWithCString("Hello from HollowCore");
    jstring helloJava = (*env)->NewStringUTF(env, HCStringAsCString(hello));
    HCRelease(hello);
    return helloJava;
}
