//
//  HCRectangle+JNI.c
//  HollowJava
//
//  Created by Matt Stoker on 1/28/20.
//  Copyright © 2020 HollowCore. All rights reserved.
//

#include "HCRectangle+JNI.h"
#include "../Core/HCObject+JNI.h"
#include "HCPoint+JNI.h"
#include "HCSize+JNI.h"

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - JNI Convenience
//----------------------------------------------------------------------------------------------------------------------------------
jclass HCRectangleJNIClazz = NULL;

#define HCRectangleJNIEdgeEnum "com/hollowcore/hollowjava/geometry/Rectangle$Edge"

void HCRectangleJNIOnLoad(JNIEnv* env) {
    HCRectangleJNIClazz = (*env)->NewGlobalRef(env, (*env)->FindClass(env, HCRectangleJNIClass));
    HCObjectJNIAssociateTypeToClass(env, HCDataType, HCRectangleJNIClazz);
}

void HCRectangleJNIInstallReferenceInJObject(JNIEnv* env, jobject thiz, HCRectangle self) {
    HCDataRef value = HCDataCreateWithBytes(sizeof(self), (HCByte*)&self);
    jfieldID fieldID = (*env)->GetFieldID(env, HCRectangleJNIClazz, HCObjectJNIReferenceFieldID, HCObjectJNIReferenceFieldSignature);
    (*env)->SetLongField(env, thiz, fieldID, (jlong)value);
}

void HCRectangleJNIReleaseReferenceInJObject(JNIEnv* env, jobject thiz) {
    jfieldID fieldID = (*env)->GetFieldID(env, HCRectangleJNIClazz, HCObjectJNIReferenceFieldID, HCObjectJNIReferenceFieldSignature);
    HCDataRef value = (HCDataRef)(*env)->GetLongField(env, thiz, fieldID);
    (*env)->SetLongField(env, thiz, fieldID, (jlong)NULL);
    HCRelease(value);
}

HCRectangle HCRectangleJNIFromJObject(JNIEnv* env, jobject thiz) {
    jfieldID fieldID = (*env)->GetFieldID(env, HCRectangleJNIClazz, HCObjectJNIReferenceFieldID, HCObjectJNIReferenceFieldSignature);
    HCDataRef value = (HCDataRef)(*env)->GetLongField(env, thiz, fieldID);
    HCRectangle self = *((HCRectangle*)HCDataBytes(value));
    return self;
}

jobject HCRectangleJNINewJObject(JNIEnv* env, HCRectangle self) {
    jmethodID constructor = (*env)->GetMethodID(env, HCRectangleJNIClazz, "<init>", "()V");
    jobject thiz = (*env)->NewObject(env, HCRectangleJNIClazz, constructor);
    HCRectangleJNIInstallReferenceInJObject(env, thiz, self);
    return thiz;
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Constructors
//----------------------------------------------------------------------------------------------------------------------------------
JNIEXPORT void JNICALL
Java_com_hollowcore_hollowjava_geometry_Rectangle_initNative(JNIEnv *env, jobject thiz, jobject origin_instance, jobject size_instance) {
    HCPoint origin = HCPointJNIFromJObject(env, origin_instance);
    HCSize size = HCSizeJNIFromJObject(env, size_instance);
    HCRectangle self = HCRectangleMake(origin, size);
    HCRectangleJNIInstallReferenceInJObject(env, thiz, self);
}

JNIEXPORT void JNICALL
Java_com_hollowcore_hollowjava_geometry_Rectangle_initComponentsNative(JNIEnv *env, jobject thiz, jdouble x, jdouble y, jdouble width, jdouble height) {
    HCRectangle self = HCRectangleMakeWithComponents(x, y, width, height);
    HCRectangleJNIInstallReferenceInJObject(env, thiz, self);
}

JNIEXPORT void JNICALL
Java_com_hollowcore_hollowjava_geometry_Rectangle_finalizeNative(JNIEnv *env, jobject thiz) {
    HCRectangleJNIReleaseReferenceInJObject(env, thiz);
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Object Polymorphic Functions
//----------------------------------------------------------------------------------------------------------------------------------
JNIEXPORT jboolean JNICALL
Java_com_hollowcore_hollowjava_geometry_Rectangle_isEqualNative(JNIEnv *env, jobject thiz, jobject other_instance) {
    HCRectangle self = HCRectangleJNIFromJObject(env, thiz);
    HCRectangle other = HCRectangleJNIFromJObject(env, other_instance);
    HCBoolean isEqual = HCRectangleIsEqual(self, other);
    return (jboolean)isEqual;
}

JNIEXPORT jlong JNICALL
Java_com_hollowcore_hollowjava_geometry_Rectangle_hashNative(JNIEnv *env, jobject thiz) {
    HCRectangle self = HCRectangleJNIFromJObject(env, thiz);
    HCInteger hashValue = HCRectangleHashValue(self);
    return (jlong)hashValue;
}

JNIEXPORT jstring JNICALL
Java_com_hollowcore_hollowjava_geometry_Rectangle_toStringNative(JNIEnv *env, jobject thiz) {
    HCRectangle self = HCRectangleJNIFromJObject(env, thiz);
    // TODO: memoryStream
//    HCRectanglePrint(self, memoryStream);
    jstring stringValue = (*env)->NewStringUTF(env, "TODO: Implement Rectangle toStringNative");
//    HCRelease(memoryStream);
    return stringValue;
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Attributes
//----------------------------------------------------------------------------------------------------------------------------------
JNIEXPORT jobject JNICALL
Java_com_hollowcore_hollowjava_geometry_Rectangle_getOriginNative(JNIEnv *env, jobject thiz) {
    HCRectangle self = HCRectangleJNIFromJObject(env, thiz);
    HCPoint origin = self.origin;
    return HCPointJNINewJObject(env, origin);
}

JNIEXPORT jobject JNICALL
Java_com_hollowcore_hollowjava_geometry_Rectangle_getSizeNative(JNIEnv *env, jobject thiz) {
    HCRectangle self = HCRectangleJNIFromJObject(env, thiz);
    HCSize size = self.size;
    return HCSizeJNINewJObject(env, size);
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Calculated Properties
//----------------------------------------------------------------------------------------------------------------------------------
JNIEXPORT jdouble JNICALL
Java_com_hollowcore_hollowjava_geometry_Rectangle_getWidthNative(JNIEnv *env, jobject thiz) {
    HCRectangle self = HCRectangleJNIFromJObject(env, thiz);
    HCReal width = HCRectangleWidth(self);
    return (jdouble)width;
}

JNIEXPORT jdouble JNICALL
Java_com_hollowcore_hollowjava_geometry_Rectangle_getHeightNative(JNIEnv *env, jobject thiz) {
    HCRectangle self = HCRectangleJNIFromJObject(env, thiz);
    HCReal height = HCRectangleHeight(self);
    return (jdouble)height;
}

JNIEXPORT jdouble JNICALL
Java_com_hollowcore_hollowjava_geometry_Rectangle_getMinXNative(JNIEnv *env, jobject thiz) {
    HCRectangle self = HCRectangleJNIFromJObject(env, thiz);
    HCReal minX = HCRectangleMinX(self);
    return (jdouble)minX;
}

JNIEXPORT jdouble JNICALL
Java_com_hollowcore_hollowjava_geometry_Rectangle_getMidXNative(JNIEnv *env, jobject thiz) {
    HCRectangle self = HCRectangleJNIFromJObject(env, thiz);
    HCReal midX = HCRectangleMidX(self);
    return (jdouble)midX;
}

JNIEXPORT jdouble JNICALL
Java_com_hollowcore_hollowjava_geometry_Rectangle_getMaxXNative(JNIEnv *env, jobject thiz) {
    HCRectangle self = HCRectangleJNIFromJObject(env, thiz);
    HCReal maxX = HCRectangleMaxX(self);
    return (jdouble)maxX;
}

JNIEXPORT jdouble JNICALL
Java_com_hollowcore_hollowjava_geometry_Rectangle_getMinYNative(JNIEnv *env, jobject thiz) {
    HCRectangle self = HCRectangleJNIFromJObject(env, thiz);
    HCReal minY = HCRectangleMinY(self);
    return (jdouble)minY;
}

JNIEXPORT jdouble JNICALL
Java_com_hollowcore_hollowjava_geometry_Rectangle_getMidYNative(JNIEnv *env, jobject thiz) {
    HCRectangle self = HCRectangleJNIFromJObject(env, thiz);
    HCReal midY = HCRectangleMidY(self);
    return (jdouble)midY;
}

JNIEXPORT jdouble JNICALL
Java_com_hollowcore_hollowjava_geometry_Rectangle_getMaxYNative(JNIEnv *env, jobject thiz) {
    HCRectangle self = HCRectangleJNIFromJObject(env, thiz);
    HCReal maxY = HCRectangleMaxY(self);
    return (jdouble)maxY;
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Queries
//----------------------------------------------------------------------------------------------------------------------------------
JNIEXPORT jboolean JNICALL
Java_com_hollowcore_hollowjava_geometry_Rectangle_isZeroNative(JNIEnv *env, jobject thiz) {
    HCRectangle self = HCRectangleJNIFromJObject(env, thiz);
    HCBoolean isZero = HCRectangleIsZero(self);
    return (jboolean)isZero;
}

JNIEXPORT jboolean JNICALL
Java_com_hollowcore_hollowjava_geometry_Rectangle_isInfiniteNative(JNIEnv *env, jobject thiz) {
    HCRectangle self = HCRectangleJNIFromJObject(env, thiz);
    HCBoolean isInfinite = HCRectangleIsInfinite(self);
    return (jboolean)isInfinite;
}

JNIEXPORT jboolean JNICALL
Java_com_hollowcore_hollowjava_geometry_Rectangle_isInvalidNative(JNIEnv *env, jobject thiz) {
    HCRectangle self = HCRectangleJNIFromJObject(env, thiz);
    HCBoolean isInvalid = HCRectangleIsInvalid(self);
    return (jboolean)isInvalid;
}

JNIEXPORT jboolean JNICALL
Java_com_hollowcore_hollowjava_geometry_Rectangle_isSimilarNative(JNIEnv *env, jobject thiz, jobject other_instance, jdouble axis_dissimilarity) {
    HCRectangle self = HCRectangleJNIFromJObject(env, thiz);
    HCRectangle other = HCRectangleJNIFromJObject(env, other_instance);
    HCBoolean isSimilar = HCRectangleIsSimilar(self, other, axis_dissimilarity);
    return (jboolean)isSimilar;
}

JNIEXPORT jboolean JNICALL
Java_com_hollowcore_hollowjava_geometry_Rectangle_containsPointNative(JNIEnv *env, jobject thiz, jobject point_instance) {
    HCRectangle self = HCRectangleJNIFromJObject(env, thiz);
    HCPoint point = HCPointJNIFromJObject(env, point_instance);
    HCBoolean containsPoint = HCRectangleContainsPoint(self, point);
    return (jboolean)containsPoint;
}

JNIEXPORT jboolean JNICALL
Java_com_hollowcore_hollowjava_geometry_Rectangle_containsRectangleNative(JNIEnv *env, jobject thiz, jobject rectangle_instance) {
    HCRectangle self = HCRectangleJNIFromJObject(env, thiz);
    HCRectangle rectangle = HCRectangleJNIFromJObject(env, rectangle_instance);
    HCBoolean containsRectangle = HCRectangleContainsRectangle(self, rectangle);
    return (jboolean)containsRectangle;
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Operations
//----------------------------------------------------------------------------------------------------------------------------------
JNIEXPORT jobject JNICALL
Java_com_hollowcore_hollowjava_geometry_Rectangle_standardizedNative(JNIEnv *env, jobject thiz) {
    HCRectangle self = HCRectangleJNIFromJObject(env, thiz);
    HCRectangle standardized = HCRectangleStandardize(self);
    return HCRectangleJNINewJObject(env, standardized);
}

JNIEXPORT jobject JNICALL
Java_com_hollowcore_hollowjava_geometry_Rectangle_integralNative(JNIEnv *env, jobject thiz) {
    HCRectangle self = HCRectangleJNIFromJObject(env, thiz);
    HCRectangle integral = HCRectangleIntegral(self);
    return HCRectangleJNINewJObject(env, integral);
}

JNIEXPORT jobject JNICALL
Java_com_hollowcore_hollowjava_geometry_Rectangle_outsetNative(JNIEnv *env, jobject thiz, jdouble dx, jdouble dy) {
    HCRectangle self = HCRectangleJNIFromJObject(env, thiz);
    HCRectangle outset = HCRectangleOutset(self, dx, dy);
    return HCRectangleJNINewJObject(env, outset);
}

JNIEXPORT jobject JNICALL
Java_com_hollowcore_hollowjava_geometry_Rectangle_insetNative(JNIEnv *env, jobject thiz, jdouble dx, jdouble dy) {
    HCRectangle self = HCRectangleJNIFromJObject(env, thiz);
    HCRectangle inset = HCRectangleInset(self, dx, dy);
    return HCRectangleJNINewJObject(env, inset);
}

JNIEXPORT jobject JNICALL
Java_com_hollowcore_hollowjava_geometry_Rectangle_offsetNative(JNIEnv *env, jobject thiz, jdouble dx, jdouble dy) {
    HCRectangle self = HCRectangleJNIFromJObject(env, thiz);
    HCRectangle offset = HCRectangleOffset(self, dx, dy);
    return HCRectangleJNINewJObject(env, offset);
}

JNIEXPORT jobject JNICALL
Java_com_hollowcore_hollowjava_geometry_Rectangle_unionNative(JNIEnv *env, jobject thiz, jobject other_instance) {
    HCRectangle self = HCRectangleJNIFromJObject(env, thiz);
    HCRectangle other = HCRectangleJNIFromJObject(env, other_instance);
    HCRectangle unionRectangle = HCRectangleUnion(self, other);
    return HCRectangleJNINewJObject(env, unionRectangle);
}

JNIEXPORT jobject JNICALL
Java_com_hollowcore_hollowjava_geometry_Rectangle_intersectionNative(JNIEnv *env, jobject thiz, jobject other_instance) {
    HCRectangle self = HCRectangleJNIFromJObject(env, thiz);
    HCRectangle other = HCRectangleJNIFromJObject(env, other_instance);
    HCRectangle intersectionRectangle = HCRectangleIntersection(self, other);
    return HCRectangleJNINewJObject(env, intersectionRectangle);
}

JNIEXPORT jobjectArray JNICALL
Java_com_hollowcore_hollowjava_geometry_Rectangle_dividedNative(JNIEnv *env, jobject thiz, jdouble amount, jobject edge_instance) {
    HCRectangle self = HCRectangleJNIFromJObject(env, thiz);

    jclass edgeEnumClazz = (*env)->FindClass(env, HCRectangleJNIEdgeEnum);
    jfieldID minXFieldID = (*env)->GetStaticFieldID(env, edgeEnumClazz , "MIN_X", "L" HCRectangleJNIEdgeEnum ";");
    jobject minXField = (*env)->GetStaticObjectField(env, edgeEnumClazz, minXFieldID);
    jfieldID minYFieldID = (*env)->GetStaticFieldID(env, edgeEnumClazz , "MIN_Y", "L" HCRectangleJNIEdgeEnum ";");
    jobject minYField = (*env)->GetStaticObjectField(env, edgeEnumClazz, minXFieldID);
    jfieldID maxXFieldID = (*env)->GetStaticFieldID(env, edgeEnumClazz , "MAX_X", "L" HCRectangleJNIEdgeEnum ";");
    jobject maxYField = (*env)->GetStaticObjectField(env, edgeEnumClazz, minXFieldID);
    jfieldID maxYFieldID = (*env)->GetStaticFieldID(env, edgeEnumClazz , "MAX_Y", "L" HCRectangleJNIEdgeEnum ";");
    jobject maxXField = (*env)->GetStaticObjectField(env, edgeEnumClazz, minXFieldID);

    HCRectangleEdge edge = HCRectangleEdgeMinX;
    if (edge_instance == minXField) {
        edge = HCRectangleEdgeMinX;
    }
    if (edge_instance == minYField) {
        edge = HCRectangleEdgeMinY;
    }
    if (edge_instance == maxXField) {
        edge = HCRectangleEdgeMaxX;
    }
    if (edge_instance == maxYField) {
        edge = HCRectangleEdgeMaxY;
    }

    HCRectangle slice = HCRectangleZero;
    HCRectangle remainder = HCRectangleZero;
    HCRectangleDivide(self, &slice, &remainder, amount, edge);

    jobjectArray rectangles = (*env)->NewObjectArray(env, 2, HCRectangleJNIClazz, NULL);
    (*env)->SetObjectArrayElement(env, rectangles, 0, HCRectangleJNINewJObject(env, slice));
    (*env)->SetObjectArrayElement(env, rectangles, 0, HCRectangleJNINewJObject(env, remainder));
    return rectangles;
}
