//
//  debugTests.mm
//  debugTests
//
//  Created by Jeong YunWon on 12. 10. 22..
//  Copyright (c) 2012 youknowone.org. All rights reserved.
//


@import XCTest;
@import debug;


@interface debugTests : XCTestCase

@end


@implementation debugTests

- (void)setUp
{
    [super setUp];
    
    // Set-up code here.
}

- (void)tearDown
{
    // Tear-down code here.
    
    [super tearDown];
}

- (void)testCrash
{
    if (!_DEBUG) {
        XCTFail(@"Not debug mode");
    }
    dprintf(@"Hello %@", @"World");
    dlog(1, @"Hello %@", @"World");
    dassert(true);
    dassertlog(true, @"This will now shown");
}

- (void)testOutput
{
    dlog(1, @"-----------------------");
    dlog(1, @"Is this formatted well? %@", @"yay!");
    for (int i = 0; i < 3; i++) {
        dlog(1, @"\tNumber test: %d", i);
    }
    dlog(1, @"-----------------------");
}

@end
