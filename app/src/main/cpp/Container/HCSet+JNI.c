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
jclass HCSetJNIClazz = NULL;
jclass HCSetIteratorJNIClazz = NULL;

#define HCSetIteratorJNIClass "com/hollowcore/hollowjava/container/HollowSet$HollowSetIterator"

void HCSetJNIOnLoad(JNIEnv* env) {
    HCSetJNIClazz = (*env)->NewGlobalRef(env, (*env)->FindClass(env, HCSetJNIClass));
    HCSetIteratorJNIClazz = (*env)->NewGlobalRef(env, (*env)->FindClass(env, HCSetIteratorJNIClass));
    HCObjectJNIAssociateTypeToClass(env, HCSetType, HCSetJNIClazz);
}

void HCSetJNIInstallReferenceInJObject(JNIEnv* env, jobject thiz, HCSetRef self) {
    HCObjectJNIInstallReferenceInJObject(env, thiz, self);
}

void HCSetJNIReleaseReferenceInJObject(JNIEnv* env, jobject thiz) {
    HCObjectJNIReleaseReferenceInJObject(env, thiz);
}

HCSetRef HCSetJNIFromJObject(JNIEnv* env, jobject thiz) {
    return HCObjectJNIFromJObject(env, thiz);
}

jobject HCSetJNINewJObject(JNIEnv* env, HCSetRef self) {
    jmethodID constructor = (*env)->GetMethodID(env, HCSetJNIClazz, "<init>", "()V");
    jobject thiz = (*env)->NewObject(env, HCSetJNIClazz, constructor);
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

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Set Interface Support
//----------------------------------------------------------------------------------------------------------------------------------
void HCSetIteratorJNIInstallReferenceInJObject(JNIEnv* env, jobject thiz, HCSetIterator self) {
    HCDataRef value = HCDataCreateWithBytes(sizeof(self), (HCByte*)&self);
    jfieldID fieldID = (*env)->GetFieldID(env, HCSetIteratorJNIClazz, HCObjectJNIReferenceFieldID, HCObjectJNIReferenceFieldSignature);
    (*env)->SetLongField(env, thiz, fieldID, (jlong)value);
}

void HCSetIteratorJNIReleaseReferenceInJObject(JNIEnv* env, jobject thiz) {
    jfieldID fieldID = (*env)->GetFieldID(env, HCSetIteratorJNIClazz, HCObjectJNIReferenceFieldID, HCObjectJNIReferenceFieldSignature);
    HCDataRef value = (HCDataRef)(*env)->GetLongField(env, thiz, fieldID);
    (*env)->SetLongField(env, thiz, fieldID, (jlong)NULL);
    HCRelease(value);
}

HCSetIterator* HCSetIteratorJNIFromJObject(JNIEnv* env, jobject thiz) {
    jfieldID fieldID = (*env)->GetFieldID(env, HCSetIteratorJNIClazz, HCObjectJNIReferenceFieldID, HCObjectJNIReferenceFieldSignature);
    HCDataRef value = (HCDataRef)(*env)->GetLongField(env, thiz, fieldID);
    HCSetIterator* selfPointer = (HCSetIterator*)HCDataBytes(value);
    return selfPointer;
}

jobject HCSetIteratorJNINewJObject(JNIEnv* env, HCSetIterator self) {
    jmethodID constructor = (*env)->GetMethodID(env, HCSetIteratorJNIClazz, "<init>", "()V");
    jobject thiz = (*env)->NewObject(env, HCSetIteratorJNIClazz, constructor);
    HCSetIteratorJNIInstallReferenceInJObject(env, thiz, self);
    return thiz;
}

JNIEXPORT jobject JNICALL
Java_com_hollowcore_hollowjava_container_HollowSet_iteratorNative(JNIEnv *env, jobject thiz) {
    HCSetRef self = HCSetJNIFromJObject(env, thiz);
    HCSetIterator i = HCSetIterationBegin(self);
    return HCSetIteratorJNINewJObject(env, i);
}

JNIEXPORT void JNICALL
Java_com_hollowcore_hollowjava_container_HollowSet_00024HollowSetIterator_finalizeIteratorNative(JNIEnv *env, jobject thiz) {
    HCSetIteratorJNIReleaseReferenceInJObject(env, thiz);
}

JNIEXPORT jboolean JNICALL
Java_com_hollowcore_hollowjava_container_HollowSet_00024HollowSetIterator_hasNextNative(JNIEnv *env, jobject thiz) {
    // NOTE: The concept of "hasNext" for Iterator is the same as "ended" for HCSetIterator, not "hasNext".
    HCSetIterator* i = HCSetIteratorJNIFromJObject(env, thiz);
    HCBoolean hasEnded = HCSetIterationHasEnded(i);
    return (jboolean)!hasEnded;
}

JNIEXPORT jobject JNICALL
Java_com_hollowcore_hollowjava_container_HollowSet_00024HollowSetIterator_nextNative(JNIEnv *env, jobject thiz) {
    // NOTE: The concept of "next" for Iterator is the same as "current" for HCSetIterator, but also indicates to move to "next".
    HCSetIterator* i = HCSetIteratorJNIFromJObject(env, thiz);
    HCRef object = i->object;
    HCSetIterationNext(i);
    return HCObjectJNINewJObject(env, object);
}

JNIEXPORT void JNICALL
Java_com_hollowcore_hollowjava_container_HollowSet_00024HollowSetIterator_removeNative(JNIEnv *env, jobject thiz) {
    HCSetIterator* i = HCSetIteratorJNIFromJObject(env, thiz);
    // TODO: Does this put the iterator in an invalid state?
    HCSetRemoveObject(i->set, i->object);
}
