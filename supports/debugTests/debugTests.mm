//
//  debugTests.m
//  debugTests
//
//  Created by youknowone on 12. 10. 22..
//  Copyright (c) 2012 youknowone.org. All rights reserved.
//

#import "debug.h"

#import "debugTests.h"

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
        STFail(@"Not debug mode");
    }
    dprintf(@"Hello %@", @"World");
    dlog(1, @"Hello %@", @"World");
    dassert(true);
    dassertlog(true, @"This will now shown");
}

@end
