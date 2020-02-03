package com.hollowcore.hollowjava.data;

import com.hollowcore.hollowjava.core.HollowObject;

public class HollowNumber {
    private long reference = 0;

    //----------------------------------------------------------------------------------------------------------------------------------
    // MARK: - Construction
    //----------------------------------------------------------------------------------------------------------------------------------
    public HollowNumber() { initNative(); }
    private native void initNative();

    public HollowNumber(boolean b) { initWithBooleanNative(b); }
    private native void initWithBooleanNative(boolean b);

    public HollowNumber(int integer) { initWithIntegerNative(integer); }
    private native void initWithIntegerNative(int integer);

    public HollowNumber(double real) { initWithRealNative(real); }
    private native void initWithRealNative(double real);
    
    private HollowNumber(HollowObject unused) { reference = 0xDEADBEEF; }

    @Override
    protected void finalize() throws Throwable {
        finalizeNative();
        super.finalize();
    }
    private native void finalizeNative();

    //----------------------------------------------------------------------------------------------------------------------------------
    // MARK: - Object Polymorphic Functions
    //----------------------------------------------------------------------------------------------------------------------------------
    public boolean isEqual(HollowNumber other) { return isEqualNative(other); }
    private native boolean isEqualNative(HollowNumber other);

    public long hashValue() { return hashNative(); }
    private native long hashNative();

    public String toString() { return toStringNative(); }
    private native String toStringNative();
    
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
