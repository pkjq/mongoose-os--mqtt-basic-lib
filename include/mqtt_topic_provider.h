/*
 * Copyright (c) 2018-2019 pkjq
 * All rights reserved
 *
 * Licensed under the Apache License, Version 2.0 (the ""License"");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an ""AS IS"" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef G46BE9372_5397_4F22_A9F5_A84C9DE4AF42
#define G46BE9372_5397_4F22_A9F5_A84C9DE4AF42


#include <mgos_config.h>
#include <string>


namespace mqtt
{
class MqttTopicProvider
{
public:
    MqttTopicProvider() = default;
    MqttTopicProvider(MqttTopicProvider&&) = default;
    MqttTopicProvider(const MqttTopicProvider&) = delete;

public:
    inline const std::string& GetTopic4Command(const char *device_class) const
    {
        ComposeMqttTopic(buffer, mgos_sys_config_get_app_mqtt()->command_topic_prefix, device_class);
        return buffer;
    }
    
    inline const std::string& GetTopic4Command(const char *device_class, uint_fast8_t device_class_uid) const
    {
        ComposeMqttTopic(buffer, mgos_sys_config_get_app_mqtt()->command_topic_prefix, device_class, device_class_uid);
        return buffer;
    }

    inline const std::string& GetTopic4Telemetry(const char *device_class) const
    {
        ComposeMqttTopic(buffer, mgos_sys_config_get_app_mqtt()->telemetry_topic_prefix, device_class);
        return buffer;
    }

    inline const std::string& GetTopic4State(const char *device_class) const
    {
        ComposeMqttTopic(buffer, mgos_sys_config_get_app_mqtt()->state_topic_prefix, device_class);
        return buffer;
    }

    inline const std::string& GetTopic4Announce(const char *device_class) const
    {
        ComposeMqttTopic(buffer, mgos_sys_config_get_app_mqtt()->announce_topic_prefix, device_class);
        return buffer;
    }

    inline const std::string& GetTopic4OnlineStatus() const
    {
        ComposeMqttTopic(buffer, mgos_sys_config_get_app_mqtt()->online_topic_prefix, nullptr);
        return buffer;
    }

    const std::string& GetServerOnlineStatusTopic() const
    {
        buffer.clear();
        buffer = mgos_sys_config_get_app_mqtt()->online_topic_prefix;

        buffer += '/';
        buffer += mgos_sys_config_get_app_mqtt()->server_uid_for_online_topic;

        return buffer;
    }    

private:
    static void ComposeMqttTopic(std::string &buffer, const char *topic_prefix, const char *device_class)
    {
        buffer.clear();
        buffer = topic_prefix;

        buffer += '/';
        buffer += mgos_sys_config_get_device_id();

        if (device_class)
        {
            buffer += '/';
            buffer += device_class;
        }
    }
    
    static void ComposeMqttTopic(std::string &buffer, const char *topic_prefix, const char *device_class, uint_fast8_t device_class_uid)
    {
        ComposeMqttTopic(buffer, topic_prefix, device_class);
        
        // assert(!!device_class);
        buffer += '/';
        buffer += std::to_string(device_class_uid);
    }    

private:
    mutable std::string buffer;
};
}


#endif//G46BE9372_5397_4F22_A9F5_A84C9DE4AF42
