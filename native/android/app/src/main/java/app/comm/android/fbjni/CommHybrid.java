package app.comm.android.fbjni;

import android.content.Context;
import com.facebook.react.bridge.ReactContext;
import com.facebook.react.turbomodule.core.CallInvokerHolderImpl;
import java.util.HashMap;

public class CommHybrid {

  private CommHybrid() {
  }

  public static void initHybrid(ReactContext context) {
    CallInvokerHolderImpl holder =
        (CallInvokerHolderImpl)context.getCatalystInstance()
            .getJSCallInvokerHolder();
    long contextPointer = context.getJavaScriptContextHolder().get();

    // additional parameters
    String sqliteFilePath = context.getDatabasePath("comm.sqlite").toString();
    String encryptionKey = CommSecureStore.get("encryptionKey");

    if (encryptionKey == null) {
      encryptionKey = PlatformSpecificTools.generateSQLCipherEncryptionKey();
      CommSecureStore.set("encryptionKey", encryptionKey);
    }

    HashMap<String, Object> additionalParameters =
        new HashMap<String, Object>();
    additionalParameters.put("sqliteFilePath", sqliteFilePath);
    additionalParameters.put("encryptionKey", encryptionKey);

    new CommHybrid().initHybrid(contextPointer, holder, additionalParameters);
  }

  public native void initHybrid(
      long jsContextNativePointer,
      CallInvokerHolderImpl jsCallInvokerHolder,
      HashMap<String, Object> additionalParameters);
}
