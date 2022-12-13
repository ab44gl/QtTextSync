#pragma once
#include "stdafx.h"
template <class T> class LiveData
{
  public:
    using ObserveFun = void(T newData);

  private:
    T _data;
    std::function<ObserveFun> _observeFun = nullptr;

  public:
    LiveData(T data);
    void observe(std::function<ObserveFun> callback);
    void set(T newData);
    T get();

  private:
    void notify();
};

template <class T> inline LiveData<T>::LiveData(T data) : _data(data)
{
}

template <class T> inline void LiveData<T>::observe(std::function<ObserveFun> callback)
{
    auto isNull = _observeFun == nullptr;
    _observeFun = callback;
    if (isNull)
    {
        notify();
    }
}

template <class T> inline void LiveData<T>::set(T newData)
{
    if (_data != newData)
    {
        _data = newData;
        notify();
    }
}

template <class T> inline T LiveData<T>::get()
{
    return _data;
}

template <class T> inline void LiveData<T>::notify()
{
    if (_observeFun != nullptr)
        _observeFun(_data);
}
