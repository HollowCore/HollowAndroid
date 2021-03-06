package com.hollowcore.hollowjava.container;

import com.hollowcore.hollowjava.core.HollowObject;

import java.util.AbstractSet;
import java.util.Collection;
import java.util.Iterator;
import java.util.Set;

public class HollowSet extends AbstractSet implements Set {
    private long reference = 0;

    //----------------------------------------------------------------------------------------------------------------------------------
    // MARK: - Construction
    //----------------------------------------------------------------------------------------------------------------------------------
    public HollowSet() { this(8); }
    public HollowSet(int capacity) { initNative(capacity); }
    private native void initNative(int capacity);

    public HollowSet(Collection c) {
        this(c.size());
        addAll(c);
    }

    private HollowSet(HollowObject unused) { reference = 0xDEADBEEF; }

    protected void finalize() throws Throwable {
        finalizeNative();
        super.finalize();
    }
    private native void finalizeNative();

    //----------------------------------------------------------------------------------------------------------------------------------
    // MARK: - Object Polymorphic Functions
    //----------------------------------------------------------------------------------------------------------------------------------
    public boolean isEqual(HollowSet other) { return isEqualNative(other); }
    private native boolean isEqualNative(HollowSet other);

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

    public boolean add(Object o) { return addNative(o); }
    private native boolean addNative(Object o);

    public boolean remove(Object o) { return removeNative(o); }
    private native boolean removeNative(Object o);

    //----------------------------------------------------------------------------------------------------------------------------------
    // MARK: - Set Interface Support
    //----------------------------------------------------------------------------------------------------------------------------------
    public Iterator iterator() { return iteratorNative(); }
    private native Iterator iteratorNative();

    private class HollowSetIterator implements Iterator {
        private long reference = 0;

        private HollowSetIterator() { reference = 0xDEADBEEF; }

        protected void finalize() throws Throwable {
            finalizeIteratorNative();
            super.finalize();
        }
        private native void finalizeIteratorNative();

        public boolean hasNext() { return hasNextNative(); }
        private native boolean hasNextNative();

        public Object next() { return nextNative(); }
        private native Object nextNative();

        public void remove() { removeNative(); }
        private native void removeNative();
    }
}
