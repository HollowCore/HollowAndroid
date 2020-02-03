//
//  HCObject+JNI.h
//  HollowJava
//
//  Created by Matt Stoker on 2/1/20.
//  Copyright © 2020 HollowCore. All rights reserved.
//

#ifndef HOLLOWSHAPES_HCOBJECT_JNI_H
#define HOLLOWSHAPES_HCOBJECT_JNI_H

#include <jni.h>
#include "../HollowCore/Source/HollowCore.h"

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - JNI Type Class Mapping
//----------------------------------------------------------------------------------------------------------------------------------
HCType HCObjectJNITypeForClass(JNIEnv* env, jclass object_clazz);
const char* HCObjectJNITypeNameForClass(JNIEnv* env, jclass object_clazz);
jclass HCObjectJNIClassForType(JNIEnv* env, HCType type);
jclass HCObjectJNIClassForTypeName(JNIEnv* env, const char* typeName);
void HCObjectJNIAssociateTypeToClass(JNIEnv* env, HCType type, jclass object_clazz);

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - JNI Convenience
//----------------------------------------------------------------------------------------------------------------------------------
#define HCObjectJNIClass "com/hollowcore/hollowjava/core/HollowObject"
#define HCObjectJNIReferenceFieldID "reference"
#define HCObjectJNIReferenceFieldSignature "J"
#define HCObjectJNIConstructor "<init>"
#define HCObjectJNIConstructorSignature "(L" HCObjectJNIClass ";)V"

void HCObjectJNIOnLoad(JNIEnv* env);
void HCObjectJNIInstallReferenceInJObject(JNIEnv* env, jobject thiz, HCRef self);
void HCObjectJNIReleaseReferenceInJObject(JNIEnv* env, jobject thiz);
HCRef HCObjectJNIFromJObject(JNIEnv* env, jobject thiz);
jobject HCObjectJNINewJObject(JNIEnv* env, HCRef self);

#endif //HOLLOWSHAPES_HCOBJECT_JNI_H
