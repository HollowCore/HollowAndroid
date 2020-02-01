//
//  HCMap+JNI.h
//  HollowJava
//
//  Created by Matt Stoker on 2/1/20.
//  Copyright © 2020 HollowCore. All rights reserved.
//
//

#include "HCMap+JNI.h"
#include "../Core/HCObject+JNI.h"

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - JNI Convenience
//----------------------------------------------------------------------------------------------------------------------------------
void HCMapJNIInstallReferenceInJObject(JNIEnv* env, jobject thiz, HCMapRef self) {
    jclass clazz = (*env)->GetObjectClass(env, thiz);
    jfieldID fieldID = (*env)->GetFieldID(env, clazz, HCMapJNIReferenceFieldID, HCMapJNIReferenceFieldSignature);
    (*env)->SetLongField(env, thiz, fieldID, (jlong)self);
}

void HCMapJNIReleaseReferenceInJObject(JNIEnv* env, jobject thiz) {
    jclass clazz = (*env)->GetObjectClass(env, thiz);
    jfieldID fieldID = (*env)->GetFieldID(env, clazz, HCMapJNIReferenceFieldID, HCMapJNIReferenceFieldSignature);
    HCMapRef self = (HCMapRef)(*env)->GetLongField(env, thiz, fieldID);
    (*env)->SetLongField(env, thiz, fieldID, (jlong)NULL);
    HCRelease(self);
}

HCMapRef HCMapJNIFromJObject(JNIEnv* env, jobject thiz) {
    jclass clazz = (*env)->GetObjectClass(env, thiz);
    jfieldID fieldID = (*env)->GetFieldID(env, clazz, HCMapJNIReferenceFieldID, HCMapJNIReferenceFieldSignature);
    HCMapRef self = (HCMapRef)(*env)->GetLongField(env, thiz, fieldID);
    return self;
}

jobject HCMapJNINewJObject(JNIEnv* env, HCMapRef self) {
    jclass clazz = (*env)->FindClass(env, HCMapJNIClass);
    jmethodID constructor = (*env)->GetMethodID(env, clazz, "<init>", "()V");
    jobject thiz = (*env)->NewObject(env, clazz, constructor);
    HCMapJNIInstallReferenceInJObject(env, thiz, self);
    return thiz;
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Construction
//----------------------------------------------------------------------------------------------------------------------------------
JNIEXPORT void JNICALL
Java_com_hollowcore_hollowjava_container_HollowMap_initNative(JNIEnv *env, jobject thiz, jint capacity) {
    HCMapRef self = HCMapCreateWithCapacity(capacity);
    HCMapJNIInstallReferenceInJObject(env, thiz, self);
}

JNIEXPORT void JNICALL
Java_com_hollowcore_hollowjava_container_HollowMap_finalizeNative(JNIEnv *env, jobject thiz) {
    HCMapJNIReleaseReferenceInJObject(env, thiz);
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Object Polymorphic Functions
//----------------------------------------------------------------------------------------------------------------------------------
JNIEXPORT jboolean JNICALL
Java_com_hollowcore_hollowjava_container_HollowMap_isEqualNative(JNIEnv *env, jobject thiz, jobject otherInstance) {
    HCMapRef self = HCMapJNIFromJObject(env, thiz);
    HCMapRef other = HCMapJNIFromJObject(env, otherInstance);
    return (jboolean)HCMapIsEqual(self, other);
}

JNIEXPORT jlong JNICALL
Java_com_hollowcore_hollowjava_container_HollowMap_hashNative(JNIEnv *env, jobject thiz) {
    HCMapRef self = HCMapJNIFromJObject(env, thiz);
    return self == NULL ? 0 : HCMapHashValue(self);
}

JNIEXPORT jstring JNICALL
Java_com_hollowcore_hollowjava_container_HollowMap_toStringNative(JNIEnv *env, jobject thiz) {
    HCMapRef self = HCMapJNIFromJObject(env, thiz);
    // TODO: memoryStream
//    HCMapPrint(self, memoryStream);
    jstring stringValue = (*env)->NewStringUTF(env, "TODO: Implement Map toStringNative");
//    HCRelease(memoryStream);
    return stringValue;
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Content
//----------------------------------------------------------------------------------------------------------------------------------
JNIEXPORT jboolean JNICALL
Java_com_hollowcore_hollowjava_container_HollowMap_isEmptyNative(JNIEnv *env, jobject thiz) {
    HCMapRef self = HCMapJNIFromJObject(env, thiz);
    HCBoolean isEmpty = HCMapIsEmpty(self);
    return (jboolean)isEmpty;
}

JNIEXPORT jint JNICALL
Java_com_hollowcore_hollowjava_container_HollowMap_sizeNative(JNIEnv *env, jobject thiz) {
    HCMapRef self = HCMapJNIFromJObject(env, thiz);
    HCInteger count = HCMapCount(self);
    return (jint)count;
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Searching
//----------------------------------------------------------------------------------------------------------------------------------
JNIEXPORT jboolean JNICALL
Java_com_hollowcore_hollowjava_container_HollowMap_containsKeyNative(JNIEnv *env, jobject thiz, jobject key_instance) {
    HCMapRef self = HCMapJNIFromJObject(env, thiz);
    HCRef key = HCObjectJNIFromJObject(env, key_instance);
    HCBoolean containsObject = HCMapContainsKey(self, key);
    return (jboolean)containsObject;
}

JNIEXPORT jobject JNICALL
Java_com_hollowcore_hollowjava_container_HollowMap_firstKeyNative(JNIEnv *env, jobject thiz) {
    HCMapRef self = HCMapJNIFromJObject(env, thiz);
    HCRef firstKey = HCMapFirstKey(self);
    return HCObjectJNINewJObject(env, firstKey);
}

JNIEXPORT jobject JNICALL
Java_com_hollowcore_hollowjava_container_HollowMap_lastKeyNative(JNIEnv *env, jobject thiz) {
    HCMapRef self = HCMapJNIFromJObject(env, thiz);
    HCRef lastKey = HCMapLastKey(self);
    return HCObjectJNINewJObject(env, lastKey);
}

JNIEXPORT jobject JNICALL
Java_com_hollowcore_hollowjava_container_HollowMap_getKeyNative(JNIEnv *env, jobject thiz, jint iteration_index) {
    HCMapRef self = HCMapJNIFromJObject(env, thiz);
    HCRef key = HCMapKeyAtIterationIndex(self, iteration_index);
    return HCObjectJNINewJObject(env, key);
}

JNIEXPORT jboolean JNICALL
Java_com_hollowcore_hollowjava_container_HollowMap_containsValueNative(JNIEnv *env, jobject thiz, jobject object_instance) {
    HCMapRef self = HCMapJNIFromJObject(env, thiz);
    HCRef object = HCObjectJNIFromJObject(env, object_instance);
    HCBoolean containsObject = HCMapContainsObject(self, object);
    return (jboolean)containsObject;
}

JNIEXPORT jobject JNICALL
Java_com_hollowcore_hollowjava_container_HollowMap_firstNative(JNIEnv *env, jobject thiz) {
    HCMapRef self = HCMapJNIFromJObject(env, thiz);
    HCRef first = HCMapFirstObject(self);
    return HCObjectJNINewJObject(env, first);
}

JNIEXPORT jobject JNICALL
Java_com_hollowcore_hollowjava_container_HollowMap_lastNative(JNIEnv *env, jobject thiz) {
    HCMapRef self = HCMapJNIFromJObject(env, thiz);
    HCRef last = HCMapLastObject(self);
    return HCObjectJNINewJObject(env, last);
}

JNIEXPORT jobject JNICALL
Java_com_hollowcore_hollowjava_container_HollowMap_getNative(JNIEnv *env, jobject thiz, jint iteration_index) {
    HCMapRef self = HCMapJNIFromJObject(env, thiz);
    HCRef object = HCMapObjectAtIterationIndex(self, iteration_index);
    return HCObjectJNINewJObject(env, object);
}

JNIEXPORT jobject JNICALL
Java_com_hollowcore_hollowjava_container_HollowMap_getForKeyNative(JNIEnv *env, jobject thiz, jobject key_instance) {
    HCMapRef self = HCMapJNIFromJObject(env, thiz);
    HCRef key = HCObjectJNIFromJObject(env, key_instance);
    HCRef object = HCMapObjectForKey(self, key);
    return HCObjectJNINewJObject(env, object);
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Operations
//----------------------------------------------------------------------------------------------------------------------------------
JNIEXPORT void JNICALL
Java_com_hollowcore_hollowjava_container_HollowMap_clearNative(JNIEnv *env, jobject thiz) {
    HCMapRef self = HCMapJNIFromJObject(env, thiz);
    HCMapClear(self);
}

JNIEXPORT jobject JNICALL
Java_com_hollowcore_hollowjava_container_HollowMap_putNative(JNIEnv *env, jobject thiz, jobject key_instance, jobject object_instance) {
    HCMapRef self = HCMapJNIFromJObject(env, thiz);
    HCRef key = HCObjectJNIFromJObject(env, key_instance);
    HCRef object = HCObjectJNIFromJObject(env, object_instance);
    HCRef existingObject = HCRetain(HCMapObjectForKey(self, key));
    HCMapAddObjectForKey(self, key, object);
    return HCObjectJNINewJObject(env, existingObject);
}

JNIEXPORT jobject JNICALL
Java_com_hollowcore_hollowjava_container_HollowMap_removeNative(JNIEnv *env, jobject thiz, jobject key_instance) {
    HCMapRef self = HCMapJNIFromJObject(env, thiz);
    HCRef key = HCObjectJNIFromJObject(env, key_instance);
    HCRef existingObject = HCMapRemoveObjectRetainedForKey(self, key);
    return HCObjectJNINewJObject(env, existingObject);
}
