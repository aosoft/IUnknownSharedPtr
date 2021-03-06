#include "stdafx.h"
#include "Wrapper.h"

SumInternal::SumInternal() : m_counter(0)
{
}

void SumInternal::Increment(int32_t a)
{
	m_counter += a;
}

int32_t SumInternal::GetCurrent()
{
	return m_counter;
}


SumWrapper::SumWrapper() :
	m_ref(0),
	m_internal(std::make_shared<SumInternal>())
{
}

HRESULT STDMETHODCALLTYPE SumWrapper::QueryInterface(REFIID riid, void **ppvObject)
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

ULONG STDMETHODCALLTYPE SumWrapper::AddRef(void)
{
	return ++m_ref;
}

ULONG STDMETHODCALLTYPE SumWrapper::Release(void)
{
	int32_t count = --m_ref;
	if (count == 0)
	{
		delete this;
	}
	return count;
}

HRESULT SumWrapper::GetWeakReference(IWeakReference **weakReference)
{
	return E_NOTIMPL;
}

void SumWrapper::Increment(int32_t a)
{
	m_internal->Increment(a);
}

int32_t SumWrapper::GetCurrent()
{
	return m_internal->GetCurrent();
}
