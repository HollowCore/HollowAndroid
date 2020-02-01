//
//  HCObject+JNI.h
//  HollowJava
//
//  Created by Matt Stoker on 2/1/20.
//  Copyright © 2020 HollowCore. All rights reserved.
//
//

#include "HCObject+JNI.h"

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - JNI Convenience
//----------------------------------------------------------------------------------------------------------------------------------
void HCObjectJNIInstallReferenceInJObject(JNIEnv* env, jobject thiz, HCObjectRef self) {
    jclass clazz = (*env)->GetObjectClass(env, thiz);
    jfieldID fieldID = (*env)->GetFieldID(env, clazz, HCObjectJNIReferenceFieldID, HCObjectJNIReferenceFieldSignature);
    (*env)->SetLongField(env, thiz, fieldID, (jlong)self);
}

void HCObjectJNIReleaseReferenceInJObject(JNIEnv* env, jobject thiz) {
    jclass clazz = (*env)->GetObjectClass(env, thiz);
    jfieldID fieldID = (*env)->GetFieldID(env, clazz, HCObjectJNIReferenceFieldID, HCObjectJNIReferenceFieldSignature);
    HCObjectRef self = (HCObjectRef)(*env)->GetLongField(env, thiz, fieldID);
    (*env)->SetLongField(env, thiz, fieldID, (jlong)NULL);
    HCRelease(self);
}

HCObjectRef HCObjectJNIFromJObject(JNIEnv* env, jobject thiz) {
    jclass clazz = (*env)->GetObjectClass(env, thiz);
    jfieldID fieldID = (*env)->GetFieldID(env, clazz, HCObjectJNIReferenceFieldID, HCObjectJNIReferenceFieldSignature);
    HCObjectRef self = (HCObjectRef)(*env)->GetLongField(env, thiz, fieldID);
    return self;
}

jobject HCObjectJNINewJObject(JNIEnv* env, HCObjectRef self) {
    jclass clazz = (*env)->FindClass(env, HCObjectJNIClass);
    jmethodID constructor = (*env)->GetMethodID(env, clazz, "<init>", "()V");
    jobject thiz = (*env)->NewObject(env, clazz, constructor);
    HCObjectJNIInstallReferenceInJObject(env, thiz, self);
    return thiz;
}
