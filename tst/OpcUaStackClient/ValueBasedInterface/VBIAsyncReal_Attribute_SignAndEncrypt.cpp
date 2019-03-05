#include "unittest.h"
#include "OpcUaStackCore/Utility/Environment.h"
#include "OpcUaStackClient/CryptoManagerTest.h"
#include "OpcUaStackClient/ValueBasedInterface/VBIClient.h"
#include "OpcUaStackClient/ValueBasedInterface/VBIClientHandlerTest.h"

using namespace OpcUaStackCore;
using namespace OpcUaStackClient;

BOOST_AUTO_TEST_SUITE(VBIAsyncReal_Attribute_SignAndEncrypt_)

BOOST_AUTO_TEST_CASE(VBIAsyncReal_Attribute_SignAndEncrypt_)
{
	std::cout << "VBIAsyncReal_Attribute_SignAndEncrypt_t" << std::endl;
}

#ifdef REAL_SERVER
BOOST_AUTO_TEST_CASE(VBIAsyncReal_Attribute_SignAndEncrypt_read)
{

	VBIClientHandlerTest vbiClientHandlerTest;
	VBIClient client;

	// set session change callback
	client.setSessionChangeCallback(
		boost::bind(&VBIClientHandlerTest::sessionStateUpdate, &vbiClientHandlerTest, (uint32_t)1234, _1, _2)
	);

	// connect session
	//
	// To enable security, fields applicationUri, securityMode and security policy
	// must be specified.
	//
	std::string applicationUri = std::string("urn:") + CryptoManagerTest::getServerHostName() + std::string(":ASNeG:ASNeG-Demo");
	ConnectContext connectContext;
	connectContext.endpointUrl_ = REAL_SERVER_URI;
	connectContext.sessionName_ = REAL_SESSION_NAME;
	connectContext.applicationUri_ = applicationUri;					// needed to detect right certificate
	connectContext.securityMode_ = SM_SignAndEncrypt;					// security mode
	connectContext.securityPolicy_ = SP_Basic128Rsa15;					// security policy
	connectContext.cryptoManager_ = CryptoManagerTest::getInstance();
	connectContext.secureChannelLog_ = true;
	vbiClientHandlerTest.sessionStateUpdate_.initEvent();
	client.asyncConnect(connectContext);
	BOOST_REQUIRE(vbiClientHandlerTest.sessionStateUpdate_.waitForEvent(3000) == true);
	BOOST_REQUIRE(vbiClientHandlerTest.sessionState_ == SS_Connect);
	BOOST_REQUIRE(vbiClientHandlerTest.clientHandle_ == 1234);

	// read
	OpcUaNodeId nodeId;
	nodeId.set((OpcUaInt32)2259);
	vbiClientHandlerTest.readComplete_.initEvent();
	client.asyncRead(
		nodeId,
		boost::bind(&VBIClientHandlerTest::readComplete, &vbiClientHandlerTest, _1, _2, _3)
	);
	BOOST_REQUIRE(vbiClientHandlerTest.readComplete_.waitForEvent(3000) == true);
	BOOST_REQUIRE(vbiClientHandlerTest.statusCode_ == Success);
	vbiClientHandlerTest.dataValue_.out(std::cout);

	// disconnect session
	vbiClientHandlerTest.sessionStateUpdate_.initEvent();
	client.asyncDisconnect();
	BOOST_REQUIRE(vbiClientHandlerTest.sessionStateUpdate_.waitForEvent(3000) == true);
	BOOST_REQUIRE(vbiClientHandlerTest.sessionState_ == SS_Disconnect);
	BOOST_REQUIRE(vbiClientHandlerTest.clientHandle_ == 1234);
}

BOOST_AUTO_TEST_CASE(VBIAsyncReal_Attribute_SignAndEncrypt_write)
{
	VBIClientHandlerTest vbiClientHandlerTest;
	VBIClient client;

	// set session change callback
	client.setSessionChangeCallback(
		boost::bind(&VBIClientHandlerTest::sessionStateUpdate, &vbiClientHandlerTest, (uint32_t)1234, _1, _2)
	);

	// connect session
	//
	// To enable security, fields applicationUri, securityMode and security policy
	// must be specified.
	//
	std::string applicationUri = std::string("urn:") + CryptoManagerTest::getServerHostName() + std::string(":ASNeG:ASNeG-Demo");
	ConnectContext connectContext;
	connectContext.endpointUrl_ = REAL_SERVER_URI;
	connectContext.sessionName_ = REAL_SESSION_NAME;
	connectContext.applicationUri_ = applicationUri;					// needed to detect right certificate
	connectContext.securityMode_ = SM_SignAndEncrypt;					// security mode
	connectContext.securityPolicy_ = SP_Basic128Rsa15;					// security policy
	connectContext.cryptoManager_ = CryptoManagerTest::getInstance();;
	connectContext.secureChannelLog_ = true;
	vbiClientHandlerTest.sessionStateUpdate_.initEvent();
	client.asyncConnect(connectContext);
	BOOST_REQUIRE(vbiClientHandlerTest.sessionStateUpdate_.waitForEvent(3000) == true);
	BOOST_REQUIRE(vbiClientHandlerTest.sessionState_ == SS_Connect);
	BOOST_REQUIRE(vbiClientHandlerTest.clientHandle_ == 1234);

	// write
	OpcUaNodeId nodeId;
	OpcUaDataValue dataValue;
	dataValue.variant()->set((OpcUaBoolean)1);
	nodeId.set(220, 1);
	vbiClientHandlerTest.writeComplete_.initEvent();
	client.asyncWrite(
		nodeId,
		dataValue,
		boost::bind(&VBIClientHandlerTest::writeComplete, &vbiClientHandlerTest, _1, _2)
	);
	BOOST_REQUIRE(vbiClientHandlerTest.writeComplete_.waitForEvent(3000) == true);
	BOOST_REQUIRE(vbiClientHandlerTest.statusCode_ == Success);

	// disconnect session
	vbiClientHandlerTest.sessionStateUpdate_.initEvent();
	client.asyncDisconnect();
	BOOST_REQUIRE(vbiClientHandlerTest.sessionStateUpdate_.waitForEvent(3000) == true);
	BOOST_REQUIRE(vbiClientHandlerTest.sessionState_ == SS_Disconnect);
	BOOST_REQUIRE(vbiClientHandlerTest.clientHandle_ == 1234);
}
#endif

BOOST_AUTO_TEST_SUITE_END()
