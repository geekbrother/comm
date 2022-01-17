package app.comm.android.fbjni;

import android.util.Log;
import java.nio.charset.StandardCharsets;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;

public class PlatformSpecificTools {
  static SecureRandom secureRandom = new SecureRandom();

  public static byte[] generateSecureRandomBytes(int size) {
    byte[] buffer = new byte[size];
    secureRandom.nextBytes(buffer);
    return buffer;
  }

  public static String generateSQLCipherEncryptionKey() {
    byte[] randomBytes = PlatformSpecificTools.generateSecureRandomBytes(32);
    String randomHexString = "";
    for (byte b : randomBytes) {
      randomHexString += String.format("%02X", b);
    }
    return randomHexString;
  }
}
