#include "stdafx.h"

#include <memory>
#include <unknwn.h>
#include <atlcomcli.h>

#include "Wrapper.h"

int main()
{
	CComPtr<ISum> sum = new Sum();

	sum->Increment(1);
	printf("%d\n", sum->GetCurrent());
	sum->Increment(5);
	printf("%d\n", sum->GetCurrent());

	sum = nullptr;

    return 0;
}

