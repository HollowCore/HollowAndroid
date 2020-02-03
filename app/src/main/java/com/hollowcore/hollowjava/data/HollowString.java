package com.hollowcore.hollowjava.data;

import com.hollowcore.hollowjava.core.HollowObject;

// TODO: Make class conform to CharSequence
public class HollowString {
    private long reference = 0;

    //----------------------------------------------------------------------------------------------------------------------------------
    // MARK: - Construction
    //----------------------------------------------------------------------------------------------------------------------------------
    public HollowString() { initNative(); }
    private native void initNative();

    public HollowString(byte[] utf8) { initWithUTF8Native(utf8); }
    private native void initWithUTF8Native(byte[] bytesUTF8);

    public HollowString(short[] utf16) { initWithUTF16Native(utf16); }
    private native void initWithUTF16Native(short[] utf16);

    public HollowString(int[] utf32) { initWithUTF32Native(utf32); }
    private native void initWithUTF32Native(int[] utf32);

    public HollowString(String string) { initWithStringNative(string); }
    private native void initWithStringNative(String string);

    public HollowString(boolean b) { initWithBooleanNative(b); }
    private native void initWithBooleanNative(boolean b);

    public HollowString(int integer) { initWithIntegerNative(integer); }
    private native void initWithIntegerNative(int integer);

    public HollowString(double real) { initWithRealNative(real); }
    private native void initWithRealNative(double real);

    private HollowString(HollowObject unused) { reference = 0xDEADBEEF; }

    @Override
    protected void finalize() throws Throwable {
        finalizeNative();
        super.finalize();
    }
    private native void finalizeNative();

    //----------------------------------------------------------------------------------------------------------------------------------
    // MARK: - Object Polymorphic Functions
    //----------------------------------------------------------------------------------------------------------------------------------
    public boolean isEqual(HollowString other) { return isEqualNative(other); }
    private native boolean isEqualNative(HollowString other);

    public long hashValue() { return hashNative(); }
    private native long hashNative();

    public String toString() { return toStringNative(); }
    private native String toStringNative();

    //----------------------------------------------------------------------------------------------------------------------------------
    // MARK: - Attributes
    //----------------------------------------------------------------------------------------------------------------------------------
    public boolean isEmpty() { return isEmptyNative(); }
    private native boolean isEmptyNative();

    public int getCodeUnitCount() { return getCodeUnitCountNative(); }
    private native int getCodeUnitCountNative();

    public byte getCodeUnit(int codeUnitIndex) { return getCodeUnitNative(codeUnitIndex); }
    private native byte getCodeUnitNative(int codeUnitIndex);

    public byte[] getCodeUnits(int codeUnitIndex, int count) { return getCodeUnitsNative(codeUnitIndex, count); }
    private native byte[] getCodeUnitsNative(int codeUnitIndex, int count);

    public int getCodePointCount() { return getCodePointCountNative(); }
    private native int getCodePointCountNative();

    public int getCodePoint(int codePointIndex) { return getCodePointNative(codePointIndex); }
    private native int getCodePointNative(int codePointIndex);

    public int[] getCodePoints(int codePointIndex, int count) { return getCodePointsNative(codePointIndex, count); }
    private native int[] getCodePointsNative(int codePointIndex, int count);

    //----------------------------------------------------------------------------------------------------------------------------------
    // MARK: - Conversion
    //----------------------------------------------------------------------------------------------------------------------------------
    public boolean isBoolean() { return isBooleanNative(); }
    private native boolean isBooleanNative();

    public boolean asBoolean() { return asBooleanNative(); }
    private native boolean asBooleanNative();

    public boolean isInteger() { return isIntegerNative(); }
    private native boolean isIntegerNative();

    public int asInteger() { return asIntegerNative(); }
    private native int asIntegerNative();

    public boolean isReal() { return isRealNative(); }
    private native boolean isRealNative();

    public double asReal() { return asRealNative(); }
    private native double asRealNative();
}
