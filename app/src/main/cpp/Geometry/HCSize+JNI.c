//
//  HCSize+JNI.c
//  HollowJava
//
//  Created by Matt Stoker on 1/28/20.
//  Copyright © 2020 HollowCore. All rights reserved.
//

#include "HCSize+JNI.h"
#include "../Core/HCObject+JNI.h"

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - JNI Convenience
//----------------------------------------------------------------------------------------------------------------------------------
jclass HCSizeJNIClazz = NULL;

void HCSizeJNIOnLoad(JNIEnv* env) {
    HCSizeJNIClazz = (*env)->NewGlobalRef(env, (*env)->FindClass(env, HCSizeJNIClass));
    HCObjectJNIAssociateTypeToClass(env, HCDataType, HCSizeJNIClazz);
}

void HCSizeJNIInstallReferenceInJObject(JNIEnv* env, jobject thiz, HCSize self) {
    HCDataRef value = HCDataCreateWithBytes(sizeof(self), (HCByte*)&self);
    jfieldID fieldID = (*env)->GetFieldID(env, HCSizeJNIClazz, HCObjectJNIReferenceFieldID, HCObjectJNIReferenceFieldSignature);
    (*env)->SetLongField(env, thiz, fieldID, (jlong)value);
}

void HCSizeJNIReleaseReferenceInJObject(JNIEnv* env, jobject thiz) {
    jfieldID fieldID = (*env)->GetFieldID(env, HCSizeJNIClazz, HCObjectJNIReferenceFieldID, HCObjectJNIReferenceFieldSignature);
    HCDataRef value = (HCDataRef)(*env)->GetLongField(env, thiz, fieldID);
    (*env)->SetLongField(env, thiz, fieldID, (jlong)NULL);
    HCRelease(value);
}

HCSize HCSizeJNIFromJObject(JNIEnv* env, jobject thiz) {
    jfieldID fieldID = (*env)->GetFieldID(env, HCSizeJNIClazz, HCObjectJNIReferenceFieldID, HCObjectJNIReferenceFieldSignature);
    HCDataRef value = (HCDataRef)(*env)->GetLongField(env, thiz, fieldID);
    HCSize self = *((HCSize*)HCDataBytes(value));
    return self;
}

jobject HCSizeJNINewJObject(JNIEnv* env, HCSize self) {
    jmethodID constructor = (*env)->GetMethodID(env, HCSizeJNIClazz, "<init>", "()V");
    jobject thiz = (*env)->NewObject(env, HCSizeJNIClazz, constructor);
    HCSizeJNIInstallReferenceInJObject(env, thiz, self);
    return thiz;
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Constructors
//----------------------------------------------------------------------------------------------------------------------------------
JNIEXPORT void JNICALL
Java_com_hollowcore_hollowjava_geometry_Size_initNative(JNIEnv *env, jobject thiz, jdouble x, jdouble y) {
    HCSize self = HCSizeMake(x, y);
    HCSizeJNIInstallReferenceInJObject(env, thiz, self);
}

JNIEXPORT void JNICALL
Java_com_hollowcore_hollowjava_geometry_Size_finalizeNative(JNIEnv *env, jobject thiz) {
    HCSizeJNIReleaseReferenceInJObject(env, thiz);
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Object Polymorphic Functions
//----------------------------------------------------------------------------------------------------------------------------------
JNIEXPORT jboolean JNICALL
Java_com_hollowcore_hollowjava_geometry_Size_isEqualNative(JNIEnv *env, jobject thiz, jobject other_instance) {
    HCSize self = HCSizeJNIFromJObject(env, thiz);
    HCSize other = HCSizeJNIFromJObject(env, other_instance);
    HCBoolean isEqual = HCSizeIsEqual(self, other);
    return (jboolean)isEqual;
}

JNIEXPORT jlong JNICALL
Java_com_hollowcore_hollowjava_geometry_Size_hashNative(JNIEnv *env, jobject thiz) {
    HCSize self = HCSizeJNIFromJObject(env, thiz);
    HCInteger hashValue = HCSizeHashValue(self);
    return (jlong)hashValue;
}

JNIEXPORT jstring JNICALL
Java_com_hollowcore_hollowjava_geometry_Size_toStringNative(JNIEnv *env, jobject thiz) {
    HCSize self = HCSizeJNIFromJObject(env, thiz);
    // TODO: memoryStream
//    HCSizePrint(self, memoryStream);
    jstring stringValue = (*env)->NewStringUTF(env, "TODO: Implement Size toStringNative");
//    HCRelease(memoryStream);
    return stringValue;
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Attributes
//----------------------------------------------------------------------------------------------------------------------------------
JNIEXPORT jdouble JNICALL
Java_com_hollowcore_hollowjava_geometry_Size_getWidthNative(JNIEnv *env, jobject thiz) {
    HCSize self = HCSizeJNIFromJObject(env, thiz);
    HCReal width = self.width;
    return (jdouble)width;
}

JNIEXPORT jdouble JNICALL
Java_com_hollowcore_hollowjava_geometry_Size_getHeightNative(JNIEnv *env, jobject thiz) {
    HCSize self = HCSizeJNIFromJObject(env, thiz);
    HCReal height = self.height;
    return (jdouble)height;
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Queries
//----------------------------------------------------------------------------------------------------------------------------------
JNIEXPORT jboolean JNICALL
Java_com_hollowcore_hollowjava_geometry_Size_isZeroNative(JNIEnv *env, jobject thiz) {
    HCSize self = HCSizeJNIFromJObject(env, thiz);
    HCBoolean isZero = HCSizeIsZero(self);
    return (jboolean)isZero;
}

JNIEXPORT jboolean JNICALL
Java_com_hollowcore_hollowjava_geometry_Size_isInfiniteNative(JNIEnv *env, jobject thiz) {
    HCSize self = HCSizeJNIFromJObject(env, thiz);
    HCBoolean isInfinite = HCSizeIsInfinite(self);
    return (jboolean)isInfinite;
}

JNIEXPORT jboolean JNICALL
Java_com_hollowcore_hollowjava_geometry_Size_isInvalidNative(JNIEnv *env, jobject thiz) {
    HCSize self = HCSizeJNIFromJObject(env, thiz);
    HCBoolean isInvalid = HCSizeIsInvalid(self);
    return (jboolean)isInvalid;
}

JNIEXPORT jboolean JNICALL
Java_com_hollowcore_hollowjava_geometry_Size_isSimilarNative(JNIEnv *env, jobject thiz, jobject other_instance, jdouble axis_dissimilarity) {
    HCSize self = HCSizeJNIFromJObject(env, thiz);
    HCSize other = HCSizeJNIFromJObject(env, other_instance);
    HCBoolean isSimilar = HCSizeIsSimilar(self, other, axis_dissimilarity);
    return (jboolean)isSimilar;
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Operations
//----------------------------------------------------------------------------------------------------------------------------------
JNIEXPORT jobject JNICALL
Java_com_hollowcore_hollowjava_geometry_Size_increasedNative(JNIEnv *env, jobject thiz, jdouble dx, jdouble dy) {
    HCSize self = HCSizeJNIFromJObject(env, thiz);
    HCSize increased = HCSizeIncrease(self, dx, dy);
    return HCSizeJNINewJObject(env, increased);
}

JNIEXPORT jobject JNICALL
Java_com_hollowcore_hollowjava_geometry_Size_decreasedNative(JNIEnv *env, jobject thiz, jdouble dx, jdouble dy) {
    HCSize self = HCSizeJNIFromJObject(env, thiz);
    HCSize decreased = HCSizeDecrease(self, dx, dy);
    return HCSizeJNINewJObject(env, decreased);
}

JNIEXPORT jobject JNICALL
Java_com_hollowcore_hollowjava_geometry_Size_scaledNative(JNIEnv *env, jobject thiz, jdouble scalar) {
    HCSize self = HCSizeJNIFromJObject(env, thiz);
    HCSize scaled = HCSizeScale(self, scalar);
    return HCSizeJNINewJObject(env, scaled);
}
