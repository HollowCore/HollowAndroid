package com.hollowcore.hollowjava.container;

import com.hollowcore.hollowjava.core.HollowObject;

import java.util.AbstractMap;
import java.util.Collection;
import java.util.HashSet;
import java.util.Iterator;
import java.util.Map;
import java.util.Set;

public class HollowMap extends AbstractMap implements Map {
    private long reference = 0;

    //----------------------------------------------------------------------------------------------------------------------------------
    // MARK: - Construction
    //----------------------------------------------------------------------------------------------------------------------------------
    public HollowMap() { this(8); }
    public HollowMap(int capacity) { initNative(capacity); }
    private native void initNative(int capacity);

    public HollowMap(Map m) {
        this(m.size());
        putAll(m);
    }

    private HollowMap(HollowObject unused) { reference = 0xDEADBEEF; }

    @Override
    protected void finalize() throws Throwable {
        finalizeNative();
        super.finalize();
    }
    private native void finalizeNative();

    //----------------------------------------------------------------------------------------------------------------------------------
    // MARK: - Object Polymorphic Functions
    //----------------------------------------------------------------------------------------------------------------------------------
    public boolean isEqual(HollowMap other) { return isEqualNative(other); }
    private native boolean isEqualNative(HollowMap other);

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
    public boolean containsKey(Object key) { return containsKeyNative(key); }
    private native boolean containsKeyNative(Object key);

    public Object firstKey() { return firstKeyNative(); }
    private native Object firstKeyNative();

    public Object lastKey() { return lastKeyNative(); }
    private native Object lastKeyNative();

    public Object getKey(int iterationIndex) { return getKeyNative(iterationIndex); }
    private native Object getKeyNative(int iterationIndex);

    public boolean containsValue(Object o) { return containsValueNative(o); }
    private native boolean containsValueNative(Object o);

    public Object first() { return firstNative(); }
    private native Object firstNative();

    public Object last() { return lastNative(); }
    private native Object lastNative();

    public Object get(int iterationIndex) { return getNative(iterationIndex); }
    private native Object getNative(int iterationIndex);

    public Object get(Object key) { return getForKeyNative(key); }
    private native Object getForKeyNative(Object key);

    //----------------------------------------------------------------------------------------------------------------------------------
    // MARK: - Operations
    //----------------------------------------------------------------------------------------------------------------------------------
    public void clear() { clearNative(); }
    private native void clearNative();

    public Object put(Object key, Object object) { return putNative(key, object); }
    private native Object putNative(Object key, Object object);

    public Object remove(Object key) { return removeNative(key); }
    private native Object removeNative(Object key);

    //----------------------------------------------------------------------------------------------------------------------------------
    // MARK: - Map Interface Support
    //----------------------------------------------------------------------------------------------------------------------------------
    public Set<Entry> entrySet() {
        // TODO: Find a way to eliminate needing to construct this
        Set<Entry> entrySet = new HashSet<>();
        for (int keyIndex = 0; keyIndex < size(); keyIndex++) {
            Entry entry = new HollowMapEntry(this, keyIndex);
            entrySet.add(entry);
        }
        return entrySet;
    }

    private class HollowMapEntry implements Entry {
        private HollowMapEntry(HollowMap map, int iterationIndex) {
            this.map = map;
            this.iterationIndex = iterationIndex;
        }

        private HollowMap map;
        private int iterationIndex;

        public Object getKey() {
            return map.getKey(iterationIndex);
        }

        public Object getValue() {
            return map.get(getKey());
        }

        public Object setValue(Object o) {
            return map.put(getKey(), o);
        }
    }
}
