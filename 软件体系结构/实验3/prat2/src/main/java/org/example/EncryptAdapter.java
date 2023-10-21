package org.example;

public class EncryptAdapter implements EncryptModel{
    private EncryptAdaptee encryptAdaptee;

    public EncryptAdapter(EncryptAdaptee encryptAdaptee) {
        this.encryptAdaptee = new EncryptAdaptee();
    }

    @Override
    public String userEncrypt(String str) {
        return encryptAdaptee.MD5Encrypt(str);
    }


}
