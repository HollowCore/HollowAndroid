package com.hollowcore.hollowjava.core;

import java.util.HashMap;
import java.util.Map;

public class HollowObject {
    //----------------------------------------------------------------------------------------------------------------------------------
    // MARK: - JNI Type Class Mapping
    //----------------------------------------------------------------------------------------------------------------------------------
    private static Map<Long, Class> typeClassMap = new HashMap<Long, Class>();
    private static Map<String, Class> typeNameClassMap = new HashMap<String, Class>();
    private static Map<Class, Long> classTypeMap = new HashMap<Class, Long>();
    private static Map<Class, String> classTypeNameMap = new HashMap<Class, String>();

    private static Class getClassForType(long type) {
        Class clazz = typeClassMap.get(type);
        return clazz;
    }

    private static Class getClassForTypeName(String typeName) {
        Class clazz = typeNameClassMap.get(typeName);
        return clazz;
    }

    private static long getTypeForClass(Class clazz) {
        Long type = classTypeMap.get(clazz);
        return type == null ? classTypeMap.get(HollowObject.class) : type;
    }

    private static String getTypeNameForClass(Class clazz) {
        String typeName = classTypeNameMap.get(clazz);
        return typeName == null ? classTypeNameMap.get(HollowObject.class) : typeName;
    }

    private static void associateTypeToClass(long type, String typeName, Class clazz) {
        typeClassMap.put(type, clazz);
        typeNameClassMap.put(typeName, clazz);
        classTypeMap.put(clazz, type);
        classTypeNameMap.put(clazz, typeName);
    }

    //----------------------------------------------------------------------------------------------------------------------------------
    // MARK: - Construction
    //----------------------------------------------------------------------------------------------------------------------------------
    private long reference = 0;

    private HollowObject(HollowObject unused) { reference = 0xDEADBEEF; }

    @Override
    protected void finalize() throws Throwable {
        finalizeNative();
        super.finalize();
    }
    private native void finalizeNative();

    //----------------------------------------------------------------------------------------------------------------------------------
    // MARK: - Object Polymorphic Functions
    //----------------------------------------------------------------------------------------------------------------------------------
    public boolean isEqual(HollowObject other) { return isEqualNative(other); }
    private native boolean isEqualNative(HollowObject other);

    public long hashValue() { return hashNative(); }
    private native long hashNative();

    public String toString() { return toStringNative(); }
    private native String toStringNative();
}
