package com.hollowcore.hollowjava.data;

public class HollowData {
    private long reference = 0;

    //----------------------------------------------------------------------------------------------------------------------------------
    // MARK: - Construction
    //----------------------------------------------------------------------------------------------------------------------------------
    public HollowData(byte[] bytes) { initWithBytesNative(bytes); }
    private native void initWithBytesNative(byte[] bytes);

    public HollowData(boolean b) { initWithBooleanNative(b); }
    private native void initWithBooleanNative(boolean b);

    public HollowData(int integer) { initWithIntegerNative(integer); }
    private native void initWithIntegerNative(int integer);

    public HollowData(double real) { initWithRealNative(real); }
    private native void initWithRealNative(double real);

    private HollowData() { reference = 0xDEADBEEF; }

    @Override
    protected void finalize() throws Throwable {
        finalizeNative();
        super.finalize();
    }
    private native void finalizeNative();

    //----------------------------------------------------------------------------------------------------------------------------------
    // MARK: - Object Polymorphic Functions
    //----------------------------------------------------------------------------------------------------------------------------------
    public boolean isEqual(HollowData other) { return isEqualNative(other); }
    private native boolean isEqualNative(HollowData other);

    public long hashValue() { return hashNative(); }
    private native long hashNative();

    public String toString() { return toStringNative(); }
    private native String toStringNative();

    //----------------------------------------------------------------------------------------------------------------------------------
    // MARK: - Attributes
    //----------------------------------------------------------------------------------------------------------------------------------
    public boolean isEmpty() { return isEmptyNative(); }
    private native boolean isEmptyNative();

    public int getSize() { return getSizeNative(); }
    private native int getSizeNative();

    public byte[] getBytes() { return getBytesNative(); }
    private native byte[] getBytesNative();

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

    //----------------------------------------------------------------------------------------------------------------------------------
    // MARK: - Operations
    //----------------------------------------------------------------------------------------------------------------------------------
    public void clear() { clearNative(); }
    private native void clearNative();

    public void addBytes(byte[] bytes) { addBytesNative(bytes); }
    private native void addBytesNative(byte[] bytes);

    public void removeBytes(int count) { removeBytesNative(count); }
    private native void removeBytesNative(int count);

    public void addBoolean(boolean value) { addBooleanNative(value); }
    private native void addBooleanNative(boolean value);

    public void removeBoolean() { removeBooleanNative(); }
    private native void removeBooleanNative();

    public void addInteger(int value) { addIntegerNative(value); }
    private native void addIntegerNative(int value);

    public void removeInteger() { removeIntegerNative(); }
    private native void removeIntegerNative();

    public void addReal(double value) { addRealNative(value); }
    private native void addRealNative(double value);

    public void removeReal() { removeRealNative(); }
    private native void removeRealNative();
}
