/*
   Copyright 2018-2021 Kai Huebl (kai@huebl-sgh.de)

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

#include "OpcUaStackCore/SecureChannel/SecureChannelSecuritySettings.h"

namespace OpcUaStackCore
{

	SecureChannelSecuritySettings::SecureChannelSecuritySettings(void)
	: cryptoBase_()
	, partnerNonce_()
	, ownNonce_()
	{
	}

	void
	SecureChannelSecuritySettings::cryptoBase(CryptoBase::SPtr& cryptoBase)
	{
		cryptoBase_ = cryptoBase;
	}

	SecureChannelSecuritySettings::~SecureChannelSecuritySettings(void)
	{
	}

	CryptoBase::SPtr&
	SecureChannelSecuritySettings::cryptoBase(void)
	{
		return cryptoBase_;
	}

	EndpointDescription::SPtr&
	SecureChannelSecuritySettings::endpointDescription(void)
	{
		return endpointDescription_;
	}

	SecureChannelKeys&
	SecureChannelSecuritySettings::secureChannelKeys(void)
	{
		return secureChannelKeys_;
	}

	bool
	SecureChannelSecuritySettings::isOwnEncryptionEnabled(void)
	{
		return ownCertificateChain_.size() > 0;

	}

	bool
	SecureChannelSecuritySettings::isOwnSignatureEnabled(void)
	{
		return partnerCertificateThumbprint_.exist();
	}

	OpcUaByteString&
	SecureChannelSecuritySettings::ownCertificateThumbprint(void)
	{
		return ownCertificateThumbprint_;
	}

	void
	SecureChannelSecuritySettings::ownSecurityPolicyUri(const OpcUaByteString& ownSecurityPolicyUri)
	{
		ownSecurityPolicyUri_ = ownSecurityPolicyUri;
	}

	const OpcUaByteString&
	SecureChannelSecuritySettings::ownSecurityPolicyUri(void)
	{
		return ownSecurityPolicyUri_;
	}

	void
	SecureChannelSecuritySettings::ownSecurityPolicy(SecurityPolicy::Enum ownSecurityPolicy)
	{
		ownSecurityPolicyUri_ = SecurityPolicy::enum2Str(ownSecurityPolicy);
	}

	SecurityPolicy::Enum
	SecureChannelSecuritySettings::ownSecurityPolicy(void)
	{
		return SecurityPolicy::str2Enum(ownSecurityPolicyUri_.toString());
	}

	void
	SecureChannelSecuritySettings::ownSecurityMode(MessageSecurityMode::Enum ownSecurityMode)
	{
		ownSecurityMode_ = ownSecurityMode;
	}

	MessageSecurityMode::Enum
	SecureChannelSecuritySettings::ownSecurityMode(void)
	{
		return ownSecurityMode_;
	}

	CertificateChain&
	SecureChannelSecuritySettings::ownCertificateChain(void)
	{
		return ownCertificateChain_;
	}

	MemoryBuffer&
	SecureChannelSecuritySettings::ownNonce(void)
	{
		return ownNonce_;
	}

	bool
	SecureChannelSecuritySettings::isPartnerEncryptionEnabled(void)
	{
		return ownCertificateThumbprint_.exist();
	}

	bool
	SecureChannelSecuritySettings::isPartnerSignatureEnabled(void)
	{
		return partnerCertificateChain_.size() > 0;
	}

	OpcUaByteString&
	SecureChannelSecuritySettings::partnerCertificateThumbprint(void)
	{
		return partnerCertificateThumbprint_;
	}

	OpcUaByteString&
	SecureChannelSecuritySettings::partnerSecurityPolicyUri(void)
	{
		return partnerSecurityPolicyUri_;
	}

	CertificateChain&
	SecureChannelSecuritySettings::partnerCertificateChain(void)
	{
		return partnerCertificateChain_;
	}

	MemoryBuffer&
	SecureChannelSecuritySettings::partnerNonce(void)
	{
		return partnerNonce_;
	}

}


