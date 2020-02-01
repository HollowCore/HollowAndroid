//
//  HCNumber+JNI.h
//  HollowJava
//
//  Created by Matt Stoker on 1/30/20.
//  Copyright © 2020 HollowCore. All rights reserved.
//
//

#include "HCNumber+JNI.h"

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - JNI Convenience
//----------------------------------------------------------------------------------------------------------------------------------
void HCNumberJNIInstallReferenceInJObject(JNIEnv* env, jobject thiz, HCNumberRef self) {
    jclass clazz = (*env)->GetObjectClass(env, thiz);
    jfieldID fieldID = (*env)->GetFieldID(env, clazz, HCNumberJNIReferenceFieldID, HCNumberJNIReferenceFieldSignature);
    (*env)->SetLongField(env, thiz, fieldID, (jlong)self);
}

void HCNumberJNIReleaseReferenceInJObject(JNIEnv* env, jobject thiz) {
    jclass clazz = (*env)->GetObjectClass(env, thiz);
    jfieldID fieldID = (*env)->GetFieldID(env, clazz, HCNumberJNIReferenceFieldID, HCNumberJNIReferenceFieldSignature);
    HCNumberRef self = (HCNumberRef)(*env)->GetLongField(env, thiz, fieldID);
    (*env)->SetLongField(env, thiz, fieldID, (jlong)NULL);
    HCRelease(self);
}

HCNumberRef HCNumberJNIFromJObject(JNIEnv* env, jobject thiz) {
    jclass clazz = (*env)->GetObjectClass(env, thiz);
    jfieldID fieldID = (*env)->GetFieldID(env, clazz, HCNumberJNIReferenceFieldID, HCNumberJNIReferenceFieldSignature);
    HCNumberRef self = (HCNumberRef)(*env)->GetLongField(env, thiz, fieldID);
    return self;
}

jobject HCNumberJNINewJObject(JNIEnv* env, HCNumberRef self) {
    jclass clazz = (*env)->FindClass(env, HCNumberJNIClass);
    jmethodID constructor = (*env)->GetMethodID(env, clazz, "<init>", "()V");
    jobject thiz = (*env)->NewObject(env, clazz, constructor);
    HCNumberJNIInstallReferenceInJObject(env, thiz, self);
    return thiz;
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Construction
//----------------------------------------------------------------------------------------------------------------------------------
JNIEXPORT void JNICALL
Java_com_hollowcore_hollowjava_data_HollowNumber_initWithBooleanNative(JNIEnv *env, jobject thiz, jboolean b) {
    HCNumberRef self = HCNumberCreateWithBoolean(b);
    HCNumberJNIInstallReferenceInJObject(env, thiz, self);
}

JNIEXPORT void JNICALL
Java_com_hollowcore_hollowjava_data_HollowNumber_initWithIntegerNative(JNIEnv *env, jobject thiz, jint integer) {
    HCNumberRef self = HCNumberCreateWithInteger(integer);
    HCNumberJNIInstallReferenceInJObject(env, thiz, self);
}

JNIEXPORT void JNICALL
Java_com_hollowcore_hollowjava_data_HollowNumber_initWithRealNative(JNIEnv *env, jobject thiz, jdouble real) {
    HCNumberRef self = HCNumberCreateWithReal(real);
    HCNumberJNIInstallReferenceInJObject(env, thiz, self);
}

JNIEXPORT void JNICALL
Java_com_hollowcore_hollowjava_data_HollowNumber_finalizeNative(JNIEnv *env, jobject thiz) {
    HCNumberJNIReleaseReferenceInJObject(env, thiz);
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Object Polymorphic Functions
//----------------------------------------------------------------------------------------------------------------------------------
JNIEXPORT jboolean JNICALL
Java_com_hollowcore_hollowjava_data_HollowNumber_isEqualNative(JNIEnv *env, jobject thiz, jobject otherInstance) {
    HCNumberRef self = HCNumberJNIFromJObject(env, thiz);
    HCNumberRef other = HCNumberJNIFromJObject(env, otherInstance);
    return (jboolean)HCNumberIsEqual(self, other);
}

JNIEXPORT jlong JNICALL
Java_com_hollowcore_hollowjava_data_HollowNumber_hashNative(JNIEnv *env, jobject thiz) {
    HCNumberRef self = HCNumberJNIFromJObject(env, thiz);
    return self == NULL ? 0 : HCNumberHashValue(self);
}

JNIEXPORT jstring JNICALL
Java_com_hollowcore_hollowjava_data_HollowNumber_toStringNative(JNIEnv *env, jobject thiz) {
    HCNumberRef self = HCNumberJNIFromJObject(env, thiz);
    // TODO: memoryStream
//    HCNumberPrint(self, memoryStream);
    jstring stringValue = (*env)->NewStringUTF(env, "TODO: Implement Number toStringNative");
//    HCRelease(memoryStream);
    return stringValue;
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Conversion
//----------------------------------------------------------------------------------------------------------------------------------
JNIEXPORT jboolean JNICALL
Java_com_hollowcore_hollowjava_data_HollowNumber_isBooleanNative(JNIEnv *env, jobject thiz) {
    HCNumberRef self = HCNumberJNIFromJObject(env, thiz);
    HCBoolean isBoolean = HCNumberIsBoolean(self);
    return (jboolean)isBoolean;
}

JNIEXPORT jboolean JNICALL
Java_com_hollowcore_hollowjava_data_HollowNumber_asBooleanNative(JNIEnv *env, jobject thiz) {
    HCNumberRef self = HCNumberJNIFromJObject(env, thiz);
    HCBoolean asBoolean = HCNumberAsBoolean(self);
    return (jboolean)asBoolean;
}

JNIEXPORT jboolean JNICALL
Java_com_hollowcore_hollowjava_data_HollowNumber_isIntegerNative(JNIEnv *env, jobject thiz) {
    HCNumberRef self = HCNumberJNIFromJObject(env, thiz);
    HCBoolean isInteger = HCNumberIsInteger(self);
    return (jboolean)isInteger;
}

JNIEXPORT jint JNICALL
Java_com_hollowcore_hollowjava_data_HollowNumber_asIntegerNative(JNIEnv *env, jobject thiz) {
    HCNumberRef self = HCNumberJNIFromJObject(env, thiz);
    HCInteger asInteger = HCNumberAsInteger(self);
    return (jint)asInteger;
}

JNIEXPORT jboolean JNICALL
Java_com_hollowcore_hollowjava_data_HollowNumber_isRealNative(JNIEnv *env, jobject thiz) {
    HCNumberRef self = HCNumberJNIFromJObject(env, thiz);
    HCBoolean isReal = HCNumberIsReal(self);
    return (jboolean)isReal;
}

JNIEXPORT jdouble JNICALL
Java_com_hollowcore_hollowjava_data_HollowNumber_asRealNative(JNIEnv *env, jobject thiz) {
    HCNumberRef self = HCNumberJNIFromJObject(env, thiz);
    HCReal asReal = HCNumberAsReal(self);
    return (jdouble)asReal;
}
