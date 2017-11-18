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

#include "OpcUaStackPubSub/DataSetMessage/EventDataSetMessage.h"

namespace OpcUaStackPubSub
{

	EventDataSetMessage::EventDataSetMessage(void)
	: dataSetFields_(constructSPtr<DataSetFieldArray>())
	, fieldEncoding_(VariantEncoding)
	{
		messageType(EventData);
	}

	EventDataSetMessage::~EventDataSetMessage(void)
	{
	}

	DataSetFieldArray::SPtr&
	EventDataSetMessage::dataSetFields(void)
	{
		return dataSetFields_;
	}

	void
	EventDataSetMessage::opcUaBinaryEncode(std::ostream& os) const
	{
		uint16_t fieldCount = dataSetFields_->size();
		if (fieldCount == 0) return;

		DataSetField::SPtr dataSetField;
		dataSetFields_->get(0, dataSetField);
		if (dataSetField->dataType() == None) return;

		DataSetMessageHeader& hdr = const_cast<EventDataSetMessage*>(this)->dataSetMessageHeader();
		hdr.fieldEncoding(dataSetField->dataType());
		hdr.dataSetMessageSequenceNumberEnabled(true);
		hdr.dataSetFlag2Enabled(true);
		hdr.opcUaBinaryEncode(os);

		OpcUaNumber::opcUaBinaryEncode(os, fieldCount);
		for (uint32_t idx=0; idx<fieldCount; idx++) {
			DataSetField::SPtr dataSetField;
			dataSetFields_->get(idx, dataSetField);

			dataSetField->opcUaBinaryEncode(os);
		}
	}

	void
	EventDataSetMessage::opcUaBinaryDecode(std::istream& is)
	{
		DataSetMessageHeader& hdr = const_cast<EventDataSetMessage*>(this)->dataSetMessageHeader();
		hdr.opcUaBinaryDecode(is);
		fieldEncoding_ = hdr.fieldEncoding();
		if (fieldEncoding_ == None) return;

		uint16_t fieldCount;
		OpcUaNumber::opcUaBinaryDecode(is, fieldCount);
		if (fieldCount == 0) return;

		dataSetFields_->resize(fieldCount);
		for (uint32_t idx=0; idx<fieldCount; idx++) {
			DataSetField::SPtr dataSetField = constructSPtr<DataSetField>();

			dataSetField->createObject(VariantEncoding);
			dataSetField->opcUaBinaryDecode(is);
			dataSetFields_->push_back(dataSetField);
		}
	}

}
