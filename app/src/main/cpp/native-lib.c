#include <jni.h>
#include "HollowCore/Source/HollowCore.h"

JNIEXPORT jstring JNICALL
Java_com_hollowcore_hollowshapes_MainActivity_stringFromJNI(JNIEnv* env, jobject this) {
    HCStringRef hello = HCStringCreateWithCString("Hello from HollowCore");
    jstring helloJava = (*env)->NewStringUTF(env, HCStringAsCString(hello));
    HCRelease(hello);
    return helloJava;
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - JNI Convenience
//----------------------------------------------------------------------------------------------------------------------------------
#define HCPointJavaClass "com/hollowcore/hollowjava/geometry/Point"
#define HCPointJavaReferenceFieldID "reference"
#define HCPointJavaReferenceFieldSignature "J"

void HCPointInstallReferenceInJObject(JNIEnv* env, jobject thiz, HCPoint self) {
    HCDataRef value = HCDataCreateWithBytes(sizeof(self), (HCByte*)&self);
    jclass clazz = (*env)->GetObjectClass(env, thiz);
    jfieldID fieldID = (*env)->GetFieldID(env, clazz, HCPointJavaReferenceFieldID, HCPointJavaReferenceFieldSignature);
    (*env)->SetLongField(env, thiz, fieldID, (jlong)value);
}

void HCPointReleaseReferenceInJObject(JNIEnv* env, jobject thiz) {
    jclass clazz = (*env)->GetObjectClass(env, thiz);
    jfieldID fieldID = (*env)->GetFieldID(env, clazz, HCPointJavaReferenceFieldID, HCPointJavaReferenceFieldSignature);
    HCDataRef value = (HCDataRef)(*env)->GetLongField(env, thiz, fieldID);
    (*env)->SetLongField(env, thiz, fieldID, (jlong)NULL);
    HCRelease(value);
}

HCPoint HCPointFromJObject(JNIEnv* env, jobject thiz) {
    jclass clazz = (*env)->GetObjectClass(env, thiz);
    jfieldID fieldID = (*env)->GetFieldID(env, clazz, HCPointJavaReferenceFieldID, HCPointJavaReferenceFieldSignature);
    HCDataRef value = (HCDataRef)(*env)->GetLongField(env, thiz, fieldID);
    HCPoint self = *((HCPoint*)HCDataBytes(value));
    return self;
}

jobject HCPointNewJObject(JNIEnv* env, HCPoint self) {
    jclass clazz = (*env)->FindClass(env, HCPointJavaClass);
    jmethodID constructor = (*env)->GetMethodID(env, clazz, "<init>", "()V");
    jobject thiz = (*env)->NewObject(env, clazz, constructor);
    HCPointInstallReferenceInJObject(env, thiz, self);
    return thiz;
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Constructors
//----------------------------------------------------------------------------------------------------------------------------------
JNIEXPORT void JNICALL
Java_com_hollowcore_hollowjava_geometry_Point_initNative(JNIEnv *env, jobject thiz, jdouble x, jdouble y) {
    HCPoint self = HCPointMake(x, y);
    HCPointInstallReferenceInJObject(env, thiz, self);
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Attributes
//----------------------------------------------------------------------------------------------------------------------------------
JNIEXPORT jdouble JNICALL
Java_com_hollowcore_hollowjava_geometry_Point_getXNative(JNIEnv *env, jobject thiz) {
    HCPoint self = HCPointFromJObject(env, thiz);
    HCReal x = self.x;
    return (jdouble)x;
}

JNIEXPORT jdouble JNICALL
Java_com_hollowcore_hollowjava_geometry_Point_getYNative(JNIEnv *env, jobject thiz) {
    HCPoint self = HCPointFromJObject(env, thiz);
    HCReal y = self.y;
    return (jdouble)y;
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Object Polymorphic Functions
//----------------------------------------------------------------------------------------------------------------------------------
JNIEXPORT jboolean JNICALL
Java_com_hollowcore_hollowjava_geometry_Point_isEqualNative(JNIEnv *env, jobject thiz, jobject other_instance) {
    HCPoint self = HCPointFromJObject(env, thiz);
    HCPoint other = HCPointFromJObject(env, other_instance);
    HCBoolean isEqual = HCPointIsEqual(self, other);
    return (jboolean)isEqual;
}

JNIEXPORT jlong JNICALL
Java_com_hollowcore_hollowjava_geometry_Point_hashNative(JNIEnv *env, jobject thiz) {
    HCPoint self = HCPointFromJObject(env, thiz);
    HCInteger hashValue = HCPointHashValue(self);
    return (jlong)hashValue;
}

JNIEXPORT jstring JNICALL
Java_com_hollowcore_hollowjava_geometry_Point_toStringNative(JNIEnv *env, jobject thiz) {
    HCPoint self = HCPointFromJObject(env, thiz);
    // TODO: memoryStream
//    HCPointPrint(self, memoryStream);
    jstring stringValue = (*env)->NewStringUTF(env, "TODO: Implement Point toStringNative");
//    HCRelease(memoryStream);
    return stringValue;
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Queries
//----------------------------------------------------------------------------------------------------------------------------------
JNIEXPORT jboolean JNICALL
Java_com_hollowcore_hollowjava_geometry_Point_isZeroNative(JNIEnv *env, jobject thiz) {
    HCPoint self = HCPointFromJObject(env, thiz);
    HCBoolean isZero = HCPointIsZero(self);
    return (jboolean)isZero;
}

JNIEXPORT jboolean JNICALL
Java_com_hollowcore_hollowjava_geometry_Point_isInfiniteNative(JNIEnv *env, jobject thiz) {
    HCPoint self = HCPointFromJObject(env, thiz);
    HCBoolean isInfinite = HCPointIsInfinite(self);
    return (jboolean)isInfinite;
}

JNIEXPORT jboolean JNICALL
Java_com_hollowcore_hollowjava_geometry_Point_isInvalidNative(JNIEnv *env, jobject thiz) {
    HCPoint self = HCPointFromJObject(env, thiz);
    HCBoolean isInvalid = HCPointIsInvalid(self);
    return (jboolean)isInvalid;
}

JNIEXPORT jboolean JNICALL
Java_com_hollowcore_hollowjava_geometry_Point_isSimilarNative(JNIEnv *env, jobject thiz, jobject other_instance, jdouble axis_dissimilarity) {
    HCPoint self = HCPointFromJObject(env, thiz);
    HCPoint other = HCPointFromJObject(env, other_instance);
    HCBoolean isSimilar = HCPointIsSimilar(self, other, axis_dissimilarity);
    return (jboolean)isSimilar;
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Operations
//----------------------------------------------------------------------------------------------------------------------------------
JNIEXPORT jobject JNICALL
Java_com_hollowcore_hollowjava_geometry_Point_offsetNative(JNIEnv *env, jobject thiz, jdouble dx, jdouble dy) {
    HCPoint self = HCPointFromJObject(env, thiz);
    HCPoint offset = HCPointOffset(self, dx, dy);
    return HCPointNewJObject(env, offset);
}

JNIEXPORT jobject JNICALL
Java_com_hollowcore_hollowjava_geometry_Point_scaledNative(JNIEnv *env, jobject thiz, jdouble scalar) {
    HCPoint self = HCPointFromJObject(env, thiz);
    HCPoint scaled = HCPointScale(self, scalar);
    return HCPointNewJObject(env, scaled);
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - JNI Convenience
//----------------------------------------------------------------------------------------------------------------------------------

#define HCPathJavaClass "com/hollowcore/hollowjava/graphic/Path"
#define HCPathJavaReferenceFieldID "reference"
#define HCPathJavaReferenceFieldSignature "J"
#define HCPathJavaIntersectionListenerClass "com/hollowcore/hollowjava/graphic/Path$IntersectionListener"
#define HCPathJavaIntersectionListenerIntersectionMethodID "intersection"
#define HCPathJavaIntersectionListenerIntersectionMethodSignature "(L" HCPathJavaClass ";L" HCPathJavaClass ";L" HCPointJavaClass ";)Z"

void HCPathInstallReferenceInJObject(JNIEnv* env, jobject thiz, HCPathRef self) {
    jclass clazz = (*env)->GetObjectClass(env, thiz);
    jfieldID fieldID = (*env)->GetFieldID(env, clazz, HCPathJavaReferenceFieldID, HCPathJavaReferenceFieldSignature);
    (*env)->SetLongField(env, thiz, fieldID, (jlong)self);
}

void HCPathReleaseReferenceInJObject(JNIEnv* env, jobject thiz) {
    jclass clazz = (*env)->GetObjectClass(env, thiz);
    jfieldID fieldID = (*env)->GetFieldID(env, clazz, HCPathJavaReferenceFieldID, HCPathJavaReferenceFieldSignature);
    HCPathRef self = (HCPathRef)(*env)->GetLongField(env, thiz, fieldID);
    (*env)->SetLongField(env, thiz, fieldID, (jlong)NULL);
    HCRelease(self);
}

HCPathRef HCPathFromJObject(JNIEnv* env, jobject thiz) {
    jclass clazz = (*env)->GetObjectClass(env, thiz);
    jfieldID fieldID = (*env)->GetFieldID(env, clazz, HCPathJavaReferenceFieldID, HCPathJavaReferenceFieldSignature);
    HCPathRef self = (HCPathRef)(*env)->GetLongField(env, thiz, fieldID);
    return self;
}

jobject HCPathNewJObject(JNIEnv* env, HCPathRef self) {
    jclass clazz = (*env)->FindClass(env, HCPathJavaClass);
    jmethodID constructor = (*env)->GetMethodID(env, clazz, "<init>", "()V");
    jobject thiz = (*env)->NewObject(env, clazz, constructor);
    HCPathInstallReferenceInJObject(env, thiz, self);
    return thiz;
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Construction
//----------------------------------------------------------------------------------------------------------------------------------
JNIEXPORT void JNICALL
Java_com_hollowcore_hollowjava_graphic_Path_initNative(JNIEnv *env, jobject thiz, jstring svg_path_data) {
    const char* svgPathData = (*env)->GetStringUTFChars(env, svg_path_data, NULL);
    HCPathRef self = HCPathCreate(svgPathData);
    (*env)->ReleaseStringUTFChars(env, svg_path_data, svgPathData);
    HCPathInstallReferenceInJObject(env, thiz, self);
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Object Polymorphic Functions
//----------------------------------------------------------------------------------------------------------------------------------
JNIEXPORT jboolean JNICALL
Java_com_hollowcore_hollowjava_graphic_Path_isEqualNative(JNIEnv *env, jobject thiz, jobject otherInstance) {
    HCPathRef self = HCPathFromJObject(env, thiz);
    HCPathRef other = HCPathFromJObject(env, otherInstance);
    return (jboolean)HCPathIsEqual(self, other);
}

JNIEXPORT jlong JNICALL
Java_com_hollowcore_hollowjava_graphic_Path_hashNative(JNIEnv *env, jobject thiz) {
    HCPathRef self = HCPathFromJObject(env, thiz);
    return self == NULL ? 0 : HCPathHashValue(self);
}

JNIEXPORT jstring JNICALL
Java_com_hollowcore_hollowjava_graphic_Path_toStringNative(JNIEnv *env, jobject thiz) {
    HCPathRef self = HCPathFromJObject(env, thiz);
    // TODO: memoryStream
//    HCPathPrint(self, memoryStream);
    jstring stringValue = (*env)->NewStringUTF(env, "TODO: Implement Path toStringNative");
//    HCRelease(memoryStream);
    return stringValue;
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Attributes
//----------------------------------------------------------------------------------------------------------------------------------
JNIEXPORT jint JNICALL
Java_com_hollowcore_hollowjava_graphic_Path_getElementCountNative(JNIEnv *env, jobject thiz) {
    HCPathRef self = HCPathFromJObject(env, thiz);
    HCInteger elementCount = HCPathElementCount(self);
    return (jint)elementCount;
}

JNIEXPORT jobject JNICALL
Java_com_hollowcore_hollowjava_graphic_Path_getElementNative(JNIEnv *env, jobject thiz, jint element_index) {
    HCPathRef self = HCPathFromJObject(env, thiz);
    HCInteger elementIndex = (HCInteger)element_index;
    HCPathElement element = HCPathElementAt(self, elementIndex);
    // TODO: Package into Path.Element
    return NULL;
}

JNIEXPORT jobject JNICALL
Java_com_hollowcore_hollowjava_graphic_Path_getCurrentPointNative(JNIEnv *env, jobject thiz) {
    HCPathRef self = HCPathFromJObject(env, thiz);
    HCPoint currentPoint = HCPathCurrentPoint(self);
    return HCPointNewJObject(env, currentPoint);
}

JNIEXPORT jobject JNICALL
Java_com_hollowcore_hollowjava_graphic_Path_getBoundsNative(JNIEnv *env, jobject thiz) {
    HCPathRef self = HCPathFromJObject(env, thiz);
    HCRectangle bounds = HCPathBounds(self);
    // TODO: Package into Rectangle
    return NULL;
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Path Manipulation
//----------------------------------------------------------------------------------------------------------------------------------
JNIEXPORT void JNICALL
Java_com_hollowcore_hollowjava_graphic_Path_moveNative(JNIEnv *env, jobject thiz, jdouble x, jdouble y) {
    HCPathRef self = HCPathFromJObject(env, thiz);
    HCPathMoveToPoint(self, x, y);
}

JNIEXPORT void JNICALL
Java_com_hollowcore_hollowjava_graphic_Path_addLineNative(JNIEnv *env, jobject thiz, jdouble x, jdouble y) {
    HCPathRef self = HCPathFromJObject(env, thiz);
    HCPathAddLine(self, x, y);
}

JNIEXPORT void JNICALL
Java_com_hollowcore_hollowjava_graphic_Path_addQuadraticCurveNative(JNIEnv *env, jobject thiz, jdouble cx, jdouble cy, jdouble x, jdouble y) {
    HCPathRef self = HCPathFromJObject(env, thiz);
    HCPathAddQuadraticCurve(self, cx, cy, x, y);
}

JNIEXPORT void JNICALL
Java_com_hollowcore_hollowjava_graphic_Path_addCubicCurveNative(JNIEnv *env, jobject thiz, jdouble cx0, jdouble cy0, jdouble cx1, jdouble cy1, jdouble x, jdouble y) {
    HCPathRef self = HCPathFromJObject(env, thiz);
    HCPathAddCubicCurve(self, cx0, cy0, cx1, cy1, x, y);
}

JNIEXPORT void JNICALL
Java_com_hollowcore_hollowjava_graphic_Path_closeSubpathNative(JNIEnv *env, jobject thiz) {
    HCPathRef self = HCPathFromJObject(env, thiz);
    HCPathCloseSubpath(self);
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Path Conversion
//----------------------------------------------------------------------------------------------------------------------------------
JNIEXPORT jstring JNICALL
Java_com_hollowcore_hollowjava_graphic_Path_asSVGPathDataNative(JNIEnv *env, jobject thiz) {
    HCPathRef self = HCPathFromJObject(env, thiz);
    // TODO: memoryStream
//    HCStringRef svgPathData = HCPathPrintData(self, memoryStream);
    jstring stringValue = (*env)->NewStringUTF(env, "TODO: Implement Path HCPathPrintData");
//    HCRelease(memoryStream);
    return stringValue;
}

JNIEXPORT jobjectArray JNICALL
Java_com_hollowcore_hollowjava_graphic_Path_asLineSegmentsNative(JNIEnv *env, jobject thiz, jdouble flatness_threshold) {
    HCPathRef self = HCPathFromJObject(env, thiz);
    HCDataRef lineSegmentData = HCPathAsLineSegmentDataRetained(self, HCPathFlatnessNormal);
    // TODO: Package line segments
    HCRelease(lineSegmentData);
    return NULL;
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Path Intersection
//----------------------------------------------------------------------------------------------------------------------------------
JNIEXPORT jboolean JNICALL
Java_com_hollowcore_hollowjava_graphic_Path_containsPointNative(JNIEnv *env, jobject thiz, jobject point_instance) {
    HCPathRef self = HCPathFromJObject(env, thiz);
    HCPoint point = HCPointFromJObject(env, point_instance);
    HCBoolean containsPoint = HCPathContainsPoint(self, point);
    return (jboolean)containsPoint;
}

JNIEXPORT jboolean JNICALL
Java_com_hollowcore_hollowjava_graphic_Path_containsPointNonZeroNative(JNIEnv *env, jobject thiz, jobject point_instance) {
    HCPathRef self = HCPathFromJObject(env, thiz);
    HCPoint point = HCPointFromJObject(env, point_instance);
    HCBoolean containsPoint = HCPathContainsPointNonZero(self, point);
    return (jboolean)containsPoint;
}

JNIEXPORT jboolean JNICALL
Java_com_hollowcore_hollowjava_graphic_Path_intersectsPathNative(JNIEnv *env, jobject thiz, jobject other_instance) {
    HCPathRef self = HCPathFromJObject(env, thiz);
    HCPathRef other = HCPathFromJObject(env, other_instance);
    HCBoolean intersectsPath = HCPathIntersectsPath(self, other);
    return (jboolean)intersectsPath;
}

typedef struct HCPathIntersectionJavaContext {
    JNIEnv* env;
    jobject thiz;
    jobject other_instance;
    jobject intersection_listener;
} HCPathIntersectionJavaContext;
void HCPathIntersectionJava(void* context, HCBoolean* continueSearching, HCPathRef path, HCPathRef otherPath, HCPoint point) {
    JNIEnv* env = ((HCPathIntersectionJavaContext*)context)->env;
    jobject thiz = ((HCPathIntersectionJavaContext*)context)->thiz;
    jobject other_instance = ((HCPathIntersectionJavaContext*)context)->other_instance;
    jobject intersection_listener = ((HCPathIntersectionJavaContext*)context)->intersection_listener;
    jmethodID intersectionMethodID = (*env)->GetMethodID(env, HCPathJavaIntersectionListenerClass, HCPathJavaIntersectionListenerIntersectionMethodID, HCPathJavaIntersectionListenerIntersectionMethodSignature);
    jobject point_instance = HCPointNewJObject(env, point);
    *continueSearching = (*env)->CallBooleanMethod(env, intersection_listener, intersectionMethodID, thiz, other_instance, point_instance);
}

JNIEXPORT void JNICALL
Java_com_hollowcore_hollowjava_graphic_Path_intersectionsNative(JNIEnv *env, jobject thiz, jobject other_instance, jobject intersection_listener) {
    HCPathRef self = HCPathFromJObject(env, thiz);
    HCPathRef other = HCPathFromJObject(env, other_instance);
    HCPathIntersectionJavaContext context = { .env = env, .thiz = thiz, .other_instance = other_instance, .intersection_listener = intersection_listener };
    HCPathIntersections(self, other, HCPathIntersectionJava, &context);
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Path Evaluation
//----------------------------------------------------------------------------------------------------------------------------------
//    void HCPathEvaluateLine(HCReal t, HCReal x0, HCReal y0, HCReal x1, HCReal y1, HCReal* sx, HCReal* sy, HCReal* dx, HCReal* dy);
//    void HCPathEvaluateQuadraticCurve(HCReal t, HCReal x0, HCReal y0, HCReal cx, HCReal cy, HCReal x1, HCReal y1, HCReal* sx, HCReal* sy, HCReal* dx, HCReal* dy);
//    void HCPathEvaluateCubicCurve(HCReal t, HCReal x0, HCReal y0, HCReal cx0, HCReal cy0, HCReal cx1, HCReal cy1, HCReal x1, HCReal y1, HCReal* sx, HCReal* sy, HCReal* dx, HCReal* dy);
//    void HCPathLineLineIntersection(HCReal x0, HCReal y0, HCReal x1, HCReal y1, HCReal x2, HCReal y2, HCReal x3, HCReal y3, HCReal* t, HCReal* u);
