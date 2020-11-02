/*
   Copyright 2020 Kai Huebl (kai@huebl-sgh.de)

   Lizenziert gemäß Apache Licence Version 2.0 (die „Lizenz“); Nutzung dieser
   Datei nur in Übereinstimmung mit der Lizenz erlaubt.
   Eine Kopie der Lizenz erhalten Sie auf http://www.apache.org/licenses/LICENSE-2.0.

   Sofern nicht gemäß geltendem Recht vorgeschrieben oder schriftlich vereinbart,
   erfolgt die Bereitstellung der im Rahmen der Lizenz verbreiteten Software OHNE
   GEWÄHR ODER VORBEHALTE – ganz gleich, ob ausdrücklich oder stillschweigend.

   Informationen über die jeweiligen Bedingungen für Genehmigungen und Einschränkungen
   im Rahmen der Lizenz finden Sie in der Lizenz.

   Autor: Kai Huebl (kai@huebl-sgh.de)
 */

#ifndef __OpcUaStackCore_RegisterForwardNodeAsyncResponse_h__
#define __OpcUaStackCore_RegisterForwardNodeAsyncResponse_h__

#include "OpcUaStackCore/Base/Object.h"
#include "OpcUaStackCore/BuildInTypes/OpcUaStatusCode.h"

namespace OpcUaStackCore
{

	class DLLEXPORT RegisterForwardNodeAsyncResponse
	: public Object
	{
	  public:
		using SPtr = boost::shared_ptr<RegisterForwardNodeAsyncResponse>;

	    RegisterForwardNodeAsyncResponse(void);
		virtual ~RegisterForwardNodeAsyncResponse(void);

		void statusCodeArray(const OpcUaStatusCodeArray::SPtr statusCodeArray);
		OpcUaStatusCodeArray::SPtr statusCodeArray(void) const;

		bool opcUaBinaryEncode(std::ostream& os) const;
		bool opcUaBinaryDecode(std::istream& is);

	  private:
		OpcUaStatusCodeArray::SPtr statusCodeArraySPtr_;
	};
}

#endif
