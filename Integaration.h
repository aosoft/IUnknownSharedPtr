#pragma once

#include "ISum.h"
#include <atomic>
#include <memory>

class Sum :
	public ISum,
	public std::enable_shared_from_this<Sum>
{
private:
	std::atomic_int32_t m_ref;
	std::shared_ptr<Sum> m_sharedThis;

	int32_t m_counter;

public:
	Sum();
	~Sum();

	static HRESULT CreateInstance(ISum **instance);

	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void **ppvObject) override;
	virtual ULONG STDMETHODCALLTYPE AddRef(void) override;
	virtual ULONG STDMETHODCALLTYPE Release(void) override;

	virtual HRESULT STDMETHODCALLTYPE GetWeakReference(IWeakReference **weakReference) override;
	virtual void STDMETHODCALLTYPE Increment(int32_t a) override;
	virtual int32_t STDMETHODCALLTYPE GetCurrent() override;
};

class WeakReference :
	public IWeakReference
{
private:
	std::atomic_int32_t m_ref;
	std::weak_ptr<Sum> m_weak;

public:
	WeakReference(std::weak_ptr<Sum> const& sharedThis);

	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void **ppvObject) override;
	virtual ULONG STDMETHODCALLTYPE AddRef(void) override;
	virtual ULONG STDMETHODCALLTYPE Release(void) override;

	virtual HRESULT STDMETHODCALLTYPE Resolve(REFIID iid, void **ppv) override;
};