#import "Tools.h"
#import "PlatformSpecificTools.h"
#import <Foundation/Foundation.h>
#import <stdexcept>

@implementation Tools

+ (NSString *)getSQLiteFilePath {
  NSError *err = nil;
  NSURL *documentsUrl =
      [NSFileManager.defaultManager URLForDirectory:NSDocumentDirectory
                                           inDomain:NSUserDomainMask
                                  appropriateForURL:nil
                                             create:false
                                              error:&err];

  if (err) {
    NSLog(@"Error: %@", err);
    throw std::runtime_error(
        "Failed to resolve database path - could not find documentsUrl");
  }

  return [documentsUrl URLByAppendingPathComponent:@"comm.sqlite"].path;
}

+ (NSString *)generateSQLCipherEncryptionKey {
  comm::crypto::OlmBuffer buffer;
  comm::PlatformSpecificTools::generateSecureRandomBytes(buffer, 32);
  NSMutableString *randomHexString = [NSMutableString new];

  for (NSInteger i = 0; i < buffer.size(); i++) {
    [randomHexString appendFormat:@"%02X", buffer[i]];
  }
  return randomHexString;
}

@end
