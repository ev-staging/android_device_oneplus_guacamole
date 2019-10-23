/*
   Copyright (C) 2017-2018 The Android Open Source Project

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above
      copyright notice, this list of conditions and the following
      disclaimer in the documentation and/or other materials provided
      with the distribution.
    * Neither the name of The Linux Foundation nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
   WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
   ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
   BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
   BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
   WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
   OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
   IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <android-base/logging.h>
#include <android-base/properties.h>

#include <string>
#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>

#include "property_service.h"
#include "vendor_init.h"

using ::android::init::property_set;

constexpr const char* RO_PROP_SOURCES[] = {
        nullptr, "product.", "product_services.", "odm.", "vendor.", "system.", "bootimage.",
};

constexpr const char* BUILD_DEVICE[] = {
        "OnePlus7",
        "OnePlus7Pro",
        "OnePlus7ProNR",
};

constexpr const char* BUILD_DESCRIPTION[] = {
        "OnePlus7-user 10 QKQ1.190716.003 1910280100 release-keys",
        "OnePlus7Pro-user 10 QKQ1.190716.003 1910280100 release-keys",
        "OnePlus7ProNR-user 10 QKQ1.190716.003 1910280100 release-keys",
};

constexpr const char* BUILD_FINGERPRINT[] = {
        "OnePlus/OnePlus7/OnePlus7:10/QKQ1.190716.003/1910280100:user/release-keys",
        "OnePlus/OnePlus7Pro/OnePlus7Pro:10/QKQ1.190716.003/1910280100:user/release-keys",
        "OnePlus/OnePlus7ProNR/OnePlus7ProNR:10/QKQ1.190716.003/1910280100:user/release-keys",
};

void property_override(char const prop[], char const value[]) {
    prop_info* pi = (prop_info*)__system_property_find(prop);
    if (pi) {
        __system_property_update(pi, value, strlen(value));
    }
}

void load_props(const char* model, int id) {
    const auto ro_prop_override = [](const char* source, const char* prop, const char* value,
                                     bool product) {
        std::string prop_name = "ro.";

        if (product) prop_name += "product.";
        if (source != nullptr) prop_name += source;
        if (!product) prop_name += "build.";
        prop_name += prop;

        property_override(prop_name.c_str(), value);
    };

    for (const auto& source : RO_PROP_SOURCES) {
        ro_prop_override(source, "device", BUILD_DEVICE[id], true);
        ro_prop_override(source, "model", model, true);
        ro_prop_override(source, "fingerprint", BUILD_FINGERPRINT[id],
                         false);
    }
    ro_prop_override(nullptr, "description", BUILD_DESCRIPTION[id], false);
    ro_prop_override(nullptr, "product", "OnePlus7", false);

    // ro.build.fingerprint property has not been set
    property_set("ro.build.fingerprint", BUILD_FINGERPRINT[id]);
}

void vendor_load_properties() {
    int project_name = stoi(android::base::GetProperty("ro.boot.project_name", ""));

    if (project_name == 18827) {
        /* 5G */
        load_props("GM1920", 2);
        return;
    } else  if (project_name == 18831) {
        /* T-Mobile */
        load_props("GM1915", 1);
        return;
    }

    int rf_version = stoi(android::base::GetProperty("ro.boot.rf_version", ""));
    bool is_pro = project_name != 18857;
    switch (rf_version){
        case 1:
            /* China*/
            load_props(is_pro ? "GM1910" : "GM1900", is_pro ? 1 : 0);
            break;
        case 3:
            /* India*/
            load_props(is_pro ? "GM1911" : "GM1901", is_pro ? 1 : 0);
            break;
        case 4:
            /* Europe */
            load_props(is_pro ? "GM1913" : "GM1903", is_pro ? 1 : 0);
            break;
        case 5:
            /* Global / US Unlocked */
            load_props(is_pro ? "GM1917" : "GM1907", is_pro ? 1 : 0);
            break;
        default:
            /* Generic*/
            load_props(is_pro ? "GM1917" : "GM1907", is_pro ? 1 : 0);
            break;
    }
}
