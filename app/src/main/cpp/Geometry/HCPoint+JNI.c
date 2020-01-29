//
//  HCPoint+JNI.c
//  HollowJava
//
//  Created by Matt Stoker on 1/28/20.
//  Copyright © 2020 HollowCore. All rights reserved.
//

#include "HCPoint+JNI.h"

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - JNI Convenience
//----------------------------------------------------------------------------------------------------------------------------------
void HCPointJNIInstallReferenceInJObject(JNIEnv* env, jobject thiz, HCPoint self) {
    HCDataRef value = HCDataCreateWithBytes(sizeof(self), (HCByte*)&self);
    jclass clazz = (*env)->GetObjectClass(env, thiz);
    jfieldID fieldID = (*env)->GetFieldID(env, clazz, HCPointJNIReferenceFieldID, HCPointJNIReferenceFieldSignature);
    (*env)->SetLongField(env, thiz, fieldID, (jlong)value);
}

void HCPointJNIReleaseReferenceInJObject(JNIEnv* env, jobject thiz) {
    jclass clazz = (*env)->GetObjectClass(env, thiz);
    jfieldID fieldID = (*env)->GetFieldID(env, clazz, HCPointJNIReferenceFieldID, HCPointJNIReferenceFieldSignature);
    HCDataRef value = (HCDataRef)(*env)->GetLongField(env, thiz, fieldID);
    (*env)->SetLongField(env, thiz, fieldID, (jlong)NULL);
    HCRelease(value);
}

HCPoint HCPointJNIFromJObject(JNIEnv* env, jobject thiz) {
    jclass clazz = (*env)->GetObjectClass(env, thiz);
    jfieldID fieldID = (*env)->GetFieldID(env, clazz, HCPointJNIReferenceFieldID, HCPointJNIReferenceFieldSignature);
    HCDataRef value = (HCDataRef)(*env)->GetLongField(env, thiz, fieldID);
    HCPoint self = *((HCPoint*)HCDataBytes(value));
    return self;
}

jobject HCPointJNINewJObject(JNIEnv* env, HCPoint self) {
    jclass clazz = (*env)->FindClass(env, HCPointJNIClass);
    jmethodID constructor = (*env)->GetMethodID(env, clazz, "<init>", "()V");
    jobject thiz = (*env)->NewObject(env, clazz, constructor);
    HCPointJNIInstallReferenceInJObject(env, thiz, self);
    return thiz;
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Constructors
//----------------------------------------------------------------------------------------------------------------------------------
JNIEXPORT void JNICALL
Java_com_hollowcore_hollowjava_geometry_Point_initNative(JNIEnv *env, jobject thiz, jdouble x, jdouble y) {
    HCPoint self = HCPointMake(x, y);
    HCPointJNIInstallReferenceInJObject(env, thiz, self);
}

JNIEXPORT void JNICALL
Java_com_hollowcore_hollowjava_geometry_Point_finalizeNative(JNIEnv *env, jobject thiz) {
    HCPointJNIReleaseReferenceInJObject(env, thiz);
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Object Polymorphic Functions
//----------------------------------------------------------------------------------------------------------------------------------
JNIEXPORT jboolean JNICALL
Java_com_hollowcore_hollowjava_geometry_Point_isEqualNative(JNIEnv *env, jobject thiz, jobject other_instance) {
    HCPoint self = HCPointJNIFromJObject(env, thiz);
    HCPoint other = HCPointJNIFromJObject(env, other_instance);
    HCBoolean isEqual = HCPointIsEqual(self, other);
    return (jboolean)isEqual;
}

JNIEXPORT jlong JNICALL
Java_com_hollowcore_hollowjava_geometry_Point_hashNative(JNIEnv *env, jobject thiz) {
    HCPoint self = HCPointJNIFromJObject(env, thiz);
    HCInteger hashValue = HCPointHashValue(self);
    return (jlong)hashValue;
}

JNIEXPORT jstring JNICALL
Java_com_hollowcore_hollowjava_geometry_Point_toStringNative(JNIEnv *env, jobject thiz) {
    HCPoint self = HCPointJNIFromJObject(env, thiz);
    // TODO: memoryStream
//    HCPointPrint(self, memoryStream);
    jstring stringValue = (*env)->NewStringUTF(env, "TODO: Implement Point toStringNative");
//    HCRelease(memoryStream);
    return stringValue;
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Attributes
//----------------------------------------------------------------------------------------------------------------------------------
JNIEXPORT jdouble JNICALL
Java_com_hollowcore_hollowjava_geometry_Point_getXNative(JNIEnv *env, jobject thiz) {
    HCPoint self = HCPointJNIFromJObject(env, thiz);
    HCReal x = self.x;
    return (jdouble)x;
}

JNIEXPORT jdouble JNICALL
Java_com_hollowcore_hollowjava_geometry_Point_getYNative(JNIEnv *env, jobject thiz) {
    HCPoint self = HCPointJNIFromJObject(env, thiz);
    HCReal y = self.y;
    return (jdouble)y;
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Queries
//----------------------------------------------------------------------------------------------------------------------------------
JNIEXPORT jboolean JNICALL
Java_com_hollowcore_hollowjava_geometry_Point_isZeroNative(JNIEnv *env, jobject thiz) {
    HCPoint self = HCPointJNIFromJObject(env, thiz);
    HCBoolean isZero = HCPointIsZero(self);
    return (jboolean)isZero;
}

JNIEXPORT jboolean JNICALL
Java_com_hollowcore_hollowjava_geometry_Point_isInfiniteNative(JNIEnv *env, jobject thiz) {
    HCPoint self = HCPointJNIFromJObject(env, thiz);
    HCBoolean isInfinite = HCPointIsInfinite(self);
    return (jboolean)isInfinite;
}

JNIEXPORT jboolean JNICALL
Java_com_hollowcore_hollowjava_geometry_Point_isInvalidNative(JNIEnv *env, jobject thiz) {
    HCPoint self = HCPointJNIFromJObject(env, thiz);
    HCBoolean isInvalid = HCPointIsInvalid(self);
    return (jboolean)isInvalid;
}

JNIEXPORT jboolean JNICALL
Java_com_hollowcore_hollowjava_geometry_Point_isSimilarNative(JNIEnv *env, jobject thiz, jobject other_instance, jdouble axis_dissimilarity) {
    HCPoint self = HCPointJNIFromJObject(env, thiz);
    HCPoint other = HCPointJNIFromJObject(env, other_instance);
    HCBoolean isSimilar = HCPointIsSimilar(self, other, axis_dissimilarity);
    return (jboolean)isSimilar;
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Operations
//----------------------------------------------------------------------------------------------------------------------------------
JNIEXPORT jobject JNICALL
Java_com_hollowcore_hollowjava_geometry_Point_offsetNative(JNIEnv *env, jobject thiz, jdouble dx, jdouble dy) {
    HCPoint self = HCPointJNIFromJObject(env, thiz);
    HCPoint offset = HCPointOffset(self, dx, dy);
    return HCPointJNINewJObject(env, offset);
}

JNIEXPORT jobject JNICALL
Java_com_hollowcore_hollowjava_geometry_Point_scaledNative(JNIEnv *env, jobject thiz, jdouble scalar) {
    HCPoint self = HCPointJNIFromJObject(env, thiz);
    HCPoint scaled = HCPointScale(self, scalar);
    return HCPointJNINewJObject(env, scaled);
}
