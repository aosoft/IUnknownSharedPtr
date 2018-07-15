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

class Sum :
	public ISum
{
private:
	std::atomic_int32_t m_ref;
	std::shared_ptr<SumInternal> m_internal;

public:
	Sum();

	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid,void **ppvObject) override;
	virtual ULONG STDMETHODCALLTYPE AddRef(void) override;
	virtual ULONG STDMETHODCALLTYPE Release(void) override;

	virtual void STDMETHODCALLTYPE Increment(int32_t a) override;
	virtual int32_t STDMETHODCALLTYPE GetCurrent() override;
};
