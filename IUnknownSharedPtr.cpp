#include "stdafx.h"

#include <memory>
#include <unknwn.h>
#include <atlcomcli.h>

#include "Wrapper.h"
#include "Integaration.h"

void TestWeak(IWeakReference *weak)
{
	CComPtr<ISum> sum;
	weak->Resolve(IID_PPV_ARGS(&sum));

	if (sum != nullptr)
	{
		printf("ISum is alive.\n");
		sum->Increment(1);
		printf("%d\n", sum->GetCurrent());
	}
	else
	{
		printf("ISum is destructed.\n");
	}
}

int main()
{
	{
		CComPtr<ISum> sum = new SumWrapper();

		sum->Increment(1);
		printf("%d\n", sum->GetCurrent());
		sum->Increment(5);
		printf("%d\n", sum->GetCurrent());

		sum = nullptr;
	}

	{
		CComPtr<ISum> sum;
		Sum::CreateInstance(&sum);

		CComPtr<IWeakReference> weak;
		sum->GetWeakReference(&weak);

		sum->Increment(1);
		printf("%d\n", sum->GetCurrent());
		sum->Increment(5);
		printf("%d\n", sum->GetCurrent());

		TestWeak(weak);
		sum = nullptr;
		TestWeak(weak);
	}

    return 0;
}

