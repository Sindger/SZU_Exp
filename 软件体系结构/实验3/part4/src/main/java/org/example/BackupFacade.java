package org.example;

public class BackupFacade {
    private SMSManager sms;
    private SongsManager song;
    private ContactManager contact;
    private PhotoManager photo;
    public BackupFacade() {
        sms = new SMSManager();
        song = new SongsManager();
        contact = new ContactManager();
        photo = new PhotoManager();
    }
    public void oneKeyBackup() {
        sms.oneKeyBackup();
        song.oneKeyBackup();
        contact.oneKeyBackup();
        photo.oneKeyBackup();
    }
}
