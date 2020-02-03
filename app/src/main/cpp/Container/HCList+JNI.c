//
//  HCList+JNI.h
//  HollowJava
//
//  Created by Matt Stoker on 2/1/20.
//  Copyright © 2020 HollowCore. All rights reserved.
//
//

#include "HCList+JNI.h"
#include "../Core/HCObject+JNI.h"

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - JNI Convenience
//----------------------------------------------------------------------------------------------------------------------------------
jclass HCListJNIClazz = NULL;

void HCListJNIOnLoad(JNIEnv* env) {
    HCListJNIClazz = (*env)->NewGlobalRef(env, (*env)->FindClass(env, HCListJNIClass));
    HCObjectJNIAssociateTypeToClass(env, HCListType, HCListJNIClazz);
}

void HCListJNIInstallReferenceInJObject(JNIEnv* env, jobject thiz, HCListRef self) {
    HCObjectJNIInstallReferenceInJObject(env, thiz, self);
}

void HCListJNIReleaseReferenceInJObject(JNIEnv* env, jobject thiz) {
    HCObjectJNIReleaseReferenceInJObject(env, thiz);
}

HCListRef HCListJNIFromJObject(JNIEnv* env, jobject thiz) {
    return HCObjectJNIFromJObject(env, thiz);
}

jobject HCListJNINewJObject(JNIEnv* env, HCListRef self) {
    jmethodID constructor = (*env)->GetMethodID(env, HCListJNIClazz, "<init>", "()V");
    jobject thiz = (*env)->NewObject(env, HCListJNIClazz, constructor);
    HCListJNIInstallReferenceInJObject(env, thiz, self);
    return thiz;
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Construction
//----------------------------------------------------------------------------------------------------------------------------------
JNIEXPORT void JNICALL
Java_com_hollowcore_hollowjava_container_HollowList_initNative(JNIEnv *env, jobject thiz, jint capacity) {
    HCListRef self = HCListCreateWithCapacity(capacity);
    HCListJNIInstallReferenceInJObject(env, thiz, self);
}

JNIEXPORT void JNICALL
Java_com_hollowcore_hollowjava_container_HollowList_finalizeNative(JNIEnv *env, jobject thiz) {
    HCListJNIReleaseReferenceInJObject(env, thiz);
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Object Polymorphic Functions
//----------------------------------------------------------------------------------------------------------------------------------
JNIEXPORT jboolean JNICALL
Java_com_hollowcore_hollowjava_container_HollowList_isEqualNative(JNIEnv *env, jobject thiz, jobject otherInstance) {
    HCListRef self = HCListJNIFromJObject(env, thiz);
    HCListRef other = HCListJNIFromJObject(env, otherInstance);
    return (jboolean)HCListIsEqual(self, other);
}

JNIEXPORT jlong JNICALL
Java_com_hollowcore_hollowjava_container_HollowList_hashNative(JNIEnv *env, jobject thiz) {
    HCListRef self = HCListJNIFromJObject(env, thiz);
    return self == NULL ? 0 : HCListHashValue(self);
}

JNIEXPORT jstring JNICALL
Java_com_hollowcore_hollowjava_container_HollowList_toStringNative(JNIEnv *env, jobject thiz) {
    HCListRef self = HCListJNIFromJObject(env, thiz);
    // TODO: memoryStream
//    HCListPrint(self, memoryStream);
    jstring stringValue = (*env)->NewStringUTF(env, "TODO: Implement List toStringNative");
//    HCRelease(memoryStream);
    return stringValue;
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Content
//----------------------------------------------------------------------------------------------------------------------------------
JNIEXPORT jboolean JNICALL
Java_com_hollowcore_hollowjava_container_HollowList_isEmptyNative(JNIEnv *env, jobject thiz) {
    HCListRef self = HCListJNIFromJObject(env, thiz);
    HCBoolean isEmpty = HCListIsEmpty(self);
    return (jboolean)isEmpty;
}

JNIEXPORT jint JNICALL
Java_com_hollowcore_hollowjava_container_HollowList_sizeNative(JNIEnv *env, jobject thiz) {
    HCListRef self = HCListJNIFromJObject(env, thiz);
    HCInteger count = HCListCount(self);
    return (jint)count;
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Searching
//----------------------------------------------------------------------------------------------------------------------------------
JNIEXPORT jboolean JNICALL
Java_com_hollowcore_hollowjava_container_HollowList_containsNative(JNIEnv *env, jobject thiz, jobject o) {
    HCListRef self = HCListJNIFromJObject(env, thiz);
    HCRef object = HCObjectJNIFromJObject(env, o);
    HCBoolean contains = HCListContainsObject(self, object);
    return (jboolean)contains;
}

JNIEXPORT jobject JNICALL
Java_com_hollowcore_hollowjava_container_HollowList_firstNative(JNIEnv *env, jobject thiz) {
    HCListRef self = HCListJNIFromJObject(env, thiz);
    HCRef first = HCListFirstObject(self);
    return HCObjectJNINewJObject(env, first);
}

JNIEXPORT jobject JNICALL
Java_com_hollowcore_hollowjava_container_HollowList_lastNative(JNIEnv *env, jobject thiz) {
    HCListRef self = HCListJNIFromJObject(env, thiz);
    HCRef last = HCListLastObject(self);
    return HCObjectJNINewJObject(env, last);
}

JNIEXPORT jobject JNICALL
Java_com_hollowcore_hollowjava_container_HollowList_getNative(JNIEnv *env, jobject thiz, jint iteration_index) {
    HCListRef self = HCListJNIFromJObject(env, thiz);
    HCRef object = HCListObjectAtIndex(self, iteration_index);
    return HCObjectJNINewJObject(env, object);
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Operations
//----------------------------------------------------------------------------------------------------------------------------------
JNIEXPORT void JNICALL
Java_com_hollowcore_hollowjava_container_HollowList_clearNative(JNIEnv *env, jobject thiz) {
    HCListRef self = HCListJNIFromJObject(env, thiz);
    HCListClear(self);
}

JNIEXPORT void JNICALL
Java_com_hollowcore_hollowjava_container_HollowList_addNative(JNIEnv *env, jobject thiz, jint index, jobject object_instance) {
    HCListRef self = HCListJNIFromJObject(env, thiz);
    HCRef object = HCObjectJNIFromJObject(env, object_instance);
    HCListAddObjectAtIndex(self, index, object);
}

JNIEXPORT jobject JNICALL
Java_com_hollowcore_hollowjava_container_HollowList_removeNative(JNIEnv *env, jobject thiz, jint index) {
    HCListRef self = HCListJNIFromJObject(env, thiz);
    HCRef existingObject = HCListRemoveObjectRetainedAtIndex(self, index);
    return HCObjectJNINewJObject(env, existingObject);
}

JNIEXPORT jobject JNICALL
Java_com_hollowcore_hollowjava_container_HollowList_setNative(JNIEnv *env, jobject thiz, jint index, jobject object_instance) {
    HCListRef self = HCListJNIFromJObject(env, thiz);
    HCRef object = HCObjectJNIFromJObject(env, object_instance);
    HCRef existingObject = HCListRemoveObjectRetainedAtIndex(self, index);
    HCListAddObjectAtIndex(self, index, object);
    return HCObjectJNINewJObject(env, existingObject);
}
