#include <mqtt_topic_provider.h>


namespace mqtt
{
void MqttTopicProvider::ComposeMqttTopic(std::string &buffer, const char *topic_prefix, const char *device_class)
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

void MqttTopicProvider::ComposeMqttTopic(std::string &buffer, const char *topic_prefix, const char *device_class, uint_fast8_t device_class_uid)
{
    ComposeMqttTopic(buffer, topic_prefix, device_class);
    
    // assert(!!device_class);
    buffer += '/';
    // assert(device_class_uid < 10);
    buffer += static_cast<const char>(device_class_uid + '0');
}    
}
