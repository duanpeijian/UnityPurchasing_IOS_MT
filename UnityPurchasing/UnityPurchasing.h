#import <StoreKit/StoreKit.h>

typedef NS_ENUM(NSInteger, IAPDownloadStatus)
{
    IAPDownloadStarted, // Indicates that downloading a hosted content has started
    IAPDownloadInProgress, // Indicates that a hosted content is currently being downloaded
    IAPDownloadFailed,  // Indicates that downloading a hosted content failed
    IAPDownloadSucceeded, // Indicates that a hosted content was successfully downloaded
    IAPDownloadCanceled
};

typedef void (*SKDownloadCallback)(int status, const char* payload, float progress);

// Callback to Unity identifying the subject, JSON message body and optional app receipt.
// Note that App Receipts are sent separately to the JSON body for performance reasons.
typedef void (*UnityPurchasingCallback)(const char* subject, const char* payload, const char* receipt, const char* transactionId);

@interface ProductDefinition : NSObject
    
@property (nonatomic, strong) NSString *id;
@property (nonatomic, strong) NSString *storeSpecificId;
@property (nonatomic, strong) NSString *type;
@end

@interface ReceiptRefresher : NSObject <SKRequestDelegate>

@property (nonatomic, strong) void (^callback)(BOOL);

@end

@interface UnityPurchasing : NSObject <SKProductsRequestDelegate, SKPaymentTransactionObserver> {
    SKDownloadCallback downloadCallback;
    UnityPurchasingCallback messageCallback;
    NSMutableDictionary* validProducts;
    NSSet* productIds;
    SKProductsRequest *request;
    NSMutableDictionary *pendingTransactions;
}

+ (NSArray*) deserializeProductDefs:(NSString*)json;
+ (ProductDefinition*) deserializeProductDef:(NSString*)json;
+ (NSString*) serializeProductMetadata:(NSArray*)products;

-(void) restorePurchases;
-(NSString*) getAppReceipt;
-(void) addTransactionObserver;
@property (nonatomic, strong) ReceiptRefresher* receiptRefresher;
@property (nonatomic, strong) SKReceiptRefreshRequest* refreshRequest;

@end
