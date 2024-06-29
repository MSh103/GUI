#ifndef MessageBoxForMACOS_h
#define MessageBoxForMACOS_h

#include <CoreFoundation/CoreFoundation.h>

#define MB_OK               0x01
#define MB_OKCANCEL         0x02
#define MB_YESNO            0x04
#define MB_YESNOCANCEL      0x08
#define MB_ICONINFORMATION  0x10
#define MB_ICONERROR        0x20
#define MB_ICONQUESTION     0x40
#define MB_ICONWARNING      0x80

namespace Gui
{
class MessageBoxM {
private:
    int choice;

public:
    MessageBoxM(const char* header, const char* message, unsigned long message_type) {
        CFStringRef header_ref = CFStringCreateWithCString(NULL, header, kCFStringEncodingUTF8);
        CFStringRef message_ref = CFStringCreateWithCString(NULL, message, kCFStringEncodingUTF8);

        CFURLRef iconURL = NULL;
        CFStringRef defaultButton_ref = NULL;
        CFStringRef altButton_ref = NULL;
        CFStringRef otherButton_ref = NULL;


        if (message_type & (MB_OK)) {
            defaultButton_ref = CFStringCreateWithCString(NULL, "OK", kCFStringEncodingUTF8);
        } else if (message_type & (MB_YESNO)) {
            defaultButton_ref = CFStringCreateWithCString(NULL, "Yes", kCFStringEncodingUTF8);
            altButton_ref = CFStringCreateWithCString(NULL, "No", kCFStringEncodingUTF8);
        } else if (message_type & (MB_YESNOCANCEL)) {
            defaultButton_ref = CFStringCreateWithCString(NULL, "Yes", kCFStringEncodingUTF8);
            altButton_ref = CFStringCreateWithCString(NULL, "No", kCFStringEncodingUTF8);
            otherButton_ref = CFStringCreateWithCString(NULL, "Cancel", kCFStringEncodingUTF8);
        } else if (message_type & (MB_OKCANCEL)) {
            defaultButton_ref = CFStringCreateWithCString(NULL, "OK", kCFStringEncodingUTF8);
            altButton_ref = CFStringCreateWithCString(NULL, "Cancel", kCFStringEncodingUTF8);
        }

        if (message_type & MB_ICONINFORMATION) {
            const char* iconPath = "/Users/msh/dev/VISUAL_STUDIO_CODE_REPOS/Gui Development/GUI/res/icons/info.png";
            CFStringRef path_ref = CFStringCreateWithCString(NULL, iconPath, kCFStringEncodingUTF8);
            iconURL = CFURLCreateWithFileSystemPath(NULL, path_ref, kCFURLPOSIXPathStyle, false);
            CFRelease(path_ref);
        } else if (message_type & MB_ICONERROR) {
            const char* iconPath = "/Users/msh/dev/VISUAL_STUDIO_CODE_REPOS/Gui Development/GUI/res/icons/error.png";
            CFStringRef path_ref = CFStringCreateWithCString(NULL, iconPath, kCFStringEncodingUTF8);
            iconURL = CFURLCreateWithFileSystemPath(NULL, path_ref, kCFURLPOSIXPathStyle, false);
            CFRelease(path_ref);
        } else if (message_type & MB_ICONQUESTION) {
            const char* iconPath = "/Users/msh/dev/VISUAL_STUDIO_CODE_REPOS/Gui Development/GUI/res/icons/question.png";
            CFStringRef path_ref = CFStringCreateWithCString(NULL, iconPath, kCFStringEncodingUTF8);
            iconURL = CFURLCreateWithFileSystemPath(NULL, path_ref, kCFURLPOSIXPathStyle, false);
            CFRelease(path_ref);
        } else if (message_type & MB_ICONWARNING) {
            const char* iconPath = "/Users/msh/dev/VISUAL_STUDIO_CODE_REPOS/Gui Development/GUI/res/icons/warning.png";
            CFStringRef path_ref = CFStringCreateWithCString(NULL, iconPath, kCFStringEncodingUTF8);
            iconURL = CFURLCreateWithFileSystemPath(NULL, path_ref, kCFURLPOSIXPathStyle, false);
            CFRelease(path_ref);
        }

        CFOptionFlags result = 0;  // Result code from the message box

        SInt32 err = CFUserNotificationDisplayAlert(
            0, // No timeout
            kCFUserNotificationNoteAlertLevel,
            iconURL, // Icon URL
            NULL, // Sound URL
            NULL, // Localization URL
            header_ref, // Header text
            message_ref, // Message text
            defaultButton_ref, // Default button text
            altButton_ref, // Alternate button text
            otherButton_ref, // Other button text
            &result // Response flags
        );

        if (err == kCFUserNotificationDefaultResponse || err == kCFUserNotificationAlternateResponse) {
            if (message_type & (MB_OKCANCEL)) {
                choice = (result == kCFUserNotificationDefaultResponse) ? 1 : 2;
            } else if (message_type & (MB_YESNOCANCEL)) {
                if (result == kCFUserNotificationDefaultResponse)
                    choice = 1;
                else if (result == kCFUserNotificationAlternateResponse)
                    choice = 2;
                else
                    choice = 3;
            } else if (message_type & (MB_YESNO)) {
                choice = (result == kCFUserNotificationDefaultResponse) ? 1 : 2;
            }
        }

        // Clean up the strings and URL
        CFRelease(header_ref);
        CFRelease(message_ref);
        if (iconURL) CFRelease(iconURL);
        if (defaultButton_ref) CFRelease(defaultButton_ref);
        if (altButton_ref) CFRelease(altButton_ref);
        if (otherButton_ref) CFRelease(otherButton_ref);
    }

    int getChoice() const { return this->choice; }
};
}

#endif /* MessageBox_h */
