#include "stdafx.h"
#include "Integaration.h"
#include <comdef.h>

template<class Intf>
using ComPtr = _com_ptr_t<_com_IIID<Intf, &__uuidof(Intf)>>;

Sum::Sum() :
	m_ref(0),
	m_counter(0)
{
	printf("Sum::ctor\n");
}

Sum::~Sum()
{
	printf("Sum::dtor\n");
}

HRESULT Sum::CreateInstance(ISum **instance)
{
	return std::make_shared<Sum>()->QueryInterface(IID_PPV_ARGS(instance));
}

HRESULT STDMETHODCALLTYPE Sum::QueryInterface(REFIID riid, void **ppvObject)
{
	if (ppvObject == nullptr)
	{
		return E_POINTER;
	}

	if (riid == IID_IUnknown || riid == __uuidof(ISum))
	{
		AddRef();
		*ppvObject = static_cast<ISum *>(this);
		return S_OK;
	}
	return E_NOINTERFACE;
}

ULONG STDMETHODCALLTYPE Sum::AddRef(void)
{
	int32_t count = ++m_ref;
	if (count == 1)
	{
		m_sharedThis = shared_from_this();
	}
	return count;
}

ULONG STDMETHODCALLTYPE Sum::Release(void)
{
	int32_t count = --m_ref;
	if (count == 0)
	{
		m_sharedThis = nullptr;
	}
	return count;
}

HRESULT Sum::GetWeakReference(IWeakReference **weakReference)
{
	if (weakReference == nullptr)
	{
		return E_POINTER;
	}
	ComPtr<IWeakReference> ret = new WeakReference(shared_from_this());
	return ret.QueryInterface(IID_PPV_ARGS(weakReference));
}

void Sum::Increment(int32_t a)
{
	m_counter += a;
}

int32_t Sum::GetCurrent()
{
	return m_counter;
}


WeakReference::WeakReference(std::shared_ptr<Sum> const& sharedThis) :
	m_ref(0),
	m_weak(sharedThis)
{
}

HRESULT STDMETHODCALLTYPE WeakReference::QueryInterface(REFIID riid, void **ppvObject)
{
	if (ppvObject == nullptr)
	{
		return E_POINTER;
	}

	if (riid == IID_IUnknown || riid == __uuidof(IWeakReference))
	{
		AddRef();
		*ppvObject = static_cast<IWeakReference *>(this);
		return S_OK;
	}
	return E_NOINTERFACE;
}

ULONG STDMETHODCALLTYPE WeakReference::AddRef(void)
{
	return ++m_ref;
}

ULONG STDMETHODCALLTYPE WeakReference::Release(void)
{
	int32_t count = --m_ref;
	if (count == 0)
	{
		delete this;
	}
	return count;
}

HRESULT STDMETHODCALLTYPE WeakReference::Resolve(REFIID iid, void **ppv)
{
	if (ppv == nullptr)
	{
		return E_POINTER;
	}

	auto locked = m_weak.lock();
	if (locked != nullptr)
	{
		return locked->QueryInterface(iid, ppv);
	}

	*ppv = nullptr;
	return S_OK;
}

