//
// Created by Michael Ong on 19/5/17.
// Copyright (c) 2017 Michael Ong. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@interface WindowViewController : UIViewController

@property(nonatomic)
void* ref_window;

- (void) sendMessage;

@end
