// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Core/Interface/ISGMessageContext.h"
#include "Core/Interface/ISGMessageAttachment.h"

/**
 * Implements a message context for messages sent through the message bus.
 *
 * Message contexts contain a message and additional data about that message,
 * such as when the message was sent, who sent it and where it is being sent to.
 */

class FSGMessageContext
	: public ISGMessageContext
{
public:

	/** Default constructor. */
	FSGMessageContext()
		: Message(nullptr)
		, TypeInfo(nullptr)
	{ }

	/**
	 * Creates and initializes a new message context.
	 *
	 * This constructor overload is used for published and sent messages.
	 *
	 * @param InMessage The message payload.
	 * @param InTypeInfo The message's type information.
	 * @param InAnnotation The message header to attach to the message.
	 * @param InAttachment The binary data to attach to the message.
	 * @param InSender The sender's address.
	 * @param InRecipients The message recipients.
	 * @param InScope The message scope.
	 * @param InFlags The message flags.
	 * @param InTimeSent The time at which the message was sent.
	 * @param InExpiration The message's expiration time.
	 * @param InSenderThread The name of the thread from which the message was sent.
	 */
	FSGMessageContext(
		void* InMessage,
		UScriptStruct* InTypeInfo,
		const TMap<FName, FString>& InAnnotations,
		const TSharedPtr<ISGMessageAttachment, ESPMode::ThreadSafe>& InAttachment,
		const FSGMessageAddress& InSender,
		const TArray<FSGMessageAddress>& InRecipients,
		ESGMessageScope InScope,
		ESGMessageFlags InFlags,
		const FDateTime& InTimeSent,
		const FDateTime& InExpiration,
		ENamedThreads::Type InSenderThread
	)
		: Annotations(InAnnotations)
		, Attachment(InAttachment)
		, Expiration(InExpiration)
		, Message(InMessage)
		, Recipients(InRecipients)
		, Scope(InScope)
		, Flags(InFlags)
		, Sender(InSender)
		, SenderThread(InSenderThread)
		, TimeSent(InTimeSent)
		, TypeInfo(InTypeInfo)
	{ }

	FSGMessageContext(
	const FName& InMessageTag,
	void* InMessage,
	const TMap<FName, FString>& InAnnotations,
	const TSharedPtr<ISGMessageAttachment, ESPMode::ThreadSafe>& InAttachment,
	const FSGMessageAddress& InSender,
	const TArray<FSGMessageAddress>& InRecipients,
	ESGMessageScope InScope,
	ESGMessageFlags InFlags,
	const FDateTime& InTimeSent,
	const FDateTime& InExpiration,
	ENamedThreads::Type InSenderThread
)
	: Annotations(InAnnotations)
	, Attachment(InAttachment)
	, Expiration(InExpiration)
	, MessageTag(InMessageTag)
	, Message(InMessage)
	, Recipients(InRecipients)
	, Scope(InScope)
	, Flags(InFlags)
	, Sender(InSender)
	, SenderThread(InSenderThread)
	, TimeSent(InTimeSent)
	{ }

	/**
	 * Creates and initializes a new message context from an existing context.
	 *
	 * This constructor overload is used for forwarded messages.
	 *
	 * @param InContext The existing context.
	 * @param InForwarder The forwarder's address.
	 * @param NewRecipients The recipients of the new context.
	 * @param NewScope The message's new scope.
	 * @param InTimeForwarded The time at which the message was forwarded.
	 * @param InForwarderThread The name of the thread from which the message was forwarded.
	 */
	FSGMessageContext(
		const TSharedRef<ISGMessageContext, ESPMode::ThreadSafe>& InContext,
		const FSGMessageAddress& InForwarder,
		const TArray<FSGMessageAddress>& NewRecipients,
		ESGMessageScope NewScope,
		const FDateTime& InTimeForwarded,
		ENamedThreads::Type InForwarderThread
	)
		: Message(nullptr)
		, OriginalContext(InContext)
		, Recipients(NewRecipients)
		, Scope(NewScope)
		, Flags(ESGMessageFlags::None)
		, Sender(InForwarder)
		, SenderThread(InForwarderThread)
		, TimeSent(InTimeForwarded)
	{ }

	/** Destructor. */
	virtual ~FSGMessageContext() override;

public:

	//~ ISGMessageContext interface

	virtual const TMap<FName, FString>& GetAnnotations() const override;
	virtual TSharedPtr<ISGMessageAttachment, ESPMode::ThreadSafe> GetAttachment() const override;
	virtual const FDateTime& GetExpiration() const override;
	virtual const void* GetMessage() const override;
	virtual const TWeakObjectPtr<UScriptStruct>& GetMessageTypeInfo() const override;
	virtual TSharedPtr<ISGMessageContext, ESPMode::ThreadSafe> GetOriginalContext() const override;
	virtual const TArray<FSGMessageAddress>& GetRecipients() const override;
	virtual ESGMessageScope GetScope() const override;
	virtual ESGMessageFlags GetFlags() const override;
	virtual const FSGMessageAddress& GetSender() const override;
	virtual const FSGMessageAddress& GetForwarder() const override;
	virtual ENamedThreads::Type GetSenderThread() const override;
	virtual const FDateTime& GetTimeForwarded() const override;
	virtual const FDateTime& GetTimeSent() const override;
	virtual FName GetMessageType() const override;

private:

	/** Holds the optional message annotations. */
	TMap<FName, FString> Annotations;

	/** Holds a pointer to attached binary data. */
	TSharedPtr<ISGMessageAttachment, ESPMode::ThreadSafe> Attachment;

	/** Holds the expiration time. */
	FDateTime Expiration;

	FName MessageTag;

	/** Holds the message. */
	void* Message;

	/** Holds the original message context. */
	TSharedPtr<ISGMessageContext, ESPMode::ThreadSafe> OriginalContext;

	/** Holds the message recipients. */
	TArray<FSGMessageAddress> Recipients;

	/** Holds the message's scope. */
	ESGMessageScope Scope;

	/** Holds the message's scope. */
	ESGMessageFlags Flags;

	/** Holds the sender's identifier. */
	FSGMessageAddress Sender;

	/** Holds the name of the thread from which the message was sent. */
	ENamedThreads::Type SenderThread;

	/** Holds the time at which the message was sent. */
	FDateTime TimeSent;

	/** Holds the message's type information. */
	TWeakObjectPtr<UScriptStruct> TypeInfo;
};
