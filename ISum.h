#pragma once

#include <Unknwn.h>
#include <stdint.h>

class __declspec(uuid("{05DF99DC-2A25-4B49-AE17-31DE9A2BFBFF}")) IWeakReference : public IUnknown
{
public:
	virtual HRESULT STDMETHODCALLTYPE Resolve(REFIID iid, void **ppv) = 0;
};

class __declspec(uuid("{3FEC4416-AAB7-4595-B99C-A5998E294C0F}")) ISum : public IUnknown
{
public:
	virtual HRESULT STDMETHODCALLTYPE GetWeakReference(IWeakReference **weakReference) = 0;

	virtual void STDMETHODCALLTYPE Increment(int32_t a) = 0;
	virtual int32_t STDMETHODCALLTYPE GetCurrent() = 0;
};
