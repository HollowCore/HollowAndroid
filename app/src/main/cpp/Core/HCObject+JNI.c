//
//  HCObject+JNI.h
//  HollowJava
//
//  Created by Matt Stoker on 2/1/20.
//  Copyright © 2020 HollowCore. All rights reserved.
//
//

#include "HCObject+JNI.h"
#include "../HollowCore/Source/Core/HCObject_Internal.h"

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - JNI Type Class Mapping
//----------------------------------------------------------------------------------------------------------------------------------
jclass HCObjectJNIClazz = NULL;

#define HCObjectJNITypeForClassMethod "getTypeForClass"
#define HCObjectJNITypeForClassMethodSignature "(Ljava/lang/Class;)J"
#define HCObjectJNITypeNameForClassMethod "getTypeNameForClass"
#define HCObjectJNITypeNameForClassMethodSignature "(Ljava/lang/Class;)Ljava/lang/String;"
#define HCObjectJNIClassForTypeMethod "getClassForType"
#define HCObjectJNIClassForTypeMethodSignature "(J)Ljava/lang/Class;"
#define HCObjectJNIClassForTypeNameMethod "getClassForTypeName"
#define HCObjectJNIClassForTypeNameMethodSignature "(Ljava/lang/String;)Ljava/lang/Class;"
#define HCObjectJNIAssociateTypeToClassMethod "associateTypeToClass"
#define HCObjectJNIAssociateTypeToClassMethodSignature "(JLjava/lang/String;Ljava/lang/Class;)V"

HCType HCObjectJNITypeForClass(JNIEnv* env, jclass object_clazz) {
    HCObjectJNIClazz = (*env)->NewGlobalRef(env, (*env)->FindClass(env, HCObjectJNIClass));
    jmethodID methodID = (*env)->GetStaticMethodID(env, HCObjectJNIClazz, HCObjectJNITypeForClassMethod, HCObjectJNITypeForClassMethodSignature);
    HCType type = (HCType)(*env)->CallStaticLongMethod(env, HCObjectJNIClazz, methodID, object_clazz);
    return type == 0 ? HCObjectType : type;
}

const char* HCObjectJNITypeNameForClass(JNIEnv* env, jclass object_clazz) {
    jmethodID methodID = (*env)->GetStaticMethodID(env, HCObjectJNIClazz, HCObjectJNITypeForClassMethod, HCObjectJNITypeForClassMethodSignature);
    HCType type = (HCType)(*env)->CallStaticLongMethod(env, HCObjectJNIClazz, methodID, object_clazz);
    return type == 0 ? HCObjectType->name : type->name;
}

jclass HCObjectJNIClassForType(JNIEnv* env, HCType type) {
    jmethodID methodID = (*env)->GetStaticMethodID(env, HCObjectJNIClazz, HCObjectJNIClassForTypeNameMethod, HCObjectJNIClassForTypeNameMethodSignature);
    jstring type_name = (*env)->NewStringUTF(env, type->name);
    jclass object_clazz = (*env)->CallStaticObjectMethod(env, HCObjectJNIClazz, methodID, type_name);
    return object_clazz == NULL ? HCObjectJNIClazz : object_clazz;
}

jclass HCObjectJNIClassForTypeName(JNIEnv* env, const char* typeName) {
    jmethodID methodID = (*env)->GetStaticMethodID(env, HCObjectJNIClazz, HCObjectJNIClassForTypeNameMethod, HCObjectJNIClassForTypeNameMethodSignature);
    jstring type_name = (*env)->NewStringUTF(env, typeName);
    jclass object_clazz = (*env)->CallStaticObjectMethod(env, HCObjectJNIClazz, methodID, type_name);
    return object_clazz == NULL ? HCObjectJNIClazz : object_clazz;
}

void HCObjectJNIAssociateTypeToClass(JNIEnv* env, HCType type, jclass object_clazz) {
    jmethodID methodID = (*env)->GetStaticMethodID(env, HCObjectJNIClazz, HCObjectJNIAssociateTypeToClassMethod, HCObjectJNIAssociateTypeToClassMethodSignature);
    jstring type_name = (*env)->NewStringUTF(env, type->name);
    (*env)->CallStaticVoidMethod(env, HCObjectJNIClazz, methodID, (jlong)type, type_name, object_clazz);
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - JNI Convenience
//----------------------------------------------------------------------------------------------------------------------------------
void HCObjectJNIOnLoad(JNIEnv* env) {
    HCObjectJNIClazz = (*env)->NewGlobalRef(env, (*env)->FindClass(env, HCObjectJNIClass));
    HCObjectJNIAssociateTypeToClass(env, HCObjectType, HCObjectJNIClazz);
}

void HCObjectJNIInstallReferenceInJObject(JNIEnv* env, jobject thiz, HCRef self) {
    if (thiz == NULL || self == NULL) {
        return;
    }
    jclass clazz = (*env)->GetObjectClass(env, thiz);
    jfieldID fieldID = (*env)->GetFieldID(env, clazz, HCObjectJNIReferenceFieldID, HCObjectJNIReferenceFieldSignature);
    (*env)->SetLongField(env, thiz, fieldID, (jlong)self);
}

void HCObjectJNIReleaseReferenceInJObject(JNIEnv* env, jobject thiz) {
    if (thiz == NULL) {
        return;
    }
    jclass clazz = (*env)->GetObjectClass(env, thiz);
    jfieldID fieldID = (*env)->GetFieldID(env, clazz, HCObjectJNIReferenceFieldID, HCObjectJNIReferenceFieldSignature);
    HCObjectRef self = (HCObjectRef)(*env)->GetLongField(env, thiz, fieldID);
    (*env)->SetLongField(env, thiz, fieldID, (jlong)NULL);
    HCRelease(self);
}

HCRef HCObjectJNIFromJObject(JNIEnv* env, jobject thiz) {
    if (thiz == NULL) {
        return NULL;
    }
    jclass clazz = (*env)->GetObjectClass(env, thiz);
    jfieldID fieldID = (*env)->GetFieldID(env, clazz, HCObjectJNIReferenceFieldID, HCObjectJNIReferenceFieldSignature);
    HCObjectRef self = (HCObjectRef)(*env)->GetLongField(env, thiz, fieldID);
    return self;
}

jobject HCObjectJNINewJObject(JNIEnv* env, HCRef self) {
    if (self == NULL) {
        return NULL;
    }
    jclass clazz = HCObjectJNIClassForType(env, ((HCObjectRef)self)->type);
    jmethodID constructor = (*env)->GetMethodID(env, clazz, HCObjectJNIConstructor, HCObjectJNIConstructorSignature);
    jobject thiz = (*env)->NewObject(env, clazz, constructor, NULL);
    HCObjectJNIInstallReferenceInJObject(env, thiz, self);
    return thiz;
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Construction
//----------------------------------------------------------------------------------------------------------------------------------
JNIEXPORT void JNICALL
Java_com_hollowcore_hollowjava_core_HollowObject_finalizeNative(JNIEnv *env, jobject thiz) {
    HCObjectJNIReleaseReferenceInJObject(env, thiz);
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Object Polymorphic Functions
//----------------------------------------------------------------------------------------------------------------------------------
JNIEXPORT jboolean JNICALL
Java_com_hollowcore_hollowjava_core_HollowObject_isEqualNative(JNIEnv *env, jobject thiz, jobject other_instance) {
    HCObjectRef self = HCObjectJNIFromJObject(env, thiz);
    HCObjectRef other = HCObjectJNIFromJObject(env, other_instance);
    return (jboolean)HCObjectIsEqual(self, other);
}

JNIEXPORT jlong JNICALL
Java_com_hollowcore_hollowjava_core_HollowObject_hashNative(JNIEnv *env, jobject thiz) {
    HCObjectRef self = HCObjectJNIFromJObject(env, thiz);
    return self == NULL ? 0 : HCObjectHashValue(self);
}

JNIEXPORT jstring JNICALL
Java_com_hollowcore_hollowjava_core_HollowObject_toStringNative(JNIEnv *env, jobject thiz) {
    HCObjectRef self = HCObjectJNIFromJObject(env, thiz);
    // TODO: memoryStream
//    HCObjectPrint(self, memoryStream);
    jstring stringValue = (*env)->NewStringUTF(env, "TODO: Implement Object toStringNative");
//    HCRelease(memoryStream);
    return stringValue;
}