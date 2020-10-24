/*
   Copyright 2017-2020 Kai Huebl (kai@huebl-sgh.de)

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

#ifndef __OpcUaStackCore_RegisterForwardMethodRequest_h__
#define __OpcUaStackCore_RegisterForwardMethodRequest_h__

#include "OpcUaStackCore/BuildInTypes/OpcUaNodeId.h"
#include "OpcUaStackCore/ServiceSetApplication/ForwardMethodSync.h"

namespace OpcUaStackCore
{

	class DLLEXPORT RegisterForwardMethodRequest
	: public  Object
	{
	  public:
		typedef boost::shared_ptr<RegisterForwardMethodRequest> SPtr;

		RegisterForwardMethodRequest(void);
		virtual ~RegisterForwardMethodRequest(void);

		void forwardMethodSync(ForwardMethodSync::SPtr forwardMethodSync);
		ForwardMethodSync::SPtr& forwardMethodSync(void);
		void objectNodeId(OpcUaNodeId& objectNodeId);
		OpcUaNodeId& objectNodeId(void);
		void methodNodeId(OpcUaNodeId& methodNodeId);
		OpcUaNodeId& methodNodeId(void);

		bool opcUaBinaryEncode(std::ostream& os) const;
		bool opcUaBinaryDecode(std::istream& is);

	  private:
		ForwardMethodSync::SPtr forwardMethodSync_;
		OpcUaNodeId objectNodeId_;
		OpcUaNodeId methodNodeId_;
	};

}

#endif
