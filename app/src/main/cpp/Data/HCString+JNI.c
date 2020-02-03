//
//  HCString+JNI.h
//  HollowJava
//
//  Created by Matt Stoker on 1/30/20.
//  Copyright © 2020 HollowCore. All rights reserved.
//
//

#include "HCString+JNI.h"
#include "../Core/HCObject+JNI.h"

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - JNI Convenience
//----------------------------------------------------------------------------------------------------------------------------------
jclass HCStringJNIClazz = NULL;

void HCStringJNIOnLoad(JNIEnv* env) {
    HCStringJNIClazz = (*env)->NewGlobalRef(env, (*env)->FindClass(env, HCStringJNIClass));
    HCObjectJNIAssociateTypeToClass(env, HCStringType, HCStringJNIClazz);
}

void HCStringJNIInstallReferenceInJObject(JNIEnv* env, jobject thiz, HCStringRef self) {
    HCObjectJNIInstallReferenceInJObject(env, thiz, self);
}

void HCStringJNIReleaseReferenceInJObject(JNIEnv* env, jobject thiz) {
    HCObjectJNIReleaseReferenceInJObject(env, thiz);
}

HCStringRef HCStringJNIFromJObject(JNIEnv* env, jobject thiz) {
    return HCObjectJNIFromJObject(env, thiz);
}

jobject HCStringJNINewJObject(JNIEnv* env, HCStringRef self) {
    jmethodID constructor = (*env)->GetMethodID(env, HCStringJNIClazz, "<init>", "()V");
    jobject thiz = (*env)->NewObject(env, HCStringJNIClazz, constructor);
    HCStringJNIInstallReferenceInJObject(env, thiz, self);
    return thiz;
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Construction
//----------------------------------------------------------------------------------------------------------------------------------
JNIEXPORT void JNICALL
Java_com_hollowcore_hollowjava_data_HollowString_initNative(JNIEnv *env, jobject thiz) {
    HCStringRef self = HCStringCreate();
    HCStringJNIInstallReferenceInJObject(env, thiz, self);
}

JNIEXPORT void JNICALL
Java_com_hollowcore_hollowjava_data_HollowString_initWithUTF8Native(JNIEnv *env, jobject thiz, jbyteArray byte_array) {
    HCByte* bytes = (HCByte*)(*env)->GetByteArrayElements(env, byte_array, NULL);
    HCInteger size = (*env)->GetArrayLength(env, bytes);
    HCStringRef self = HCStringCreateWithBytes(HCStringEncodingUTF8, size, bytes);
    (*env)->ReleaseByteArrayElements(env, byte_array, (jbyte*)bytes, 0);
    HCStringJNIInstallReferenceInJObject(env, thiz, self);
}

JNIEXPORT void JNICALL
Java_com_hollowcore_hollowjava_data_HollowString_initWithUTF16Native(JNIEnv *env, jobject thiz, jshortArray short_array) {
    HCByte* bytes = (HCByte*)(*env)->GetShortArrayElements(env, short_array, NULL);
    HCInteger size = (*env)->GetArrayLength(env, bytes) * sizeof(jshort);
    HCStringRef self = HCStringCreateWithBytes(HCStringEncodingUTF16, size, bytes);
    (*env)->ReleaseShortArrayElements(env, short_array, (jshort*)bytes, 0);
    HCStringJNIInstallReferenceInJObject(env, thiz, self);
}

JNIEXPORT void JNICALL
Java_com_hollowcore_hollowjava_data_HollowString_initWithUTF32Native(JNIEnv *env, jobject thiz, jintArray int_array) {
    HCByte* bytes = (HCByte*)(*env)->GetByteArrayElements(env, int_array, NULL);
    HCInteger size = (*env)->GetArrayLength(env, bytes) * sizeof(jint);
    HCStringRef self = HCStringCreateWithBytes(HCStringEncodingUTF32, size, bytes);
    (*env)->ReleaseByteArrayElements(env, int_array, (jbyte*)bytes, 0);
    HCStringJNIInstallReferenceInJObject(env, thiz, self);
}

JNIEXPORT void JNICALL
Java_com_hollowcore_hollowjava_data_HollowString_initWithStringNative(JNIEnv *env, jobject thiz, jstring string) {
    const char* cString = (*env)->GetStringUTFChars(env, string, NULL);
    HCStringRef self = HCStringCreateWithCString(cString);
    (*env)->ReleaseStringUTFChars(env, string, cString);
    HCStringJNIInstallReferenceInJObject(env, thiz, self);
}

JNIEXPORT void JNICALL
Java_com_hollowcore_hollowjava_data_HollowString_initWithBooleanNative(JNIEnv *env, jobject thiz, jboolean b) {
    HCStringRef self = HCStringCreateWithBoolean(b);
    HCStringJNIInstallReferenceInJObject(env, thiz, self);
}

JNIEXPORT void JNICALL
Java_com_hollowcore_hollowjava_data_HollowString_initWithIntegerNative(JNIEnv *env, jobject thiz, jint integer) {
    HCStringRef self = HCStringCreateWithInteger(integer);
    HCStringJNIInstallReferenceInJObject(env, thiz, self);
}

JNIEXPORT void JNICALL
Java_com_hollowcore_hollowjava_data_HollowString_initWithRealNative(JNIEnv *env, jobject thiz, jdouble real) {
    HCStringRef self = HCStringCreateWithReal(real);
    HCStringJNIInstallReferenceInJObject(env, thiz, self);
}

JNIEXPORT void JNICALL
Java_com_hollowcore_hollowjava_data_HollowString_finalizeNative(JNIEnv *env, jobject thiz) {
    HCStringJNIReleaseReferenceInJObject(env, thiz);
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Object Polymorphic Functions
//----------------------------------------------------------------------------------------------------------------------------------
JNIEXPORT jboolean JNICALL
Java_com_hollowcore_hollowjava_data_HollowString_isEqualNative(JNIEnv *env, jobject thiz, jobject otherInstance) {
    HCStringRef self = HCStringJNIFromJObject(env, thiz);
    HCStringRef other = HCStringJNIFromJObject(env, otherInstance);
    return (jboolean)HCStringIsEqual(self, other);
}

JNIEXPORT jlong JNICALL
Java_com_hollowcore_hollowjava_data_HollowString_hashNative(JNIEnv *env, jobject thiz) {
    HCStringRef self = HCStringJNIFromJObject(env, thiz);
    return self == NULL ? 0 : HCStringHashValue(self);
}

JNIEXPORT jstring JNICALL
Java_com_hollowcore_hollowjava_data_HollowString_toStringNative(JNIEnv *env, jobject thiz) {
    HCStringRef self = HCStringJNIFromJObject(env, thiz);
    // TODO: memoryStream
//    HCStringPrint(self, memoryStream);
    jstring stringValue = (*env)->NewStringUTF(env, "TODO: Implement String toStringNative");
//    HCRelease(memoryStream);
    return stringValue;
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Attributes
//----------------------------------------------------------------------------------------------------------------------------------
JNIEXPORT jboolean JNICALL
Java_com_hollowcore_hollowjava_data_HollowString_isEmptyNative(JNIEnv *env, jobject thiz) {
    HCStringRef self = HCStringJNIFromJObject(env, thiz);
    HCBoolean isEmpty = HCStringIsEmpty(self);
    return (jboolean)isEmpty;
}

JNIEXPORT jint JNICALL
Java_com_hollowcore_hollowjava_data_HollowString_getCodeUnitCountNative(JNIEnv *env, jobject thiz) {
    HCStringRef self = HCStringJNIFromJObject(env, thiz);
    HCInteger codeUnitCount = HCStringCodePointCount(self);
    return (jint)codeUnitCount;
}

JNIEXPORT jbyte JNICALL
Java_com_hollowcore_hollowjava_data_HollowString_getCodeUnitNative(JNIEnv *env, jobject thiz, jint code_unit_index) {
    HCStringRef self = HCStringJNIFromJObject(env, thiz);
    HCStringCodeUnit codeUnit = HCStringCodeUnitAtIndex(self, code_unit_index);
    return (jbyte)codeUnit;
}

JNIEXPORT jbyteArray JNICALL
Java_com_hollowcore_hollowjava_data_HollowString_getCodeUnitsNative(JNIEnv *env, jobject thiz, jint code_unit_index, jint count) {
    HCStringRef self = HCStringJNIFromJObject(env, thiz);
    HCStringCodeUnit codeUnits[count];
    HCStringExtractCodeUnits(self, code_unit_index, count, codeUnits);
    jbyteArray code_unit_array = (*env)->NewByteArray(env, count);
    (*env)->SetByteArrayRegion(env, code_unit_array, 0, count, (const jbyte*)codeUnits);
    return code_unit_array;
}

JNIEXPORT jint JNICALL
Java_com_hollowcore_hollowjava_data_HollowString_getCodePointCountNative(JNIEnv *env, jobject thiz) {
    HCStringRef self = HCStringJNIFromJObject(env, thiz);
    HCInteger codePointCount = HCStringCodePointCount(self);
    return (jint)codePointCount;
}

JNIEXPORT jint JNICALL
Java_com_hollowcore_hollowjava_data_HollowString_getCodePointNative(JNIEnv *env, jobject thiz, jint code_point_index) {
    HCStringRef self = HCStringJNIFromJObject(env, thiz);
    HCStringCodePoint codePoint = HCStringCodePointAtIndex(self, code_point_index);
    return (jint)codePoint;
}

JNIEXPORT jintArray JNICALL
Java_com_hollowcore_hollowjava_data_HollowString_getCodePointsNative(JNIEnv *env, jobject thiz, jint code_point_index, jint count) {
    HCStringRef self = HCStringJNIFromJObject(env, thiz);
    HCStringCodePoint codePoints[count];
    HCStringExtractCodePoints(self, code_point_index, count, codePoints);
    jbyteArray code_point_array = (*env)->NewIntArray(env, count);
    (*env)->SetIntArrayRegion(env, code_point_array, 0, count, (const jint*)codePoints);
    return code_point_array;
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Conversion
//----------------------------------------------------------------------------------------------------------------------------------
JNIEXPORT jboolean JNICALL
Java_com_hollowcore_hollowjava_data_HollowString_isBooleanNative(JNIEnv *env, jobject thiz) {
    HCStringRef self = HCStringJNIFromJObject(env, thiz);
    HCBoolean isBoolean = HCStringIsBoolean(self);
    return (jboolean)isBoolean;
}

JNIEXPORT jboolean JNICALL
Java_com_hollowcore_hollowjava_data_HollowString_asBooleanNative(JNIEnv *env, jobject thiz) {
    HCStringRef self = HCStringJNIFromJObject(env, thiz);
    HCBoolean asBoolean = HCStringAsBoolean(self);
    return (jboolean)asBoolean;
}

JNIEXPORT jboolean JNICALL
Java_com_hollowcore_hollowjava_data_HollowString_isIntegerNative(JNIEnv *env, jobject thiz) {
    HCStringRef self = HCStringJNIFromJObject(env, thiz);
    HCBoolean isInteger = HCStringIsInteger(self);
    return (jboolean)isInteger;
}

JNIEXPORT jint JNICALL
Java_com_hollowcore_hollowjava_data_HollowString_asIntegerNative(JNIEnv *env, jobject thiz) {
    HCStringRef self = HCStringJNIFromJObject(env, thiz);
    HCInteger asInteger = HCStringAsInteger(self);
    return (jint)asInteger;
}

JNIEXPORT jboolean JNICALL
Java_com_hollowcore_hollowjava_data_HollowString_isRealNative(JNIEnv *env, jobject thiz) {
    HCStringRef self = HCStringJNIFromJObject(env, thiz);
    HCBoolean isReal = HCStringIsReal(self);
    return (jboolean)isReal;
}

JNIEXPORT jdouble JNICALL
Java_com_hollowcore_hollowjava_data_HollowString_asRealNative(JNIEnv *env, jobject thiz) {
    HCStringRef self = HCStringJNIFromJObject(env, thiz);
    HCReal asReal = HCStringAsReal(self);
    return (jdouble)asReal;
}
