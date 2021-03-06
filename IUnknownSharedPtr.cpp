#include "stdafx.h"

#include <memory>
#include <unknwn.h>

#include "Wrapper.h"
#include "Integaration.h"

#include <comdef.h>

template<class Intf>
using ComPtr = _com_ptr_t<_com_IIID<Intf, &__uuidof(Intf)>>;

void TestWeak(IWeakReference *weak)
{
	ComPtr<ISum> sum;
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
	/*{
		ComPtr<ISum> sum = new SumWrapper();

		sum->Increment(1);
		printf("%d\n", sum->GetCurrent());
		sum->Increment(2);
		printf("%d\n", sum->GetCurrent());

		sum = nullptr;
	}*/

	{
		ComPtr<ISum> sum;
		Sum::CreateInstance(&sum);

		ComPtr<IWeakReference> weak;
		sum->GetWeakReference(&weak);

		sum->Increment(1);
		printf("%d\n", sum->GetCurrent());
		sum->Increment(2);
		printf("%d\n", sum->GetCurrent());

		TestWeak(weak);
		sum = nullptr;
		TestWeak(weak);
	}

    return 0;
}

