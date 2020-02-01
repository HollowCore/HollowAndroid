//
//  HCSet+JNI.h
//  HollowJava
//
//  Created by Matt Stoker on 2/1/20.
//  Copyright © 2020 HollowCore. All rights reserved.
//
//

#include "HCSet+JNI.h"
#include "../Core/HCObject+JNI.h"

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - JNI Convenience
//----------------------------------------------------------------------------------------------------------------------------------
void HCSetJNIInstallReferenceInJObject(JNIEnv* env, jobject thiz, HCSetRef self) {
    jclass clazz = (*env)->GetObjectClass(env, thiz);
    jfieldID fieldID = (*env)->GetFieldID(env, clazz, HCSetJNIReferenceFieldID, HCSetJNIReferenceFieldSignature);
    (*env)->SetLongField(env, thiz, fieldID, (jlong)self);
}

void HCSetJNIReleaseReferenceInJObject(JNIEnv* env, jobject thiz) {
    jclass clazz = (*env)->GetObjectClass(env, thiz);
    jfieldID fieldID = (*env)->GetFieldID(env, clazz, HCSetJNIReferenceFieldID, HCSetJNIReferenceFieldSignature);
    HCSetRef self = (HCSetRef)(*env)->GetLongField(env, thiz, fieldID);
    (*env)->SetLongField(env, thiz, fieldID, (jlong)NULL);
    HCRelease(self);
}

HCSetRef HCSetJNIFromJObject(JNIEnv* env, jobject thiz) {
    jclass clazz = (*env)->GetObjectClass(env, thiz);
    jfieldID fieldID = (*env)->GetFieldID(env, clazz, HCSetJNIReferenceFieldID, HCSetJNIReferenceFieldSignature);
    HCSetRef self = (HCSetRef)(*env)->GetLongField(env, thiz, fieldID);
    return self;
}

jobject HCSetJNINewJObject(JNIEnv* env, HCSetRef self) {
    jclass clazz = (*env)->FindClass(env, HCSetJNIClass);
    jmethodID constructor = (*env)->GetMethodID(env, clazz, "<init>", "()V");
    jobject thiz = (*env)->NewObject(env, clazz, constructor);
    HCSetJNIInstallReferenceInJObject(env, thiz, self);
    return thiz;
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Construction
//----------------------------------------------------------------------------------------------------------------------------------
JNIEXPORT void JNICALL
Java_com_hollowcore_hollowjava_container_HollowSet_initNative(JNIEnv *env, jobject thiz, jint capacity) {
    HCSetRef self = HCSetCreateWithCapacity(capacity);
    HCSetJNIInstallReferenceInJObject(env, thiz, self);
}

JNIEXPORT void JNICALL
Java_com_hollowcore_hollowjava_container_HollowSet_finalizeNative(JNIEnv *env, jobject thiz) {
    HCSetJNIReleaseReferenceInJObject(env, thiz);
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Object Polymorphic Functions
//----------------------------------------------------------------------------------------------------------------------------------
JNIEXPORT jboolean JNICALL
Java_com_hollowcore_hollowjava_container_HollowSet_isEqualNative(JNIEnv *env, jobject thiz, jobject otherInstance) {
    HCSetRef self = HCSetJNIFromJObject(env, thiz);
    HCSetRef other = HCSetJNIFromJObject(env, otherInstance);
    return (jboolean)HCSetIsEqual(self, other);
}

JNIEXPORT jlong JNICALL
Java_com_hollowcore_hollowjava_container_HollowSet_hashNative(JNIEnv *env, jobject thiz) {
    HCSetRef self = HCSetJNIFromJObject(env, thiz);
    return self == NULL ? 0 : HCSetHashValue(self);
}

JNIEXPORT jstring JNICALL
Java_com_hollowcore_hollowjava_container_HollowSet_toStringNative(JNIEnv *env, jobject thiz) {
    HCSetRef self = HCSetJNIFromJObject(env, thiz);
    // TODO: memoryStream
//    HCSetPrint(self, memoryStream);
    jstring stringValue = (*env)->NewStringUTF(env, "TODO: Implement Set toStringNative");
//    HCRelease(memoryStream);
    return stringValue;
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Content
//----------------------------------------------------------------------------------------------------------------------------------
JNIEXPORT jboolean JNICALL
Java_com_hollowcore_hollowjava_container_HollowSet_isEmptyNative(JNIEnv *env, jobject thiz) {
    HCSetRef self = HCSetJNIFromJObject(env, thiz);
    HCBoolean isEmpty = HCSetIsEmpty(self);
    return (jboolean)isEmpty;
}

JNIEXPORT jint JNICALL
Java_com_hollowcore_hollowjava_container_HollowSet_sizeNative(JNIEnv *env, jobject thiz) {
    HCSetRef self = HCSetJNIFromJObject(env, thiz);
    HCInteger count = HCSetCount(self);
    return (jint)count;
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Searching
//----------------------------------------------------------------------------------------------------------------------------------
JNIEXPORT jboolean JNICALL
Java_com_hollowcore_hollowjava_container_HollowSet_containsNative(JNIEnv *env, jobject thiz, jobject o) {
    HCSetRef self = HCSetJNIFromJObject(env, thiz);
    HCRef object = HCObjectJNIFromJObject(env, o);
    HCBoolean contains = HCSetContainsObject(self, object);
    return (jboolean)contains;
}

JNIEXPORT jobject JNICALL
Java_com_hollowcore_hollowjava_container_HollowSet_firstNative(JNIEnv *env, jobject thiz) {
    HCSetRef self = HCSetJNIFromJObject(env, thiz);
    HCRef first = HCSetFirstObject(self);
    return HCObjectJNINewJObject(env, first);
}

JNIEXPORT jobject JNICALL
Java_com_hollowcore_hollowjava_container_HollowSet_lastNative(JNIEnv *env, jobject thiz) {
    HCSetRef self = HCSetJNIFromJObject(env, thiz);
    HCRef last = HCSetLastObject(self);
    return HCObjectJNINewJObject(env, last);
}

JNIEXPORT jobject JNICALL
Java_com_hollowcore_hollowjava_container_HollowSet_getNative(JNIEnv *env, jobject thiz, jint iteration_index) {
    HCSetRef self = HCSetJNIFromJObject(env, thiz);
    HCRef object = HCSetObjectAtIterationIndex(self, iteration_index);
    return HCObjectJNINewJObject(env, object);
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Operations
//----------------------------------------------------------------------------------------------------------------------------------
JNIEXPORT void JNICALL
Java_com_hollowcore_hollowjava_container_HollowSet_clearNative(JNIEnv *env, jobject thiz) {
    HCSetRef self = HCSetJNIFromJObject(env, thiz);
    HCSetClear(self);
}

JNIEXPORT jboolean JNICALL
Java_com_hollowcore_hollowjava_container_HollowSet_addNative(JNIEnv *env, jobject thiz, jobject o) {
    HCSetRef self = HCSetJNIFromJObject(env, thiz);
    HCRef object = HCObjectJNIFromJObject(env, o);
    HCBoolean exists = HCSetContainsObject(self, object);
    if (exists) {
        return (jboolean)false;
    }
    else {
        HCSetAddObject(self, object);
        return (jboolean)true;
    }
}

JNIEXPORT jboolean JNICALL
Java_com_hollowcore_hollowjava_container_HollowSet_removeNative(JNIEnv *env, jobject thiz, jobject o) {
    HCSetRef self = HCSetJNIFromJObject(env, thiz);
    HCRef object = HCObjectJNIFromJObject(env, o);
    HCBoolean exists = HCSetContainsObject(self, object);
    if (exists) {
        HCSetRemoveObject(self, object);
        return (jboolean)true;
    }
    else {
        return (jboolean)false;
    }
}
