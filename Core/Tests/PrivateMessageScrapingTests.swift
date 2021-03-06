//  PrivateMessageScrapingTests.swift
//
//  Copyright 2013 Awful Contributors. CC BY-NC-SA 3.0 US https://github.com/Awful/Awful.app

@testable import AwfulCore
import XCTest

final class PrivateMessageScrapingTests: XCTestCase {

    func testFolder() throws {
        let result = try scrapeHTMLFixture(PrivateMessageFolderScrapeResult.self, named: "private-list")

        XCTAssertEqual(result.allFolders.map { $0.id.rawValue }, ["0", "-1"])
        XCTAssertEqual(result.allFolders.map { $0.name }, ["Inbox", "Sent Items"])

        XCTAssertEqual(result.folder?.id.rawValue, "0")
        XCTAssertEqual(result.folder?.name, "Inbox")

        XCTAssertFalse(result.isOnlyShowingLastFiftyMessages)

        XCTAssertEqual(result.messages.count, 4)

        let first = result.messages[0]
        XCTAssert(first.hasBeenSeen)
        XCTAssertEqual(first.id.rawValue, "4601204")
        XCTAssertEqual(first.senderUsername, "InFlames235")
        XCTAssertEqual(first.sentDate?.timeIntervalSince1970, 1352431800)
        XCTAssertEqual(first.subject, "Re: Awful app")
        XCTAssertFalse(first.wasForwarded)
        XCTAssertFalse(first.wasRepliedTo)
    }

    func testSingleMessage() throws {
        let result = try scrapeHTMLFixture(PrivateMessageScrapeResult.self, named: "private-one")

        XCTAssertEqual(result.privateMessageID, PrivateMessageID(rawValue: "4601162"))
        XCTAssertEqual(result.subject, "Awful app")
        XCTAssert(result.hasBeenSeen)
        XCTAssert(!result.wasRepliedTo)
        XCTAssert(!result.wasForwarded)
        XCTAssertEqual(result.sentDate?.timeIntervalSince1970, 1352429760)
        XCTAssert(result.body.contains("awesome app"))
        XCTAssertEqual(result.author?.userID, UserID(rawValue: "47395"))
        XCTAssertEqual(result.author?.username, "InFlames235")
        XCTAssertEqual(result.author?.regdate?.timeIntervalSince1970, 1073973600)
    }
}
