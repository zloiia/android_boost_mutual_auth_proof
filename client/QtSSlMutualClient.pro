TEMPLATE = app

QT += qml quick
CONFIG += c++11

SOURCES += main.cpp

RESOURCES += qml.qrc

INCLUDEPATH += ../libs/OpenSSL-for-Android-Prebuilt/openssl-1.0.2/include
LIBS += -L../libs/OpenSSL-for-Android-Prebuilt/openssl-1.0.2/armeabi-v7a/lib -lcrypto -lssl

LIBS += -L../libs/Boost-for-Android-Prebuilt/boost_1_53_0/armeabi-v7a/lib -lboost_system-gcc-mt-1_53
INCLUDEPATH += ../libs/Boost-for-Android-Prebuilt/boost_1_53_0/include

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

contains(ANDROID_TARGET_ARCH,armeabi-v7a) {
    ANDROID_EXTRA_LIBS = \
        ../libs/OpenSSL-for-Android-Prebuilt/openssl-1.0.2/armeabi-v7a/lib/libcrypto.so \
        ../libs/OpenSSL-for-Android-Prebuilt/openssl-1.0.2/armeabi-v7a/lib/libssl.so \
        ../libs/OpenSSL-for-Android-Prebuilt/openssl-1.0.2/armeabi-v7a/lib/libcrypto_1_0_0.so \
        ../libs/OpenSSL-for-Android-Prebuilt/openssl-1.0.2/armeabi-v7a/lib/libssl_1_0_0.so
}

#DISTFILES += \
#    certs/AndroidManifest.xml \
#    certs/gradle/wrapper/gradle-wrapper.jar \
#    certs/gradlew \
#    certs/res/values/libs.xml \
#    certs/build.gradle \
#    certs/gradle/wrapper/gradle-wrapper.properties \
#    certs/gradlew.bat

#ANDROID_PACKAGE_SOURCE_DIR = $$PWD/certs

