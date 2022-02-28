#pragma once
#import <EXSecureStore/EXSecureStore.h>
#import <ExpoModulesCore/EXModuleRegistryProvider.h>

#import <Foundation/Foundation.h>

@interface CommSecureStoreIOSWrapper : NSObject
+ (id)sharedInstance;

- (void)initialize;
- (void)set:(NSString *)key value:(NSString *)value;
- (NSString *)get:(NSString *)key;
@end
