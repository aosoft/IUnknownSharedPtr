#pragma once

#include "ISum.h"
#include <atomic>
#include <memory>

class SumInternal
{
private:
	int32_t m_counter;
public:
	SumInternal();
	void Increment(int32_t a);
	int32_t GetCurrent();
};

class SumWrapper :
	public ISum
{
private:
	std::atomic_int32_t m_ref;
	std::shared_ptr<SumInternal> m_internal;

public:
	SumWrapper();

	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid,void **ppvObject) override;
	virtual ULONG STDMETHODCALLTYPE AddRef(void) override;
	virtual ULONG STDMETHODCALLTYPE Release(void) override;

	virtual HRESULT STDMETHODCALLTYPE GetWeakReference(IWeakReference **weakReference) override;
	virtual void STDMETHODCALLTYPE Increment(int32_t a) override;
	virtual int32_t STDMETHODCALLTYPE GetCurrent() override;
};
