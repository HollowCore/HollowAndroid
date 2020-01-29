//
//  HCRectangle+JNI.h
//  HollowJava
//
//  Created by Matt Stoker on 1/28/20.
//  Copyright © 2020 HollowCore. All rights reserved.
//

#ifndef HOLLOWSHAPES_HCRECTANGLE_JNI_H
#define HOLLOWSHAPES_HCRECTANGLE_JNI_H

#include <jni.h>
#include "../HollowCore/Source/HollowCore.h"

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - JNI Convenience
//----------------------------------------------------------------------------------------------------------------------------------
#define HCRectangleJNIClass "com/hollowcore/hollowjava/geometry/Rectangle"
#define HCRectangleJNIReferenceFieldID "reference"
#define HCRectangleJNIReferenceFieldSignature "J"
#define HCRectangleJNIEdgeEnum "com/hollowcore/hollowjava/geometry/Rectangle$Edge"

void HCRectangleJNIInstallReferenceInJObject(JNIEnv* env, jobject thiz, HCRectangle self);
void HCRectangleJNIReleaseReferenceInJObject(JNIEnv* env, jobject thiz);
HCRectangle HCRectangleJNIFromJObject(JNIEnv* env, jobject thiz);
jobject HCRectangleJNINewJObject(JNIEnv* env, HCRectangle self);

#endif //HOLLOWSHAPES_HCRECTANGLE_JNI_H
