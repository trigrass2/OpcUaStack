#ifndef __OpcUaStackCore_SetMonitoringModeRequest_h__
#define __OpcUaStackCore_SetMonitoringModeRequest_h__

#include <stdint.h>
#include "OpcUaStackCore/Base/ObjectPool.h"
#include "OpcUaStackCore/Base/os.h"
#include "OpcUaStackCore/BuildInTypes/BuildInTypes.h"
#include "OpcUaStackCore/SecureChannel/RequestHeader.h"

namespace OpcUaStackCore
{

	typedef enum {
		MonitoringMode_Disabled = 0,
		MonitoringMode_Sampling = 1,
		MonitoringMode_Reporting = 2
	} MonitoringMode;

	class DLLEXPORT SetMonitoringModeRequest : public  ObjectPool<SetMonitoringModeRequest>
	{
	  public:
		SetMonitoringModeRequest(void);
		virtual ~SetMonitoringModeRequest(void);

		void requestHeader(const RequestHeader::SPtr requestHeader);
		RequestHeader::SPtr requestHeader(void) const;
		void subscriptionId(const OpcUaUInt32& subscriptionId);
		OpcUaUInt32 subscriptionId(void) const;
		void monitoringMode(const MonitoringMode monitoringMode);
		MonitoringMode monitoringMode(void) const;
		void monitoredItemIds(const OpcUaUInt32Array::SPtr monitordItemIds);
		OpcUaUInt32Array::SPtr monitoredItemIds(void) const;

		void opcUaBinaryEncode(std::ostream& os) const;
		void opcUaBinaryDecode(std::istream& is);

	  private:
		RequestHeader::SPtr requestHeaderSPtr_;
		OpcUaUInt32 subscriptionId_;
		MonitoringMode monitoringMode_;
		OpcUaUInt32Array::SPtr monitoredItemIdArraySPtr_;
	};

}

#endif