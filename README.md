# DM2335PGE_Assignment01

Please include your own cocos2d folder which we generated as it is too large to upload to github.


# How to compile a Release:
Open a command prompt and navigate to your project directory.
Then run: cocos deploy -p win32 -m release



# How to compile on Android-Studio:
Rebuild a new cocos2dx project.  Make sure the naming of directories leading towards the project folder is not a total of more than 255 Characters.

Copy your existing Classes folder and replace it with the newly created project.

As I have already configured the current proj.android-studio folder, just copy and replace it with the newly created project as well.

Next, open Android Studio software and open the proj.android-studio folder in the newly created project and build.  Currently, you are unable to debug and run using the emulator, you can only do this using your own android phone, it's the backend limitations of the emulator, nothing can be done at the moment unless I touch the source codes.

If you want to setup your own, the files required to configure are:
\proj.android-studio\app\jni\Android.mk
\proj.android-studio\app\jni\Application.mk
\proj.android-studio\gradle\wrapper\gradle-wrapper.properties
\proj.android-studio\app\build.gradle
\proj.android-studio\build.gradle

Things to note when configuring are:
- APP_ABI
- Inclusion of cpp files in Android.mk
- Gradle Build version
- Gradle Plugin version (Distribution)
- Gradle Build & Gradle Plugin versions are not the same, they need to be compatible with each other.
- Build Tool version