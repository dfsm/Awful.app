//  AwfulForm.h
//
//  Copyright 2013 Awful Contributors. CC BY-NC-SA 3.0 US https://github.com/Awful/Awful.app

@import CoreData;
@import Foundation;
@import HTMLReader;
@class ThreadTag;

NS_ASSUME_NONNULL_BEGIN

/// Describes an HTML form and helps prepare it for submission.
@interface AwfulForm : NSObject

/// @param element The <form> element representing the form.
- (nullable instancetype)initWithElement:(HTMLElement *)element NS_DESIGNATED_INITIALIZER;

- (instancetype)init NS_UNAVAILABLE;

@property (readonly, strong, nonatomic) HTMLElement *element;

/// The name of the form in markup.
@property (readonly, nullable, copy, nonatomic) NSString *name;

/// The HTTP method suitable for submitting the form.
@property (readonly, nullable, copy, nonatomic) NSString *HTTPMethod;

/// The URL to which the form should be submitted.
@property (readonly, nullable, strong, nonatomic) NSURL *submissionURL;

/// Finds all thread tags in the form and updates a managed object context with the findings.
- (void)scrapeThreadTagsIntoManagedObjectContext:(NSManagedObjectContext *)managedObjectContext;

/// An array of AwfulThreadTag objects found in the form. Returns nil if -scrapeThreadTagsIntoMangagedObjectContext: has never been called. Returns an empty array if no thread tags are found.
@property (readonly, nullable, copy, nonatomic) NSArray<ThreadTag *> *threadTags;

/// The key for the selected thread tag.
@property (readonly, nullable, copy, nonatomic) NSString *selectedThreadTagKey;

/// An array of secondary AwfulThreadTag objects found in the form. Returns nil if -scrapeThreadTagsIntoMangagedObjectContext: has never been called. Returns an empty array if no thread tags are found.
@property (readonly, nullable, copy, nonatomic) NSArray<ThreadTag *> *secondaryThreadTags;

/// The key for the selected secondary thread tag.
@property (readonly, nullable, copy, nonatomic) NSString *selectedSecondaryThreadTagKey;

/// Returns the thread tag ID associated with an image name, or `nil` if none exists.
- (nullable NSString *)threadTagIDWithImageName:(NSString *)imageName;

/// Returns the secondary thread tag ID associated with an image name, or `nil` if none exists.
- (nullable NSString *)secondaryThreadTagIDWithImageName:(NSString *)imageName;

/**
    A dictionary of parameters necessary (but perhaps insufficient) to submit the form.
 
    Returned as a mutable dictionary under the presumption that the caller will further modify the dictionary in prepration for submission.
 */
- (nullable NSMutableDictionary<NSString *, NSString *> *)recommendedParameters;

/// A dictionary of all parameters in the form.
@property (readonly, nullable, copy, nonatomic) NSDictionary<NSString *, NSString *> *allParameters;

@end

NS_ASSUME_NONNULL_END
