LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos/audio/include)

LOCAL_MODULE := MyGame_shared

LOCAL_MODULE_FILENAME := libMyGame

LOCAL_SRC_FILES := $(LOCAL_PATH)/hellocpp/main.cpp \
                   $(LOCAL_PATH)/../../../Classes/AppDelegate.cpp \
				   $(LOCAL_PATH)/../../../Classes/BossController.cpp \
				   $(LOCAL_PATH)/../../../Classes/Controls.cpp \
				   $(LOCAL_PATH)/../../../Classes/DamageText.cpp \
				   $(LOCAL_PATH)/../../../Classes/Enemy.cpp \
				   $(LOCAL_PATH)/../../../Classes/Flame.cpp \
				   $(LOCAL_PATH)/../../../Classes/GameController.cpp \
				   $(LOCAL_PATH)/../../../Classes/GameObject.cpp \
				   $(LOCAL_PATH)/../../../Classes/GameObjectManager.cpp \
				   $(LOCAL_PATH)/../../../Classes/GravityBullet.cpp \
                   $(LOCAL_PATH)/../../../Classes/HelloWorldScene.cpp \
                   $(LOCAL_PATH)/../../../Classes/HudLayer.cpp \
                   $(LOCAL_PATH)/../../../Classes/InventoryManager.cpp \
                   $(LOCAL_PATH)/../../../Classes/JoyStick.cpp \
				   $(LOCAL_PATH)/../../../Classes/LoadScene.cpp \
				   $(LOCAL_PATH)/../../../Classes/Pickup.cpp \
				   $(LOCAL_PATH)/../../../Classes/Player.cpp \
				   $(LOCAL_PATH)/../../../Classes/Projectile.cpp \
				   $(LOCAL_PATH)/../../../Classes/SceneManager.cpp \
				   $(LOCAL_PATH)/../../../Classes/Shell.cpp \
				   $(LOCAL_PATH)/../../../Classes/Swarmer.cpp \
				   $(LOCAL_PATH)/../../../Classes/UpgradeStone.cpp \
				   $(LOCAL_PATH)/../../../Classes/Vortex.cpp \
				   $(LOCAL_PATH)/../../../Classes/Weapon.cpp \
				   $(LOCAL_PATH)/../../../Classes/WeaponGenerator.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../Classes

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
