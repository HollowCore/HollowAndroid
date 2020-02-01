package com.hollowcore.hollowjava.container;

import java.util.AbstractList;
import java.util.List;

public class HollowList extends AbstractList implements List {
    private long reference = 0;

    //----------------------------------------------------------------------------------------------------------------------------------
    // MARK: - Construction
    //----------------------------------------------------------------------------------------------------------------------------------
    public HollowList(int capacity) { initNative(capacity); }
    private native void initNative(int capacity);

    private HollowList() { reference = 0xDEADBEEF; }

    @Override
    protected void finalize() throws Throwable {
        finalizeNative();
        super.finalize();
    }
    private native void finalizeNative();

    //----------------------------------------------------------------------------------------------------------------------------------
    // MARK: - Object Polymorphic Functions
    //----------------------------------------------------------------------------------------------------------------------------------
    public boolean isEqual(HollowList other) { return isEqualNative(other); }
    private native boolean isEqualNative(HollowList other);

    public long hashValue() { return hashNative(); }
    private native long hashNative();

    public String toString() { return toStringNative(); }
    private native String toStringNative();

    //----------------------------------------------------------------------------------------------------------------------------------
    // MARK: - Content
    //----------------------------------------------------------------------------------------------------------------------------------
    public boolean isEmpty() { return isEmptyNative(); }
    private native boolean isEmptyNative();

    public int size() { return sizeNative(); }
    private native int sizeNative();

    //----------------------------------------------------------------------------------------------------------------------------------
    // MARK: - Searching
    //----------------------------------------------------------------------------------------------------------------------------------
    public boolean contains(Object o) { return containsNative(o); }
    private native boolean containsNative(Object o);

    public Object first() { return firstNative(); }
    private native Object firstNative();

    public Object last() { return lastNative(); }
    private native Object lastNative();

    public Object get(int iterationIndex) { return getNative(iterationIndex); }
    private native Object getNative(int iterationIndex);

    //----------------------------------------------------------------------------------------------------------------------------------
    // MARK: - Operations
    //----------------------------------------------------------------------------------------------------------------------------------
    public void clear() { clearNative(); }
    private native void clearNative();

    public void add(int index, Object o) { addNative(index, o); }
    private native void addNative(int index, Object o);

    public Object remove(int index) { return removeNative(index); }
    private native Object removeNative(int index);

    public Object set(int index, Object o) { return setNative(index, o); }
    private native Object setNative(int index, Object o);

    //----------------------------------------------------------------------------------------------------------------------------------
    // MARK: - List Interface Support
    //----------------------------------------------------------------------------------------------------------------------------------
}
