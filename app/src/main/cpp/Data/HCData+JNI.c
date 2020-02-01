//
//  HCData+JNI.h
//  HollowJava
//
//  Created by Matt Stoker on 1/30/20.
//  Copyright © 2020 HollowCore. All rights reserved.
//
//

#include "HCData+JNI.h"

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - JNI Convenience
//----------------------------------------------------------------------------------------------------------------------------------
void HCDataJNIInstallReferenceInJObject(JNIEnv* env, jobject thiz, HCDataRef self) {
    jclass clazz = (*env)->GetObjectClass(env, thiz);
    jfieldID fieldID = (*env)->GetFieldID(env, clazz, HCDataJNIReferenceFieldID, HCDataJNIReferenceFieldSignature);
    (*env)->SetLongField(env, thiz, fieldID, (jlong)self);
}

void HCDataJNIReleaseReferenceInJObject(JNIEnv* env, jobject thiz) {
    jclass clazz = (*env)->GetObjectClass(env, thiz);
    jfieldID fieldID = (*env)->GetFieldID(env, clazz, HCDataJNIReferenceFieldID, HCDataJNIReferenceFieldSignature);
    HCDataRef self = (HCDataRef)(*env)->GetLongField(env, thiz, fieldID);
    (*env)->SetLongField(env, thiz, fieldID, (jlong)NULL);
    HCRelease(self);
}

HCDataRef HCDataJNIFromJObject(JNIEnv* env, jobject thiz) {
    jclass clazz = (*env)->GetObjectClass(env, thiz);
    jfieldID fieldID = (*env)->GetFieldID(env, clazz, HCDataJNIReferenceFieldID, HCDataJNIReferenceFieldSignature);
    HCDataRef self = (HCDataRef)(*env)->GetLongField(env, thiz, fieldID);
    return self;
}

jobject HCDataJNINewJObject(JNIEnv* env, HCDataRef self) {
    jclass clazz = (*env)->FindClass(env, HCDataJNIClass);
    jmethodID constructor = (*env)->GetMethodID(env, clazz, "<init>", "()V");
    jobject thiz = (*env)->NewObject(env, clazz, constructor);
    HCDataJNIInstallReferenceInJObject(env, thiz, self);
    return thiz;
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Construction
//----------------------------------------------------------------------------------------------------------------------------------
JNIEXPORT void JNICALL
Java_com_hollowcore_hollowjava_data_HollowData_initWithBytesNative(JNIEnv *env, jobject thiz, jbyteArray byte_array) {
    HCByte* bytes = (HCByte*)(*env)->GetByteArrayElements(env, byte_array, NULL);
    HCInteger size = (*env)->GetArrayLength(env, byte_array);
    HCDataRef self = HCDataCreateWithBytes(size, bytes);
    (*env)->ReleaseByteArrayElements(env, byte_array, (jbyte*)bytes, 0);
    HCDataJNIInstallReferenceInJObject(env, thiz, self);
}

JNIEXPORT void JNICALL
Java_com_hollowcore_hollowjava_data_HollowData_initWithBooleanNative(JNIEnv *env, jobject thiz, jboolean b) {
    HCDataRef self = HCDataCreateWithBoolean(b);
    HCDataJNIInstallReferenceInJObject(env, thiz, self);
}

JNIEXPORT void JNICALL
Java_com_hollowcore_hollowjava_data_HollowData_initWithIntegerNative(JNIEnv *env, jobject thiz, jint integer) {
    HCDataRef self = HCDataCreateWithInteger(integer);
    HCDataJNIInstallReferenceInJObject(env, thiz, self);
}

JNIEXPORT void JNICALL
Java_com_hollowcore_hollowjava_data_HollowData_initWithRealNative(JNIEnv *env, jobject thiz, jdouble real) {
    HCDataRef self = HCDataCreateWithReal(real);
    HCDataJNIInstallReferenceInJObject(env, thiz, self);
}

JNIEXPORT void JNICALL
Java_com_hollowcore_hollowjava_data_HollowData_finalizeNative(JNIEnv *env, jobject thiz) {
    HCDataJNIReleaseReferenceInJObject(env, thiz);
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Object Polymorphic Functions
//----------------------------------------------------------------------------------------------------------------------------------
JNIEXPORT jboolean JNICALL
Java_com_hollowcore_hollowjava_data_HollowData_isEqualNative(JNIEnv *env, jobject thiz, jobject otherInstance) {
    HCDataRef self = HCDataJNIFromJObject(env, thiz);
    HCDataRef other = HCDataJNIFromJObject(env, otherInstance);
    return (jboolean)HCDataIsEqual(self, other);
}

JNIEXPORT jlong JNICALL
Java_com_hollowcore_hollowjava_data_HollowData_hashNative(JNIEnv *env, jobject thiz) {
    HCDataRef self = HCDataJNIFromJObject(env, thiz);
    return self == NULL ? 0 : HCDataHashValue(self);
}

JNIEXPORT jstring JNICALL
Java_com_hollowcore_hollowjava_data_HollowData_toStringNative(JNIEnv *env, jobject thiz) {
    HCDataRef self = HCDataJNIFromJObject(env, thiz);
    // TODO: memoryStream
//    HCDataPrint(self, memoryStream);
    jstring stringValue = (*env)->NewStringUTF(env, "TODO: Implement HollowData toStringNative");
//    HCRelease(memoryStream);
    return stringValue;
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Attributes
//----------------------------------------------------------------------------------------------------------------------------------
JNIEXPORT jboolean JNICALL
Java_com_hollowcore_hollowjava_data_HollowData_isEmptyNative(JNIEnv *env, jobject thiz) {
    HCDataRef self = HCDataJNIFromJObject(env, thiz);
    HCBoolean isEmpty = HCDataIsEmpty(self);
    return (jboolean)isEmpty;
}

JNIEXPORT jint JNICALL
Java_com_hollowcore_hollowjava_data_HollowData_getSizeNative(JNIEnv *env, jobject thiz) {
    HCDataRef self = HCDataJNIFromJObject(env, thiz);
    HCInteger size = HCDataSize(self);
    return (jint)size;
}

JNIEXPORT jbyteArray JNICALL
Java_com_hollowcore_hollowjava_data_HollowData_getBytesNative(JNIEnv *env, jobject thiz) {
    HCDataRef self = HCDataJNIFromJObject(env, thiz);
    const HCByte* bytes = HCDataBytes(self);
    HCInteger size = HCDataSize(self);
    jbyteArray byte_array = (*env)->NewByteArray(env, (jsize)size);
    (*env)->SetByteArrayRegion(env, byte_array, 0, (jsize)size, (const jbyte*)bytes);
    return byte_array;
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Conversion
//----------------------------------------------------------------------------------------------------------------------------------
JNIEXPORT jboolean JNICALL
Java_com_hollowcore_hollowjava_data_HollowData_isBooleanNative(JNIEnv *env, jobject thiz) {
    HCDataRef self = HCDataJNIFromJObject(env, thiz);
    HCBoolean isBoolean = HCDataIsBoolean(self);
    return (jboolean)isBoolean;
}

JNIEXPORT jboolean JNICALL
Java_com_hollowcore_hollowjava_data_HollowData_asBooleanNative(JNIEnv *env, jobject thiz) {
    HCDataRef self = HCDataJNIFromJObject(env, thiz);
    HCBoolean asBoolean = HCDataAsBoolean(self);
    return (jboolean)asBoolean;
}

JNIEXPORT jboolean JNICALL
Java_com_hollowcore_hollowjava_data_HollowData_isIntegerNative(JNIEnv *env, jobject thiz) {
    HCDataRef self = HCDataJNIFromJObject(env, thiz);
    HCBoolean isInteger = HCDataIsInteger(self);
    return (jboolean)isInteger;
}

JNIEXPORT jint JNICALL
Java_com_hollowcore_hollowjava_data_HollowData_asIntegerNative(JNIEnv *env, jobject thiz) {
    HCDataRef self = HCDataJNIFromJObject(env, thiz);
    HCInteger asInteger = HCDataAsInteger(self);
    return (jint)asInteger;
}

JNIEXPORT jboolean JNICALL
Java_com_hollowcore_hollowjava_data_HollowData_isRealNative(JNIEnv *env, jobject thiz) {
    HCDataRef self = HCDataJNIFromJObject(env, thiz);
    HCBoolean isReal = HCDataIsReal(self);
    return (jboolean)isReal;
}

JNIEXPORT jdouble JNICALL
Java_com_hollowcore_hollowjava_data_HollowData_asRealNative(JNIEnv *env, jobject thiz) {
    HCDataRef self = HCDataJNIFromJObject(env, thiz);
    HCReal asReal = HCDataAsReal(self);
    return (jdouble)asReal;
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Operations
//----------------------------------------------------------------------------------------------------------------------------------
JNIEXPORT void JNICALL
Java_com_hollowcore_hollowjava_data_HollowData_clearNative(JNIEnv *env, jobject thiz) {
    HCDataRef self = HCDataJNIFromJObject(env, thiz);
    HCDataClear(self);
}

JNIEXPORT void JNICALL
Java_com_hollowcore_hollowjava_data_HollowData_addBytesNative(JNIEnv *env, jobject thiz, jbyteArray byte_array) {
    HCDataRef self = HCDataJNIFromJObject(env, thiz);
    HCByte* bytes = (HCByte*)(*env)->GetByteArrayElements(env, byte_array, NULL);
    HCInteger size = (*env)->GetArrayLength(env, byte_array);
    HCDataAddBytes(self, size, bytes);
    (*env)->ReleaseByteArrayElements(env, byte_array, (jbyte*)bytes, 0);
}

JNIEXPORT void JNICALL
Java_com_hollowcore_hollowjava_data_HollowData_removeBytesNative(JNIEnv *env, jobject thiz, jint count) {
    HCDataRef self = HCDataJNIFromJObject(env, thiz);
    HCDataRemoveBytes(self, count);
}

JNIEXPORT void JNICALL
Java_com_hollowcore_hollowjava_data_HollowData_addBooleanNative(JNIEnv *env, jobject thiz, jboolean value) {
    HCDataRef self = HCDataJNIFromJObject(env, thiz);
    HCDataAddBoolean(self, value);
}

JNIEXPORT void JNICALL
Java_com_hollowcore_hollowjava_data_HollowData_removeBooleanNative(JNIEnv *env, jobject thiz) {
    HCDataRef self = HCDataJNIFromJObject(env, thiz);
    HCDataRemoveBoolean(self);
}

JNIEXPORT void JNICALL
Java_com_hollowcore_hollowjava_data_HollowData_addIntegerNative(JNIEnv *env, jobject thiz, jint value) {
    HCDataRef self = HCDataJNIFromJObject(env, thiz);
    HCDataAddInteger(self, value);
}

JNIEXPORT void JNICALL
Java_com_hollowcore_hollowjava_data_HollowData_removeIntegerNative(JNIEnv *env, jobject thiz) {
    HCDataRef self = HCDataJNIFromJObject(env, thiz);
    HCDataRemoveInteger(self);
}

JNIEXPORT void JNICALL
Java_com_hollowcore_hollowjava_data_HollowData_addRealNative(JNIEnv *env, jobject thiz, jdouble value) {
    HCDataRef self = HCDataJNIFromJObject(env, thiz);
    HCDataAddReal(self, value);
}

JNIEXPORT void JNICALL
Java_com_hollowcore_hollowjava_data_HollowData_removeRealNative(JNIEnv *env, jobject thiz) {
    HCDataRef self = HCDataJNIFromJObject(env, thiz);
    HCDataRemoveReal(self);
}
