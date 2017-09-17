/*
   Copyright 2017 Kai Huebl (kai@huebl-sgh.de)

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

#ifndef __OpcUaEventTypeGenerator_OpcUaEventTypeGenerator_h__
#define __OpcUaEventTypeGenerator_OpcUaEventTypeGenerator_h__

#include "OpcUaStackCore/BuildInTypes/OpcUaNodeId.h"
#include "OpcUaStackServer/InformationModel/InformationModel.h"

using namespace OpcUaStackCore;
using namespace OpcUaStackServer;

namespace OpcUaEventTypeGenerator
{

	class OpcUaEventTypeGenerator
	{
	  public:
		OpcUaEventTypeGenerator(void);
		~OpcUaEventTypeGenerator(void);

		uint32_t start(int argc, char** argv);

	  private:
		InformationModel::SPtr informationModel_;
		OpcUaNodeId eventTypeNodeId_;

		void usage(void);
		bool findNodeId(const std::string& eventTypeName, const OpcUaNodeId& nodeId);

	};

}

#endif
