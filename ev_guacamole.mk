#
# Copyright 2015 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

# Inherit from the common Open Source product configuration
$(call inherit-product, $(SRC_TARGET_DIR)/product/core_64_bit.mk)
$(call inherit-product, $(SRC_TARGET_DIR)/product/aosp_base_telephony.mk)
$(call inherit-product, $(SRC_TARGET_DIR)/product/product_launched_with_p.mk)

PRODUCT_NAME := ev_guacamole
PRODUCT_DEVICE := guacamole
PRODUCT_BRAND := OnePlus
PRODUCT_MODEL := guacamole
PRODUCT_MANUFACTURER := OnePlus
PRODUCT_RESTRICT_VENDOR_FILES := false

$(call inherit-product, device/oneplus/guacamole/device.mk)

# Inherit some common evervolv stuff.
$(call inherit-product, $(SRC_EVERVOLV_DIR)/config/common_full_phone.mk)

# Bootanimation
BOOT_ANIMATION_SIZE := 1080p

# Build info
BUILD_FINGERPRINT := "OnePlus/OnePlus7Pro/OnePlus7Pro:9/PKQ1.190110.001/1906032330:user/release-keys"

PRODUCT_GMS_CLIENTID_BASE := android-oneplus

PRODUCT_CODENAME := Expletus
PRODUCT_MOTD :="\n\n\n--------------------MESSAGE---------------------\nThank you for choosing Evervolv for your OnePlus 7 Pro\nPlease visit us at \#evervolv on irc.freenode.net\nFollow @preludedrew for the latest Evervolv updates\nGet the latest rom at evervolv.com\n------------------------------------------------\n"

