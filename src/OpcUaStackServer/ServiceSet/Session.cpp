#include "OpcUaStackServer/ServiceSet/Session.h"
#include "OpcUaStackCore/BuildInTypes/OpcUaIdentifier.h"
#include "OpcUaStackCore/Base/Log.h"
#include "OpcUaStackCore/Base/Utility.h"
#include "OpcUaStackCore/SecureChannel/RequestHeader.h"
#include "OpcUaStackCore/ServiceSet/CreateSessionRequest.h"
#include "OpcUaStackCore/ServiceSet/CreateSessionResponse.h"
#include "OpcUaStackCore/ServiceSet/CloseSessionRequest.h"
#include "OpcUaStackCore/ServiceSet/CloseSessionResponse.h"
#include "OpcUaStackCore/ServiceSet/ActivateSessionResponse.h"

using namespace OpcUaStackCore;

namespace OpcUaStackServer 
{

	boost::mutex Session::mutex_;
	OpcUaUInt32 Session::uniqueSessionId_ = 0;
	OpcUaUInt32 Session::uniqueAuthenticationToken_ = 0;
	
	OpcUaUInt32 
	Session::getUniqueSessionId(void)
	{
		boost::mutex::scoped_lock g(mutex_);
		uniqueSessionId_++;
		return uniqueSessionId_;
	}

	OpcUaUInt32 
	Session::getUniqueAuthenticationToken(void)
	{
		boost::mutex::scoped_lock g(mutex_);
		uniqueAuthenticationToken_++;
		return uniqueAuthenticationToken_;
	}


	Session::Session(void)
	: Component()
	, sessionState_(SessionState_Close)
	, sessionId_(getUniqueSessionId())
	, authenticationToken_(getUniqueAuthenticationToken())
	{
		Log(Info, "session construct")
			.parameter("SessionId", sessionId_)
			.parameter("AuthenticationToken", authenticationToken_);
		componentName("Session");
	}

	Session::~Session(void)
	{
		Log(Info, "session destruct")
			.parameter("SessionId", sessionId_)
			.parameter("AuthenticationToken", authenticationToken_);
	}

	void 
	Session::transactionManager(TransactionManager::SPtr transactionManagerSPtr)
	{
		transactionManagerSPtr_ = transactionManagerSPtr;
	}

	void 
	Session::sessionManagerIf(SessionManagerIf* sessionManagerIf)
	{
		sessionManagerIf_ = sessionManagerIf;
	}

	OpcUaUInt32 
	Session::sessionId(void)
	{
		return sessionId_;
	}

	OpcUaUInt32 
	Session::authenticationToken(void)
	{
		return authenticationToken_;
	}

	void 
	Session::endpointDescriptionArray(EndpointDescriptionArray::SPtr endpointDescriptionArray)
	{
		endpointDescriptionArray_ = endpointDescriptionArray;
	}

	bool 
	Session::message(SecureChannelTransaction& secureChannelTransaction)
	{
		switch (secureChannelTransaction.requestTypeNodeId_.nodeId<OpcUaStackCore::OpcUaUInt32>())
		{
			case OpcUaId_CreateSessionRequest_Encoding_DefaultBinary:
			{
				Log(Debug, "receive create session request");
				secureChannelTransaction.responseTypeNodeId_.nodeId(OpcUaId_CreateSessionResponse_Encoding_DefaultBinary);
				return receiveCreateSessionRequest(secureChannelTransaction);
				break;
			}
			case OpcUaId_ActivateSessionRequest_Encoding_DefaultBinary:
			{
				Log(Debug, "receive activate session request");
				secureChannelTransaction.responseTypeNodeId_.nodeId(OpcUaId_ActivateSessionResponse_Encoding_DefaultBinary);
				return receiveActivateSessionRequest(secureChannelTransaction);
				break;
			}
			case OpcUaId_CloseSessionRequest_Encoding_DefaultBinary:
			{
				Log(Debug, "receive close session request");
				secureChannelTransaction.responseTypeNodeId_.nodeId(OpcUaId_CloseSessionResponse_Encoding_DefaultBinary);
				return receiveCloseSessionRequest(secureChannelTransaction);
				break;
			}
			case OpcUaId_CancelRequest_Encoding_DefaultBinary:
			{
				Log(Debug, "receive cancel request");
				secureChannelTransaction.responseTypeNodeId_.nodeId(OpcUaId_CancelResponse_Encoding_DefaultBinary);
				return receiveCancelRequest(secureChannelTransaction);
				break;
			}
			default:
			{
				return receiveMessage(secureChannelTransaction);
			}
		}
	}

	bool 
	Session::receiveCreateSessionRequest(SecureChannelTransaction& secureChannelTransaction)
	{
		// FIXME: authenticationToken in secureChannelTransaction must be 0

		if (sessionState_ != SessionState_Close) {
			Log(Error, "receive create session request in invalid state")
				.parameter("SessionState", sessionState_);
			return false;
		}

		std::iostream ios(&secureChannelTransaction.is_);
		CreateSessionRequest createSessionRequest;
		createSessionRequest.opcUaBinaryDecode(ios);

		// FIXME: analyse request data

		boost::asio::streambuf sbres;
		std::iostream iosres(&sbres);

		CreateSessionResponse createSessionResponse;
		createSessionResponse.responseHeader()->requestHandle(createSessionRequest.requestHeader()->requestHandle());
		createSessionResponse.responseHeader()->serviceResult(Success);

		createSessionResponse.sessionId().namespaceIndex(1);
		createSessionResponse.sessionId().nodeId(sessionId_);
		createSessionResponse.authenticationToken().namespaceIndex(1);
		createSessionResponse.authenticationToken().nodeId(sessionId_);
		createSessionResponse.receivedSessionTimeout(120000);
		createSessionResponse.serverEndpoints(endpointDescriptionArray_);
		createSessionResponse.maxRequestMessageSize(0);

		createSessionResponse.opcUaBinaryEncode(iosres);

		sessionState_ = SessionState_CreateSessionResponse;

		secureChannelTransaction.authenticationToken_ = authenticationToken_;
		if (sessionManagerIf_ != nullptr) sessionManagerIf_->sessionMessage(sbres, secureChannelTransaction);
		return true;
	}
		
	bool 
	Session::receiveActivateSessionRequest(SecureChannelTransaction& secureChannelTransaction)
	{
		// FIXME: if authenticationToken in the secureChannelTransaction contains 0 then 
		//        the session has a new sechure channel


		std::iostream ios(&secureChannelTransaction.is_);
		ActivateSessionRequest activateSessionRequest;
		activateSessionRequest.opcUaBinaryDecode(ios);

		if (sessionState_ != SessionState_CreateSessionResponse) {
			Log(Error, "receive activate session request in invalid state")
				.parameter("SessionState", sessionState_);
			activateSessionRequestError(activateSessionRequest, secureChannelTransaction, BadIdentityTokenInvalid);
			return true;
		}

		// FIXME: analyse request data

		boost::asio::streambuf sbres;
		std::iostream iosres(&sbres);

		ActivateSessionResponse activateSessionResponse;
		activateSessionResponse.responseHeader()->requestHandle(activateSessionRequest.requestHeader()->requestHandle());
		activateSessionResponse.responseHeader()->serviceResult(Success);

		activateSessionResponse.opcUaBinaryEncode(iosres);

		sessionState_ = SessionState_Ready;

		secureChannelTransaction.authenticationToken_ = authenticationToken_;
		if (sessionManagerIf_ != nullptr) sessionManagerIf_->sessionMessage(sbres, secureChannelTransaction);
		return true;
	}

	void
	Session::activateSessionRequestError(ActivateSessionRequest& activateSessionRequest, SecureChannelTransaction& secureChannelTransaction, OpcUaStatusCode statusCode)
	{
		boost::asio::streambuf sbres;
		std::iostream iosres(&sbres);

		ActivateSessionResponse activateSessionResponse;
		activateSessionResponse.responseHeader()->requestHandle(activateSessionRequest.requestHeader()->requestHandle());
		activateSessionResponse.responseHeader()->serviceResult(statusCode);

		activateSessionResponse.opcUaBinaryEncode(iosres);

		if (sessionManagerIf_ != nullptr) sessionManagerIf_->sessionMessage(sbres, secureChannelTransaction);
	}

	bool 
	Session::receiveCloseSessionRequest(SecureChannelTransaction& secureChannelTransaction)
	{
		std::iostream ios(&secureChannelTransaction.is_);
		CloseSessionRequest closeSessionRequest;
		closeSessionRequest.opcUaBinaryDecode(ios);

		boost::asio::streambuf sbres;
		std::iostream iosres(&sbres);

		CloseSessionResponse closeSessionResponse;
		closeSessionResponse.responseHeader()->requestHandle(closeSessionRequest.requestHeader()->requestHandle());
		closeSessionResponse.responseHeader()->serviceResult(Success);

		if (sessionManagerIf_ != nullptr) sessionManagerIf_->sessionMessage(sbres, secureChannelTransaction);
		return true;
	}

	bool 
	Session::receiveCancelRequest(SecureChannelTransaction& secureChannelTransaction)
	{
		std::cout << "not implemented..." << std::endl;
		return false;
	}

	bool 
	Session::receiveMessage(SecureChannelTransaction& secureChannelTransaction)
	{
		if (sessionState_ != SessionState_Ready) {
			Log(Error, "receive message request in invalid state")
				.parameter("SessionState", sessionState_)
				.parameter("TypeId", secureChannelTransaction.requestTypeNodeId_);
			return false;
		}

		if (transactionManagerSPtr_.get() == nullptr) {
			Log(Error, "transaction manager empty");
			return false;
		}

		ServiceTransaction::SPtr serviceTransactionSPtr = transactionManagerSPtr_->getTransaction(secureChannelTransaction.requestTypeNodeId_);
		if (serviceTransactionSPtr.get() == nullptr) {
			Log(Error, "receive invalid message type")
				.parameter("TypeId", secureChannelTransaction.requestTypeNodeId_);
			return false;
		}
		serviceTransactionSPtr->componentSession(this);
		serviceTransactionSPtr->sessionId(sessionId_);
		serviceTransactionSPtr->channelId(secureChannelTransaction.channelId_);

		std::iostream ios(&secureChannelTransaction.is_);
		RequestHeader::SPtr requestHeader = serviceTransactionSPtr->requestHeader();
		//OpcUaStackCore::dumpHex(sb);
		requestHeader->opcUaBinaryDecode(ios);
		//OpcUaStackCore::dumpHex(sb);
		serviceTransactionSPtr->opcUaBinaryDecodeRequest(ios);
		//OpcUaStackCore::dumpHex(sb); 
		serviceTransactionSPtr->requestId_ = secureChannelTransaction.requestId_;
		serviceTransactionSPtr->statusCode(Success);

		Log(Debug, "receive request in session")
			.parameter("TrxId", serviceTransactionSPtr->transactionId())
			.parameter("TypeId", serviceTransactionSPtr->requestName());

		serviceTransactionSPtr->componentService()->send(secureChannelTransaction.requestTypeNodeId_, serviceTransactionSPtr);
		return true;
	}

	void  
	Session::receive(OpcUaNodeId& typeId, Message::SPtr message) 
	{
		ServiceTransaction::SPtr serviceTransactionSPtr = boost::static_pointer_cast<ServiceTransaction>(message);
		Log(Debug, "receive response in session")
			.parameter("TrxId", serviceTransactionSPtr->transactionId())
			.parameter("TypeId", serviceTransactionSPtr->responseName())
			.parameter("StatusCode", OpcUaStatusCodeMap::shortString(serviceTransactionSPtr->statusCode()));

		RequestHeader::SPtr requestHeader = serviceTransactionSPtr->requestHeader();
		ResponseHeader::SPtr responseHeader = serviceTransactionSPtr->responseHeader();
		responseHeader->requestHandle(requestHeader->requestHandle());
		responseHeader->serviceResult(serviceTransactionSPtr->statusCode());

		boost::asio::streambuf sb;
		std::iostream ios(&sb);
		responseHeader->opcUaBinaryEncode(ios);
		serviceTransactionSPtr->opcUaBinaryEncodeResponse(ios);

		SecureChannelTransaction secureChannelTransaction;
		secureChannelTransaction.requestId_ = serviceTransactionSPtr->requestId_;
		secureChannelTransaction.channelId_ = serviceTransactionSPtr->channelId();
		secureChannelTransaction.responseTypeNodeId_.nodeId(serviceTransactionSPtr->nodeTypeResponse().nodeId<uint32_t>());
		if (sessionManagerIf_ != nullptr) sessionManagerIf_->sessionMessage(sb, secureChannelTransaction);

	}

}
